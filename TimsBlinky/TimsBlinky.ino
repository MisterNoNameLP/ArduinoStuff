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

int state = 0;
bool buttonPressed = false;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(A0, OUTPUT);
  pinMode(A1, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Init done");
}

// the loop function runs over and over again forever
void loop() {
  if (!buttonPressed && !digitalRead(A1)) {
    buttonPressed = true;
    state += 1;
    if (state > 2) {
      state = 0;
    }
  }
  if (digitalRead(A1)) {
    buttonPressed = false;
  }
  
  Serial.println(state);
  Serial.println(buttonPressed);
  if (state == 0) {
    digitalWrite(A0, true);
  } else if (state == 1) {
    digitalWrite(A0, false);
  } else if (state == 2) {
    digitalWrite(A0, false);
    delay(300);
    digitalWrite(A0, true);
    delay(300);
  }
}
