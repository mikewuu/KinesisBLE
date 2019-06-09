#include "Matrix.h"
#include "MCP23S17.h"

#include <Arduino.h>

const uint8_t Matrix::rowPins[] = {
  4, 3, 2, 16, 15, 7, 11
};

const uint8_t Matrix::colPins[] = {
  1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15
};

MCP mcp(0, 27); 

Matrix::Matrix(void) {
  memset(keys, 0, sizeof(keys));
}

void Matrix::begin(void) {
  mcp.begin();
  
  for (auto c = 0; c < (int)Matrix::Dim::Col; c++) {
    mcp.pinMode(colPins[c], OUTPUT);
    mcp.digitalWrite(colPins[c], HIGH);
  }
  
  for (auto r = 0; r < (int)Matrix::Dim::Row; r++) {
    pinMode(rowPins[r], INPUT_PULLUP);
  }

}


bool Matrix::updateState(const int row, const int col, const bool pressed) {
    
  KeyState *state = &(keys[row][col]);
  auto scanTime = millis();
  bool bouncing = (scanTime - state->pressTime) < debounceTime;
  
  switch (state->status) {
    case KeyStatus::NOT_PRESSED:
    if (!pressed) {
      return false;
    }
    // state transition from not pressed to pressed
    state->status = KeyStatus::PRESSED_BOUNCING;
    state->pressTime = scanTime;
    return true;

    case KeyStatus::PRESSED_BOUNCING:
      if (bouncing) {
        return false;
      }
      state->status = KeyStatus::PRESSED;
      return false;

    case KeyStatus::PRESSED:
    if (pressed) {
      return false;
    }
    // state transition from pressed to not pressed
    state->status = KeyStatus::RELEASING_BOUNCING;
    state->pressTime = scanTime;
    return true;

    case KeyStatus::RELEASING_BOUNCING:
    if (bouncing) {
      return false;
    }
    state->status = KeyStatus::NOT_PRESSED;
    return false;
  }

  return false; // unreached
}


bool Matrix::scan(void) {
  auto scanTime = millis();

  bool update = false;

  for (auto c = 0; c < (int)Matrix::Dim::Col; c++) {

    mcp.digitalWrite(colPins[c], LOW);
  
    for (auto r = 0; r < (int)Matrix::Dim::Row; r++) {
      auto pressed = digitalRead(rowPins[r]) == LOW;

      bool updated = updateState(r, c, pressed);
      if(!update) {
        update = updated;
      }
      
    }
  
    mcp.digitalWrite(colPins[c], HIGH);
  }

  return update;
}

bool Matrix::pressed(const Matrix::Key k) const {
  return keys[k.r][k.c].status == KeyStatus::PRESSED || keys[k.r][k.c].status == KeyStatus::PRESSED_BOUNCING;
}

void Matrix::sleep(void) {
  for (auto c = 0; c < (int)Matrix::Dim::Col; c++) {
    mcp.digitalWrite(colPins[c], LOW);
  }

  for (auto r = 0; r < (int)Matrix::Dim::Row; r++) {
      nrf_gpio_cfg_sense_input(g_ADigitalPinMap[rowPins[r]], NRF_GPIO_PIN_PULLUP, NRF_GPIO_PIN_SENSE_LOW);
  }
}
