#include <Arduino.h>
#include "battery.h"
#include "config.h"

int timeLastBreak = 0;    // Timestamp of end of last break
bool needsBreak = false;

bool restLedOn = false;
int  timeLastRestLedToggle = 0;

/**
 * Let user know that they need to take a break.
 */
void indicateNeedBreak(int now) {

      // Only set LED(s) every so often to give flashing effect.
      if (now - timeLastRestLedToggle < 300) {
          return;
      }
      
      if(restLedOn) {
          setAllBatteryLed(LOW);
          restLedOn = false;
      } else {
          setAllBatteryLed(HIGH);
          restLedOn = true;
      }
      
      timeLastRestLedToggle = now;
}

/**
 * Check if user has taken a break.
 */
bool hasTakenBreak(int now, int lastKeypressTimestamp) {
    return now - lastKeypressTimestamp > REST_INTERVAL_SECS*1000;
}

/**
 * Rest Timer
 */
void process_rest_timer(int lastKeypressTimestamp) {
  
    int now = millis();

    // If we're inactive for more than WORK_TIMEOUT_MINS, assume we're 
    //already on a break.
    if(now - lastKeypressTimestamp > WORK_TIMEOUT_MINS*60*1000) {
      needsBreak = false;
      timeLastBreak = now;
    }

    // If we have been working for longer than our set interval limit
    // we should take a break
    if(now - timeLastBreak > WORK_INTERVAL_MINS*60*1000) {
      needsBreak = true;
    }
  
    if(needsBreak) {
     
        indicateNeedBreak(now);

        if(hasTakenBreak(now, lastKeypressTimestamp)){
          needsBreak = false;
          timeLastBreak = now;
          setAllBatteryLed(LOW);
        }
        
    }
    
}



