/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

int RXLED = 17; // The RX LED has a defined Arduino pin
int TXLED = 30; // The TX LED has a defined Arduino pin

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A0, OUTPUT);
  pinMode(TXLED, OUTPUT);
  pinMode(RXLED, OUTPUT);
  pinMode(A1, INPUT_PULLUP);
}

// the loop function runs over and over again forever
void loop() {
  if (!digitalRead(A1)) {
    digitalWrite(A0, HIGH);  // turn the LED on (HIGH is the voltage level)
    digitalWrite(TXLED, HIGH);
    digitalWrite(RXLED, LOW);
    delay(50);                      // wait for a second
    digitalWrite(A0, LOW);   // turn the LED off by making the voltage LOW
    digitalWrite(TXLED, LOW);
    digitalWrite(RXLED, HIGH);
    delay(50);                      // wait for a second
  } else {
    digitalWrite(A0, HIGH);   // turn the LED off by making the voltage LOW
    digitalWrite(TXLED, HIGH);
    digitalWrite(RXLED, HIGH);
  }
}
