#ifndef REST_TIMER_H
#define REST_TIMER_H

#include <bluefruit.h>

class RestTimer {
  
  public:
  
    RestTimer(void);
    void process(unsigned long idleTime);
    bool hasTakenBreak(unsigned long idleTime);
    bool shouldTakeShortBreak(unsigned long idleTime);
    bool shouldTakeLongBreak(unsigned long idleTime);
    
  private:
   
   unsigned long workIntervalMs;
   unsigned long shortBreakDurationMs;
   unsigned long longBreakDurationMs;
   int numShortBreak;
   bool needsShortBreak;
   bool needsLongBreak;
   unsigned long lastBreakTime;
   int breakNumber;
   bool onBreak;
   unsigned long lastKeyPressTime;

   bool hasTakenBreakForPeriod(unsigned long idleTime);
   bool shouldTakeBreak(unsigned long idleTime);
   bool isShortBreakPeriod(void);

};


#endif
