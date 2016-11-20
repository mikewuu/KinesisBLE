#include <Arduino.h>

#include "keymap.h"
#include "keycodes.h"
#include "bluetooth.h"

#define LAYERS 4
#define BASE 0
#define LOWER 1
#define RAISE 2
#define HOME 3
#define IS_LAYER_ON(layer) (active_layers & (1 << layer))
uint8_t active_layers = 1; // layer 0 is always active

inline
void set_layer(uint8_t layer) {
  active_layers |= (1 << layer);
}

inline
void unset_layer(uint8_t layer) {
  active_layers &= ~(1 << layer);
}

uint32_t last_pressed = 0;
uint8_t pressed_alone = 0;
#define PRESSED_LSFT 0
#define PRESSED_RSFT 1
#define PRESSED_LOW  2
#define PRESSED_RAIS 3
#define PRESSED_HOME 4


const uint16_t PROGMEM layers[LAYERS][4][12] = {
  [BASE] = {
    {K_ESC,  K_A,    K_Z,    K_E,    K_R,    K_T,    K_Y,    K_U,    K_I,    K_O,    K_P,    K_BSPC},
    {K_TAB,  K_Q,    K_S,    K_D,    K_F,    K_G,    K_H,    K_J,    K_K,    K_L,    K_M,    K_ENT},
    {K_LSFT, K_W,    K_X,    K_C,    K_V,    K_B,    K_N,    K_COMM, K_SCLN, K_COLN, K_UP,   K_RSFT},
    {K_HOME, K_CTRL, K_OPT,  K_CMD,  K_LOW,  K_SPC,  K_SPC,  K_RAIS, K_OPT,  K_LEFT, K_DOWN, K_RGHT}
  },
  [LOWER] = {
    {K_AT,   K_AMP,  K_EACU, K_QUOT, K_APOS, K_LPRN, K_SECT, K_EGRV, K_EXLM, K_CCED, K_AGRV, ______},
    {______, ______, ______, ______, ______, ______, ______, K_CIRC, K_DLR,  K_RPRN, K_MINS, ______},
    {______, K_LESS,  ______, ______, ______, ______, ______, K_EQL,  K_UGRV, K_GRV,  ______, ______},
    {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______}
  },

  [RAISE] = {
    {K_HASH, K_1,    K_2,    K_3,    K_4,    K_5,    K_6,    K_7,    K_8,    K_9,    K_0,    ______},
    {______, ______, ______, ______, ______, ______, ______, K_UMLT, K_ASTR, K_DEG,  K_UNDS, ______},
    {______, K_GRTR, ______, ______, ______, ______, ______, K_PLUS, K_PERC, K_PND,  ______, ______},
    {______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______, ______}
  },

  [HOME] = {
    {K_TERM, K_SFRI, K_MAIL, K_CAL,  K_ITNS, K_PREV, K_PLAY, K_NEXT, K_MUTE, K_VOLD, K_VOLU, ______},
    {K_SP1,  K_SP2,  K_SP3,  K_SP4,  K_FULL, ______, ______, ______, ______, ______, ______, ______},
    {______, ______, ______, ______, ______, K_CAPF, K_CAPR, ______, ______, ______, K_BRIU, ______},
    {______, ______, ______, ______, ______, K_CHAR, K_CHAR, ______, ______, ______, K_BRID, ______},
  }
};


uint16_t get_keycode_at(uint8_t row, uint8_t col) {
  for (uint8_t layer = LAYERS - 1; layer >= 0; layer--) {
    if (IS_LAYER_ON(layer)) {
      uint16_t keycode = pgm_read_word(&(layers[layer][row][col]));
      if (keycode != ______) {
        return keycode;
      }
    }
  }
  return K_NO;
}

void handle_keychange(uint8_t row, uint8_t col, state_t state) {
  uint16_t keycode = get_keycode_at(row, col);
  if (state == DOWN) {
    pressed_alone = 0;
  }

  switch (keycode) {
    case K_LSFT: {
      if (state == DOWN) {
        pressed_alone |= (1 << PRESSED_LSFT);
        last_pressed = millis();
        register_keydown(K_SHFT);
      } else {
        register_keyup(K_SHFT);
        if (
            (millis() - last_pressed < 1000) &&
            (pressed_alone & (1 << PRESSED_LSFT))
        ) {
          if (IS_LAYER_ON(RAISE)) {
            register_keydown(K_LCBR);
            register_keyup(K_LCBR);
          } else if (IS_LAYER_ON(LOWER)) {
            register_keydown(K_LBRC);
            register_keyup(K_LBRC);
          } else {
            register_keydown(K_LPRN);
            register_keyup(K_LPRN);
          }
        }
      }
      break;
    }
    case K_RSFT: {
      if (state == DOWN) {
        pressed_alone |= (1 << PRESSED_RSFT);
        last_pressed = millis();
        register_keydown(K_SHFT);
      } else {
        register_keyup(K_SHFT);
        if (
            (millis() - last_pressed < 1000) &&
            (pressed_alone & (1 << PRESSED_RSFT))
        ) {
          if (IS_LAYER_ON(RAISE)) {
            register_keydown(K_RCBR);
            register_keyup(K_RCBR);
          } else if (IS_LAYER_ON(LOWER)) {
            register_keydown(K_RBRC);
            register_keyup(K_RBRC);
          } else {
            register_keydown(K_RPRN);
            register_keyup(K_RPRN);
          }
        }
      }
      break;
    }
    case K_LOW: {
      if (state == DOWN) {
        set_layer(LOWER);
        last_pressed = millis();
        pressed_alone |= (1 << PRESSED_LOW);
      } else {
        unset_layer(LOWER);
        if (
            (millis() - last_pressed < 1000) &&
            (pressed_alone & (1 << PRESSED_LOW))
        ) {
          register_keydown(K_QUOT);
          register_keyup(K_QUOT);
        }
      }
      break;
    }
    case K_RAIS: {
      if (state == DOWN) {
        set_layer(RAISE);
        last_pressed = millis();
        pressed_alone |= (1 << PRESSED_RAIS);
      } else {
        unset_layer(RAISE);
        if (
            (millis() - last_pressed < 1000) &&
            (pressed_alone & (1 << PRESSED_RAIS))
        ) {
          register_keydown(K_APOS);
          register_keyup(K_APOS);
        }
      }
      break;
    }
    case K_HOME: {
      if (state == DOWN) {
        set_layer(HOME);
        last_pressed = millis();
        pressed_alone |= (1 << PRESSED_HOME);
      } else {
        unset_layer(HOME);
        if (
            (millis() - last_pressed < 1000) &&
            (pressed_alone & (1 << PRESSED_HOME))
        ) {
          register_keydown(K_CAPS);
          register_keyup(K_CAPS);
        }
      }
      break;
    }
    default: {
      if (state == DOWN) {
        register_keydown(keycode);
      } else {
        register_keyup(keycode);
      }
      break;
    }
  }
}

