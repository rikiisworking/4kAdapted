#include "shapeExpanding.h"

void shapeExpanding::setup()
{
	for (int i = 0; i < 80; i++) {
		sizes[i] = i*30.0f;
	}
	angle = 0;
	expandSpeed = 3.0f;
	shapeExpandShader.load("bodyParticleShader/bodyParticleShader");
}

void shapeExpanding::update(float * amps,bool kick)
{
	for (int i = 0; i < 80; i++) {
		sizes[i] = sizes[i] + expandSpeed;
		if (sizes[i] > 2400.0f) {
			sizes[i] = 0.f;
		}
	}
	expandSpeed = kick ? expandSpeed + 3.5f : expandSpeed;
	expandSpeed = expandSpeed + amps[25]/5.0f;
	angle = kick ? angle + 1.5f : angle;
	if (expandSpeed > 1.0f) {
		expandSpeed=expandSpeed - 0.3f;
	}
}
void shapeExpanding::drawRect(float * amps)//function for debug
{
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofSetColor(ofColor::white);
	ofNoFill();

		for (int i = 0; i <80; i++) {
			ofPushMatrix();
			ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
			float tempRotation = ofMap(ofDist(ofGetMouseX(),ofGetMouseY(),ofGetWidth()/2,ofGetHeight()/2),0.f,1101.45f,1.f,1.2f,true);
			ofRotate((angle+sizes[i]/5)*tempRotation);
			float tempScale = ofMap(ofDist(ofGetMouseX(), ofGetMouseY(), ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.45f, 1.0f, 1.2f, true);
			ofScale(ofPoint(tempScale, tempScale));
			ofDrawRectangle(0, 0,sizes[i],sizes[i]);
			ofPopMatrix();
		}
	
	
	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
}

void shapeExpanding::drawRectFromPosition(float * amps,ofVec2f lHand,ofVec2f rHand)
{
	shapeExpandShader.begin();
	shapeExpandShader.setUniform1f("time", ofGetElapsedTimef() * 2);
	shapeExpandShader.setUniform1fv("fft", &amps[0], 100);
	ofSetRectMode(OF_RECTMODE_CENTER);
	ofNoFill();

	for (int i = 0; i <80; i++) {
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		float tempRotation = ofMap(ofDist(rHand.x, rHand.y, ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.45f, 1.f, 5.f, true);
		ofRotate((angle + sizes[i] / 5)*tempRotation);
		float tempScale = ofMap(ofDist(lHand.x,lHand.y, ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.45f, 1.f, 6.5f, true);
		ofScale(ofPoint(tempScale, tempScale));
		ofDrawRectangle(0, 0, sizes[i], sizes[i]);
		ofPopMatrix();
	}

	ofSetRectMode(OF_RECTMODE_CORNER);
	ofFill();
	shapeExpandShader.end();
}

void shapeExpanding::drawTriFromPosition(float * amps,ofVec2f lHand,ofVec2f rHand)
{
	shapeExpandShader.begin();
	shapeExpandShader.setUniform1f("time", ofGetElapsedTimef() * 2);
	shapeExpandShader.setUniform1fv("fft", &amps[0], 100);
	ofNoFill();

	for (int i = 0; i <80; i++) {
		ofPushMatrix();
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		float tempRotation = ofMap(ofDist(rHand.x, rHand.y, ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.45f, 1.f, 5.f, true);
		ofRotate((angle + sizes[i] / 5)*tempRotation);
		float tempScale = ofMap(ofDist(lHand.x, lHand.y, ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.45f, 1.f, 6.5f, true);
		ofScale(ofPoint(tempScale, tempScale));
		ofDrawTriangle(0, -sizes[i] *2/5 ,sizes[i] / 2, sizes[i] / 2, -sizes[i] / 2, sizes[i] / 2);
		ofPopMatrix();
	}
	ofFill();
	shapeExpandShader.end();
}

