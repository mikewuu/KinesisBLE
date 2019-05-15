#include <Arduino.h>
#include <SPI.h>

#include "battery.h"
#include "bluetooth.h"
#include "button.h"
#include "config.h"
#include "keycodes.h"
#include "keymap.h"
#include "MCP23S17.h"
#include "rest_timer.h"

uint8_t col_pins[COLS] = COL_PINS;
uint8_t row_pins[ROWS] = ROW_PINS;

uint8_t prev_states[ROWS] = { 0 };
uint8_t curr_states[ROWS] = { 0 };
uint8_t temp_states[ROWS] = { 0 };

uint8_t debouncing = DEBOUNCING_DELAY;

inline
state_t get_state(uint8_t row, uint8_t col) {
  return (curr_states[row] >> (col)) & 1;
}


int batteryOnTime = MINS_SHOW_BATTERY_LED*60*1000;                       
int lastKeypressTimestamp = 0;
int inactivityTimeout = MINS_BEFORE_SHUTDOWN*60*1000;   

MCP mcp(0, SPI_SS_PIN); 

bool charging = false;

void setup(void) {

    mcp.begin();

    #ifdef DEBUG
        Serial.begin(USB_BAUDRATE);
    #endif

    init_bluetooth();

    for (uint8_t row = 0; row < ROWS; row++) {
        mcp.pinMode(row_pins[row], OUTPUT);
        mcp.digitalWrite(row_pins[row], HIGH);
    }
  
    for (uint8_t col = 0; col < COLS; col++) {
        pinMode(col_pins[col], INPUT_PULLUP);
        digitalWrite(col_pins[col], HIGH);
    }

    /**
     * Initialize Battery Indicator LED(s)
     */

  initializeBatteryLedPins();
  showBatteryLevel();
  disableExtraFeatures();
  buttonColor(BLUE);
    
}

void initializeBatteryLedPins() {
  pinMode(LED_CAPS_PIN, OUTPUT);
  pinMode(LED_NUM_PIN, OUTPUT);
  pinMode(LED_SCR_PIN, OUTPUT);
  pinMode(LED_KEY_PIN, OUTPUT);
}

void disableExtraFeatures() {
  #ifndef DEBUG
    NRF_UARTE0->ENABLE = 0; // disable UART
  #endif
  
  NRF_TWIM1 ->ENABLE = 0; //disable TWI Master
  NRF_TWIS1 ->ENABLE = 0; //disable TWI Slave
  NRF_NFCT->TASKS_DISABLE = 1; //disable NFC, confirm this is the right way  
}

void loop(void) {

    // Priorities REST TIMER LED Control
    if(!restTimerUsingLeds) { 
        process_battery_leds();
    }

    scan_kb_matrix();

    handle_debouncing();

    check_row_states();
    
    #ifdef REST_TIMER
        process_rest_timer(lastKeypressTimestamp);
    #endif

    if(shouldEnterDeepSleep(lastKeypressTimestamp)){ 
        keyboardShutdown();
    }

    disable_fpu();

    /**
     * Power Savings Sleep (wait for event, not deep-sleep)
     * 
     * This is what allows for lower power consumption. As the loop takes 1ms to run, if we're 
     * sleeping for 7ms, we're theoretically only using 12.5% of the power we would require
     * if we were to run the loop without the delay.
     */
    delay(2);
 
} // END loop()

void scan_kb_matrix() {
    for (uint8_t row = 0; row < ROWS; row++) {
    
      uint8_t row_read = 0;
    
      /**
       * Pull current row to low as columns are set to INPUT_PULLUP.
       * The alternative would be to wire pulldown resistors.
       */
      mcp.digitalWrite(row_pins[row], LOW);                  
    
      delayMicroseconds(30);
    
      /**
       * Loop through each column on each row to check to see if a key
       * was pressed. The column pin will read LOW too if a key 
       * switch is down.
       */
      for (uint8_t col = 0; col < COLS; col++) {            
       
          if (digitalRead(col_pins[col]) == LOW) {            
        
            /**
             * Turn first bit into 1 and shift left by column number.
             * If the 5th and 7th column of the row was pressed, 
             * row_read for the row would be 101000.
             */         
              row_read |= 1 << col;
      
          }
      }
    
      /**
       * Set Debouncing Delay
       * 
       * Every new row_read needs to be the same (stored in temp_states)
       * for DEBOUNCING_DELAY amount of time. ie. Prevent the row
       * states from rapidly changing.
       */
      if (temp_states[row] != row_read) {
          temp_states[row] = row_read;          
          debouncing = DEBOUNCING_DELAY;        
      }
    
       mcp.digitalWrite(row_pins[row], HIGH);
    
    }
}

/**
 * Handle Debouncing
 * 
 * If debouncing delay is up and the states are still the same, 
 * then go ahead and accept the new states to be processed.
 */
void handle_debouncing() {
    if (debouncing) {
      if (--debouncing) {
          delay(1);          
      } else {
          for (uint8_t row = 0; row < ROWS; row++) {
              prev_states[row] = curr_states[row];
              curr_states[row] = temp_states[row];
          }
      }
    }
}

/**
 * Set Keyboard LED(s) according to charge status.
 */
void process_battery_leds() {
      if(usbConnected()){
          if(usbVoltage() > USB_FULL_MIN_MV) {
              setAllBatteryLed(HIGH);
          } else {
              batteryChargingAnimation();
              charging = true;
          }
      } else {
          // Set battery LED to what it would be without charging animation
          if (charging) {
              showBatteryLevel();
              charging = false;
          }
            // Turn off battery indicator LEDs after set time
            if (batteryLedOn && ((millis() - batteryLedTimer) > batteryOnTime)) {
                setAllBatteryLed(LOW);
            }
      }  
} // END process_battery_leds()

/**
 * Compare Row States
 * 
 * Check to see if anything has changed and subsequently handle
 * the change.
 */
void check_row_states() {
    for (uint8_t row = 0; row < ROWS; row++) {
    
      if (curr_states[row] == prev_states[row]) {
          continue;
      }
    
    for (uint8_t col = 0; col < COLS; col++) {
      
        // shift right to look at current column, then bitwise & 1 which
        // ignores columns to the left and checks to see if state is a
        // 1 or 0.
    
        /**
         * Check Each Column
         * 
         * Examines each bit to see if the state is a 0 or a 1. Shift
         * right by column index to get current column and & 1 to
         * ignore all bits to the left.
         */
        state_t curr = (curr_states[row] >> col) & 1;       
        state_t prev = (prev_states[row] >> col) & 1;
        
        if (curr != prev) {
          
            int command = handle_keychange(row, col, curr);

            handle_command(command);
           
        
            prev_states[row] ^= (uint16_t)1 << col;
            lastKeypressTimestamp = millis();    // Update last activity timer to prevent sleep
            goto END_OF_LOOP;    // Handle 1 key change at a time
        }
    }
    
    }
    
    END_OF_LOOP:;
}

/**
 * Check if keyboard has been inactive long enough to be
 * put into deep-sleep mode.
 */
bool shouldEnterDeepSleep(int lastKeypressTimestamp){
  return millis() - lastKeypressTimestamp > inactivityTimeout;
}

/**
 * Deep-sleep (max power saving)
 * 
 * Once entered, the keyboard will need to 'wake-up' on a keypress. This might
 * take a few seconds, so we only enter this mode after some idle time or
 * manually. Consumes about 150uA.
 */
void keyboardShutdown() {

  /**
   * Turn off LED(s)
   */
  buttonColor(OFF);       
  setAllBatteryLed(LOW);   

  /**
   * Switch all the row pins to LOW
   */
  for (uint8_t row = 0; row < ROWS; row++) {
    mcp.digitalWrite(row_pins[row], LOW);    
  }

  /**
   * Set up column pins to wake-up on LOW.
   */
  for (uint8_t col = 0; col < COLS; col++) {
    NRF_GPIO->PIN_CNF[col_pins[col]] |= ((uint32_t) GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
  }

  uint8_t sd_en;
  (void) sd_softdevice_is_enabled(&sd_en);

  /**
   * Enter system-off state.
   */
  if ( sd_en )
  {
    sd_power_system_off();
  }else
  {
    NRF_POWER->SYSTEMOFF = 1;
  }
}

/** 
 *  FPU prevents the nRF52 from going to sleep. We need
 *  to disable it manually after it encountering a 
 *  FLOAT to allow sleep on delay().
 */
void disable_fpu() {
    #if (__FPU_USED == 1)
        __set_FPSCR(__get_FPSCR() & ~(0x0000009F)); 
        (void) __get_FPSCR();
        NVIC_ClearPendingIRQ(FPU_IRQn);
    #endif
    uint32_t err_code = sd_app_evt_wait();  
}

/**
 *  Handle custom commands, certain key combinations / presses
 *  can send commands and here is where you'd define how to 
 *  handle them.
 */
void handle_command(int command) {
    switch (command) {
        case COMMAND_SHUTDOWN: {
            delay(1000);
            keyboardShutdown();
            break;
        }
        case COMMAND_START_BREAK: {
            start_break();
            break;  
        }
    }
}

