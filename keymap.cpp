#include <Arduino.h>

#include "config.h"
#include "keymap.h"
#include "keycodes.h"
#include "bluetooth.h"

uint16_t matrix_cache[7][15] = {
  {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______}
};

const uint16_t PROGMEM matrix[7][15] = {
  {KEY_EQUAL,        KEY_1,     KEY_2,      KEY_3,    KEY_4,    KEY_5,     KEY_6,    KEY_7,    KEY_8,     KEY_9,         KEY_0,          KEY_MINUS,          KEY_ESC,   KEY_F1,      KEY_F2        },
  {KEY_TAB,          KEY_Q,     KEY_W,      KEY_E,    KEY_R,    KEY_T,     KEY_Y,    KEY_U,    KEY_I,     KEY_O,         KEY_P,          KEY_BACKSLASH,      KEY_F3,    KEY_F4,      KEY_F5        },
  {KEY_CAPSLOCK,     KEY_A,     KEY_S,      KEY_D,    KEY_F,    KEY_G,     KEY_H,    KEY_J,    KEY_K,     KEY_L,         KEY_SEMICOLON,  KEY_APOSTROPHE,     KEY_F6,    KEY_F7,      KEY_F8        },
  {KEY_MOD_LSHIFT,   KEY_Z,     KEY_X,      KEY_C,    KEY_V,    KEY_B,     KEY_N,    KEY_M,    KEY_COMMA, KEY_DOT,       KEY_SLASH,      KEY_MOD_RSHIFT,     KEY_F9,    KEY_F10,     KEY_F11       },
  {______,           KEY_GRAVE, KEY_INSERT, KEY_LEFT, ______,   KEY_RIGHT, KEY_UP,   ______,   KEY_DOWN,  KEY_LEFTBRACE, KEY_RIGHTBRACE, ______,             KEY_F12,   KEY_SYSRQ,   KEY_SCROLLLOCK},
  {______,           ______,    KEY_SL1,    KEY_SL2,  ______,   KEY_SL5,   KEY_SR4,  KEY_SR3,  KEY_SR6,   ______,        ______,         ______,             KEY_PAUSE, KEY_PROGRAM, KEY_KEYPAD    },
  {______,           ______,    ______,     KEY_SL4,  KEY_SL3,  KEY_SL6,   KEY_SR1,  ______,   KEY_SR2,   KEY_SR5,       ______,         ______,             ______,    ______,      ______        }
};


uint16_t get_keycode_at(uint8_t row, uint8_t col) {

  // get from cache
  uint16_t cached = matrix[row][col];
  if (cached != ______) {
    return cached;
  }

  uint16_t keycode = pgm_read_word(&(matrix[row][col]));
    if (keycode != ______) {
      return keycode;
    }
  
  return KEY_NONE;
}

void handle_keychange(uint8_t row, uint8_t col, state_t state) { 
  
  uint16_t keycode = get_keycode_at(row, col);

  if (state == DOWN) {
    register_keydown(keycode);
  } else {
    register_keyup(keycode);
  }

  // Store to cache
  if (state == DOWN) {
    matrix_cache[row][col] = keycode;
  } else {
    matrix_cache[row][col] =  ______;
  }

  
}
