#include "LED.h"


LED::LED(void) {
  pinMode(CAPS_PIN, OUTPUT);
  pinMode(NUM_PIN, OUTPUT);
  pinMode(SCR_PIN, OUTPUT);
  pinMode(KEY_PIN, OUTPUT);
  onTime = 0;
  isFlashing = false;
  lastFlashTime = 0;
  slowFlashGap = 1000;
  fastFlashGap = 200;
}

void LED::begin(void) {
  powerButtonOn();
}

void LED::offAll(void) {
  powerButtonOff();
  LEDsOff();
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

void LED::numLEDsOnForDuration(int num, unsigned long duration) {
  
    shouldTurnOffAfterDuration = true;
    onTime = millis();
    onDuration = duration;
    
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

void LED::process(void) {
  
  if(shouldTurnOffAfterDuration) {    
    unsigned long now = millis();
    bool shouldTurnOffLEDs =  now - onTime > onDuration;
    if (shouldTurnOffLEDs) {
      LEDsOff();
    }  
  }

  if(isFlashing) {
    unsigned long now = millis();
    unsigned long flashGap = flashSpeed == HIGH ? fastFlashGap : slowFlashGap;
    bool shouldToggleFlashState = now - lastFlashTime > flashGap;
    if(shouldToggleFlashState) {
      
      lastFlashTime = now;
      if(flashingLedOn) {
        setAllLEDs(LOW);
        flashingLedOn = false;
      } else {
        setAllLEDs(HIGH);
        flashingLedOn = true;
      }      
      
    }
  }
}

void LED::LEDsOff() {
  setAllLEDs(LOW);
  shouldTurnOffAfterDuration = false;
}

void LED::flashWithSpeed(bool speed) {
  if(!isFlashing || speed != flashSpeed) {
    isFlashing = true;
    flashSpeed = speed;
    shouldTurnOffAfterDuration = false; 
  }
}

void LED::stopFlashing(void) {
  if(isFlashing) {
    isFlashing = false;
    LEDsOff(); 
  }
}
