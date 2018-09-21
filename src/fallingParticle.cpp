#include "fallingParticle.h"

void fallingParticle::setup()
{
	this->box2d.init();
	this->box2d.setGravity(0, 15);
	this->box2d.createBounds();
	this->box2d.setFPS(30.0);
	this->box2d.registerGrabbing();

	this->number_of_targets = 200;

	for (int i = 0; i < this->number_of_targets; i++) {
		this->circles.push_back(shared_ptr<ofxBox2dCircle>(new ofxBox2dCircle));	
		this->circles.back().get()->setPhysics(1.5, 0.75, 0.1);
		this->circles.back().get()->setup(this->box2d.getWorld(), ofRandom(150.0f, ofGetWidth() - 150.0f), ofRandom(ofGetHeight()), ofRandom(7.0f, 21.0f));
		this->sizes.push_back(this->circles.back().get()->getRadius());
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
		this->colors.push_back(color);
		this->lifes.push_back(ofRandom(400, 500));
	}
	this->particleShader.load("particleShader/particleShader");

	currentColor = 0;
}

void fallingParticle::update(ofPolyline line,bool kicked)
{
	this->edgeLine.clear();
	this->edgeLine.addVertexes(line);
	this->edgeLine.setPhysics(0.0, 0.5, 0.5);
	this->edgeLine.create(this->box2d.getWorld());

	if (kicked) {
		currentColor++;
		if (currentColor == 4) {
			currentColor = 0;
		}
	}

	for (int i = 0; i < this->circles.size(); i++) {
		if (kicked) {
			this->circles[i]->addForce(ofVec2f(0, ofRandom(-1.0, -8.0f)), 100.0f);
			/*
			if (this->circles[i]->getPosition().y > ofGetHeight() - 100) {
				this->circles[i]->addForce(ofVec2f(0, ofRandom(-1.0,-8.0f)), 100.0f);
			}
			*/
			if (this->lifes[i] <= 0) {
				this->circles[i]->setPosition(ofRandom(150.0f, ofGetWidth() - 150.0f), 0);
				this->lifes[i] = ofRandom(400.0f, 500.0f);
			}
		}
		if (this->lifes[i] <= 0){ this->circles[i]->setPosition(ofRandom(150.0f, ofGetWidth() - 150.0f), 0); }
		if(this->lifes[i]>0){ this->lifes[i] -= 2.0; }
	}
	this->box2d.update();
}

void fallingParticle::update(ofPolyline line, bool kicked,ofVec2f lHandPos,ofVec2f rHandPos)
{
	this->edgeLine.clear();
	this->edgeLine.addVertexes(line);
	this->edgeLine.setPhysics(0.0, 0.5, 0.5);
	this->edgeLine.create(this->box2d.getWorld());

	for (int i = 0; i < this->circles.size(); i++) {
		if (kicked) {
			this->circles[i]->addRepulsionForce(ofVec2f(ofRandom(0.0f, 1920.0f), ofRandom(0.0f, 1080.0f)), 4.5f);
			if (this->lifes[i] <= 0) {
				if (i % 3 == 0) {this->circles[i]->setPosition(lHandPos.x+ofRandom(-15.0f, 15.0f), lHandPos.y+ofRandom(-15.0f, 15.0f));}
				else if(i%3==1){this->circles[i]->setPosition(rHandPos.x + ofRandom(-15.0f, 15.0f), rHandPos.y + ofRandom(-15.0f, 15.0f));}
				else{ this->circles[i]->setPosition(ofRandom(150.0f, ofGetWidth() - 150.0f), 0); }
				this->lifes[i] = ofRandom(300.0f,400.0f);
			}
		}
		if (this->lifes[i] > 0) {
			this->lifes[i] -= 2.0;
		}
	}
	this->box2d.update();
}

void fallingParticle::draw(float* amps)
{
	vector<ofVec4f> points;
	for (int i = 0; i < this->number_of_targets; i++) {
		ofVec4f p = ofVec4f(this->circles[i]->getPosition().x, this->circles[i]->getPosition().y, 0, 0);
		points.push_back(p);
	}

	this->particleShader.begin();
	this->particleShader.setUniform1fv("lives", &lifes[0], this->number_of_targets);
	this->particleShader.setUniform1fv("sizes", &this->sizes[0], this->number_of_targets);
	this->particleShader.setUniform1f("time", ofGetElapsedTimef());
	this->particleShader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->particleShader.setUniform4fv("targets", &points[0].x, this->number_of_targets);
	this->particleShader.setUniform4fv("colors", &this->colors[0].r, this->number_of_targets);
	this->particleShader.setUniform1fv("amps", &amps[0],this->number_of_targets);
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
