#pragma once
#include "ofMain.h"

class typo {
public:
	void setup();
	void update();
	void draw();
	vector<char> charactors;

	ofTrueTypeFont font;
	int font_size;

};