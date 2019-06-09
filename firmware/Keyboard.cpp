#include "Keyboard.h"

Keyboard::Keyboard(void)
: matrix(), keymap(), hid() {
  idleTime = 0;
}

void Keyboard::begin(void) {
  hid.begin();
  matrix.begin();
}

void Keyboard::update(void) {
   
  auto update = matrix.scan();
  if (update) {
    idleTime = millis();
    keymap.update(&matrix);
    hid.sendKeys(&keymap);
  }

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
