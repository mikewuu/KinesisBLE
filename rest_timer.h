#ifndef REST_TIMER_H
#define REST_TIMER_H

extern bool restTimerUsingLeds;

void process_rest_timer(int lastKeypressTimestamp);
void start_break();

#endif //REST_TIMER_H
