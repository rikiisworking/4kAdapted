#include "requireInPosition.h"

void requireInPosition::setup()
{
	this->font.load("sd.ttf", 40);

}

void requireInPosition::update(float distInput)
{
	this->dist = distInput;
}

void requireInPosition::draw()
{
	ofSetColor(ofColor::white);
	if (dist > 2.4f) {
		
		//font.drawString("Please, step forward", 1920 - font.stringWidth("Please, step forward")/2, 1480);
	}
	else if (dist < 1.6f) {
		
		//font.drawString("Please, step backward", 1920 - font.stringWidth("Please,step backward")/2, 1480);
	}
}

string requireInPosition::returnMessage()
{
	string temp;
	if (dist > 2.6f) {
		temp= "Please, step forward";
	}
	else if (dist < 1.6f) {
		temp="Please, step backward";
	}
	return temp;
}
