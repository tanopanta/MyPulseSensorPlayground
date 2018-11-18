#include "Interrupts.h"

Ticker samplingTimer;

boolean PulseSensorPlaygroundSetupInterrupt() {
    samplingTimer.attach_ms(SAMPLE_MS, ISR);
    return true;
}

void ISR() {
    PulseSensorPlayground::OurThis->onSampleTime();
}