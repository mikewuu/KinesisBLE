#ifndef REST_TIMER_H
#define REST_TIMER_H

#include <bluefruit.h>

class RestTimer {
  
  public:
  
    RestTimer(void);
    void process(unsigned long idleTime);
    bool getNeedsBreak(void);
    bool isShortBreakPeriod(void);
    
  private:
   
   unsigned long workIntervalMs;
   unsigned long shortBreakDurationMs;
   unsigned long longBreakDurationMs;
   
   int numShortBreak;

   unsigned long lastBreakTime;
   int breakNumber;
   bool onBreak;
   unsigned long lastKeyPressTime;
   bool needsBreak;

   bool hasTakenBreakForPeriod(unsigned long idleTime);
   bool backFromBreak(unsigned long idleTime);
   bool shouldTakeBreak();

};


#endif
