#include "armReach.h"

void armReach::setup(int xInterval, int yInterval)
{
	wInterval = xInterval;
	hInterval = yInterval;

	xPos.resize(ofGetWidth() / wInterval);
	yPos.resize(ofGetHeight() / hInterval);
	theCase.resize(ofGetWidth() / wInterval * ofGetHeight() / hInterval);

	for (int i = 0; i < ofGetWidth() / wInterval; i++) {
		xPos[i] = i * wInterval + wInterval / 2;
		for (int i2 = 0; i2 < ofGetHeight() / hInterval; i2++) {
			theCase[i + i2*(ofGetHeight() / wInterval)] = (int)(ofRandom(0, 15));
		}
	}
	for (int i = 0; i < ofGetHeight() / hInterval; i++) {
		yPos[i] = i * hInterval + hInterval / 2;
	}

	armReachShader.load("defaultShader/defaultShader");
}

void armReach::update(float* amps,ofVec2f lHand,ofVec2f rHand)
{
	red3 = ofColor(255, 30, 45), red4 = ofColor(230, 15, 15),
		yellow3 = ofColor(255, 255, 0), yellow4 = ofColor(255, 205, 50);
	float tempLdist = ofMap(ofDist(lHand.x,lHand.y,ofGetWidth()/2,ofGetHeight()/2), 0.f, 1101.f, 0.f, 1.0f, true);
	float tempRdist = ofMap(ofDist(rHand.x, rHand.y, ofGetWidth() / 2, ofGetHeight() / 2), 0.f, 1101.f, 0.f, 1.0f, true);

	red3.lerp(yellow3, tempLdist);
	yellow4.lerp(red4, tempRdist);
}

void armReach::draw(float x, float y, float * soundStrength)
{
	armReachShader.begin();

	armReachShader.setUniform1f("sound", soundStrength[0]);
	armReachShader.setUniform1f("time", ofGetElapsedTimef());
	armReachShader.setUniform4f("inputColor1",ofFloatColor(red3));
	armReachShader.setUniform4f("inputColor2", ofFloatColor(yellow4));
	for (int i = 0; i < ofGetWidth() / wInterval; i++) {
		for (int i2 = 0; i2 < ofGetHeight() / hInterval; i2++) {
			drawEach(xPos[i], yPos[i2], -soundStrength[theCase[i + i2*(ofGetHeight() / wInterval)]] * 80, x, y);
		}
	}
	armReachShader.end();
}

void armReach::drawEach(float xPos, float yPos, float segLength, float inputX, float inputY)
{
	float angle = atan2(inputY - yPos, inputX - xPos);
	float segX = xPos + segLength*cos(angle);
	float segY = yPos + segLength*sin(angle);
	ofPolyline temp;
	temp.addVertex(xPos, yPos);
	temp.lineTo(segX, segY);
	ofGetGLRenderer()->draw(temp);
}
