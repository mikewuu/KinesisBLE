#include "RestTimer.h"

RestTimer::RestTimer(void){

  workIntervalMs = 25 * 60 * 1000;  
  shortBreakDurationMs = 3 * 60 * 1000;
  longBreakDurationMs = 20 * 60 * 1000;
  needsBreak = false;

  lastBreakTime = 0;
  lastKeyPressTime = 0;
  breakNumber = 1;
  onBreak = false;
  needsBreak = false;
}


void RestTimer::process(unsigned long idleTime) {

  bool startingKeyboard = idleTime == 0;
  
  if(startingKeyboard) {
    lastBreakTime = millis();
    return;
  }

  if(shouldTakeBreak()) {
    needsBreak = true;
  }

  if(backFromBreak(idleTime)) {
    onBreak = false;  
    breakNumber++;
  }

  if(onBreak) {
    lastBreakTime = millis();
  }

  if(needsBreak && hasTakenBreakForPeriod(idleTime)) {
    onBreak = true;
    needsBreak = false;
    lastBreakTime = millis();
  }
  
}

bool RestTimer::backFromBreak(unsigned long idleTime) {
  return onBreak && idleTime > lastBreakTime;
}


bool RestTimer::shouldTakeBreak() {
    return !onBreak && millis() - lastBreakTime > workIntervalMs;
}

bool RestTimer::hasTakenBreakForPeriod(unsigned long idleTime) {  
  if(isShortBreakPeriod()) {
    return millis() - idleTime  > shortBreakDurationMs;
  } else {
    return millis() - idleTime > longBreakDurationMs;
  }
}

bool RestTimer::isShortBreakPeriod() {
  return breakNumber % 4 != 0;
}


bool RestTimer::getNeedsBreak() {
  return needsBreak;
}
