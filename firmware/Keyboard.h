#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Matrix.h"
#include "KeyMap.h"
#include "HID.h"
#include "LED.h"
#include "Power.h"
#include "RestTimer.h"

class Keyboard {
  public:
    Keyboard(void);
    void begin(void);
    void update(void);
    void restCheck(void);
    void sleepCheck(void);    

  private:
    Matrix matrix;
    Keymap keymap;
    HID hid;
    LED led;
    Power power;
    RestTimer restTimer;
    unsigned long idleTime;
    void indicateBatteryLevel(void);
    unsigned long batteryLEDOnDuration;

    static const uint8_t sleepMinutes = 10;
};


#endif
