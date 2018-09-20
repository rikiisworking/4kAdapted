#include "kinectEngine.h"
auto kinectEngine::getNearestBody(map<int, ofxKinectForWindows2::Data::Body> bodies)
{
	ofxKinectForWindows2::Data::Body bodyToReturn = bodies.begin()->second;
	for (auto body : bodies) {
		if (ofDistSquared(0.f, 0.f, 0.f,body.second.joints[JointType_SpineMid].getPosition().x, body.second.joints[JointType_SpineMid].getPosition().y, body.second.joints[JointType_SpineMid].getPosition().z)
			< ofDistSquared(0.f, 0.f,0.f, bodyToReturn.joints[JointType_SpineMid].getPosition().x, bodyToReturn.joints[JointType_SpineMid].getPosition().y, bodyToReturn.joints[JointType_SpineMid].getPosition().z)) {
			bodyToReturn = body.second;
		}
	}
	return bodyToReturn;
}

void kinectEngine::set()
{
	ofSetVerticalSync(false);
	kinect.open();
	kinect.initDepthSource();
	kinect.initColorSource();
	kinect.initInfraredSource();
	kinect.initBodySource();
	kinect.initBodyIndexSource();
	isEmpty = true;
	trackingId = 0;
	isStreamed = false;
}

void kinectEngine::update()
{
	if (!kinect.getBodyIndexSource()->getPixels().size()) {if (isStreamed) {isStreamed = false;}}
	else {if (!isStreamed) {isStreamed = true;}}

	map<int, ofxKinectForWindows2::Data::Body> bodiesSortedByAge;
	kinect.update();
	{
		auto bodies = kinect.getBodySource()->getBodies();

		for (auto body : bodies) {if (body.tracked) {bodiesSortedByAge[body.trackingId] = body;}}
		if (!bodiesSortedByAge.empty()) {
			if (isEmpty) {isEmpty = false;}

			auto firstBody = getNearestBody(bodiesSortedByAge);

			trackingId = firstBody.bodyId;
			projectedJoints = kinect.getBodySource()->getProjectedJoints(trackingId);

			leftHand = projectedJoints[JointType_HandLeft];
			rightHand = projectedJoints[JointType_HandRight];
			head = projectedJoints[JointType_Head];
			leftHandRelative = firstBody.joints[JointType_HandLeft].getPosition() - firstBody.joints[JointType_SpineBase].getPosition();
			rightHandRelative = firstBody.joints[JointType_HandRight].getPosition() - firstBody.joints[JointType_SpineBase].getPosition();
	
		}else {if (!isEmpty) { isEmpty = true; }}
	}
}

