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
	inPosition.setup();
	//arduino.setup();
	//-----------------other variables--------------------------
	kicked = false;
	snared = false;
	drawMod = 0;
	isMusicPlaying = false;
}

//--------------------------------------------------------------
void ofApp::update(){

	//arduino.update();
	kicked = soundAnalyzer.getKick();
	snared = soundAnalyzer.getSnare();

	kinectEngine.update();
	oscEngine.recieve();
	soundAnalyzer.update(oscEngine.ampList);
	
	//arduino.update();
	//artwork
	
	if (!kinectEngine.isEmpty &&kinectEngine.isStreamed) {
		
			if (!isMusicPlaying) {
				isMusicPlaying = true;
				oscEngine.send(0, 0.f, 0.f, 960.0f, 400.0f,0,0);
			}
			if (!kinectEngine.inPosition) {
				firework.update2();
				rectMotion.update2();
				inPosition.update(kinectEngine.headZ);
			}
			else {
				//------------------basic body masking---------------------
				auto temp = kinectEngine.kinect.getBodyIndexSource()->getPixels();
				temp.resize(64, 53);
				bodyMasker.update2(&(temp), kinectEngine.trackingId, kicked);
				//---------------------------------------------------------
				if (drawMod == 0) {
					shapeExpand.update(oscEngine.smoothed, kicked);
				}
				else if (drawMod == 1) {
					bodyExpand.update(snared, kicked, bodyMasker.modifiedPath);
				}
				else if (drawMod == 2) {
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
					fallingParticle.update(kicked, ofVec2f(kinectEngine.leftHand.x * 2, kinectEngine.leftHand.y * 2), ofVec2f(kinectEngine.rightHand.x * 2, kinectEngine.rightHand.y * 2), kinectEngine.lHandState, kinectEngine.rHandState,
						kinectEngine.leftHandRelative.z, kinectEngine.rightHandRelative.z);
				}
				else if (drawMod == 8) {

				}
				oscEngine.send(0, kinectEngine.leftHandRelative.z, kinectEngine.rightHandRelative.z, kinectEngine.head.x, ofMap(ofDistSquared(kinectEngine.leftHand.x, kinectEngine.leftHand.y, kinectEngine.rightHand.x, kinectEngine.rightHand.y), 0, 1820, 0, 400), kinectEngine.leftHand.y, kinectEngine.rightHand.y);

			}
			
	}
	else {
		if (isMusicPlaying) {
			isMusicPlaying = false;
			oscEngine.send(1, 0.f, 0.f, 960.0f, 400.0f,0,0);
		}
		firework.update2();
		rectMotion.update2();
		oscEngine.send(1,0.f, 0.f,960.0f, 400.0f,0,0);

	}
	drawMod = oscEngine.isPlayed;
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackgroundGradient(ofColor(0.f,0.f,0.f), ofColor(50.f,50.0f,75.f),OF_GRADIENT_LINEAR);
	
	if (!kinectEngine.isEmpty &&kinectEngine.isStreamed) {
		if (!kinectEngine.inPosition) {
			firework.draw2();
			rectMotion.draw();
			titlePage.draw(inPosition.returnMessage());
			//inPosition.draw();
		}
		else {
			float tempHead = abs(960.0f - kinectEngine.head.x) / 960;
			if (drawMod == 0) {
				shapeExpand.drawRectFromPosition(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
			}
			else if (drawMod == 1) {
				ofSetColor(255);
				bodyExpand.draw(oscEngine.ampList);
			}
			else if (drawMod == 2) {
				singleLine.draw(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
				multipleBodies.draw1(oscEngine.smoothed);
				bodyMasker.draw3(tempHead, oscEngine.smoothed);
			}
			else if (drawMod == 3) {
				float tempHeight = ofMap(oscEngine.smoothed[20], 0.f, 0.6f, 300.f, 2160.f);
				arms.draw2(kinectEngine.head.x * 2, tempHeight, kinectEngine.leftHand, kinectEngine.rightHand, oscEngine.smoothed);
				multipleBodies.draw2(oscEngine.smoothed);
			}
			else if (drawMod == 4) {
				beach.draw2(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
				sand.draw2(kinectEngine.leftHand, kinectEngine.rightHand, kinectEngine.head);
			}
			else if (drawMod == 5) {
				blocks.drawRect2(kinectEngine.leftHand, kinectEngine.rightHand, oscEngine.smoothed);
				multipleBodies.draw3(oscEngine.smoothed, kinectEngine.leftHand, kinectEngine.rightHand);
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
		
	}
	else {
		firework.draw2();
		rectMotion.draw();
		titlePage.draw();
	}
	

	kicked = false;
	snared = false;
}