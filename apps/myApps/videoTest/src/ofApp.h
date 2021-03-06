#pragma once

#include "ofMain.h"
#include "ofQTKitPlayer.h"
#include "ofxPostProcessing.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofQTKitPlayer fingerMovie;
    
    bool frameByframe;
    
    ofLight pointLight;
    ofColor diffuseColor;
    ofColor specularColor;
    
    ofSoundStream  soundStream;
    vector <float> left;
    bool  bang;
    float thresh;
    float smoothedVol;
    void audioIn(float * input, int bufferSize, int nChannels);
    void checkBang();
    bool eventFlg;
    
    ofxPostProcessing post;
    
    
};
