#pragma once
#include "ofMain.h"
#include "ofxKinectForWindows2.h"

class kinectEngine {
public:
	ofxKFW2::Device kinect;

	ofVec2f leftHand, rightHand, head;
	ofVec3f leftHandRelative, rightHandRelative;
	map<JointType, ofVec2f> projectedJoints;

	
	int trackingId;

	void set();
	void update();
	auto getNearestBody(map<int, ofxKinectForWindows2::Data::Body> bodies);

	bool isEmpty;
	bool isStreamed;
	bool inPosition;
	float headZ;
	int lHandState, rHandState;
};