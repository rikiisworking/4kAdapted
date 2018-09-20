#pragma once
#include "ofMain.h"
#include "rectMotionParticle.h"
class rectMotion {
public:
	void setup();
	void update(float* amp,bool kicked);
	void draw();
	vector<rectMotionParticle> particles;
	int currentColor;
	ofShader titleElementShader;

};