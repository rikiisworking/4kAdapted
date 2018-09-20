#pragma once
#include"ofMain.h"
#include"bodyExpandParticle.h"
class bodyExpand {
public:
	vector<bodyExpandParticle> bodyParticles;
	void setup();
	void update(bool kick, ofPath path);
	void update(float* fft, ofPath path);
	void update(float*fft, bool kicked, ofPath path);
	void draw(float* fft);

	ofShader bodyExpandShader;
};