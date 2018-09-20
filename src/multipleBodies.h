#pragma once
#include "ofMain.h"
class multipleBodies {
	public:
		void setup();
		void update(ofPath bodyPath);
		void draw1(float* amps);
		void draw2(float* amps);
		void draw3(float* amps);
		void draw4(float* amps);
		float addedSize;
		vector<ofPath> bodyDelayPath;
	
		void shaderBegin(ofColor color1, ofColor color2, ofColor color3, ofColor color4,float* amps);
		void shaderEnd();

		ofShader multipleBodyShader;
		
};