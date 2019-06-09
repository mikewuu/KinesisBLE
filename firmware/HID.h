#ifndef HID_H
#define HID_H

#include <bluefruit.h>

#include "KeyMap.h"

class HID {
  public:
    HID(void);
    void begin(void);
    void sendKeys(const Keymap *km);
  private:

    enum class Scancode : uint8_t {
      A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

      Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,

      Enter, Esc, BSpace, Tab, Space, Minus, Equal, LBrace, RBrace, BSlash,
      Tilde, Semicolon, SQuote, Grave, Comma, Period, Slash,

      F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

      Home, PgUp, Del, End, PgDn, Right, Left, Down, Up,

      Count,
      None
    };

    enum class Mod {
      Ctrl, Alt, Shift,
      LCtrl, LShift, LAlt, LCmd,
      RCtrl, RShift, RAlt, RCmd
    };

    struct KeyInfo {
      Scancode scancode : 7;
      bool shift : 1;
    };

    BLEHidAdafruit bleHID;
    BLEDis bleDIS;
    hid_keyboard_report_t report;

    static const uint8_t scancodes[];
    static const uint8_t modifers[];
    static const KeyInfo scancodeMap[];
    static const uint8_t modMap[];
    
};

#endif
