#include "Power.h"
#include "Led.h"

Power::Power(void){}

int Power::VBATReading(void) {
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

uint8_t Power::percentageFrom(float mvolts) {
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

uint8_t Power::batteryRemainingPercentage(void) {
  int vbat_raw = VBATReading();
  return percentageFrom(vbat_raw * MV_PER_LSB);
}

int Power::usbRawVoltage(void) {
  analogReference(AR_INTERNAL_3_0);
  analogReadResolution(12); 
  int UsbRawMv = analogRead(USB_PIN) * MV_PER_LSB * 2;  // Pair of 10k dividers
  analogReference(AR_DEFAULT);
  analogReadResolution(10);  
  return UsbRawMv;
}

int Power::usbAverageVoltage(void) {

  totalUsbMv = totalUsbMv - usbReadings[readUsbIndex];
  usbReadings[readUsbIndex] = usbRawVoltage();
  totalUsbMv = totalUsbMv + usbReadings[readUsbIndex];
  readUsbIndex += 1;

  bool maxNumReadings = readUsbIndex >= numUsbReadingsForAverage;  
  if(maxNumReadings) {
    readUsbIndex = 0;
  }

  bool notEnoughReadings = totalUsbMv < numUsbReadingsForAverage * 4000;
  if(notEnoughReadings) {
    return 0;
  }
  
  return totalUsbMv / numUsbReadingsForAverage;
}  
