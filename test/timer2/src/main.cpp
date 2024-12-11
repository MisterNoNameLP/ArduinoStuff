#include <Arduino.h>
#include <TimerInterrupt.h>

#define USE_TIMER_1 true

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int YELLOW_LED = A3;
const int RED_LED = A2;

TimerInterrupt ITimer1;

void TimerHandler1(unsigned int outputPin) {
  static bool toggle1 = false;
  digitalWrite(outputPin, toggle1);
  toggle1 = !toggle1;
}

unsigned int outputPin1 = 13; // LED_BUILTIN
#define TIMER1_INTERVAL_MS 10000

void setup() {
  pinMode(YELLOW_LED, OUTPUT);

  ITimer1.init();

  ITimer1.attachInterruptInterval(TIMER1_INTERVAL_MS, TimerHandler1, YELLOW_LED, 0);
}

void loop() {
}
