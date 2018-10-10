#pragma once
#include "ofMain.h"

//addon
#include "ofxCv.h"
#include "ofxBox2d.h"
#include "ofxOpenCv.h"

//artwork
#include "bodyMask.h"
#include "particleFirework.h"
#include "fallingParticle.h"
#include "title.h"
#include "lineMotion.h"
#include "rectMotion.h"
#include "bodyExpand.h"
#include "multipleBodies.h"
#include "singleLine.h"
#include "shapeExpanding.h"
#include "armReach.h"
#include "multipleBlocks.h"
#include "sandParticle.h"

#include "amebaCircle.h"
#include "soundBeach.h"

#include "endPage.h"

//engine
#include "kinectEngine.h"
#include "soundAnalyzer.h"
#include "oscEngine.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		kinectEngine kinectEngine;
		oscEngine oscEngine;
		soundAnalyzer soundAnalyzer;

		//bodyMask
		bodyMask bodyMasker;
		
		//artwork
		title titlePage;
		particleFirework firework;
		fallingParticle fallingParticle;
		lineMotion lineMotion;
		rectMotion rectMotion;
		bodyExpand bodyExpand;
		multipleBodies multipleBodies;
		shapeExpanding shapeExpand;
		singleLine singleLine;
		multipleBlocks blocks;
		sandParticle sand;
		armReach arms;
	
		amebaCircle amebaCircle;
		soundBeach beach;
		endPage endPage;



		bool kicked;
		bool snared;

		int drawMod;

		bool isMusicPlaying;

		ofTrueTypeFont font;
};
