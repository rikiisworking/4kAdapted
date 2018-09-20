#pragma once
#include"ofMain.h"
class rectMotionParticle {
public:
	ofColor rectColor;
	ofPoint pos;
	float rotation, width, height, motionAccel, motionSpeed, maxWidth;
	bool isAlive,expand;
	rectMotionParticle(float pow);
	void update();
	void draw();

};