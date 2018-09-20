#pragma once
#include "ofMain.h"
class singleLine {
public:
	void setup();

	void draw(float * amps);

	vector<int> amp[4];
	ofPolyline p[4];

	ofShader lineShader;
};