#include "title.h"

void title::setup()
{
	logoImage.load("logoWhite.png");
	logoImage.setAnchorPercent(0.5, 0.5);
	bold.load("sennbd.TTF", 28);
	reg.load("senndmit.TTF", 30);
	sd.load("sd.ttf", 30);
	logoPos = 0;

	logoMask.load("logoMask.png");
	logoMask.resize(600.0F, 80.8488F);
	logoMaskShader.load("logoMaskShader/logoMaskShader");
	fbo.allocate(600.0f, 80.8488f);


	
	colourSwitch = false;
}


void title::draw3(float * sound, bool kicked)
{
	ofMesh temp;
	ofColor red1(255,30,45), red2(230,15,15), blue1(5, 20, 245), blue2(0,80,255), green1(5, 205, 100), green2(0,235,180), yellow1(255, 255, 0),yellow2(255,205,50);
	red1.lerp(yellow2, ((sinf(ofGetElapsedTimef()*2.0f + sound[0] / 10)) + 1.0f) / 2);//0~1
	yellow1.lerp(red2, ((sinf(ofGetElapsedTimef()*2.0f + sound[1] / 8)) + 1.0f) / 2);//0~1

	blue1.lerp(green2, ((sinf(ofGetElapsedTimef()*2.0f+sound[0]/10))+1.0f)/2);//0~1
	green1.lerp(blue2, ((sinf(ofGetElapsedTimef()*2.0f+sound[1]/8))+1.0f)/2);//0~1
	if (kicked) {colourSwitch = colourSwitch ? false : true;}

	if (!colourSwitch) {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(green1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(green1));
		temp.draw();
	
		fbo.end();
	}else {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(yellow1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(yellow1));
		temp.draw();

		fbo.end();
	}
	

	ofPixels pixels;
	fbo.readToPixels(pixels);
	image.setFromPixels(pixels);

	logoMaskShader.begin();
	logoMaskShader.setUniformTexture("imageMask", logoMask.getTextureReference(), 1);

	image.draw(ofGetWidth() / 2-210, ofGetHeight() / 2 - 80);
	logoMaskShader.end();

	if (colourSwitch) { ofSetColor(yellow1); }
	else { ofSetColor(blue1); }
	
	reg.drawString("Draw Your Sound", ofGetWidth() / 2 - reg.stringWidth("Draw Your Sound") / 2, ofGetHeight() / 2+40.0f);
}

void title::draw(string s)
{
	ofMesh temp;
	ofColor red1(255, 30, 45), red2(230, 15, 15), blue1(5, 20, 245), blue2(0, 80, 255), green1(5, 205, 100), green2(0, 235, 180), yellow1(255, 255, 0), yellow2(255, 205, 50);
	red1.lerp(yellow2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1
	yellow1.lerp(red2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1

	blue1.lerp(green2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1
	green1.lerp(blue2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1
	if (ofGetFrameNum() % 120 == 0) { colourSwitch = colourSwitch ? false : true; }

	if (!colourSwitch) {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(green1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(green1));
		temp.draw();

		fbo.end();
	}
	else {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(yellow1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(yellow1));
		temp.draw();

		fbo.end();
	}


	ofPixels pixels;
	fbo.readToPixels(pixels);
	image.setFromPixels(pixels);

	logoMaskShader.begin();
	logoMaskShader.setUniformTexture("imageMask", logoMask.getTextureReference(), 1);

	image.draw(ofGetWidth() / 2 - 315, ofGetHeight() / 2 - 120);
	logoMaskShader.end();

	if (colourSwitch) { ofSetColor(yellow1); }
	else { ofSetColor(blue1); }

	reg.drawString("Draw Your Sound", ofGetWidth() / 2 - reg.stringWidth("Draw Your Sound") / 2, ofGetHeight() / 2 + 40.0f);
	sd.drawString(s, ofGetWidth() / 2 - reg.stringWidth(s) / 2, 1380);
}

void title::draw()
{
	ofMesh temp;
	ofColor red1(255, 30, 45), red2(230, 15, 15), blue1(5, 20, 245), blue2(0, 80, 255), green1(5, 205, 100), green2(0, 235, 180), yellow1(255, 255, 0), yellow2(255, 205, 50);
	red1.lerp(yellow2, ((sinf(ofGetElapsedTimef()*2.0f )) + 1.0f) / 2);//0~1
	yellow1.lerp(red2, ((sinf(ofGetElapsedTimef()*2.0f )) + 1.0f) / 2);//0~1

	blue1.lerp(green2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1
	green1.lerp(blue2, ((sinf(ofGetElapsedTimef()*2.0f)) + 1.0f) / 2);//0~1
	if (ofGetFrameNum()%120==0) { colourSwitch = colourSwitch ? false : true; }

	if (!colourSwitch) {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(green1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(blue1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(green1));
		temp.draw();

		fbo.end();
	}
	else {
		fbo.begin();

		temp.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
		temp.addVertex(ofPoint(0.0f, 0.0f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 0.0f));
		temp.addColor(ofColor(yellow1));
		temp.addVertex(ofPoint(0.0f, 80.8488f));
		temp.addColor(ofColor(red1));
		temp.addVertex(ofPoint(600.0f, 80.8488f));
		temp.addColor(ofColor(yellow1));
		temp.draw();

		fbo.end();
	}


	ofPixels pixels;
	fbo.readToPixels(pixels);
	image.setFromPixels(pixels);

	logoMaskShader.begin();
	logoMaskShader.setUniformTexture("imageMask", logoMask.getTextureReference(), 1);

	image.draw(ofGetWidth() / 2 - 315, ofGetHeight() / 2 - 120);
	logoMaskShader.end();

	if (colourSwitch) { ofSetColor(yellow1); }
	else { ofSetColor(blue1); }

	reg.drawString("Draw Your Sound", ofGetWidth() / 2 - reg.stringWidth("Draw Your Sound") / 2, ofGetHeight() / 2 + 40.0f);
}
