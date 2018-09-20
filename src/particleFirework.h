#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"

class particleFirework {
public:
	void setup();
	void update();
	void draw();
	void kicked(bool kicked);

	ofxBox2d box2d;
	vector<shared_ptr<ofxBox2dCircle>> circles;
	vector<float> circles_life;

	ofShader titleElementShader;
	int currentColor;
};