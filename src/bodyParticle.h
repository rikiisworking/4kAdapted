#pragma once
#include "ofMain.h"
class bodyParticle {
public:
	float lifeTime;
	ofColor bodyColor;
	ofPath thePath;

	void update();
	void draw();
	void draw(ofPoint drawPosition);
	bodyParticle(ofPath path, ofColor color = ofColor(239), float life = 50.0f);
};