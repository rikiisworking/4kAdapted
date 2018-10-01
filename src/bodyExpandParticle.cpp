#include "bodyExpandParticle.h"
bodyExpandParticle::bodyExpandParticle(ofPath path)
{
	bodyPath = path;
	bodyPath.setFilled(false);
	isAlive = true;
	scale = 1.0f;
	speed = ofRandom(0.f, 0.000021f);
	accel = ofRandom(0.000001f, 0.0025f);
	centerPos = ofPoint(0.0f, 0.0f);
	bodyStrokeColor = ofColor(239);
}

ofMesh bodyExpandParticle::generateMesh(ofPath path)
{
	ofPolyline templine = path.getOutline().at(0);
	ofMesh tempMesh;
	tempMesh.setMode(OF_PRIMITIVE_LINE_STRIP);
	for (int i = 0; i < templine.size(); i++) {
		ofVec3f n0 = templine.getNormalAtIndex(i);
		ofPoint p0 = templine.getVertices()[i];

		tempMesh.addVertex(p0);
		tempMesh.addIndex(i);
		tempMesh.addNormal(n0);
		tempMesh.addColor(ofFloatColor(1.0, 0, 0, 1.0));

	}
	return tempMesh;
}

void bodyExpandParticle::update()
{
	scale = scale + speed;
	speed = speed + accel;
	//centerPos = ofPoint((128 * 1.2)*(1 - scale)*6.0f, (106 * 1.2)*(1 - scale) * 8.0f);
	if (scale > 8.0f) {
		isAlive = false;
	}
}

void bodyExpandParticle::update(bool kicked)
{
	scale = scale + speed;
	speed = speed + accel;
	if (kicked) {
		speed = speed + 0.085f;
	}
	if (scale > 8.5f) {
		isAlive = false;
	}
}

void bodyExpandParticle::draw()
{
	ofPushMatrix();
	ofTranslate(ofGetWidth()/2, 53*6*3.5);
	ofScale(scale,scale);
	ofTranslate(-ofGetWidth()/2, -53*6*3.5);
	ofGetGLRenderer()->draw(bodyPath,0,-ofGetHeight()/2+53*6+200);
	ofPopMatrix();
}