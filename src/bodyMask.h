#pragma once
#include "ofMain.h"
#include "ofxCv.h"
#include "ofxOpenCv.h"
#include "ofxKinectForWindows2.h"

class bodyMask {
public:
	void set(int i=0);
	void update(ofPixels* bodyPixels, int id);
	void update2(ofPixels* bodyPixels, int id, bool kicked);
	void update(ofPixels* bodyPixels, ofPixels* depthPixels, ofPixels* colorPixels, int id);
	void draw();
	void draw2(float headX);
	void draw3(float headX, float* amp);
	ofPixels returnPixel();
	//variable for body mapping
	ofImage foregroundImg;
	ofImage bodyIndexImg;

	ofxCvGrayscaleImage 	grayImage;
	ofxCvGrayscaleImage 	grayBg;
	ofxCvGrayscaleImage 	grayDiff;
	ofxCvContourFinder		contourFinder;

	ofPath basePath;
	ofPath modifiedPath;

	vector<ofVec2f> colorCoords;

	ICoordinateMapper* coordinateMapper;

	ofShader bodyShader;

	int currentColor;
};