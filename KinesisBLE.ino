#include <Arduino.h>
#include <Wire.h>
#include <SPI.h> 
#include "MCP23S17.h"

#include "config.h"
#include "keycodes.h"
#include "keymap.h"
#include "bluetooth.h"
#include "battery.h"
#include "button.h"
#include "Adafruit_MCP23017.h"

/**
 * Keyboard Matrix
 */
#define ROWS 15
#define COLS 7

/**
 * Only debouncing once because each iteration already 
 * takes roughly 8ms due to nRF52 max 
 * i2C speed of 400khz.
 */
#define DEBOUNCING_DELAY 2

/**
 * Power Consumption
 */
#define MINS_BEFORE_SHUTDOWN 15
#define MINS_SHOW_BATTERY_LED 3

#define USB_BAUDRATE 115200
#define USB_FULL_MIN_MV 4978  // Used to determine if battery is charging.

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

/**
 * Battery LED on time
 */
int   batteryOnTime = MINS_SHOW_BATTERY_LED*60*1000;                       

/**
 * Timestamp of last key press activity. Used to
 * check if keyboard can go into deep-sleep.
 */
int lastKeyActivityTimer = 0;
int idleBeforeSleepTime = MINS_BEFORE_SHUTDOWN*60*1000;   

MCP mcp(0, SPI_SS_PIN); 

void setup(void) {

  mcp.begin();

//  Serial.begin(USB_BAUDRATE);

  init_bluetooth();

  for (uint8_t row = 0; row < ROWS; row++) {
    mcp.pinMode(row_pins[row], OUTPUT);
    mcp.digitalWrite(row_pins[row], HIGH);
  }
  
  for (uint8_t col = 0; col < COLS; col++) {
    pinMode(col_pins[col], INPUT_PULLUP);
    digitalWrite(col_pins[col], HIGH);
  }

  pinMode(LED_CAPS_PIN, OUTPUT);
  pinMode(LED_NUM_PIN, OUTPUT);
  pinMode(LED_SCR_PIN, OUTPUT);
  pinMode(LED_KEY_PIN, OUTPUT);
   
  showBatteryLevel();  

  NRF_UARTE0->ENABLE = 0;  //disable UART
  NRF_TWIM1 ->ENABLE = 0; //disable TWI Master
  NRF_TWIS1 ->ENABLE = 0; //disable TWI Slave
  NRF_NFCT->TASKS_DISABLE = 1; //disable NFC, confirm this is the right way

  buttonColor(BLUE);

}

bool charging = false;

void loop(void) {

    
  if(usbConnected()){
    if(usbVoltage() > USB_FULL_MIN_MV) {
//      buttonColor(GREEN);                     // FULL
      setAllBatteryLed(HIGH);
    } else {
//      buttonColor(ORANGE);                    // CHARGING
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

  /**
   * Update States
   * If debouncing delay is up and the states are still the same, 
   * then go ahead and store the new states to be processed.
   */
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

  /**
   * Compare Row States
   * Check to see if anything has changed and subsequently handle
   * the change.
   */
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
       * Examines each bit to see if the state is a 0 or a 1. Shift
       * right by column index to get current column and & 1 to
       * ignore all bits to the left.
       */
      state_t curr = (curr_states[row] >> col) & 1;       
      state_t prev = (prev_states[row] >> col) & 1;
      
      if (curr != prev) {
        
        char* command = handle_keychange(row, col, curr);

        /**
         * If we pressed a key to shutdown keyboard, put
         * the keyboard to sleep.
         */
        if(command == "shutdown") {
          delay(250); // Let things settle on key-up, to prevent immediately waking up.
          keyboardShutdown();
        }
        
        prev_states[row] ^= (uint16_t)1 << col;
        lastKeyActivityTimer = millis();                    // Update last activity timer to prevent sleep
        goto END_OF_LOOP;                                   // Handle 1 key change at a time
      }
    }
    
  }

  END_OF_LOOP:;

  if( (millis() - lastKeyActivityTimer) > idleBeforeSleepTime) {
    keyboardShutdown();
  }

  /**
   * Bug fix: Disable FPU manually to enable
   * sleep after running into
   * a float.
   */
   #if (__FPU_USED == 1)
  __set_FPSCR(__get_FPSCR() & ~(0x0000009F)); 
  (void) __get_FPSCR();
  NVIC_ClearPendingIRQ(FPU_IRQn);
  #endif
  uint32_t err_code = sd_app_evt_wait();

  delay(7);
 
}

/**
 * Deep-sleep (max power saving)
 * Enter this mode if keyboard has been idle for
 * some time.
 */
void keyboardShutdown() {

  buttonColor(OFF);       // Power button LED
  setAllBatteryLed(LOW);    // Battery indicator LEDs
  
  for (uint8_t row = 0; row < ROWS; row++) {
    mcp.digitalWrite(row_pins[row], LOW);    
  }
  
  for (uint8_t col = 0; col < COLS; col++) {
    NRF_GPIO->PIN_CNF[col_pins[col]] |= ((uint32_t) GPIO_PIN_CNF_SENSE_Low << GPIO_PIN_CNF_SENSE_Pos);
  }

  uint8_t sd_en;
  (void) sd_softdevice_is_enabled(&sd_en);

  // Enter System OFF state
  if ( sd_en )
  {
    sd_power_system_off();
  }else
  {
    NRF_POWER->SYSTEMOFF = 1;
  }
}

