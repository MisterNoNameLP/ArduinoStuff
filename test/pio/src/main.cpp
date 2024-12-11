#include <DisLib.h>

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int YELLOW_LED = A3;
const int RED_LED = A2;

DisLib dislib(TRIG_PIN, ECHO_PIN);

bool state = false;

void inter1() {
	Serial.println("BUTTON1");
	state = !state;
}
void inter2() {
	Serial.println("BUTTON2");
}

void setup() {
	Serial.begin(9600);
	dislib.init();
	
	pinMode(BUTTON1, INPUT_PULLUP);
	pinMode(BUTTON2, INPUT_PULLUP);
	pinMode(YELLOW_LED, OUTPUT);
	pinMode(RED_LED, OUTPUT);
	
	attachInterrupt(digitalPinToInterrupt(BUTTON1), inter1, FALLING);
	attachInterrupt(digitalPinToInterrupt(BUTTON2), inter2, FALLING);
	
	digitalWrite(YELLOW_LED, LOW);
	digitalWrite(RED_LED, HIGH);
}
	
void loop() {
	float distance = 0;
	
	Serial.println("TT");

	distance = dislib.getDistance();
	if (distance < 20) {
		state = false;
	} else {
		state = true;
	}
	
	Serial.println(state);
	
	if (state) {
		digitalWrite(YELLOW_LED, LOW);
		digitalWrite(RED_LED, HIGH);	
	} else {
		digitalWrite(YELLOW_LED, HIGH);
		digitalWrite(RED_LED, LOW);	
	}
	

	Serial.print("Distance: ");
	Serial.println(distance);
	delay(100);
}

