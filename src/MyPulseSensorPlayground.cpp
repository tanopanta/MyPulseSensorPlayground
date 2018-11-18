/*
   A central Playground object to manage a set of PulseSensors.
*/
#include <MyPulseSensorPlayground.h>

// Define the "this" pointer for the ISR
PulseSensorPlayground *PulseSensorPlayground::OurThis;


PulseSensorPlayground::PulseSensorPlayground() {
  // Save a static pointer to our playground so the ISR can read it.
  OurThis = this;
  Sensor = new PulseSensor;
}

boolean PulseSensorPlayground::PulseSensorPlayground::begin() {
  Sensor->initializeLEDs();

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

void PulseSensorPlayground::analogInput(int inputPin) {
  Sensor->analogInput(inputPin);
}

void PulseSensorPlayground::blinkOnPulse(int blinkPin) {
  Sensor->blinkOnPulse(blinkPin);
}

void PulseSensorPlayground::fadeOnPulse(int fadePin) {
  Sensor->fadeOnPulse(fadePin);
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
  Sensor->readNextSample();

  Sensor->processLatestSample();
  Sensor->updateLEDs();

  // Set the flag that says we've read a sample since the Sketch checked.
  SawNewSample = true;
 }

int PulseSensorPlayground::getLatestSample() {
  return Sensor->getLatestSample();
}

int PulseSensorPlayground::getBeatsPerMinute() {
  return Sensor->getBeatsPerMinute();
}

int PulseSensorPlayground::getInterBeatIntervalMs() {
  return Sensor->getInterBeatIntervalMs();
}

boolean PulseSensorPlayground::sawStartOfBeat() {
  return Sensor->sawStartOfBeat();
}

boolean PulseSensorPlayground::isInsideBeat() {
  return Sensor->isInsideBeat();
}

void PulseSensorPlayground::setThreshold(int threshold) {
  Sensor->setThreshold(threshold);
}


int PulseSensorPlayground::getPulseAmplitude() {
  return Sensor->getPulseAmplitude();
}

unsigned long PulseSensorPlayground::getLastBeatTime() {
  return Sensor->getLastBeatTime();
}

