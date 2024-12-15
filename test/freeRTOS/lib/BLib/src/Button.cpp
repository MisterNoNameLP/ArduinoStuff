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
	unsigned long currentMillis = millis();
	unsigned int debounceInterval = (uiState == BTN_PRESSED) ? _uiDebouncePushMillis : _uiDebounceReleaseMillis;

	if (uiState != _uiLatestPoll) {
		_uiDebounceStartTime = currentMillis;
		_uiLatestPoll = uiState;
	}
	
	

	if (currentMillis - _uiDebounceStartTime >= debounceInterval) {
		if (_uiStableState != uiState) {
			_uiStableState = uiState;

			if (_fnHandler) {
				_fnHandler(uiState, _caName);
			}

			return true;
		}
	}

	return false;
}