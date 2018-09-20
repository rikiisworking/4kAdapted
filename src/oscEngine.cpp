#include "oscEngine.h"

void oscEngine::setup()
{
	receiver.setup(INPORT);
	sender.setup(HOST, OUTPORT);
	isPlayed = 0;
	for (int i = 0; i < 256; i++) {
		smoothed[i] = 0.0f;
	}
}

void oscEngine::recieve()
{
	while (receiver.hasWaitingMessages())
	{
		ofxOscMessage m;
		receiver.getNextMessage(m);
		if (m.getAddress() == "list") {
			for (int i = 0; i < m.getNumArgs(); i++) {
				ampList[i] = m.getArgAsFloat(i) / 30;
			}for (int i = 0; i < 256; i++) {
				smoothed[i] *= 0.90;
				smoothed[i] = max(ampList[i], smoothed[i]);
			}
		}
		else if (m.getAddress() == "int") {
			for (int i = 0; i < m.getNumArgs(); i++) {
				isPlayed = m.getArgAsInt(i)-1;
			}
		}
	}
}

void oscEngine::send(int status, float leftz, float rightz)
{
	ofxOscMessage m;
	m.addIntArg(status);
	m.addFloatArg(leftz);
	m.addFloatArg(rightz);
	sender.sendMessage(m, false);
}
void oscEngine::send(int status, float leftz, float rightz, float headx, float handDist)
{
	ofxOscMessage m;
	m.addIntArg(status);
	m.addFloatArg(leftz);
	m.addFloatArg(rightz);
	m.addFloatArg(headx);
	m.addFloatArg(handDist);
	sender.sendMessage(m, false);
}

