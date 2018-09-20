#include "multipleBlocks.h"

void multipleBlocks::setup()
{
	multipleBlockShader.load("defaultShader/defaultShader");
	xPositions.resize(25);
	yPositions.resize(25);
	blockSizes.resize(25 * 25);
	soundAddress.resize(25 * 25);
	for (int i = 0; i < 25; i++) {
		xPositions[i] = i*(ofGetWidth() / 25) + 40.0f;
		yPositions[i] = i*(ofGetHeight() / 25) + 20.0f;
		for (int i2 = 0; i2 < 25; i2++) {
			blockSizes[i + i2 * 25] = 15.f;
			soundAddress[i + i2 * 25] = (int)ofRandom(0, 15);
		}
	}
}

void multipleBlocks::update(bool kick, float * fft)
{
	for (int i = 0; i < 25; i++) {
		for (int i2 = 0; i2 < 25; i2++) {
			if (blockSizes[i + i2 * 25] > 15.f) {
				blockSizes[i + i2 * 25] = blockSizes[i + i2 * 25] - 6.5f;
			}
			if (kick) {
				blockSizes[i + i2 * 25] = blockSizes[i + i2 * 25] + 25.0f;
			}
			if (blockSizes[i + i2 * 25] > 65.f) {
				blockSizes[i + i2 * 25] = 65.f;
			}
			blockSizes[i + i2 * 25] = blockSizes[i + i2 * 25] + fft[soundAddress[i + i2 * 25]]* (soundAddress[i + i2 * 25]+1);
		}
	}
	
	if (kick) {
		currentColor++;
		if (currentColor == 4) {
			currentColor = 0;
		}
	}
	green1 = ofColor(5, 205, 100); 
	green2 = ofColor(0, 235, 180);
	yellow1 = ofColor(255, 255, 0); 
	yellow2 = ofColor(255, 205, 50);
	red1 = ofColor(255, 30, 45);
	red2 = ofColor(230, 15, 15);
	blue1 = ofColor(5, 20, 245); 
	blue2 = ofColor(0, 80, 255);

	switch (currentColor)
	{
	case 0:
		color1 = green2.lerp(green1, (sin(ofGetElapsedTimef()*5.0f) + 1.f) / 2.f);
		color2 = yellow2.lerp(yellow1, (sin(ofGetElapsedTimef()*5.5f) + 1.f) / 2.f);
		break;
	case 1:
		color1 = red1.lerp(red2, (sin(ofGetElapsedTimef()*5.5f) + 1.f) / 2.f);
		color2 = yellow1.lerp(yellow2, (sin(ofGetElapsedTimef()*5.0f) + 1.f) / 2.f);
		break;
	case 2:
		color1 = green1.lerp(green2, (sin(ofGetElapsedTimef()*6.0f) + 1.f) / 2.f);
		color2 = yellow1.lerp(yellow2, (sin(ofGetElapsedTimef()*4.0f) + 1.f) / 2.f);
		break;
	case 3:
		color1 = green1.lerp(green2, (sin(ofGetElapsedTimef()*4.0f) + 1.f) / 2.f);
		color2 = blue1.lerp(blue2, (sin(ofGetElapsedTimef()*6.0f) + 1.f) / 2.f);
		break;
	default:
		break;
	}
}

void multipleBlocks::drawTri(float * fft)
{
	multipleBlockShader.begin();
	multipleBlockShader.setUniform1f("sound", fft[0]);
	multipleBlockShader.setUniform1f("time", ofGetElapsedTimef());
	multipleBlockShader.setUniform4f("inputColor1", color1);
	multipleBlockShader.setUniform4f("inputColor2", color2);
	
	for (int i = 0; i < 25; i++) {
		for (int i2 = 0; i2 < 25; i2++) {
			triDrawEach(xPositions[i], yPositions[i2],blockSizes[i+i2*25]*1.1f, (i + i2 * 25)%2);
		}
	}

	multipleBlockShader.end();
}

void multipleBlocks::drawRect(float * fft)
{
	multipleBlockShader.begin();
	multipleBlockShader.setUniform1f("sound", fft[0]);
	multipleBlockShader.setUniform1f("time", ofGetElapsedTimef());
	multipleBlockShader.setUniform4f("inputColor1", color1);
	multipleBlockShader.setUniform4f("inputColor2", color2);

	for (int i = 0; i < 25; i++) {
		for (int i2 = 0; i2 < 25; i2++) {
			rectDrawEach(xPositions[i], yPositions[i2], blockSizes[i + i2 * 25]);
		}
	}

	multipleBlockShader.end();
}

void multipleBlocks::triDrawEach(float x, float y, float size,int i)
{
	if(i==0){ ofTriangle(x - size / 2, y + size / 2, x, y - size / 2, x + size / 2, y + size / 2); }
	if(i==1){ ofTriangle(x - size / 2, y - size / 2, x, y + size / 2, x + size / 2, y - size / 2); }
	
}

void multipleBlocks::rectDrawEach(float x, float y, float size)
{
	ofRect(x - size / 2, y - size / 2, size, size);
}
