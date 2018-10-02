#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	//engine setup
	ofHideCursor();
	ofSetFrameRate(60);
	kinectEngine.set();
	oscEngine.setup();
	soundAnalyzer.setup(oscEngine.ampList);

	//artwork setup
	titlePage.setup();
	bodyMasker.set(1);
	firework.setup();
	fallingParticle.setup();
	rectMotion.setup();
	bodyExpand.setup();
	multipleBodies.setup();
	shapeExpand.setup();
	singleLine.setup();
	arms.setup(100,90);
	blocks.setup();
	sand.setup();
	amebaCircle.setup();
	beach.setup();
	endPage.setup();
	//-----------------other variables--------------------------
	kicked = false;
	snared = false;
	drawMod = 0;

	shouldReset = false;
}

//--------------------------------------------------------------
void ofApp::update(){
	kicked = soundAnalyzer.getKick();
	snared = soundAnalyzer.getSnare();

	kinectEngine.update();
	oscEngine.recieve();
	soundAnalyzer.update(oscEngine.ampList);
	//artwork
	
	if (!kinectEngine.isEmpty && kinectEngine.inPosition) {
		
		if (kinectEngine.isStreamed) {
			//------------------basic body masking---------------------
			auto temp = kinectEngine.kinect.getBodyIndexSource()->getPixels();
			temp.resize(64, 53);
			bodyMasker.update2(&(temp),kinectEngine.trackingId,kicked);
			//---------------------------------------------------------
			if (drawMod == 0) {
				shapeExpand.update(oscEngine.smoothed, kicked);
			}
			else if (drawMod == 1) {
				bodyExpand.update(oscEngine.ampList,kicked,bodyMasker.modifiedPath);
			}
			else if (drawMod ==2) {
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 3) {
				arms.update(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 4) {
				sand.update(oscEngine.smoothed, kicked);
				beach.update(kicked, oscEngine.smoothed);
			}
			else if (drawMod == 5) {
				blocks.update(kicked, oscEngine.smoothed);
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 6) {
				amebaCircle.update(kicked, oscEngine.smoothed);
				multipleBodies.update(bodyMasker.basePath);
			}
			else if (drawMod == 7) {
				fallingParticle.update(bodyMasker.modifiedPath.getOutline().at(0), kicked,ofVec2f(kinectEngine.leftHand.x*2,kinectEngine.leftHand.y*2),ofVec2f(kinectEngine.rightHand.x*2,kinectEngine.rightHand.y*2),kinectEngine.lHandState,kinectEngine.rHandState);
			}
			else if (drawMod == 8) {
				if (!shouldReset) {
					shouldReset = true;
				}
			}
			oscEngine.send(0, kinectEngine.leftHandRelative.z, kinectEngine.rightHandRelative.z, kinectEngine.head.x, ofMap(ofDistSquared(kinectEngine.leftHand.x, kinectEngine.leftHand.y, kinectEngine.rightHand.x, kinectEngine.rightHand.y), 0, 1820, 0, 400));
		}
	
	}
	else {
		firework.update2();
		rectMotion.update2();
		oscEngine.send(1,0.f, 0.f,960.0f, 400.0f);
		if (shouldReset) {
			reset();
			shouldReset = false;
		}
	}
	drawMod = oscEngine.isPlayed;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(0.f,0.f,0.f), ofColor(40.f,39.0f,38.f),OF_GRADIENT_LINEAR);
	if (!kinectEngine.isEmpty && kinectEngine.inPosition) {
		float tempHead = abs(960.0f - kinectEngine.head.x) / 960;
		if (drawMod == 0) {
			shapeExpand.drawRectFromPosition(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
		}
		else if (drawMod == 1) {
			ofSetColor(255);
			bodyExpand.draw(oscEngine.ampList);
		}
		else if (drawMod == 2) {
			singleLine.draw(oscEngine.smoothed);
			multipleBodies.draw1(oscEngine.smoothed);
			bodyMasker.draw3(tempHead, oscEngine.smoothed);
		}
		else if (drawMod == 3) {
			float tempHeight = ofMap(oscEngine.smoothed[20], 0.f, 0.6f, 300.f, 2160.f);
			arms.draw2(kinectEngine.head.x * 2, tempHeight,kinectEngine.leftHand,kinectEngine.rightHand,oscEngine.smoothed);
			multipleBodies.draw2(oscEngine.smoothed);
		}
		else if (drawMod == 4) {
			beach.draw2(oscEngine.smoothed,kinectEngine.leftHand,kinectEngine.rightHand,kinectEngine.head);
			sand.draw2(kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
		}
		else if (drawMod == 5) {
			blocks.drawRect2(kinectEngine.leftHand,kinectEngine.rightHand,oscEngine.smoothed);
			multipleBodies.draw3(oscEngine.smoothed);
		}
		else if (drawMod == 6) {
			amebaCircle.draw2(kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
			multipleBodies.draw4(oscEngine.smoothed);
		}
		else if (drawMod == 7) {
			fallingParticle.draw(oscEngine.ampList);
		}
		else if (drawMod == 8) {
			endPage.draw(kicked);
		}
	}
	else {
		firework.draw2();
		rectMotion.draw();
		titlePage.draw();
	}

	kicked = false;
	snared = false;
}

void ofApp::reset()
{
	titlePage.setup();
	bodyMasker.set(1);
	firework.setup();
	fallingParticle.setup();
	rectMotion.setup();
	bodyExpand.setup();
	multipleBodies.setup();
	shapeExpand.setup();
	singleLine.setup();
	arms.setup(100, 90);
	blocks.setup();
	sand.setup();
	amebaCircle.setup();
	beach.setup();
	endPage.setup();
}
