#include "Arduino.h"
#include "DisLib.h"

DisLib::DisLib(int trigPin, int echoPin) {
  _trigPin = trigPin;
  _echoPin = echoPin;
}

void DisLib::init() {
  pinMode(_trigPin, OUTPUT);
  pinMode(_echoPin, INPUT);
}

float DisLib::getDistance() {
  float duration;

  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);

  duration = pulseIn(_echoPin, HIGH);
  return (duration*.0343)/2;
}