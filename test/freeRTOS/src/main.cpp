#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <DisLib.h>
//#include <Debounce.h>
#include <Button.h>
#include <semphr.h>

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int BUTTON1 = 6;
const int YELLOW_LED = A3;
const int RED_LED = A2;


void vButtonHandler() {
	Serial.println("BUTTON");
}
Button button(BUTTON1, vButtonHandler, NULL);

void vButton2Debounce() {
	while (true) {
		//xSemaphoreTake(sButton2, portMAX_DELAY);
		//bButton.update();
		vTaskDelay(5);
	}
}


void vTest() {
	while (true) {
		Serial.println();
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}



void setup() {
	while (!Serial);
	Serial.println("Init start");
	pinMode(BUTTON1, INPUT_PULLUP);
	pinMode(BUTTON1, INPUT_PULLUP);
	
	
	xTaskCreate(vButton2Debounce, "Button2Debounce", 128, NULL, 1, NULL);
	
	Serial.println("Init done");
}

void loop() {
	// Empty. FreeRTOS tasks handle everything.
}
