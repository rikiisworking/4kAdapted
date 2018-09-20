#pragma once
#include "ofMain.h"
class armReach {
public:
	void setup(int xInterval=35,int yInterval=25);
	void update(float* amps, ofVec2f lHand,ofVec2f rHand);
	void draw(float x, float y, float * soundStrength);
	void drawEach(float xPos, float yPos, float segLength, float inputX, float inputY);

	ofFloatColor color1, color2;

	int wInterval, hInterval;

	std::vector<float> xPos;
	std::vector<float> yPos;
	std::vector<int> theCase;

	ofShader armReachShader;

	ofColor red3=ofColor(255, 30, 45), red4 = ofColor(230, 15, 15),
		yellow3 = ofColor(255, 255, 0), yellow4 = ofColor(255, 205, 50);
};