#pragma once
#include "ofMain.h"
#include "typo.h"
#include "typo2.h"
#include "typo3.h"

class endPage {
public:
	typo typo1;
	void setup();
	void draw(bool kicked);

	ofShader shader;
	ofFloatColor shaderColor1, shaderColor2;
};