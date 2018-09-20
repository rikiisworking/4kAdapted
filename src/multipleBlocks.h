#pragma once
#include "ofMain.h"
class multipleBlocks {
public:
	std::vector<float> xPositions;
	std::vector<float> yPositions;
	std::vector<float> blockSizes;
	std::vector<int> soundAddress;
	void setup();
	void update(bool kick, float * fft);
	void drawTri(float * fft);
	void drawRect(float * fft);
	void triDrawEach(float x, float y,float size,int i=0);
	void rectDrawEach(float x, float y, float size);

	ofColor green1=ofColor(5, 205, 100), green2 = ofColor(0, 235, 180),
		yellow1 = ofColor(255, 255, 0), yellow2 = ofColor(255, 205, 50);
	ofColor red1 = ofColor(255, 30, 45), red2 = ofColor(230, 15, 15);
	ofColor blue1 = ofColor(5, 20, 245), blue2 = ofColor(0, 80, 255);
	ofFloatColor color1, color2;

	ofShader multipleBlockShader;
	
	int currentColor;

};