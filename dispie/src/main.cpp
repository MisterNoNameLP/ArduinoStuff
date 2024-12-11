#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <DisLib.h>
#include <Debounce.h>
#include <semphr.h>
#include <ssd1306.h>

#include "sova.h"
#include "playerSprite.h"

const int TRIG_PIN = 4;
const int ECHO_PIN = 5;
const int BUTTON1 = 2;
const int BUTTON2 = 3;
const int YELLOW_LED = A3;
const int RED_LED = A2;

DisLib dislib(TRIG_PIN, ECHO_PIN);
float distance;

SPRITE player1 = ssd1306_createSprite(10, 0, sizeof(&PlayerSprite) * 2, PlayerSprite);
//SPRITE player1 = ssd1306_createSprite(3, 0, sizeof(&Sova), Sova);

const int DIST_MULT = 6;
const int DEAD_ZONE = 50;

void vRender() {
	while (true) {
		int iPosY = (int)floor((distance - DEAD_ZONE) / DIST_MULT);
		Serial.println(distance);
		Serial.println(player1.y);
		delay(300 / portTICK_PERIOD_MS);
		
		player1.y = iPosY;
		player1.eraseTrace();
		player1.draw();
	}
}
void vGetDistance() {
	while (true) {
		taskENTER_CRITICAL();
		distance = dislib.getDistance() * 10;
		taskEXIT_CRITICAL();
		vTaskDelay(30 / portTICK_PERIOD_MS);
	}
}
void vTest() {
	while (true) {
		
	}
}



void setup() {
	while (!Serial);
	Serial.println("Init start");
	
	sh1106_128x64_i2c_init();
	ssd1306_clearScreen();
	
	xTaskCreate(vRender, "Render", 128, NULL, 1, NULL);
	xTaskCreate(vGetDistance, "GetDistance", 128, NULL, 1, NULL);
	//xTaskCreate(vTest, "Test", 128, NULL, 1, NULL);
	
	Serial.println("Init done");
}

void loop() {
	// Empty. FreeRTOS tasks handle everything.
}
