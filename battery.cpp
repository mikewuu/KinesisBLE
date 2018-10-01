#include <Arduino.h>
#include "config.h"
#include "battery.h"

int lastReportedBatteryPercentage = 0;
int lastReportTime = -10001;                                                    // Checkbattery every 10 seconds

int readVBAT(void) {
  int raw;

  // Set the analog reference to 3.0V (default = 3.6V)
  analogReference(AR_INTERNAL_3_0);

  // Set the resolution to 12-bit (0..4095)
  analogReadResolution(12); // Can be 8, 10, 12 or 14

  // Let the ADC settle
  delay(1);

  // Get the raw 12-bit, 0..3000mV ADC value
  raw = analogRead(VBAT_PIN);

  // Set the ADC back to the default settings
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  return raw;
}

uint8_t mvToPercent(float mvolts) {
    uint8_t battery_level;

    if (mvolts >= 3000)
    {
        battery_level = 100;
    }
    else if (mvolts > 2900)
    {
        battery_level = 100 - ((3000 - mvolts) * 58) / 100;
    }
    else if (mvolts > 2740)
    {
        battery_level = 42 - ((2900 - mvolts) * 24) / 160;
    }
    else if (mvolts > 2440)
    {
        battery_level = 18 - ((2740 - mvolts) * 12) / 300;
    }
    else if (mvolts > 2100)
    {
        battery_level = 6 - ((2440 - mvolts) * 6) / 340;
    }
    else
    {
        battery_level = 0;
    }

    return battery_level;
}

uint8_t batteryPercentage(void) {

  int runtime = millis(); 
  
  if( (runtime - lastReportTime) > 10000){
    int vbat_raw = readVBAT();
    lastReportedBatteryPercentage = mvToPercent(vbat_raw * MV_PER_LSB);
    lastReportTime = runtime;
    Serial.println(lastReportedBatteryPercentage);
  } 

  return lastReportedBatteryPercentage;
}

int readUSB(void) {
  // Set the analog reference to 3.0V (default = 3.6V)
  // ie. 0 = 0v and max resolution = 3v
  analogReference(AR_INTERNAL_3_0);
  // Set the resolution to 12-bit (0..4095)
  analogReadResolution(12);

  int UsbRawMv = analogRead(USB_PIN) * MV_PER_LSB * 2;      // Used 10k resistors to divide voltage in 2.
  
  // ADC needs to settle - delay for stability
  delay(1);

  // Set ADC back to defaults
  analogReference(AR_DEFAULT);
  analogReadResolution(10);

  return round(UsbRawMv / 10) * 10;
}



