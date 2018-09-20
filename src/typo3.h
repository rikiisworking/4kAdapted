#pragma once
#include "ofMain.h"
class typo3 {
public:
	ofTrueTypeFont font;
	int font_size;
	vector<char> charactors;
	void setup();
	void draw();
};