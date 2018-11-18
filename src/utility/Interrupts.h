//タイマー割り込みの設定

#ifndef PULSE_SENSOR_INTERRUPTS_H
#define PULSE_SENSOR_INTERRUPTS_H

#include <MyPulseSensorPlayground.h>
#include <Ticker.h>

#define SAMPLE_MS 2     // サンプリング間隔(ミリ秒)

boolean PulseSensorPlaygroundSetupInterrupt();

void ISR();

#endif // PULSE_SENSOR_INTERRUPTS_H
