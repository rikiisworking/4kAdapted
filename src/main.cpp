#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){
	ofGLWindowSettings settings;
	settings.setGLVersion(4, 3);
	settings.width = 3840;
	settings.height = 2160;
	settings.windowMode = OF_FULLSCREEN;
	ofCreateWindow(settings);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	//ofSetupOpenGL(1920, 1080, OF_FULLSCREEN);
	ofRunApp(new ofApp());
}
