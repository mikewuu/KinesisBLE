#include "LED.h"


LED::LED(void) {
  pinMode(CAPS_PIN, OUTPUT);
  pinMode(NUM_PIN, OUTPUT);
  pinMode(SCR_PIN, OUTPUT);
  pinMode(KEY_PIN, OUTPUT);
}

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

void LED::numLEDsOn(int num) {
    if(num == 4) {
    setLED(CAPS_PIN, HIGH);
    setLED(NUM_PIN, HIGH);
    setLED(SCR_PIN, HIGH);
    setLED(KEY_PIN, HIGH);
   } else if (num == 3) {
    setLED(CAPS_PIN, HIGH);
    setLED(NUM_PIN, HIGH);
    setLED(SCR_PIN, HIGH);
    setLED(KEY_PIN, LOW);
   } else if (num == 2) {
    setLED(CAPS_PIN, HIGH);
    setLED(NUM_PIN, HIGH);
    setLED(SCR_PIN, LOW);
    setLED(KEY_PIN, LOW);
   } else if (num == 1) {
    setLED(CAPS_PIN, HIGH);
    setLED(NUM_PIN, LOW);
    setLED(SCR_PIN, LOW);
    setLED(KEY_PIN, LOW);
   } else if (num == 0) {
    setLED(CAPS_PIN, LOW);
    setLED(NUM_PIN, LOW);
    setLED(SCR_PIN, LOW);
    setLED(KEY_PIN, LOW);
   }
   
}
