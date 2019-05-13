#include <Arduino.h>

#include "config.h"
#include "keymap.h"
#include "keycodes.h"
#include "bluetooth.h"
#include "battery.h"

uint16_t layer_cache[15][7] = {
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

#define LAYERS 2
#define BASE 0
#define RAISE 1
#define IS_LAYER_ON(layer) (active_layers & (1<<layer))
uint8_t active_layers = 1; // Base layer is always active

inline void set_layer(uint8_t layer) {
  active_layers |= (1 << layer);  // Set nth bit to 1 (n = layer)
}

inline void unset_layer(uint8_t layer) {
  active_layers &= ~(1 << layer); // Set nth bit to 0 (n = layer)
}

uint32_t last_pressed = 0;
uint8_t pressed_alone = 0;
#define PRESSED_RAISE 0

#define DUAL_TIMEOUT 300

const uint16_t PROGMEM layers[LAYERS][15][7] = {

  /**
   * DEFAULT MATRIX
   * 
   * {K_EQUL, K__TAB, K_CLCK, K_LSFT, ______, ______, ______},
   * {K____1, K____Q, K____A, K____Z, K_GRVE, ______, ______}, 
   * {K____2, K____W, K____S, K____X, K_BSLH, K__SL1, ______},
   * {K____3, K____E, K____D, K____C, K_LEFT, K__SL2, K__SL4}, 
   * {K____4, K____R, K____F, K____V, ______, ______, K__SL3},
   * {K____5, K____T, K____G, K____B, K_RGHT, K__SL5, K__SL6}, 
   * {K____6, K____Y, K____H, K____N, K___UP, K__SR4, K__SR1},
   * {K____7, K____U, K____J, K____M, ______, K__SR3, ______}, 
   * {K____8, K____I, K____K, K_CMMA, K_DOWN, K__SR6, K__SR2},
   * {K____9, K____O, K____L, K__DOT, K_LBRC, ______, K__SR5}, 
   * {K____0, K____P, K_SCLN, K_SLSH, K_RBRC, ______, ______},
   * {K_MINS, K_BSLH, K_APST, K_RSFT, ______, ______, ______},
   * {K_ESCP, K___F3, K___F6, K___F9, K__F12, K_PAUS, ______}, 
   * {K___F1, K___F4, K___F7, K__F10, K_PRSC, K_PGRM, ______},
   * {K___F2, K___F5, K___F8, K__F11, K_SLCK, K_KYPD, ______}
   */

  [BASE] = {
    {K_GRVE, K__TAB, K_CLCK, K_LSFT, ______, ______, ______},
    {K____1, K____Q, K____A, K____Z, K_GRVE, ______, ______}, 
    {K____2, K____W, K____S, K____X, K_BSLH, K__SL1, ______},
    {K____3, K____E, K____D, K____C, K_LEFT, K__SL2, K__SL4}, 
    {K____4, K____R, K____F, K____V, ______, ______, K__SL3},
    {K____5, K____T, K____G, K____B, K_RGHT, K__SL5, K__SL6}, 
    {K____6, K____Y, K____H, K____N, K___UP, K__SR4, K__SR1},
    {K____7, K____U, K____J, K____M, ______, K__SR3, ______}, 
    {K____8, K____I, K____K, K_CMMA, K_DOWN, K__SR6, K__SR2},
    {K____9, K____O, K____L, K__DOT, K_LBRC, ______, K__SR5}, 
    {K____0, K____P, K_SCLN, K_SLSH, K_RBRC, ______, ______},
    {K_MINS, K_BSLH, K_APST, K_RSFT, ______, ______, ______},
    {K_ESCP, K___F3, K___F6, K___F9, K__F12, K_PAUS, ______}, 
    {K___F1, K___F4, K___F7, K__F10, K_PRSC, K_RSTD, ______},
    {K___F2, K___F5, K___F8, K__F11, K_SLCK, K_KYPD, ______}
  },
  
  [RAISE] = {
    {______, ______, ______, ______, ______, ______, ______},
    {______, ______, ______, ______, ______, ______, ______}, 
    {______, ______, K_LEFT, ______, ______, ______, ______},
    {______, K___UP, K_DOWN, ______, K_RSLA, ______, ______}, 
    {______, ______, K_RGHT, ______, ______, ______, ______},
    {______, ______, ______, ______, K_RSRA, ______, ______}, 
    {______, ______, ______, ______, ______, ______, K_PGDN},
    {______, K_RLPT, K_RLBK, K_RLBC, ______, ______, ______}, 
    {______, K_RRPT, K_RRBK, K_RRBC, ______, ______, K_PGUP},
    {______, ______, K_SCLN, K_APST, ______, ______, ______}, 
    {______, ______, ______, K_RQTE, ______, ______, ______},
    {______, ______, ______, ______, ______, ______, ______}, 
    {______, ______, ______, ______, ______, K__F12, ______},
    {______, ______, ______, ______, K__F10, K_RRST, ______}, 
    {______, ______, ______, ______, K__F11, ______, ______}
  }
};


uint16_t get_keycode_at(uint8_t row, uint8_t col) {

  // get from cache
  uint16_t cached = layer_cache[row][col];
  if (cached != ______) {
    return cached;
  }

  for (uint8_t layer = LAYERS - 1; layer >= 0; layer-- ) {
    if (IS_LAYER_ON(layer)) {
      uint16_t keycode = pgm_read_word(&(layers[layer][row][col]));
      if (keycode != ______) {  // Remove this check to only check current layer
        return keycode;
      }
    }
  }
  
  return K_NONE;
}

int handle_keychange(uint8_t row, uint8_t col, state_t state) { 
  
  uint16_t keycode = get_keycode_at(row, col);
  if (state == DOWN) {
    pressed_alone = 0;
  }

  switch (keycode) {
    case K_RAISE: {
      if (state == DOWN){
        set_layer(RAISE);
        pressed_alone |= (1<<PRESSED_RAISE);
        last_pressed = millis();
      } else {
        unset_layer(RAISE);
        // If pressed key alone
        if (
            (millis() - last_pressed < DUAL_TIMEOUT) &&
            (pressed_alone & (1 << PRESSED_RAISE))
        ) {
            register_keydown(K__TAB);
            register_keyup(K__TAB);    
          }
      }
      break;
    }
    case K_RSLA: {
      // Select to end of line Left: CMD + Shift + Left Arrow
      if (state == DOWN) {
        register_keydown(K_LCMD);
        register_keydown(K_LSFT);
        register_keydown(K_LEFT);
      } else {
        register_keyup(K_LCMD);
        register_keyup(K_LSFT);
        register_keyup(K_LEFT);
      }
      break;
    }
    case K_RSRA: {
      // Select to end of line Left: CMD + Shift + Right Arrow
      if (state == DOWN) {
        register_keydown(K_LCMD);
        register_keydown(K_LSFT);
        register_keydown(K_RGHT);
      } else {
        register_keyup(K_LCMD);
        register_keyup(K_LSFT);
        register_keyup(K_RGHT);
      }
      break;
    }
    case K_RLPT: {
      // Left Paranthesis
      if (state == DOWN) {
        register_keydown(K_LSFT);
        register_keydown(K____9);    
      } else {
        register_keyup(K_LSFT);
        register_keyup(K____9);    
      }
      break;
    }
    case K_RRPT: {
      // Right Paranthesis
      if (state == DOWN) {
        register_keydown(K_LSFT);
        register_keydown(K____0);    
      } else {
        register_keyup(K_LSFT);
        register_keyup(K____0);    
      }
      break;
    }
    case K_RRBC: {
      // Right Brace
      if (state == DOWN) {
        register_keydown(K_LSFT);
        register_keydown(K_RBRC);     
      } else {
        register_keyup(K_LSFT);
        register_keyup(K_RBRC);     
      }
      break;
    }
    case K_RLBC: {
      // Left Brace
      if (state == DOWN) {
        register_keydown(K_LSFT);
        register_keydown(K_LBRC);     
      } else {
        register_keyup(K_LSFT);
        register_keyup(K_LBRC);     
      }
      break;
    }
    case K_RQTE: {
      // Quote key
      if (state == DOWN) {
        register_keydown(K_LSFT);
        register_keydown(K_APST);     
      } else {
        register_keyup(K_LSFT);
        register_keyup(K_APST);    
      }
      break;
    }
    case K_KYPD: {
      showBatteryLevel();  
      break;
    }
    case K_RSTD: {
      return COMMAND_SHUTDOWN;
    }
    case K_RRST: {
      return COMMAND_START_BREAK;  
    }
    default: {
      
      // Normal keycode
      if (state == DOWN) {
        register_keydown(keycode);
      } else {      
        register_keyup(keycode);
      }
      break;
    }
  }
  
  // Store to cache
  if (state == DOWN) {
    layer_cache[row][col] = keycode;
  } else {
    layer_cache[row][col] =  ______;
  }

  
}
