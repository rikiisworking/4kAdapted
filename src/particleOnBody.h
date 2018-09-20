#pragma once
#include "ofMain.h"
class particleOnBody {
public:
	void setup();
	void update(ofPath inputPath);
	void draw();

	ofVec4f colorToVec4f(ofFloatColor color);
	ofVec4f colorToVec4f(ofColor color);

	ofFbo fbo;
	ofPixels pix;

	ofShader shader;
	int number_of_targets;
	vector<ofVec4f> targets;
	vector<ofVec4f> colors;

	ofColor blue1 = ofColor(5, 20, 245), blue2 = ofColor(0, 80, 255), green1 = ofColor(5, 205, 100), green2 = ofColor(0, 235, 180),
		yellow1 = ofColor(255, 255, 0), yellow2 = ofColor(255, 205, 50),red1 = ofColor(255, 30, 45), red2 = ofColor(230, 15, 15);
};