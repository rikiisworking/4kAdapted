#pragma once
#include "ofMain.h"
#include "ofxOsc.h"

#define INPORT 7401
#define NUM_MSG_STRINGS 20

#define HOST "localhost"
#define OUTPORT 7500

class oscEngine {
public:

	ofxOscReceiver receiver;
	ofxOscSender sender;
	string msg_strings[NUM_MSG_STRINGS];

	float ampList[256];
	float smoothed[256];
	int isPlayed;

	void setup();
	void recieve();
	void send(int status, float leftz, float rightz);
	void send(int status, float leftz, float rightz, float headx, float handDist);
};