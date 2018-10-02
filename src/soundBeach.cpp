#include "SoundBeach.h"


void soundBeach::drawWaves(float * fft)
{
	ofPushMatrix();

	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofNoFill();
	ofSetLineWidth(3);
	ofSetColor(255, 100, 105);

	ofBeginShape();
	ofVertex(-400 - ofGetWidth() / 2, ofGetWidth() - ofGetHeight() / 2);
	for (int i = 0; i < 256; i++) {
		float v = ofMap(fft[fftAddress[i]], 0.0f, 2.5f, 0.0f, 1.2f, true);
		v = ofClamp(v, 0.0f, 0.2f);
		ofVertex(-800 + (i * 25) - ofGetWidth() / 2, 1000 + 1200 * v - ofGetHeight() / 2);
		ofVertex(-800 + (i * 25) - ofGetWidth() / 2 + 5.0f, 1000 + 1200 * v - ofGetHeight() / 2);
	}
	ofVertex(4020 - ofGetWidth() / 2, ofGetWidth() - ofGetHeight() / 2);
	ofEndShape();

	ofPopMatrix();
}

void soundBeach::updateParticles()
{
	for (std::vector<particle>::iterator it = particles.begin(); it != particles.end(); ++it) {
		it->velocity = it->velocity + it->accel;
		it->position = it->position + it->velocity;
		it->lifeTime = it->lifeTime - 1;
		it->size = it->size - 0.1f;
	}
	for (int i = 0; i < particles.size(); i++) {
		if (!PositionInScreen(particles[i].size, particles[i].position) || particles[i].lifeTime<0) {
			particles.erase(particles.begin() + i);
		}
	}
}

void soundBeach::drawParticles()
{
	for (std::vector<particle>::iterator it = particles.begin(); it != particles.end(); ++it) {
		ofSetColor(it->color);
		if (it->drawMod == 0) { ofDrawCircle(it->position, it->size / 2); }
		else {
			ofPushMatrix();
			ofTranslate(it->position.x, it->position.y);
			ofRotate(ofGetElapsedTimef() * 250);
			ofDrawRectangle(-it->size / 4, -it->size / 4, it->size / 2, it->size / 2);
			ofPopMatrix();
		}

	}
}

void soundBeach::generateParticles()
{
	particles.push_back(
		particle(
		(int)ofRandom(life, life + 50),
			ofRandom(10, 50),
			theColours[(int)ofRandom(0, 10)],
			ofVec2f(ofRandom(-500, ofGetWidth()+500),ofGetHeight()/2),
			ofVec2f(ofRandom(-0.1f, 0.1f), ofRandom(-particleVelocity + 5.0f, -particleVelocity)),
			ofVec2f(0, ofRandom(-2.0f, -0.1f)),
			(int)ofRandom(0, 2)
		)
	);
}

void soundBeach::setup()
{
	for (int i = 4; i < 10; i++) {
		theColours[i] = sceneColor;
	}
	life = 10;
	particleVelocity = 15.0f;

	fftAddress.resize(256);
	for (int i = 0; i < 256; i++) {
		fftAddress[i] = i;
	}
	std::random_shuffle(fftAddress.begin(), fftAddress.end());
	shader.load("defaultShader/defaultShader");
}

void soundBeach::update(bool kick, float * fft)
{
	updateParticles();
	int genPower = (int)ofMap(fft[1], 0.0f, 1.0f, 1,5);

	for (int i = 0; i<genPower; i++) {
		generateParticles();
	}

}

void soundBeach::draw(float * fft)
{
	shader.begin();
	shader.setUniform4f("inputColor1",ofVec4f(1.f,1.f,0.f,1.f ));
	shader.setUniform4f("inputColor2", ofVec4f(0.f,0.92f,0.705f,1.f));

	drawWaves(fft);
	ofFill();
	drawParticles();

	shader.end();
}
void soundBeach::draw2(float * fft, ofVec2f lHand, ofVec2f rHand, ofVec2f head)
{
	shader.begin();
	shader.setUniform4f("inputColor1", ofVec4f(1.f, 1.f, 0.f, 1.f));
	shader.setUniform4f("inputColor2", ofVec4f(0.f, 0.92f, 0.705f, 1.f));

	float scaleRate = ofMap(ofDist(lHand.x, lHand.y, rHand.x, rHand.y),0,ofGetWidth(),0.8f,1.2f,true);
	float movePos = ofMap(head.x, 0, ofGetWidth(), 200.0f, -200.0f, true);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofScale(scaleRate, scaleRate);
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
	ofTranslate(movePos, 0);
	ofPushMatrix();
	ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2);
	ofRotate(lHand.angle(rHand)+10);
	
	ofTranslate(-ofGetWidth() / 2, -ofGetHeight() / 2);
	drawWaves(fft);
	ofFill();
	drawParticles();
	ofPopMatrix();
	
	

	ofPopMatrix();

	shader.end();
}
bool soundBeach::PositionInScreen(float size, ofVec2f pos) {
	bool temp = true;
	if (pos.x<-500-size || pos.x>ofGetWidth() + 500+size || pos.y<-size || pos.y>ofGetHeight() + size) {
		temp = false;
	}return temp;
}