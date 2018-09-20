#include "particleOnBody.h"

void particleOnBody::setup()
{
	this->number_of_targets = 200;
	for (int i = 0; i < this->number_of_targets; i++) {

		ofVec4f target = ofVec4f(0.0, 0.0, 0.0, 0.0);
		this->targets.push_back(target);

		ofVec4f  color = ofVec4f(1.0, 1.0, 1.0, 0.0);
		int color_type = ofRandom(8);
		switch (color_type) {
		case 0:
			//color = ofVec4f(1.0, 0.0, 0.0, 0.0);
			color = colorToVec4f(blue1);
			break;
		case 1:
			//color = ofVec4f(0.0, 1.0, 0.0, 0.0);
			color = colorToVec4f(blue2);
			break;
		case 2:
			//color = ofVec4f(0.0, 0.0, 1.0, 0.0);
			color = colorToVec4f(green2);
			break;
		case 3:
			//color = ofVec4f(1.0, 1.0, 0.0, 0.0);
			color = colorToVec4f(green1);
			break;
		case 4:
			//color = ofVec4f(0.0, 1.0, 1.0, 0.0);
			color = colorToVec4f(yellow1);
			break;
		case 5:
			//color = ofVec4f(1.0, 0.0, 1.0, 0.0);
			color = colorToVec4f(yellow2);
			break;
		case 6:
			//color = ofVec4f(1.0, 0.0, 1.0, 0.0);
			color = colorToVec4f(red1);
			break;
		case 7:
			//color = ofVec4f(1.0, 0.0, 1.0, 0.0);
			color = colorToVec4f(red2);
			break;
		}
		this->colors.push_back(color);
	}

	this->shader.load("particleOnBodyShader/particleOnBodyShader");
}

void particleOnBody::update(ofPath inputPath)
{
	ofSeedRandom(39);

	ofPath temp = inputPath;
	this->fbo.allocate(ofGetWidth(), ofGetHeight());
	this->fbo.begin();
	ofClear(0);
	ofSetColor(0);
	temp.setFilled(true);
	inputPath.draw();
	this->fbo.end();
	this->fbo.readToPixels(this->pix);
	int i = 0;
	while (i < this->number_of_targets) {

		int x = ofRandom(ofGetWidth());
		int y = ofRandom(ofGetHeight());

		ofColor pix_color = this->pix.getColor(x, y);
		if (pix_color != ofColor(255)) {
			continue;
		}

		float x_increase = ofMap(ofNoise(ofRandom(this->number_of_targets), ofGetFrameNum() * 0.05), 0, 1, -8, 8);
		float y_increase = ofMap(ofNoise(ofRandom(this->number_of_targets), ofGetFrameNum() * 0.05), 0, 1, -8, 8);
		x += x_increase;
		y += y_increase;

		this->targets[i] = ofVec4f(x, y, 0.0, 0.0);
		i++;
	}
}

void particleOnBody::draw()
{
	this->shader.begin();
	this->shader.setUniform1f("time", ofGetElapsedTimef());
	this->shader.setUniform2f("resolution", ofGetWidth(), ofGetHeight());
	this->shader.setUniform4fv("targets", &this->targets[0].x, this->number_of_targets);
	this->shader.setUniform4fv("colors", &this->colors[0].x, this->number_of_targets);
	this->shader.setUniform3f("color2", ofVec3f(0.0f, 0.921f, 0.705f));
	ofRect(0, 0, ofGetWidth(), ofGetHeight());

	this->shader.end();
}

ofVec4f particleOnBody::colorToVec4f(ofFloatColor color)
{
	return ofVec4f(color.r,color.g,color.b,color.a);
}

ofVec4f particleOnBody::colorToVec4f(ofColor color)
{
	ofFloatColor temp = ofColor(color);
	return ofVec4f(temp.r,temp.g,temp.b,temp.a);
}
