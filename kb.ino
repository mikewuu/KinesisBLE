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

uint8_t stop = 100;

uint8_t last_reported = 999;
uint32_t last_report_time = 0;
void loop(void) {
  if (!is_bluetooth_connected()) {
    last_reported = 999;
    last_report_time = 0;
    analogWrite(LED, 128);
    delay(500);
    return;
  }

  float measuredvbat = analogRead(VBAT) * 6.6 / 1024;
  uint8_t bat_percentage = (uint8_t)round((measuredvbat - 3.7) * 200);
  if (
      (last_reported != bat_percentage) && 
      (millis() - last_report_time > 10000)
  ) {
    last_report_time = millis();
    last_reported = bat_percentage;
    update_battery(bat_percentage);
  }

  analogWrite(LED, 1 + (exp(sin(millis()/2000.0*PI)) - 0.36787944) * 107.0);

  for (uint8_t row = 0; row < ROWS; row++) {
    uint8_t row_read = 0;

    digitalWrite(row_pins[row], LOW);
    delayMicroseconds(30);

    for (uint8_t col = 0; col < COLS; col++) {
      if (digitalRead(col_pins[col]) == LOW) {
        row_read |= 1 << col;
      }
    }

    if (temp_states[row] != row_read) {
      temp_states[row] = row_read;
      debouncing = DEBOUNCING_DELAY;
    }
    digitalWrite(row_pins[row], HIGH);
  }

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

  for (uint8_t row = 0; row < ROWS; row++) {
    if (curr_states[row] == prev_states[row]) {
      continue;
    }

    for (uint8_t col = 0; col < COLS; col++) {
      state_t curr = (curr_states[row] >> col) & 1;
      state_t prev = (prev_states[row] >> col) & 1;
      if (curr != prev) {
        handle_keychange(row >> 1, 2 * col + (row & 1), curr);
        prev_states[row] ^= (uint16_t)1 << col;
        goto END_OF_LOOP;
      }
    }
  }

  END_OF_LOOP:;
}
