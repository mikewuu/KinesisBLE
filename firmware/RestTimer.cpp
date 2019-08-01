#include "RestTimer.h"

RestTimer::RestTimer(void){

  workIntervalMs = 0.083 * 60 * 1000;  
  shortBreakDurationMs = 0.167 * 60 * 1000;
  longBreakDurationMs = 0.32 * 60 * 1000;

  lastBreakTime = 0;
  lastKeyPressTime = 0;
  breakNumber = 1;
  onBreak = false;
}


void RestTimer::process(unsigned long idleTime) {

  if(onBreak || idleTime == 0) {
    Serial.println("updated last break time");
    lastBreakTime = millis();
  }

  bool backFromBreak = onBreak && idleTime > lastKeyPressTime;

  if(backFromBreak) {
    onBreak = false;
    breakNumber++;
    Serial.println("back from break");
  }

  if(hasTakenBreakForPeriod(idleTime)) {
    Serial.println("taken break");    
    onBreak = true;
    lastKeyPressTime = idleTime;
  }
  
}

bool RestTimer::hasTakenBreak(unsigned long idleTime) {

  bool keepWorking = !shouldTakeBreak(idleTime);

  if(keepWorking || !onBreak) {    
    return false;
  }
  
  if(hasTakenBreakForPeriod(idleTime)) {    
    return true;    
  } else {
    return false;
  }
}

bool RestTimer::shouldTakeBreak(unsigned long idleTime) {
  if(onBreak) {
    return false;
  } else {
    return  idleTime > 0 && idleTime - lastBreakTime > workIntervalMs;
  }    
}

bool RestTimer::hasTakenBreakForPeriod(unsigned long idleTime) {  
  if(isShortBreakPeriod()) {
    return millis() - idleTime > shortBreakDurationMs;
  } else {
    return millis() - idleTime > longBreakDurationMs;
  }
}

bool RestTimer::shouldTakeShortBreak(unsigned long idleTime) {
  return shouldTakeBreak(idleTime)  && RestTimer::isShortBreakPeriod();
}

bool RestTimer::shouldTakeLongBreak(unsigned long idleTime) {
  return shouldTakeBreak(idleTime) && !RestTimer::isShortBreakPeriod();
}

bool RestTimer::isShortBreakPeriod() {
  return breakNumber % 4 != 0;
}
