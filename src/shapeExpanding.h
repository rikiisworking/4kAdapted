#pragma once
#include "ofMain.h"
class shapeExpanding {
public:
	void setup();
	void update(float * amps,bool kick);
	
	void drawRect(float* amps);//debug code
	void drawRectFromPosition(float* amps,ofVec2f lHand,ofVec2f rHand);

	void drawTriFromPosition(float* amps,ofVec2f lHand,ofVec2f rHand);


	float sizes[80];
	float angle;
	float expandSpeed;

	ofShader shapeExpandShader;
};