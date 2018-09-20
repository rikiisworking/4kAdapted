#include "rectMotion.h"

void rectMotion::setup()
{
	currentColor = 0;
	titleElementShader.load("titleElementShader/titleElementShader");
}

void rectMotion::update(float * amp,bool kicked)
{
	if (kicked) {
		currentColor = currentColor == 0 ? 1 : 0;
		for(int i=0;i<5;i++){ particles.push_back(rectMotionParticle(amp[(int)ofRandom(0, 3)])); }
	}
	for (int i = particles.size() - 1; i >= 0; i--) {
		particles[i].update();
		if (!particles[i].isAlive) {
			particles.erase(particles.begin() + i);
		}
	}
}

void rectMotion::draw()
{
	titleElementShader.begin();
	titleElementShader.setUniform1i("currentColor", currentColor);
	for (int i = 0; i < particles.size(); i++) {
		particles[i].draw();
	}
	ofFill();
	titleElementShader.end();
}
