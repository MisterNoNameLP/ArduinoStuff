/* Copyright (c) 2011, Jan Clement
 * licenced under the GPL
 *
 * Author: Jan Clement <jan.clement@audiokits.de>
 * 
 * Example code to demonstrate the use of protothreads 
 * in an arduino sketch. It toggles an LED  using two 
 * independent protothreads. One pt toggles every 
 * 1000ms, the other one every 900ms. The result is an 
 * erratic blinking pattern.
 */

#include <pt.h>   // include protothread library

#define LEDPIN A3  // LEDPIN is a constant 

static struct pt pt1, pt2; // each protothread needs one of these

void setup() {
  pinMode(LEDPIN, OUTPUT); // LED init
  PT_INIT(&pt1);  // initialise the two
  PT_INIT(&pt2);  // protothread variables
}

void toggleLED() {
  bool ledstate = digitalRead(LEDPIN); // get LED state
  ledstate ^= 1;   // toggle LED state using xor
  digitalWrite(LEDPIN, ledstate); // write inversed state back
}

/* This function toggles the LED after 'interval' ms passed */
static int protothread1(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) { // never stop 
    /* each time the function is called the second bool
    *  argument "millis() - timestamp > interval" is re-evaluated
    *  and if false the function exits after that. */
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis(); // take a new timestamp
    toggleLED();
  }
  PT_END(pt);
}
/* exactly the same as the protothread1 function */
static int protothread2(struct pt *pt, int interval) {
  static unsigned long timestamp = 0;
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, millis() - timestamp > interval );
    timestamp = millis();
    toggleLED();
  }
  PT_END(pt);
}

void loop() {
  protothread1(&pt1, 900); // schedule the two protothreads
  protothread2(&pt2, 1000); // by calling them infinitely
}
