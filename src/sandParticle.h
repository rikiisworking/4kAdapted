#pragma once
#include "ofMain.h"
class sandParticle {
public:
	std::vector<ofVec2f> particlePosition;
	std::vector<ofVec2f> velocity;
	std::vector<float> particleSize;

	void setup();
	void update(float *fft,bool kicked);
	void draw();
	void draw2(ofVec2f lHand, ofVec2f rHand, ofVec2f head);

	int currentColor;
	ofVec3f shaderColor;
	ofVec3f shaderColor2;
	ofShader sandParticleShader;
};