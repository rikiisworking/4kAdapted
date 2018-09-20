#pragma once
#include "ofMain.h"
class amebaCircle {
public:
	void setup();
	void update(bool kicked,float* amps);
	void draw();
	void draw2(ofVec2f lHand,ofVec2f rHand,ofVec2f head);

	float noiseVal;
	int radius;
	ofShader shader;
};