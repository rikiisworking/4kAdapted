#include "arduino.h"

void arduino::setup()
{
	ard.connect("COM7");
	ard.sendAnalogPinReporting(0, ARD_ANALOG);
	isHeadphoneTaken = false;
}

void arduino::update()
{
	if (ard.isArduinoReady()) {
		ard.update();
	}
	if (ard.getAnalog(0) < 631) {
		isHeadphoneTaken = true;
	}
	else {
		isHeadphoneTaken = false;
	}
}
