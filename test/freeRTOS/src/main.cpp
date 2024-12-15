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

DisLib dislib(TRIG_PIN, ECHO_PIN);
float distance;

SemaphoreHandle_t sButton2;
void vButton2Handler(uint8_t uiState, char* caName) {
	Serial.print("BUTTON1: ");
	Serial.println(uiState);
}
static Button bButton(BUTTON1, vButton2Handler, NULL);


void vButton2Interrupt() {
	xSemaphoreGiveFromISR(sButton2, NULL);
}
void vButton2Debounce() {
	while (true) {
		//xSemaphoreTake(sButton2, portMAX_DELAY);
		//baButtons[0].bUpdate(digitalRead(BUTTON1));
		bButton.bUpdate();
		vTaskDelay(1);
	}
}

void vDebounceHandler() {
	
}


void vTest() {
	while (true) {
		
	}
}

void setup() {
	while (!Serial);
	Serial.println("Init start");
	pinMode(BUTTON1, INPUT_PULLUP);
	pinMode(BUTTON1, INPUT_PULLUP);
	
	
	xTaskCreate(vButton2Debounce, "Button2Debounce", 128, NULL, 1, NULL);
	
	//xTaskCreate(vTest, "Test", 128, NULL, 1, NULL);
	
	
	sButton2 = xSemaphoreCreateBinary();
	if (sButton2 != NULL) {
		attachInterrupt(digitalPinToInterrupt(BUTTON1), vButton2Interrupt, FALLING);
  	}
	Serial.println("Init done");
}

void loop() {
	// Empty. FreeRTOS tasks handle everything.
}
