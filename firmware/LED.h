#ifndef LED_H
#define LED_H

#include <bluefruit.h>

class LED {
  public:
    LED(void);
    void begin(void);
    void offAll(void);
  private:
    static const uint8_t POWER_BUTTON_PIN = 5;
    static const uint8_t powerButtonBrightness = 175;
    void powerButtonOn(void);
    void powerButtonOff(void);
};


#endif
