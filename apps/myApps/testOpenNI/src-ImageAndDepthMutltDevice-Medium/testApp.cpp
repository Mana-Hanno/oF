#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

    ofSetLogLevel(OF_LOG_NOTICE);

    numDevices = openNIDevices[0].getNumDevices();

    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        //openNIDevices[deviceID].setLogLevel(OF_LOG_VERBOSE);
        openNIDevices[deviceID].setup();
        openNIDevices[deviceID].addDepthGenerator();
        openNIDevices[deviceID].addImageGenerator();
        openNIDevices[deviceID].setRegister(true); // this registers all the image pixels to the depth pixels
        openNIDevices[deviceID].setMirror(true); // flips the image and depth sensors
		openNIDevices[deviceID].start();
    }

    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        openNIDevices[deviceID].update();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetColor(255, 255, 255);

    ofPushMatrix();

    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        ofTranslate(0, deviceID * 480);
        openNIDevices[deviceID].drawDebug(); // draws all generators
        //openNIDevices[deviceID].drawDepth(0, 0);
        //openNIDevices[deviceID].drawImage(640, 0);
    }

    ofPopMatrix();

	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate());
	verdana.drawString(msg, 20, numDevices * 480 - 20);
}

//--------------------------------------------------------------
void ofApp::exit(){
    for (int deviceID = 0; deviceID < numDevices; deviceID++){
        openNIDevices[deviceID].stop();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case 't':
            for (int deviceID = 0; deviceID < numDevices; deviceID++){
                openNIDevices[deviceID].toggleRegister();
            }
            break;
        case 'x':
            for (int deviceID = 0; deviceID < numDevices; deviceID++){
                openNIDevices[deviceID].stop();
            }
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}
