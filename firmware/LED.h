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
    void numLEDsOnForDuration(int num, unsigned long duration);
    void process(void);
    void offAll(void);
    void flashWithSpeed(bool speed);
    void stopFlashing(void);
    
  private:

    const uint8_t POWER_BUTTON_PIN = 5;    
    const uint8_t powerButtonBrightness = 175;
    bool shouldTurnOffAfterDuration;
    unsigned long onTime;
    unsigned long onDuration;
    bool isFlashing;
    bool flashingLedOn;
    bool flashSpeed;
    unsigned long lastFlashTime;
    unsigned long slowFlashGap;
    unsigned long fastFlashGap;
    
    void setLED(int pin, bool state);
    void setAllLEDs(bool state);
    void powerButtonOn(void);
    void powerButtonOff(void);
    void LEDsOff(void);
};


#endif
