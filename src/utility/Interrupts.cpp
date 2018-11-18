#include "Interrupts.h"

hw_timer_t * samplingTimer = NULL;

boolean PulseSensorPlaygroundSetupInterrupt() {
  // This code sets up the sample timer interrupt
  // based on the type of Arduino platform.
    samplingTimer = timerBegin(TIMER0, 80, true);
    timerAttachInterrupt(samplingTimer, &ISR, true);
    timerAlarmWrite(samplingTimer, SAMPLE_PERIOD * 1000, true);
    timerAlarmEnable(samplingTimer);
    return true;
}

void IRAM_ATTR ISR() {
    PulseSensorPlayground::OurThis->onSampleTime();
}