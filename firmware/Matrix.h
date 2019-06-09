#ifndef MATRIX_H
#define MATRIX_H

#include <stdint.h>

class Matrix {
  public:
    enum class Dim {
      Row = 7,
      Col = 15,
    };

    struct Key {
      uint8_t r;
      uint8_t c;
    };

    Matrix(void);
    void begin(void);
    bool scan(void);
    bool pressed(const Key k) const;
    void sleep(void);

  private:

    enum class KeyStatus {
      NOT_PRESSED,
      PRESSED_BOUNCING,
      PRESSED,
      RELEASING_BOUNCING,
    };
  
    struct KeyState {
      uint32_t pressTime;
      KeyStatus status;
    };

    KeyState keys[(int)Dim::Row][(int)Dim::Col];

    bool updateState(const int row, const int col, const bool pressed);

    static const uint8_t rowPins[];
    static const uint8_t colPins[];
    static const uint8_t debounceTime = 5;    
};

#endif
