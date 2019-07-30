#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "Matrix.h"
#include "KeyMap.h"
#include "HID.h"
#include "LED.h"
#include "Power.h"

class Keyboard {
  public:
    Keyboard(void);
    void begin(void);
    void update(void);
    void sleepCheck(void);

  private:
    Matrix matrix;
    Keymap keymap;
    HID hid;
    LED led;
    Power power;
    unsigned long idleTime;
    void processBatteryLEDs(void);
    void showBatteryLevel(void);
    unsigned long batteryLEDTime;
    bool batteryLEDsOn;
    unsigned long batteryLEDOnDuration;

    static const uint8_t sleepMinutes = 10;
};


#endif
