#pragma once
#include "ofMain.h"


class soundBeach {
public:
	ofColor pgGreen = ofColor(5, 205, 100);
	ofColor pgBlue = ofColor(25, 180, 255);
	ofColor pgRed = ofColor(255, 100, 105);
	ofColor pgYellow = ofColor(255, 205, 50);
	ofColor sceneColor = ofColor(239);
	ofColor theColours[10] = { pgGreen, pgBlue, pgRed, pgYellow,sceneColor, };

	typedef struct PARTICLE {
		int lifeTime;
		float size;
		ofColor color;
		ofVec2f position;
		ofVec2f velocity;
		ofVec2f accel;
		int drawMod;
		PARTICLE(int l, float s, ofColor c, ofVec2f p, ofVec2f v, ofVec2f a, int m) :
			lifeTime(l), size(s), color(c), position(p), velocity(v), accel(a), drawMod(m) {}
	} particle;

	vector<int> fftAddress;
	vector<particle> particles;

	int life;
	float particleVelocity;
	

	void drawWaves(float *fft);
	void updateParticles();
	void drawParticles();
	void generateParticles();

	void setup();
	void update(bool kick, float* fft);
	void draw(float * fft);
	void draw2(float* fft, ofVec2f lHand, ofVec2f rHand, ofVec2f head);
	bool PositionInScreen(float size, ofVec2f pos);

	ofShader shader;
};