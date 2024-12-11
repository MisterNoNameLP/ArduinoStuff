#include <Button.h>



Button::Button(uint8_t uiPinId, handlerFunction_t fnHandler, char* caName) {
	_uiPinId = uiPinId;
	_fnHandler = fnHandler;
	_caName = caName;
}

bool Button::bUpdate() {
	return Button::bUpdate(digitalRead(_uiPinId));
}

bool Button::bUpdate(uint8_t uiState) {
	
}