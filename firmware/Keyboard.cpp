#include "Keyboard.h"

Keyboard::Keyboard(void)
: matrix(), keymap(), hid(), power() {
  idleTime = 0;
  batteryLEDsOn = false;
  batteryLEDOnDuration = 3 * 60 * 1000;
}

void Keyboard::begin(void) {
  hid.begin();
  matrix.begin();
  led.begin();
  showBatteryLevel();
}

void Keyboard::update(void) {
   
  auto update = matrix.scan();
  if (update) {
    idleTime = millis();
    keymap.update(&matrix);
    hid.sendKeys(&keymap);
  }

  processBatteryLEDs();

  sleepCheck();
}

void Keyboard::sleepCheck(void) {
  if ((millis() - idleTime) > (sleepMinutes * 60 * 1000)) {
    led.offAll();
    matrix.sleep();    

    uint8_t sd_en;
    sd_softdevice_is_enabled(&sd_en);

    if (sd_en) {
      sd_power_system_off();
    } else {
      NRF_POWER->SYSTEMOFF = 1;
    }
  }
}

void Keyboard::processBatteryLEDs(void) {

  bool shouldTurnOffBatteryLEDs = batteryLEDsOn && ((millis() - batteryLEDTime) > batteryLEDOnDuration);
  if (shouldTurnOffBatteryLEDs) {
    led.numLEDsOn(0);
  }
  
}


void Keyboard::showBatteryLevel(void) {
  
  uint8_t percentage = power.batteryRemainingPercentage();
  
  if(percentage > 75) {
    led.numLEDsOn(4);
   } else if (percentage > 50) {
    led.numLEDsOn(3);
   } else if (percentage > 25) {
    led.numLEDsOn(2);
   } else {
    led.numLEDsOn(1);
   }
   
   batteryLEDsOn = true;
   batteryLEDTime = millis();
  
}
