/*
   A central Playground object to manage a set of PulseSensors.
   See https://www.pulsesensor.com to get started.
*/
#ifndef MY_PULSE_SENSOR_PLAYGROUND_H
#define MY_PULSE_SENSOR_PLAYGROUND_H

#include <M5Stack.h>

#include "utility/PulseSensor.h"

class PulseSensorPlayground {
  public:
    /*
       The number of microseconds per sample of data from the PulseSensor.
       1 millisecond is 1,000 microseconds.

       Refer to this value as PulseSensorPlayground::MICROS_PER_READ
    */
    static const unsigned long MICROS_PER_READ = (2 * 1000L); // usecs per sample.

    //---------- PulseSensor Manager functions

    PulseSensorPlayground();

    /*
       Start reading and processing data from the PulseSensors.

       Your Sketch should make all necessary PulseSensor configuration calls
       before calling begin().
    */
    boolean begin();

    //---------- Per-PulseSensor functions

    /*
       By default, the Playground assumes the PulseSensor is connected to A0.
       If your PulseSensor is connected to a different analog input pin,
       call pulse.analogInput(pin) or pulse.analogInput(pin, sensorIndex).

       inputPin = the analog input this PulseSensor is connected to.
    */
    void analogInput(int inputPin);


    /*
       beep
    */
    void beepOnPulse(int paintPin);

    /*
       (Internal to library - do not call from a Sketch)
       Perform all the processing necessary when it's time to
       read from all the PulseSensors and process their signals.
    */

    void onSampleTime();
    /*
       Returns the most recently read analog value from the given PulseSensor
       (range: 0..1023).

       sensorIndex = optional, index (0..numberOfSensors - 1)
         of the PulseSensor of interest.
    */
    int getLatestSample();

    /*
       Returns the latest beats-per-minute measure for the given PulseSensor.

       The internal beats-per-minute measure is updated per-PulseSensor,
       when a beat is detected from that PulseSensor.

       sensorIndex = optional, index (0..numberOfSensors - 1)
         of the PulseSensor of interest.
    */
    int getBeatsPerMinute();

    /*
       Returns the latest IBI (inter-beat interval, in milliseconds) measure
       for the given PulseSensor.

       The internal IBI measure is updated per-PulseSensor,
       when a beat is detected from that PulseSensor.

       sensorIndex = optional, index (0..numberOfSensors - 1)
         of the PulseSensor of interest.
    */
    int getInterBeatIntervalMs();

    /*
       Returns true if a new heartbeat (pulse) has been detected
       from the given PulseSensor since the last call to sawStartOfBeat()
       on this PulseSensor.

       Typical use in loop():
         if (pulse.sawStartOfBeat()) {
           ...do what you want to do per-heartbeat.
         }

       sensorIndex = optional, index (0..numberOfSensors - 1)
         of the PulseSensor of interest.
    */
    boolean sawStartOfBeat();

    /*
       Returns true if the given PulseSensor signal is currently
       inside a heartbeat. That is, returns true if the signal is above
       the automatically-set threshold of a beat, false otherwise.

       Typical use in loop():
         if (pulse.isInsideBeat()) {
           ...do what you want while in the beat.
         } else {
           ...do what you want while between beats.
         }

       sensorIndex = optional, index (0..numberOfSensors - 1)
         of the PulseSensor of interest.
    */
    boolean isInsideBeat();

    /*
       By default, the threshold value is 530.
       threshold is used to find the heartbeat
       adjust this value up in the setup function to avoid noise.
    */
    void setThreshold(int threshold);

    /*
        Returns the current amplitude of the pulse waveform.
    */
    int getPulseAmplitude();

    /*
       Returns the sample number when the last beat was found. 2mS resolution.
    */
    unsigned long getLastBeatTime();

    // (internal to the library) "this" pointer for the ISR.
    static PulseSensorPlayground *OurThis;

  private:

    void setupInterrupt();

    PulseSensor *  Sensor;          // use Sensor to access a sensor.
    volatile unsigned long NextSampleMicros; // Desired time to sample next.
};

/*
   We include interrupts.h here instead of above
   because it depends on variables and functions we declare (vs. define)
   in PulseSensorPlayground.h.
*/
#include "utility/Interrupts.h"

#endif // PULSE_SENSOR_PLAYGROUND_H
