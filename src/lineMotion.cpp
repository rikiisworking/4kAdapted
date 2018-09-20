#include "lineMotion.h"

void lineMotion::update(float* amp,bool snare)
{
	if (snare) {
		for (int i = 0; i < 3; i++) {
			lineParticles.push_back(lineMotionParticle(amp));
		}
	}
	for (int i = lineParticles.size() - 1; i >= 0; i--) {
		lineParticles[i].update();
		if (!lineParticles[i].isAlive) {
			lineParticles.erase(lineParticles.begin() + i);
		}
	}
}

void lineMotion::draw()
{
	for (int i = 0; i < lineParticles.size(); i++) {
		lineParticles[i].draw();
	}
	ofSetLineWidth(1);
}
