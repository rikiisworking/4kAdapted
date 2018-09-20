#pragma once
#include "ofMain.h"
#define PI 3.14159265
class lineMotionParticle {
public:
	ofColor lineColor;
	ofPoint startingPoint, currentPoint,endingPoint;
	bool isCurve, isAlive, isExpanding;
	float speed, accel, lineWidth, lineLength, angle;
	lineMotionParticle(float* amp);
	void update();
	void draw();
};