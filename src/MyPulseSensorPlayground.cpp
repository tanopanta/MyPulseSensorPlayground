/*
   A central Playground object to manage a set of PulseSensors.
*/
#include <MyPulseSensorPlayground.h>

// Define the "this" pointer for the ISR
PulseSensorPlayground *PulseSensorPlayground::OurThis;


PulseSensorPlayground::PulseSensorPlayground(int numberOfSensors) {
  // Save a static pointer to our playground so the ISR can read it.
  OurThis = this;

  // Dynamically create the array to minimize ram usage.
  SensorCount = (byte) numberOfSensors;
  Sensors = new PulseSensor[SensorCount];

}

boolean PulseSensorPlayground::PulseSensorPlayground::begin() {

  for (int i = 0; i < SensorCount; ++i) {
    Sensors[i].initializeLEDs();
  }

  // Note the time, for non-interrupt sampling and for timing statistics.
  NextSampleMicros = micros() + MICROS_PER_READ;

  SawNewSample = false;


  // Lastly, set up and turn on the interrupts.
  if (!PulseSensorPlaygroundSetupInterrupt()) {
     // The user requested interrupts, but they aren't supported. Say so.
    return false;
  }

  return true;
}

void PulseSensorPlayground::analogInput(int inputPin, int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return; // out of range.
  }
  Sensors[sensorIndex].analogInput(inputPin);
}

void PulseSensorPlayground::blinkOnPulse(int blinkPin, int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return; // out of range.
  }
  Sensors[sensorIndex].blinkOnPulse(blinkPin);
}

void PulseSensorPlayground::fadeOnPulse(int fadePin, int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return; // out of range.
  }
  Sensors[sensorIndex].fadeOnPulse(fadePin);
}

boolean PulseSensorPlayground::sawNewSample() {
  /*
     If using interrupts, this function reads and clears the
     'saw a sample' flag that is set by the ISR.

     When not using interrupts, this function sees whether it's time
     to sample and, if so, reads the sample and processes it.
  */
  noInterrupts();
  boolean sawOne = SawNewSample;
  SawNewSample = false;
  interrupts()

  return sawOne;
}


void PulseSensorPlayground::onSampleTime() {
  // Typically called from the ISR.

  /*
     Read the voltage from each PulseSensor.
     We do this separately from processing the voltages
     to minimize jitter in acquiring the signal.
  */
  for (int i = 0; i < SensorCount; ++i) {
    Sensors[i].readNextSample();
  }

  // Process those voltages.
  for (int i = 0; i < SensorCount; ++i) {
    Sensors[i].processLatestSample();
    Sensors[i].updateLEDs();
  }

  // Set the flag that says we've read a sample since the Sketch checked.
  SawNewSample = true;
 }

int PulseSensorPlayground::getLatestSample(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return -1; // out of range.
  }
  return Sensors[sensorIndex].getLatestSample();
}

int PulseSensorPlayground::getBeatsPerMinute(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return -1; // out of range.
  }
  return Sensors[sensorIndex].getBeatsPerMinute();
}

int PulseSensorPlayground::getInterBeatIntervalMs(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return -1; // out of range.
  }
  return Sensors[sensorIndex].getInterBeatIntervalMs();
}

boolean PulseSensorPlayground::sawStartOfBeat(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return false; // out of range.
  }
  return Sensors[sensorIndex].sawStartOfBeat();
}

boolean PulseSensorPlayground::isInsideBeat(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return false; // out of range.
  }
  return Sensors[sensorIndex].isInsideBeat();
}

void PulseSensorPlayground::setThreshold(int threshold, int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return; // out of range.
  }
  Sensors[sensorIndex].setThreshold(threshold);
}


int PulseSensorPlayground::getPulseAmplitude(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return -1; // out of range.
  }
  return Sensors[sensorIndex].getPulseAmplitude();
}

unsigned long PulseSensorPlayground::getLastBeatTime(int sensorIndex) {
  if (sensorIndex != constrain(sensorIndex, 0, SensorCount)) {
    return -1; // out of range.
  }
  return Sensors[sensorIndex].getLastBeatTime();
}

