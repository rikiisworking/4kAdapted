#pragma once
#include "ofxBox2d.h"
#include "ofMain.h"
class fallingParticle {
public:
	void setup();
	void update(ofPolyline line,bool kicked);
	void update(ofPolyline line, bool kicked, ofVec2f lHandPos, ofVec2f rHandPos);
	void draw(float* amps);

	ofShader particleShader;

	ofxBox2d box2d;
	ofxBox2dEdge  edgeLine;
	vector<shared_ptr<ofxBox2dCircle>> circles;
	vector<ofFloatColor> colors;
	vector<float> lifes;
	vector<float> sizes;
	int number_of_targets;

	int currentColor;
	ofVec3f shaderColor;
	//ofVec3f currentColor;
};