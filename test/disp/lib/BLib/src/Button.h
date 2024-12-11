#ifndef _BLIB_BUTTON_H_
#define _BLIB_BUTTON_H_

#include <Arduino.h>

constexpr unsigned int DEFAULT_BTN_DEBOUNCE_MILLIS = 10;

typedef void (*handlerFunction_t)(bool bState, string sName);

class Button {
	public:
		Button(int iPinID, handlerFunction_t fHandlerFunction, string sName);
		
		bool update();
		bool update(bool bState);
		
		bool getState();
		void setState();
		
		
		
}

