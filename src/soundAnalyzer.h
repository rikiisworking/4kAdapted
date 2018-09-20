#pragma once

#include "ofMain.h"

#include <iostream>
#include <ctime>
#include <cstdlib>

class soundAnalyzer {
public:
	bool kickSwitch;
	bool snareSwitch;
	double refreshRate;
	double passedTime;

	float previousKick, currentKick;
	float previousSnare, currentSnare;

	void setup(float* fft);

	clock_t time1;
	void update(float* fft);

	bool getKick();
	bool getSnare();
};