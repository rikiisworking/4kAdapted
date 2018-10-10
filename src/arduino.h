#pragma once
#include "ofMain.h"

class arduino {
public:
	void setup();
	void update();

	bool isHeadphoneTaken;
	ofArduino ard;
	

};