#include <Arduino.h>
#include <Wire.h>

#include "config.h"
#include "keycodes.h"
#include "keymap.h"
#include "bluetooth.h"
#include "battery.h"
#include "button.h"
#include "Adafruit_MCP23017.h"

#define ROWS 15
#define COLS 7

/**
 * Only debouncing once because each iteration already 
 * takes roughly 8ms due to nRF52 max 
 * i2C speed of 400khz.
 */
#define DEBOUNCING_DELAY 2

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

const int baudrate = 115200;

Adafruit_MCP23017 mcp;

/**
 * Battery LED on time
 */
bool  batteryLedOn = false; 
int   batteryLedTimer = 0;
int   batteryOnTime = 300000;                       // Keep battery LEDs on for 5 minutes each time.

/**
 * Timestamp of last key press activity. Used to
 * check if keyboard can go into deep-sleep.
 */
int lastKeyActivityTimer = 0;
int idleBeforeSleepTime = 900000;                   // 15 minutes

bool  chargingAnimationOn = false;
int   chargingAnimationLastToggle = 0;

void setup(void) {

  mcp.begin();
  Wire.setClock(400000L);                           // Manually set high speed i2c

  Serial.begin(baudrate);
  
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
}

bool charging = false;

void loop(void) {
    
    int UsbMv = readUSB();

    // USB not connected
    if(UsbMv < 2000) {

      buttonColor(BLUE);

      // Set battery LED to what it would be without charging animation
      if (charging) {
        showBatteryLevel();
        charging = false;
      }

      // Turn off battery indicator LEDs after set time
      if (batteryLedOn && ((millis() - batteryLedTimer) > batteryOnTime)) {
        setAllBatteryLed(LOW);
      }
      
    } else {
      
      if(UsbMv >= 5000) {
        buttonColor(GREEN);                     // FULL
        setAllBatteryLed(HIGH);
      } else {
        buttonColor(ORANGE);                    // CHARGING
        batteryChargingAnimation();
        charging = true;
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
        handle_keychange(row, col, curr);
        prev_states[row] ^= (uint16_t)1 << col;
        lastKeyActivityTimer = millis();                    // Update last activity timer to prevent sleep
        goto END_OF_LOOP;                                   // Handle 1 key change at a time
      }
    }
    
  }

  END_OF_LOOP:;

  if( (millis() - lastKeyActivityTimer) > idleBeforeSleepTime) {
    keyboardShutdown();
  } else {
    waitForEvent();
  }
 
}

/**
 * Read battery and update Kinesis LEDs
 * 
 */
void showBatteryLevel() {
  
   uint8_t battery = batteryPercentage();
   
   if(battery > 75) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, HIGH);
    digitalWrite(LED_KEY_PIN, HIGH);
   } else if (battery > 50) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, HIGH);
    digitalWrite(LED_KEY_PIN, LOW);
   } else if (battery > 25) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   } else {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, LOW);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   }
   batteryLedOn = true;
   batteryLedTimer = millis();
}

/**
 * Turns off all battery level
 * indicator LEDs.
 */
void setAllBatteryLed(bool state) {
    digitalWrite(LED_CAPS_PIN, state);
    digitalWrite(LED_NUM_PIN, state);
    digitalWrite(LED_SCR_PIN, state);
    digitalWrite(LED_KEY_PIN, state);
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

void batteryChargingAnimation() {
   uint8_t battery = batteryPercentage();

   int now = millis();
   
   if ( (millis() - chargingAnimationLastToggle) < 800) {
    return;
   }

   chargingAnimationLastToggle = now;
   
   if(battery > 75) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    digitalWrite(LED_SCR_PIN, HIGH);
    if (chargingAnimationOn) {
      digitalWrite(LED_KEY_PIN, HIGH);
      chargingAnimationOn = false;
    } else {
      digitalWrite(LED_KEY_PIN, LOW);
      chargingAnimationOn = true;
    }
   } else if (battery > 50) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    digitalWrite(LED_NUM_PIN, HIGH);
    if (chargingAnimationOn) {
      digitalWrite(LED_SCR_PIN, HIGH);
      chargingAnimationOn = false;
    } else {
      digitalWrite(LED_SCR_PIN, LOW);
      chargingAnimationOn = true;
    }
    digitalWrite(LED_KEY_PIN, LOW);
   } else if (battery > 25) {
    digitalWrite(LED_CAPS_PIN, HIGH);
    if (chargingAnimationOn) {
      digitalWrite(LED_NUM_PIN, HIGH);
      chargingAnimationOn = false;
    } else {
      digitalWrite(LED_NUM_PIN, LOW);
      chargingAnimationOn = true;
    }
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   } else {
    if (chargingAnimationOn) {
      digitalWrite(LED_CAPS_PIN, HIGH);
      chargingAnimationOn = false;
    } else {
      digitalWrite(LED_CAPS_PIN, LOW);
      chargingAnimationOn = true;
    }    
    digitalWrite(LED_NUM_PIN, LOW);
    digitalWrite(LED_SCR_PIN, LOW);
    digitalWrite(LED_KEY_PIN, LOW);
   }
}

