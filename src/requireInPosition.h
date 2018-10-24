#pragma once
#include "ofMain.h"
class requireInPosition {
public:
	ofTrueTypeFont font;
	float dist;
	void setup();
	void update(float distInput);
	void draw();
	string returnMessage();

};