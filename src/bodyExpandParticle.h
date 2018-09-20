#pragma once
#include "ofMain.h"
class bodyExpandParticle {
public:
	ofPath bodyPath;
	bool isAlive;
	float scale, speed, accel;
	ofPoint centerPos;
	ofColor bodyStrokeColor;

	bodyExpandParticle(ofPath path);
	ofMesh generateMesh(ofPath path);
	void update();
	void update(bool kicked);
	void draw();
};