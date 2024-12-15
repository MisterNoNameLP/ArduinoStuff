#ifndef _BLIB_BUTTON_H_
#define _BLIB_BUTTON_H_

#include <Arduino.h>


constexpr unsigned int BTN_DEBOUNCE_PUSH_MILLIS = 10;
constexpr unsigned int BTN_DEBOUNCE_RELEASE_MILLIS = 10;
constexpr uint8_t BTN_PRESSED = 0;
constexpr uint8_t BTN_OPEN = 1;

typedef void (*handlerFunction_t)(uint8_t bState, char* caName);

class Button {
	public:
		Button();
		Button(uint8_t uiPinId, handlerFunction_t fnHandler, char* caName);
		
		bool bUpdate();
		bool bUpdate(uint8_t uiState);
		bool bGetState() {return _uiStableState == 1;};
		
		void vSetHandlerFunction(handlerFunction_t fnHandler) {_fnHandler = fnHandler;};
		handlerFunction_t fnGetHandlerFunction() {return _fnHandler;};
		
		void vSetName(char* caName) {_caName = caName;};
		char* caGetName() {return _caName;};
		
		void vSetPushDebouceInterval(unsigned int uiNewDebounceInterval) {_uiDebouncePushMillis = uiNewDebounceInterval;};
		void vSetReleaseDebouceInterval(unsigned int uiNewDebounceInterval) {_uiDebounceReleaseMillis = uiNewDebounceInterval;};
		unsigned int uiGetPushDebouceInterval() {return _uiDebouncePushMillis;};
		unsigned int uiGetReleaseDebouceInterval() {return _uiDebounceReleaseMillis;};
		
	
	private:
		char* _caName;
		uint8_t _uiPinId;
		
		uint8_t _uiLatestPoll = BTN_OPEN;
		uint8_t _uiStableState = BTN_OPEN;
		
		unsigned int _uiDebouncePushMillis = BTN_DEBOUNCE_PUSH_MILLIS;
		unsigned int _uiDebounceReleaseMillis = BTN_DEBOUNCE_RELEASE_MILLIS;
		
		unsigned long int _uiDebounceStartTime;
		handlerFunction_t _fnHandler;
		
};

#endif