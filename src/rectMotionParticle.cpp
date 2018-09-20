#include "rectMotionParticle.h"

rectMotionParticle::rectMotionParticle(float pow)
{
	rotation = ofRandom(0.0f,180.0f);
	width = 5;
	height = ofRandom(10.0f/pow, 15.0f/pow);
	motionAccel = ofRandom(0.075f, 0.105f);
	motionSpeed = ofRandom(0.045f, 0.065f);
	maxWidth = ofRandom(10+ pow * 50,10+pow*85);
	pos = ofPoint(ofRandom(30, ofGetWidth() - 30), ofRandom(30, ofGetHeight() - 30));
	isAlive = true;
	expand = true;

}

void rectMotionParticle::update()
{
	if (expand) {
		width = width + motionSpeed;
		motionSpeed = motionSpeed + motionAccel;
		if (width >= maxWidth) {
			expand = false;
		}
	}
	else {
		width = width - motionSpeed;
		motionSpeed = motionSpeed - motionAccel;
		if (motionSpeed <= 0 || width <= 0) {
			isAlive = false;
		}
	}
}

void rectMotionParticle::draw()
{
	ofFill();
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofPushMatrix();
	ofTranslate(pos.x,pos.y);
	ofRotateZ(rotation);
	ofRect(0, 0, width, height);
	ofPopMatrix();
	ofSetRectMode(OF_RECTMODE_CORNER);
}
