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

