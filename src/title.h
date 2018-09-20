#pragma once
#include "ofMain.h"

class title {
public:
	float logoPos;
	bool colourSwitch;

	ofTrueTypeFont bold;
	ofTrueTypeFont reg;
	ofImage logoImage;

	ofImage image;
	ofImage logoMask;
	ofShader logoMaskShader;
	ofFbo fbo;

	void setup();

	void draw3(float* sound, bool kicked);
};