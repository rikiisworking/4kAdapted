#include "singleLine.h"
#include <algorithm>
#include <random>
void singleLine::setup()
{
	for (int i = 0; i < 256; i++) {
		for (int i2 = 0; i2 < 4; i2++) {
			amp[i2].push_back(i+i2*256);
		}
	}
	for (int i2 = 0; i2 < 4; i2++) {
		std::random_shuffle(amp[i2].begin(), amp[i2].end());
	}

	lineShader.load("bodyParticleShader/bodyParticleShader");
}

void singleLine::draw(float * amps,ofVec2f lHand, ofVec2f rHand)
{
	float moveL = ofMap(lHand.y, 0, 1080, -500.0f, 0.0f);
	float moveR = ofMap(rHand.y, 0, 1080, -500.0f, 0.0f);
	for (int i2 = 0; i2 < 4; i2++){
		p[i2].clear();
		p[i2].lineTo(0, 590.0f);
		for (int i = 0; i < 256; i++) {
			i2%2==0? p[i2].lineTo(ofPoint(i*ofGetWidth()/256, -ofClamp(amps[amp[i2][i] - 256 * i2], 0.0f, 1.3f) * 1600 + ofGetHeight())+30.0f+ofPoint(0, -moveL)):
			p[i2].lineTo(ofPoint(i*ofGetWidth() / 256, +ofClamp(amps[amp[i2][i]-256*i2], 0.0f, 1.3f) *1600-60.0f)+ofPoint(0,moveR));
		}
	}
	lineShader.begin();
	lineShader.setUniform1f("time", -ofGetElapsedTimef() / 2);
	lineShader.setUniform1fv("fft", &amps[0], 100);
	for (int i2 = 0; i2 < 4; i2++) {
		p[i2].draw();
	}
	lineShader.end();
}
