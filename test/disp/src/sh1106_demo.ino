/*
	MIT License

	Copyright (c) 2017-2018, Alexey Dynda

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
/**
 *   Attiny85 PINS (i2c)
 *			 ____
 *   RESET   -|_|  |- 3V
 *   SCL (3) -|	|- (2)
 *   SDA (4) -|	|- (1)
 *   GND	 -|____|- (0)
 *
 *   Attiny SPI PINS:	 connect LCD to D4 (D/C), GND (CS), D3 (RES), D1(DIN), D2(CLK)
 *
 *   Nano/Atmega328 PINS: connect LCD to A4/A5 (i2c)
 *   ESP8266: GPIO4(SDA) / GPIO5( SCL )
 *   STM32: B7(SDA), B6(SCL)
 */

#include "ssd1306.h"
#include "nano_gfx.h"
#include "sova.h"

/*
 * Heart image below is defined directly in flash memory.
 * This reduces SRAM consumption.
 * The image is defined from bottom to top (bits), from left to
 * right (bytes).
 */
const PROGMEM uint8_t heartImage[8] =
{
	0B00001110,
	0B00011111,
	0B00111111,
	0B01111110,
	0B01111110,
	0B00111101,
	0B00011001,
	0B00001110
};

/*
 * Define sprite width. The width can be of any size.
 * But sprite height is always assumed to be 8 pixels
 * (number of bits in single byte).
 */
const int spriteWidth = sizeof(heartImage);

SAppMenu menu;

const char *menuItems[] =
{
	"draw bitmap",
	"sprites",
	"fonts",
	"canvas gfx",
	"draw lines",
};

static void bitmapDemo()
{
	ssd1306_drawBitmap(0, 0, 128, 64, Sova);
	delay(900);
	ssd1306_invertMode();
	delay(1200);
	ssd1306_normalMode();
}

static void spriteDemo()
{
	ssd1306_clearScreen();
	/* Declare variable that represents our sprite */
	SPRITE sprite;
	/* Create sprite at 0,0 position. The function initializes sprite structure. */
	sprite = ssd1306_createSprite( 0, 0, spriteWidth, heartImage );
	for (int i=0; i<250; i++)
	{
		delay(15);
		sprite.x++;
		if (sprite.x >= ssd1306_displayWidth())
		{
			sprite.x = 0;
		}
		sprite.y++;
		if (sprite.y >= ssd1306_displayHeight())
		{
			sprite.y = 0;
		}
		/* Erase sprite on old place. The library knows old position of the sprite. */
		sprite.eraseTrace();
		/* Draw sprite on new place */
		sprite.draw();
	}
}

static void textDemo()
{
	ssd1306_setFixedFont(ssd1306xled_font6x8);
	ssd1306_clearScreen();
	ssd1306_printFixed(0,  8, "Normal text", STYLE_NORMAL);
	ssd1306_printFixed(0, 16, "Bold text", STYLE_BOLD);
	ssd1306_printFixed(0, 24, "Italic text", STYLE_ITALIC);
	ssd1306_negativeMode();
	ssd1306_printFixed(0, 32, "Inverted bold", STYLE_BOLD);
	ssd1306_positiveMode();
	delay(3000);
}

static void canvasDemo()
{
	uint8_t buffer[64*16/8];
	NanoCanvas canvas(64,16, buffer);
	ssd1306_setFixedFont(ssd1306xled_font6x8);
	ssd1306_clearScreen();
	canvas.clear();
	canvas.fillRect(10, 3, 80, 5, 0xFF);
	canvas.blt((ssd1306_displayWidth()-64)/2, 1);
	delay(500);
	canvas.fillRect(50, 1, 60, 15, 0xFF);
	canvas.blt((ssd1306_displayWidth()-64)/2, 1);
	delay(1500);
	canvas.printFixed(20, 1, " DEMO ", STYLE_BOLD );
	canvas.blt((ssd1306_displayWidth()-64)/2, 1);
	delay(3000);
}

static void drawLinesDemo()
{
	ssd1306_clearScreen();
	for (uint8_t y = 0; y < ssd1306_displayHeight(); y += 8)
	{
		ssd1306_drawLine(0,0, ssd1306_displayWidth() -1, y);
	}
	for (uint8_t x = ssd1306_displayWidth() - 1; x > 7; x -= 8)
	{
		ssd1306_drawLine(0,0, x, ssd1306_displayHeight() - 1);
	}
	delay(3000);
}

void setup()
{
	/* Select the font to use with menu and all fobitmapDemont functions */
	ssd1306_setFixedFont(ssd1306xled_font6x8);

	sh1106_128x64_i2c_init();
//	sh1106_128x64_spi_init(3,4,5);	 // Use this line for Atmega328p (3=RST, 4=CE, 5=D/C)
//	sh1106_128x64_spi_init(24, 0, 23); // Use this line for Raspberry  (gpio24=RST, 0=CE, gpio23=D/C)

	ssd1306_clearScreen();
	ssd1306_createMenu( &menu, menuItems, sizeof(menuItems) / sizeof(char *) );
	ssd1306_showMenu( &menu );
}

/*===== LUL =====*/
const int STEP_X = 35;
const int STEP_Y = 20;
const int STEPS_X = 1;
const int STEPS_Y = 2;
	
SPRITE sprites[] = {
	ssd1306_createSprite( STEP_X * 0, STEP_Y * 0, spriteWidth, heartImage ),
	ssd1306_createSprite( STEP_X * 1, STEP_Y * 1, spriteWidth, heartImage ),
	ssd1306_createSprite( STEP_X * 2, STEP_Y * 2, spriteWidth, heartImage ),
	ssd1306_createSprite( STEP_X * 3, STEP_Y * 3, spriteWidth, heartImage )
};

void tollyDemo() {
	//ssd1306_drawBitmap(0, 0, 128, 64, Sova);
	for (auto& sprite : sprites) {
		sprite.x += STEPS_X;
		if (sprite.x >= ssd1306_displayWidth()) {
			sprite.x = 0;
		}
		sprite.y += STEPS_Y;
		if (sprite.y >= ssd1306_displayHeight()) {
			sprite.y = 0;
		}
		sprite.eraseTrace();
		sprite.draw();
	}
	
	delay(100);
}

void loop()
{
	ssd1306_clearScreen();
	while (true) {
		
		tollyDemo();
	}
	delay(1000);
	switch (ssd1306_menuSelection(&menu))
	{
		case 0:
			bitmapDemo();
			break;

		case 1:
			spriteDemo();
			break;

		case 2:
			textDemo();
			break;

		case 3:
			canvasDemo();
			break;

		case 4:
			drawLinesDemo();
			break;

		default:
			break;
	}
	ssd1306_clearScreen( );
	ssd1306_showMenu(&menu);
	delay(500);
	ssd1306_menuDown(&menu);
	ssd1306_updateMenu(&menu);
}
