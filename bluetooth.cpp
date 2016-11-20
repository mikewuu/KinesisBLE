#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>

#include "keycodes.h"

#define BLE_SPI_CS 8
#define BLE_SPI_IRQ 7
#define BLE_SPI_RST 4

#define REPORT_KEYS 6

Adafruit_BluefruitLE_SPI ble(BLE_SPI_CS, BLE_SPI_IRQ, BLE_SPI_RST);
uint8_t report[REPORT_KEYS] = { 0 };
uint8_t active_mods = 0;
char payload[43] = "";

void add_mods(uint8_t mods) {
  active_mods |= mods;
}

void del_mods(uint8_t mods) {
  active_mods &= ~mods;
}

void send_report_keyboard() {
  sprintf(payload,
    "AT+BLEKEYBOARDCODE=%02x-00-%02x-%02x-%02x-%02x-%02x-%02x",
    active_mods, report[0], report[1], report[2], report[3], report[4], report[5]
  );
  ble.println(payload);
  delay(5);
}

void register_keydown(uint16_t keycode) {
  if (IN_KEYBOARD_RANGE(keycode)) {
    add_mods((uint8_t)(keycode >> 8));
    send_report_keyboard();

    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
      if (report[i] == (uint8_t)(keycode & 0xFF)) {
        break;
      }
      if (report[i] == 0) {
        report[i] = (uint8_t)(keycode & 0xFF);
        break;
      }
    }
    send_report_keyboard();
  }
}

void register_keyup(uint16_t keycode) {
  if (IN_KEYBOARD_RANGE(keycode)) {
    del_mods((uint8_t)(keycode >> 8));
    send_report_keyboard();

    for (uint8_t i = 0; i < REPORT_KEYS; i++) {
      if (report[i] == (uint8_t)(keycode & 0xFF)) {
        report[i] = 0;
      }
    }
    send_report_keyboard();
  }
}

void init_bluetooth(bool reset) {
  ble.begin(false);
  if (reset){
    ble.factoryReset();
    ble.setMode(BLUEFRUIT_MODE_COMMAND);
    ble.println("AT+GATTCLEAR");
    ble.println("AT+GAPDEVNAME=The Blanck Keyboard");

    // Add battery service
    ble.println("AT+GATTADDSERVICE=UUID=0x180F");
    // Battery level
    ble.println("AT+GATTADDCHAR=UUID=0x2A19,PROPERTIES=0x02,DATATYPE=3,MIN_LEN=1,MAX_LEN=1,VALUE=0");

    ble.println("AT+BLEHIDEN=1");
    // Device Information Service
    ble.println("AT+GATTADDSERVICE=UUID=0x180A");
    // Manufacturer name
    ble.println("AT+GATTADDCHAR=UUID=0x2A29,PROPERTIES=0x02,DATATYPE=1,MIN_LEN=15,MAX_LEN=15,VALUE=Adrien Friggeri");
    // Model Number String
    ble.println("AT+GATTADDCHAR=UUID=0x2A24,PROPERTIES=0x02,DATATYPE=1,MIN_LEN=3,MAX_LEN=3,VALUE=1.0");
    // PnP_ID
    // Vendor ID Source: 0x02
    // Vendor ID: 0x2311
    // Product ID: 0xcafe
    // Product Version: 0x0001
    ble.println("AT+GATTADDCHAR=UUID=0x2A50,PROPERTIES=0x02,DATATYPE=2,MIN_LEN=7,MAX_LEN=7,VALUE=02-11-23-fe-ca-01-00");

    // Set advertising data:
    // 2 bytes:
    //   01 Flag
    //   06 LE General Discoverable Mode | BR/EDR Not Supported
    // 7 bytes:
    //   02 Incomplete List of 16-bit Service Class UUIDs
    //   180F Battery Service
    //   180A Device Information Service
    //   1812 Human Interface Device
    // 3 bytes:
    //   0D Class of Device
    //   2540 Peripheral / Keyboard
    ble.println("AT+GAPSETADVDATA=02-01-06-07-02-0F-18-0A-18-12-18-03-0D-40-25");
    ble.echo(false);
    ble.verbose(false);
    ble.println("ATZ");
    delay(1000);
  }

  // for debugging purposes
  // ble.setMode(BLUEFRUIT_MODE_DATA);
}

void update_battery(uint8_t bat_percentage) {
  sprintf(payload, "AT+GATTCHAR=1,%d", bat_percentage);
  ble.println(payload);
  delay(5);
}

bool is_bluetooth_connected() {
  return ble.isConnected();
}
