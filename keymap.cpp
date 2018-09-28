#include <Arduino.h>

#include "config.h"
#include "keymap.h"
#include "keycodes.h"
#include "bluetooth.h"

uint16_t matrix_cache[15][7] = {
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______},
  {______, ______, ______, ______, ______, ______, ______}, 
  {______, ______, ______, ______, ______, ______, ______}
};

const uint16_t PROGMEM matrix[15][7] = {
  {K_EQUAL, K_TAB,       K_CAPSLOCK,   K_MOD_LSHIFT, ______,       ______,    ______},
  {K_1,     K_Q,         K_A,          K_Z,          K_GRAVE,      ______,    ______}, 
  {K_2,     K_W,         K_S,          K_X,          K_INSERT,     K_SL1,     ______},
  {K_3,     K_E,         K_D,          K_C,          K_LEFT,       K_SL2,     K_SL4}, 
  {K_4,     K_R,         K_F,          K_V,          ______,       ______,    K_SL3},
  {K_5,     K_T,         K_G,          K_B,          K_RIGHT,      K_SL5,     K_SL6}, 
  {K_6,     K_Y,         K_H,          K_N,          K_UP,         K_SR4,     K_SR1},
  {K_7,     K_U,         K_J,          K_M,          ______,       K_SR3,     ______}, 
  {K_8,     K_I,         K_K,          K_COMMA,      K_DOWN,       K_SR6,     K_SR2},
  {K_9,     K_O,         K_L,          K_DOT,        K_LEFTBRACE,  ______,    K_SR5}, 
  {K_0,     K_P,         K_SEMICOLON,  K_SLASH,      K_RIGHTBRACE, ______,    ______},
  {K_MINUS, K_BACKSLASH, K_APOSTROPHE, K_MOD_RSHIFT, ______,       ______,    ______},
  {K_ESC,   K_F3,        K_F6,         K_F9,         K_F12,        K_PAUSE,   ______}, 
  {K_F1,    K_F4,        K_F7,         K_F10,        K_SYSRQ,      K_PROGRAM, ______},
  {K_F2,    K_F5,        K_F8,         K_F11,        K_SCROLLLOCK, K_KEYPAD,  ______}
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
  
  return K_NONE;
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
