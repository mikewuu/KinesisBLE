#include <Arduino.h>

#include "config.h"
#include "keycodes.h"
#include "keymap.h"
#include "bluetooth.h"

#define COLS 6
#define ROWS 8

#define DEBOUNCING_DELAY 10

uint8_t col_pins[COLS] = COL_PINS;
uint8_t row_pins[ROWS] = ROW_PINS;

uint8_t prev_states[ROWS] = { 0 };
uint8_t curr_states[ROWS] = { 0 };
uint8_t temp_states[ROWS] = { 0 };
uint8_t debouncing = DEBOUNCING_DELAY;

inline
state_t get_state(uint8_t row, uint8_t col) {
  return (curr_states[2 * row + (col & 1)] >> (col >> 1)) & 1;
}
const int baudrate = 115200;
void setup(void) {
  pinMode(LED, OUTPUT);
  pinMode(CAPS_LED, OUTPUT);

  init_bluetooth();

  for (uint8_t row = 0; row < ROWS; row++) {
    pinMode(row_pins[row], OUTPUT);
    digitalWrite(row_pins[row], HIGH);
  }
  for (uint8_t col = 0; col < COLS; col++) {
    pinMode(col_pins[col], INPUT_PULLUP);
    digitalWrite(col_pins[col], HIGH);
  }

}



void loop(void) {
  
  for (uint8_t row = 0; row < ROWS; row++) {
    uint8_t row_read = 0;

    digitalWrite(row_pins[row], LOW);                     // pull the row we're currently reading to LOW

    // We set to LOW for the row we're reading because we're using INPUT_PULLUP on the column
    // pins so they default to HIGH. If we didn't do this we'd have to wire pulldown 
    // resistors to every switch!
    
    delayMicroseconds(30);

    for (uint8_t col = 0; col < COLS; col++) {            // for each column in the row
      if (digitalRead(col_pins[col]) == LOW) {            // if column is LOW, means a key is pressed
        row_read |= 1 << col;                             // shift left by column number first and then turn last binary digit into a 1
      }
    }

    // if all 6 column pins are low (ie. all 6 keys in row are pressed)
    // 1
    // 11
    // 111
    // 1111
    // 11111
    // 111111

    // if the temp state of the row isn't the same as what we read
    if (temp_states[row] != row_read) {
      temp_states[row] = row_read;          // set the temp state the read row state
      debouncing = DEBOUNCING_DELAY;        // add a debouncing delay
    }
    
    digitalWrite(row_pins[row], HIGH);
  }

  // Basically, want the read row to not have changed for DEBOUNCING_DELAY amount
  // of time until we process what we've read.

  if (debouncing) {
    if (--debouncing) {     // decreases debouncing delay by 1
      delay(1);
      // debouncing, don't update states             
    } else {

      // read the row DEBOUNCING_DELAY number of times and it's still the same,
      // so let's update our states
      
      for (uint8_t row = 0; row < ROWS; row++) {
        prev_states[row] = curr_states[row];
        curr_states[row] = temp_states[row];

        // temp is not the same as curr(ent) because we're debouncing
        // to prevent multiple key switch registers
      }
    }
  }

  // for each row
  for (uint8_t row = 0; row < ROWS; row++) {

    if (curr_states[row] == prev_states[row]) {
      // no change in state
      continue;
    }

    // there is a row change

    for (uint8_t col = 0; col < COLS; col++) {
      
      // shift right to look at current column, then bitwise & 1 which
      // ignores columns to the left and checks to see if state is a
      // 1 or 0.
      state_t curr = (curr_states[row] >> col) & 1;       
      state_t prev = (prev_states[row] >> col) & 1;
      
      if (curr != prev) {
        handle_keychange(row >> 1, 2 * col + (row & 1), curr);
        prev_states[row] ^= (uint16_t)1 << col;
        goto END_OF_LOOP;   // only handle 1 key change each iteration, debouncing!
      }
    }
  }

  END_OF_LOOP:;
}
