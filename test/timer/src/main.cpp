#include <Arduino.h>
#include <avr/interrupt.h>  // For ISR definitions

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int YELLOW_LED = A3;
const int RED_LED = A2;

void setup() {
  pinMode(YELLOW_LED, OUTPUT);  // Set the built-in LED pin as output

  cli();  // Disable global interrupts

  // Configure Timer1 for CTC mode
  TCCR1A = 0;  // Normal mode, no output compare
  TCCR1B = 0;  // Clear all bits

  TCCR1B |= (1 << WGM12);  // CTC mode (Clear Timer on Compare Match)

  // Set the compare match value for 1 second interval
  // Formula: OCR1A = (Clock Speed / (Prescaler * Target Frequency)) - 1
  // For 16MHz clock, prescaler of 1024, and 1Hz target:
  OCR1A = 15624;

  // Set prescaler to 1024
  TCCR1B |= (1 << CS12) | (1 << CS10);

  // Enable Timer1 Compare Match A interrupt
  TIMSK1 |= (1 << OCIE1A);

  sei();  // Enable global interrupts
}
	
ISR(TIMER1_COMPA_vect) {
  // Interrupt Service Routine triggered every 1 second
  digitalWrite(YELLOW_LED, !digitalRead(YELLOW_LED));  // Toggle the LED
}

void loop() {
  // The main loop is free for other tasks
}

