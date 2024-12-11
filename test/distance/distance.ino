/*
 * HC-SR04 example sketch
 *
 * https://create.arduino.cc/projecthub/Isaac100/getting-started-with-the-hc-sr04-ultrasonic-sensor-036380
 *
 * by Isaac100
 */

#include "DisLib.h"

const int trigPin = 2;
const int echoPin = 3;

const int RXLED = 17; // The RX LED has a defined Arduino pin
const int TXLED = 30; // The TX LED has a defined Arduino pin

DisLib dislib(trigPin, echoPin);

void setup() {
  dislib.init();

  Serial.begin(9600);
}

void loop() {
  float distance = 0;

  distance = dislib.getDistance();

  Serial.print("Distance: ");
  Serial.println(distance);
  delay(100);
}