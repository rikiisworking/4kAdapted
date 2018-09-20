#include "soundAnalyzer.h"

void soundAnalyzer::setup(float * fft)
{
	kickSwitch = false;
	snareSwitch = false;
	refreshRate = 185.0f;
	time1 = clock();
	currentKick = fft[1];
	currentSnare = fft[15];
}


void soundAnalyzer::update(float * fft)
{
	passedTime = (clock() - time1) / (CLOCKS_PER_SEC / 1000);
	if (passedTime > refreshRate) {
		if (!kickSwitch) {
			previousKick = currentKick;
			currentKick = fft[1];
			if (currentKick - previousKick > 1.1f) {
				kickSwitch = true;
			}
		}
		if (!snareSwitch) {
			previousSnare = currentSnare;
			currentSnare = fft[15];
			if (currentSnare - previousSnare > 0.15f) {
				snareSwitch = true;
			}
		}
		time1 = clock();
	}
}

bool soundAnalyzer::getKick()
{
	if (kickSwitch) {
		kickSwitch = false;
		return true;
	}
	else { return false; }
}

bool soundAnalyzer::getSnare()
{
	if (snareSwitch) {
		snareSwitch = false;
		return true;
	}
	else { return false; }
}
