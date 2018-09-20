#include "amebaCircle.h"

void amebaCircle::setup()
{
	shader.load("defaultShader/defaultShader");
	noiseVal = 0.f;
	radius = 650.0f;
}

void amebaCircle::update(bool kicked, float * amps)
{
	noiseVal = ofGetFrameNum() * 0.01;
	if (kicked) {
		noiseVal = noiseVal + 15.0f;
		radius=radius + 150.0f;
	}
	noiseVal = noiseVal + amps[25] * 100.0f;
	if (radius > 650) {
		radius=radius - 4.5f;
	}
	if (radius >1000) {
		radius = 1000.0f;
	}
}

void amebaCircle::draw()
{
	//ofSetColor(239);
	shader.begin();
	shader.setUniform4f("inputColor1", ofFloatColor(ofColor(5, 20, 245)));
	shader.setUniform4f("inputColor2", ofFloatColor(ofColor(0, 235, 180)));
	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 3) {
		int circle_x = radius * cos(deg * DEG_TO_RAD);
		int circle_y = radius * sin(deg * DEG_TO_RAD);

		int noise_radius = radius * ofMap(ofNoise((ofGetWidth()/2 + circle_x) * 0.01, (ofGetHeight()/2 + circle_y) * 0.01 , ofGetFrameNum() * 0.01+noiseVal*0.01)*0.9f,0.f,1.f,0.3f,0.7f);

		circle_x = noise_radius * cos(deg * DEG_TO_RAD);
		circle_y = noise_radius * sin(deg * DEG_TO_RAD);

		ofVertex(ofGetWidth()/2 + circle_x, ofGetHeight()/2 + circle_y);
	}
	ofEndShape(true);
	shader.end();
}

void amebaCircle::draw2(ofVec2f lHand, ofVec2f rHand, ofVec2f head)
{
	float scaleRate = ofMap(ofDist(lHand.x, lHand.y, rHand.x, rHand.y), 0, 1920.f, 0.8f, 3.5f, true);
	float movePos = ofMap(head.x, 0, 1920, 50.0f, -50.0f, true);
	shader.begin();
	shader.setUniform4f("inputColor1", ofFloatColor(ofColor(5, 20, 245)));
	shader.setUniform4f("inputColor2", ofFloatColor(ofColor(0, 235, 180)));
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofScale(scaleRate, scaleRate);
	ofTranslate(movePos, 0);
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
	
	ofBeginShape();
	for (int deg = 0; deg < 360; deg += 3) {
		int circle_x = radius * cos(deg * DEG_TO_RAD);
		int circle_y = radius * sin(deg * DEG_TO_RAD);

		int noise_radius = radius * ofMap(ofNoise((ofGetWidth() / 2 + circle_x) * 0.01, (ofGetHeight() / 2 + circle_y) * 0.01, ofGetFrameNum() * 0.01 + noiseVal*0.01)*0.9f, 0.f, 1.f, 0.3f, 0.7f);

		circle_x = noise_radius * cos(deg * DEG_TO_RAD);
		circle_y = noise_radius * sin(deg * DEG_TO_RAD);

		ofVertex(ofGetWidth() / 2 + circle_x, ofGetHeight() / 2 + circle_y);
	}
	ofEndShape(true);
	ofPopMatrix();
	shader.end();
}
