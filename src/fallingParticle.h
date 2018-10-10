#pragma once
#include "ofxBox2d.h"
#include "ofMain.h"
class fallingParticle {
public:
	void setup();
	void update(ofPolyline line,bool kicked);
	void update(bool kicked, ofVec2f lHandPos, ofVec2f rHandPos, int lHandState, int rHandState);
	void update(bool kicked, ofVec2f lHandPos, ofVec2f rHandPos, int lHandState, int rHandState,float lz,float rz);
	void draw(float* amps);
	
	ofShader particleShader;

	ofxBox2d box2d;
	
	ofxBox2dCircle circles[200];
	ofFloatColor colors[200];
	float lifes[200];
	float sizes[200];

	int currentColor;
	ofVec3f shaderColor;

};