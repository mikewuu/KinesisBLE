#include "LED.h"


LED::LED(void) {}

void LED::begin(void) {
  powerButtonOn();
}

void LED::offAll(void) {
  powerButtonOff();
}

void LED::powerButtonOn(void) {
  analogWrite(POWER_BUTTON_PIN, 255 - powerButtonBrightness);  
}

void LED::powerButtonOff(void) {
  analogWrite(POWER_BUTTON_PIN, 255);  
}
