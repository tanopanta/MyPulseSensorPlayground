//タイマー割り込みの設定

#ifndef PULSE_SENSOR_INTERRUPTS_H
#define PULSE_SENSOR_INTERRUPTS_H

#include <MyPulseSensorPlayground.h>

#define TIMER0 0
#define SAMPLE_PERIOD 2     // サンプリング間隔(ミリ秒)

boolean PulseSensorPlaygroundSetupInterrupt();

void IRAM_ATTR ISR();

#endif // PULSE_SENSOR_INTERRUPTS_H
