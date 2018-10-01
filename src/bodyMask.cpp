#include "bodyMask.h"

void bodyMask::set(int i)
{
	currentColor = 0;
	if(i==0){
		grayImage.allocate(128, 106);
		grayBg.allocate(128, 106);
		grayDiff.allocate(128, 106);
		bodyIndexImg.allocate(128, 106, OF_IMAGE_GRAYSCALE);
		bodyShader.load("bodyShader/bodyShader");
	}
	else if (i == 1) {
		grayImage.allocate(64, 53);
		grayBg.allocate(64, 53);
		grayDiff.allocate(64, 53);
		bodyIndexImg.allocate(64, 53, OF_IMAGE_GRAYSCALE);
		bodyShader.load("bodyShader/bodyShader");
	}
}

void bodyMask::update(ofPixels * bodyPixels, int id)
{
	//------------------basic body masking---------------------
	basePath.clear();
	modifiedPath.clear();
	bodyIndexImg.setColor(ofColor::white);
	auto& bodyIndexPix = *bodyPixels;

	for (int y = 0; y < 106; y++) {
		for (int x = 0; x < 128; x++) {
			int index = (y * 128) + x;
			float val = bodyIndexPix[index];
			if (val != id) {
				continue;
			}
			bodyIndexImg.setColor(x, y, ofColor(0));
		}
	}
	bodyIndexImg.update();

	grayImage.setFromPixels(bodyIndexImg.getPixels());
	grayBg.set(255.0f);
	grayDiff.absDiff(grayBg, grayImage);
	contourFinder.findContours(grayDiff, 10, (128 * 106) / 3, 10, true);

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		basePath.moveTo(contourFinder.blobs[i].pts[0]);
		for (int i2 = 0; i2 < contourFinder.blobs[i].nPts; i2++) {
			basePath.lineTo(contourFinder.blobs[i].pts[i2]);
		}
	}
	basePath.setStrokeWidth(1.0f);
	basePath.setFilled(true);
	basePath.simplify(0.2f);
	basePath.close();

	modifiedPath = basePath;
	modifiedPath.setFilled(true);
	ofPushMatrix();
	modifiedPath.simplify(0.2f);
	modifiedPath.scale(6.0,6.0);
	//modifiedPath.translate(ofVec2f(ofGetWidth() / 2 - 64 * 6, ofGetHeight() - 53*2 * 6));
	modifiedPath.translate(ofVec2f(ofGetWidth() / 2 - 64 * 3, ofGetHeight() - 53 * 6));
	ofPopMatrix();
	modifiedPath.close();
}

void bodyMask::update2(ofPixels * bodyPixels, int id,bool kicked)
{
	//------------------basic body masking---------------------
	basePath.clear();
	modifiedPath.clear();
	bodyIndexImg.setColor(ofColor::white);
	auto& bodyIndexPix = *bodyPixels;

	for (int y = 0; y < 53; y++) {
		for (int x = 0; x < 64; x++) {
			int index = (y * 64) + x;
			float val = bodyIndexPix[index];
			if (val != id) {
				continue;
			}
			bodyIndexImg.setColor(x, y, ofColor(0));
		}
	}
	bodyIndexImg.update();

	grayImage.setFromPixels(bodyIndexImg.getPixels());
	grayBg.set(255.0f);
	grayDiff.absDiff(grayBg, grayImage);
	contourFinder.findContours(grayDiff, 10, (64 * 53) / 2, 10, true);

	for (int i = 0; i < contourFinder.nBlobs; i++) {
		basePath.moveTo(contourFinder.blobs[i].pts[0]);
		for (int i2 = 0; i2 < contourFinder.blobs[i].nPts; i2++) {
			basePath.lineTo(contourFinder.blobs[i].pts[i2]);
		}
	}
	basePath.setFilled(false);
	//basePath.simplify(0.2f);
	basePath.close();

	modifiedPath = basePath;
	modifiedPath.setFilled(true);
	ofPushMatrix();
	modifiedPath.simplify(0.2f);
	modifiedPath.scale(24.0f, 24.0f);
	modifiedPath.translate(ofVec2f(ofGetWidth() / 2 - 32 * 24, ofGetHeight() - 53 * 24));
	ofPopMatrix();
	modifiedPath.close();
	if (kicked) {
		currentColor++;
		if (currentColor == 3) {
			currentColor = 0;
		}
	}
}

void bodyMask::update(ofPixels * bodyPixels, ofPixels * depthPixels, ofPixels * colorPixels, int id)
{
	
}

void bodyMask::draw()
{
	ofSetColor(255);
	ofGetGLRenderer()->draw(basePath);
}

void bodyMask::draw2(float headX)
{
	//this->particleShader.setUniform1f("time", ofGetElapsedTimef());
	bodyShader.begin();
	bodyShader.setUniform1f("headX", headX);
	bodyShader.setUniform1i("currentColor", currentColor);
	ofGetGLRenderer()->draw(modifiedPath);
	bodyShader.end();
}

void bodyMask::draw3(float headX, float * amp)
{
	bodyShader.begin();
	bodyShader.setUniform1f("headX", headX);
	bodyShader.setUniform1f("time", ofGetElapsedTimef());
	bodyShader.setUniform1i("currentColor", currentColor);
	bodyShader.setUniform1fv("amps", &amp[0],100);
	ofGetGLRenderer()->draw(modifiedPath);
	bodyShader.end();
}

ofPixels bodyMask::returnPixel()
{
	ofFbo tempFbo;
	ofxCvGrayscaleImage tempImage;
	ofPixels tempPixel;
	tempFbo.allocate(ofGetWidth(), ofGetHeight());
	tempFbo.begin();
	ofClear(0);
	tempImage = grayImage;
	tempImage.scale(16.0, 16.0);
	tempImage.translate(ofGetWidth() / 2 - 32 * 16, ofGetHeight() - 53 * 16);
	tempImage.draw(0, 0);
	tempFbo.end();
	
	tempFbo.readToPixels(tempPixel);
	return tempPixel;
}
