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

void LED::setAllLEDs(bool state) {
  setLED(CAPS_PIN, state);
  setLED(NUM_PIN, state);
  setLED(SCR_PIN, state);
  setLED(KEY_PIN, state);
}

void LED::setLED(int pin, bool state) {
  if (state == HIGH) {
    analogWrite(pin, 10);
  } else {
    analogWrite(pin, 0);
  }
}
