#ifndef BLUETOOTH_H
#define BLUETOOTH_H

void register_keydown(uint16_t keycode);
void register_keyup(uint16_t keycode);
void init_bluetooth(bool reset);
bool is_bluetooth_connected();
void update_battery(uint8_t bat_percentage);

#include <Arduino.h>
#include <SPI.h>
#include <SoftwareSerial.h>
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
extern Adafruit_BluefruitLE_SPI ble;

#endif //BLUETOOTH_H
