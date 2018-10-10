#include "fallingParticle.h"

void fallingParticle::setup()
{


	this->box2d.init();
	this->box2d.setGravity(0, 0);
	this->box2d.createBounds();
	this->box2d.setFPS(30.0);
	this->box2d.registerGrabbing();

	//this->number_of_targets = 200;
	
	for (int i = 0; i < 200; i++) {
		circles[i].setPhysics(1.5, 0.75, 0.9);
		circles[i].setup(this->box2d.getWorld(), ofRandom(100.0f, ofGetWidth() - 100.0f), ofRandom(30, ofGetHeight()), ofRandom(7.0f, 16.0f));
		sizes[i] = circles[i].getRadius();
		ofFloatColor  color = ofFloatColor(1.0, 1.0, 1.0, 0.0);
		int color_type = ofRandom(3);
		switch (color_type) {
		case 0:
			color = ofColor(5, 205, 100);
			break;
		case 1:
			color = ofColor(25, 180, 255);
			break;
		case 2:
			color = ofColor(255, 100, 105);
			break;
		}
		colors[i] = color;
		lifes[i] = ofRandom(300, 500);
	}
	
	this->particleShader.load("particleShader/particleShader");

	currentColor = 0;
}

void fallingParticle::update(ofPolyline line,bool kicked)
{
}

void fallingParticle::update(bool kicked,ofVec2f lHandPos,ofVec2f rHandPos,int lHandState,int rHandState)
{
}

void fallingParticle::update(bool kicked, ofVec2f lHandPos, ofVec2f rHandPos, int lHandState, int rHandState, float lz, float rz)
{

	float scaleRate = ofMap(lz + rz, -1.3f, -0.6f, 3.5f, 0.8f, true);

	if (kicked) {
		currentColor++;
		if (currentColor == 4) {
			currentColor = 0;
		}
	}
	for (int i = 0; i < 200; i++) {
		if (kicked) {
			circles[i].addForce(ofVec2f(0, ofRandom(-1.0, -8.0f)), 40.0f);
		}
		if (i % 2 == 0) {
			float ldis = lHandPos.distance(circles[i].getPosition());
			if (ldis < (lHandState == 2 ? 300 : 75))circles[i].addRepulsionForce(lHandPos, 6.5f);
			else circles[i].addAttractionPoint(lHandPos, 2.5f);
		}
		else {
			float rdis = rHandPos.distance(circles[i].getPosition());
			if (rdis < (rHandState == 2 ? 300 : 75))circles[i].addRepulsionForce(rHandPos, 6.5f);
			else circles[i].addAttractionPoint(rHandPos, 2.5f);
		}
		if (lifes[i] <= 0) {
			circles[i].setPosition(ofRandom(100.0f, ofGetWidth() - 100.0f), 20);
			lifes[i] = ofRandom(400.0f, 500.0f);
		}
		if (lifes[i]>0) { lifes[i] -= 2.0; }
		this->sizes[i] = circles[i].getRadius();
		this->sizes[i] = sizes[i] * scaleRate;
	}
	this->box2d.update();
}

void fallingParticle::draw(float* amps)
{
	vector<ofVec4f> points;
	for (int i = 0; i <200; i++) {
		ofVec4f p = ofVec4f(circles[i].getPosition().x, circles[i].getPosition().y, 0, 0);
		points.push_back(p);
	}

	this->particleShader.begin();
	this->particleShader.setUniform1fv("lives", &lifes[0],200);
	this->particleShader.setUniform1fv("sizes", &this->sizes[0], 200);
	this->particleShader.setUniform1f("time", ofGetElapsedTimef());
	this->particleShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->particleShader.setUniform4fv("targets", &points[0].x, 200);
	this->particleShader.setUniform4fv("colors", &this->colors[0].r,200);
	this->particleShader.setUniform1fv("amps", &amps[0],200);

	switch (currentColor)
	{
	case 0:
		shaderColor = ofVec3f(0.0f, 0.921f, 0.705f); //green
		break;
	case 1:
		shaderColor = ofVec3f(0.0f, 0.313f, 1.0f); //blue
		break;
	case 2:
		shaderColor = ofVec3f(1.0f, 0.117f, 0.176f); //red
		break;
	case 3:
		shaderColor = ofVec3f(1.0f, 1.0f, 0.0f); //yellow
		break;
	default:
		break;
	}
	this->particleShader.setUniform3f("color2", shaderColor);
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	this->particleShader.end();
}