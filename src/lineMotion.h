#pragma once
#include "ofMain.h"
#include "lineMotionParticle.h"
class lineMotion {
public:
	void update(float* amp, bool snare);
	void draw();
	vector<lineMotionParticle> lineParticles;
};