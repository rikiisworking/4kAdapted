#include "lineMotionParticle.h"

lineMotionParticle::lineMotionParticle(float * amp)
{
	speed = ofRandom(0.01f, 0.05f);
	accel = ofRandom(0.01f, 0.05f);
	lineWidth = ofRandom(3,6);
	angle = ofRandom(0, 180)*(PI / 180);
	lineLength = 15.0f + amp[(int)ofRandom(0,3)] * 40;

	startingPoint = ofPoint(ofRandom(50, ofGetWidth() - 50), ofRandom(50, ofGetHeight() - 50));
	currentPoint = startingPoint;
	endingPoint = ofPoint(cos(angle)*lineLength, tan(angle)*lineLength);

	isAlive = true;
	isExpanding = true;
	lineColor = (ofColor(0, 80, 255));
	/*
	int temp = (int)ofRandom(0, 3);
	if (temp == 0) { lineColor = (ofColor(5, 20, 245)); }
	else if (temp == 1) { lineColor = (ofColor(239)); }
	else if (temp == 2) { lineColor = (ofColor(239)); }
	else { lineColor = (ofColor(239)); }
	*/
	
}
/*
ofColor pgGreen=ofColor(5, 205, 100);
ofColor pgBlue = ofColor(5, 20, 245);
ofColor pgRed = ofColor(255, 30, 45);
ofColor pgYellow = ofColor(255, 255, 0);
*/
void lineMotionParticle::update()
{
	float xTemp, yTemp;
	if (isExpanding) {
		if (endingPoint.x < currentPoint.x) { currentPoint.x = currentPoint.x - speed; }
		else {currentPoint.x = currentPoint.x + speed;}
		if (endingPoint.y < currentPoint.y) {currentPoint.y = currentPoint.y - speed;}
		else { currentPoint.y = currentPoint.y + speed;}
		speed = speed + accel;
		if (ofDist(currentPoint.x, currentPoint.y, startingPoint.x, startingPoint.y) >= lineLength) {isExpanding = false;}
	}
	else {
		if (startingPoint.x < currentPoint.x) { startingPoint.x = startingPoint.x + speed; }
		else { startingPoint.x = startingPoint.x - speed; }
		if (startingPoint.y < currentPoint.y) { startingPoint.y = startingPoint.y + speed; }
		else { startingPoint.y = startingPoint.y - speed; }
		speed = speed - accel;
		if (speed < 0 || ofDist(currentPoint.x, currentPoint.y, startingPoint.x, startingPoint.y) < 0.1f) { isAlive = false; }
	}
}

void lineMotionParticle::draw()
{
	ofSetLineWidth(lineWidth);
	ofSetColor(lineColor);
	ofLine(currentPoint, startingPoint);
}
