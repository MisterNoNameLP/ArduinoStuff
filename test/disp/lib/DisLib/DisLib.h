#ifndef DisLib_h
#define DisLib_h

#include "Arduino.h"

class DisLib {
	public:
		DisLib(int trigPin, int echoPin);
		void init();
		float getDistance();
	private:
		int _trigPin;
		int _echoPin;
};

#endif