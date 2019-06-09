#ifndef KEYMAP_H
#define KEYMAP_H

#include <stdint.h>

#include "Matrix.h"

class Keymap {
  public:
    enum class Key {
      A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,

      Num1, Num2, Num3, Num4, Num5, Num6, Num7, Num8, Num9, Num0,

      Enter, Esc, BSpace, Tab, Space, Minus, Equal, LBrace, RBrace, BSlash, Tilde,
      Semicolon, SQuote, Grave, Comma, Period, Slash, Percent, At, LBrack, RBrack,
      Carrot, Pound, Dollar, LParen, RParen, Asterisk, Bang, Plus, Underscore,
      Ampersand, Pipe, Question,

      F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,

      PrintScr, ScrollLock, Pause, Home, PgUp, Del, End, PgDn, Right, Left, Down, Up,

      Capslock, Insert, SL1, SL4, SR1, SR3, SR4, 
      
      LShift, RShift, SL2, SL3, SL5, SL6, SR2, SR5, SR6,

      Ctrl, Shift, Alt, 
      
      Sym,
      Count,
      None
    };

    Keymap(void);
    void update(const Matrix *matrix);
    bool pressed(const Key k) const;

  private:
    enum class Layer {
      Base,
      Sym,
      Count
    };

    enum class ModState {
      Off,
      StickLight,
      StickHeavy
    };

    enum class Mod {
      Ctrl, Shift, Alt, Sym, Count
    };

    Key resolveKey(const Matrix::Key k) const;
    bool modActive(Mod m) const;
    Mod keyToMod(Key k) const;
    ModState nextModState(ModState modState) const;

    bool keysPressed[(int)Key::Count];
    bool matrixPressed[(int)Matrix::Dim::Row][(int)Matrix::Dim::Col];
    ModState modStates[(int)Mod::Count];

    static const Key layout[][(int)Matrix::Dim::Row][(int)Matrix::Dim::Col];
};

#endif
