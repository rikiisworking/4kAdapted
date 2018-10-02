#include "sandParticle.h"

void sandParticle::setup()
{
	particlePosition.reserve(4000);
	velocity.reserve(4000);
	particleSize.reserve(4000);
	for (int i = 0; i < 4000; i++) {
		particlePosition.push_back(ofVec2f(ofRandom(0, ofGetWidth()), (ofRandom(0, ofGetHeight()))));
		velocity.push_back(ofVec2f(0, 0));
		particleSize.push_back(ofRandom(1.0f, 2.5f));
	}
	currentColor = 0;

	sandParticleShader.load("defaultShader/defaultShader");
}

void sandParticle::update(float * fft, bool kicked)
{
	for (int i = 0; i < 4000; i++) {
		if (kicked) {
			particleSize[i] = particleSize[i] + 4.0f;
		}
		particleSize[i] = particleSize[i] + fft[i % 15] * 0.5;

		if (particleSize[i] > 23.0f) {
			particleSize[i] = 17.0f;
		}
		else if (particleSize[i] > 6.5f&& particleSize[i] <= 23.0f) {
			particleSize[i] = particleSize[i] - 3.2f;
		}
		else if (particleSize[i] > 2.f&& particleSize[i]<5.5f) {
			particleSize[i] = particleSize[i] - 1.5f;
		}
		
		particlePosition[i] = particlePosition[i] + velocity[i];
		if (velocity[i].x > 2.5) {
			velocity[i].x = velocity[i].x - 0.3f;
		}
		else if (velocity[i].x<-2.5) {
			velocity[i].x = velocity[i].x + 0.3f;
		}
		else {
			velocity[i].x = ofRandom(-5, 5)*fft[30] * 15;
		}
		if (velocity[i].y > 2.5) {
			velocity[i].y = velocity[i].y - 0.3f;
		}
		else if (velocity[i].y<-2.5) {
			velocity[i].y = velocity[i].y + 0.3f;
		}
		else {
			velocity[i].y = ofRandom(-5, 5)*fft[2] * 1.2;
		}

		if (particlePosition[i].x > ofGetWidth() || particlePosition[i].x < 0) { velocity[i].set(-velocity[i].x, velocity[i].y); }
		if (particlePosition[i].y > ofGetHeight() || particlePosition[i].y < 0) { velocity[i].set(velocity[i].x, -velocity[i].y); }
	}

	if (kicked) { 
		currentColor++;
		if (currentColor == 4) { currentColor = 0; }
	}
	switch (currentColor)
	{
	case 0:
		shaderColor = ofVec3f(0.0f, 0.921f, 0.705f); //green
		shaderColor2 = ofVec3f(0.0f, 0.313f, 1.0f); //blue
		break;
	case 1:
		shaderColor = ofVec3f(0.0f, 0.313f, 1.0f); //blue
		shaderColor2 = ofVec3f(1.0f, 1.0f, 0.0f); //yellow
		break;
	case 2:
		shaderColor = ofVec3f(1.0f, 0.117f, 0.176f); //red
		shaderColor2 = ofVec3f(1.0f, 1.0f, 0.0f); //yellow
		break;
	case 3:
		shaderColor = ofVec3f(1.0f, 1.0f, 0.0f); //yellow
		shaderColor2 = ofVec3f(0.0f, 0.921f, 0.705f); //green
		break;
	default:
		break;
	}
}

void sandParticle::draw()
{
	sandParticleShader.begin();
	sandParticleShader.setUniform1f("time", ofGetElapsedTimef());
	sandParticleShader.setUniform4f("inputColor1", shaderColor);
	sandParticleShader.setUniform4f("inputColor2", shaderColor2);

	ofSetCircleResolution(10);
	for (int i = 0; i < 4000; i++) {
		ofCircle(particlePosition[i], particleSize[i]);
	}
	ofSetCircleResolution(32);
	sandParticleShader.end();
}

void sandParticle::draw2(ofVec2f lHand, ofVec2f rHand, ofVec2f head)
{
	float scaleRate = ofMap(ofDist(lHand.x, lHand.y, rHand.x, rHand.y), 0, 1920.f, 1.0f, 1.75f, true);
	float movePos = ofMap(head.x, 0, 1920, 150.0f, -150.0f, true);

	
	sandParticleShader.begin();
	sandParticleShader.setUniform1f("time", ofGetElapsedTimef());
	sandParticleShader.setUniform4f("inputColor1", shaderColor);
	sandParticleShader.setUniform4f("inputColor2", shaderColor2);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofScale(scaleRate, scaleRate);
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
	ofTranslate(movePos, 0);
	ofSetCircleResolution(10);
	for (int i = 0; i < 4000; i++) {
		ofCircle(particlePosition[i], particleSize[i]);
	}
	
	ofSetCircleResolution(32);
	ofPopMatrix();
	sandParticleShader.end();
	
}
