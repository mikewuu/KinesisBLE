#include <Arduino.h>
#include <bluefruit.h>
#include <Nffs.h>

#include "config.h"
#include "keycodes.h"
#include "battery.h"

BLEHidAdafruit blehid;
BLEDis bledis;

#define REPORT_KEYS 6

uint8_t report[REPORT_KEYS] = { 0 };
uint8_t active_mods = 0;

/**
 * Modifier byte is a bitmap, meaning each bit corresponds to one
 * modifier key. To add a new modifier key to existing byte, 
 * combine using Compound bitwise OR.
 */
void add_mods(uint8_t mods) {
  active_mods |= mods;                      
}

void del_mods(uint8_t mods) {
  active_mods &= ~mods;          
}

void clear_bluetooth_bonds() {
  Bluefruit.clearBonds();
  Bluefruit.Central.clearBonds();
  Nffs.format();
  #ifdef DEBUG
    Serial.println("Cleared bluetooth bonds & paired devices");
  #endif

  for (int i = 0; i < 3; i++) {
    setAllBatteryLed(LOW);
    delay(150);
    setAllBatteryLed(HIGH);
    delay(150);
  }

  setAllBatteryLed(LOW);
   
}

void printKeyReports() {
  Serial.println("mods");
  Serial.println(active_mods);
  Serial.println("key0");
  Serial.println(report[0]);
  Serial.println("key1");
  Serial.println(report[1]);
  Serial.println("key2");
  Serial.println(report[2]);
  Serial.println("key3");
  Serial.println(report[3]);
  Serial.println("key4");
  Serial.println(report[4]);
  Serial.println("key5");
  Serial.println(report[5]);
  Serial.println("-----------------------------");
}

void send_report_keyboard() {

  // Right shift + left cmd  = 40
  // esc = 41
  if(active_mods == 40 && report[0] == 41) {
    clear_bluetooth_bonds();
  }

  #ifdef DEBUG
    printKeyReports();
  #endif
  
  bool err = blehid.keyboardReport(
    active_mods, report[0], report[1], report[2], report[3], report[4], report[5]
  );
}

void register_keydown(uint16_t keycode) { 
    add_mods((uint8_t)(keycode >> 8));                        // keycode >> 8 = first byte of keycode (modifier)

    uint8_t keyHexCode = (uint8_t)(keycode & 0xFF);
    
    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
      // Key already stored there
      if (report[i] == (uint8_t)(keycode & 0xFF)) {           // keycode & 0xFF = last byte of the keycode (key value)
        break;
      }
      // Empty key space
      if (report[i] == 0) {
        // Store key
        report[i] = (uint8_t)(keycode & 0xFF);
        break;
      }
    }
    
    send_report_keyboard();  
    
}

void register_keyup(uint16_t keycode) {
    del_mods((uint8_t)(keycode >> 8));

    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
      if (report[i] == (uint8_t)(keycode & 0xFF)) {           // Look for where the key is stored
        report[i] = 0;                                        // Clear it from report array
      }
    }

    send_report_keyboard();
}

void init_bluetooth() {

  Bluefruit.begin();
  Bluefruit.setName("Kinesis BLE V4");
  Bluefruit.setTxPower(-8);
  Bluefruit.autoConnLed(false);                                 // turn off Blue LED

  bledis.setManufacturer("mike wu");
  bledis.setModel("Kinesis Advantage 2");
  
  bledis.begin();
  blehid.begin();

  // Advertising packet
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  
  // Include BLE HID service
  Bluefruit.Advertising.addService(blehid);

  // There is enough room for the dev name in the advertising packet
  Bluefruit.Advertising.addName();
  
  // Apple recommended advertising settings
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}

bool is_bluetooth_connected() {
  return Bluefruit.connected();
}

