#include "config.h"
#include "Keyboard.h"
#include "LED.h"

Keyboard keyboard;
LED led;

void setup(void) {
#if DEBUG
  Serial.begin(9600);
#endif
  keyboard.begin();
  led.begin();
}

void loop(void) {  
  keyboard.update();
  // sleep to save power
  delay(10);
}
