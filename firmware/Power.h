#ifndef POWER_H
#define POWER_H

#include <bluefruit.h>

class Power {
  
  public:
    Power(void);
    uint8_t batteryRemainingPercentage(void);
    
  private:
    const float MV_PER_LSB = 0.73242188F;
    const float VBAT_DIVIDER = 0.5F;
    const float VBAT_DIVIDER_COMP = 2.0F;
    const uint8_t VBAT_PIN = A6;
    const uint8_t USB_PIN = A7;

    static const int numUsbReadingsForAverage = 30;
    int usbReadings[numUsbReadingsForAverage];
    int readUsbIndex = 0;
    int totalUsbMv = 0;
    int averageUsbMv = 0;

    bool chargingLedOn = false;
    uint32_t chargingAnimationLastToggle = 0;
    uint32_t batteryLedTimer = 0;
    bool batteryLedOn = false;

    int VBATReading(void);
    uint8_t percentageFrom(float mvolts);
    int batteryMv(void);
    bool  usbConnected(void);
    int usbRawVoltage(void);
    int usbAverageVoltage(void);
};


#endif
