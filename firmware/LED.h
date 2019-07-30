#ifndef LED_H
#define LED_H

#include <bluefruit.h>

class LED {
  public:
  
    const static uint8_t CAPS_PIN = 29;
    const static uint8_t NUM_PIN = 28;
    const static uint8_t SCR_PIN = 26;
    const static uint8_t KEY_PIN = 25; 
    
    LED(void);
    void begin(void);
    void offAll(void);
    void setLED(int pin, bool state);
    void setAllLEDs(bool state);
  private:
  
    const uint8_t POWER_BUTTON_PIN = 5;    
    const uint8_t powerButtonBrightness = 175;
    
    void powerButtonOn(void);
    void powerButtonOff(void);
};


#endif
