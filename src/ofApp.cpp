#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){	 
    ofSetVerticalSync(true);
    ofEnableDepthTest();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    cam.setDistance(1000);
    //ofSetCircleResolution(64);
    
	// load in sounds:
    //altj.loadSound("sounds/otograph.mp3");
    altj.loadSound("sounds/altj.mp3");
    
    helvetica.loadFont("HelveticaNeue-Bold.ttf", 32);
    helvetica.setLetterSpacing(0.9);
    helvetica.setLineHeight(38.0);

	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 50;
    
    for (int i=0; i< nBandsToGet; i++) {
        depths.push_back(ofRandom(0.0, 300.0));
        xorigins.push_back(ofRandom(-500.0, 480.0));
    }
    
    //altj.play();
    
}


//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
	
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
	for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
    
//	ofRotateX(ofRadToDeg(.5));
//	ofRotateY(ofRadToDeg(-.5));
    
    ofBackground(0);
    
    // floor
//    cam.begin();
//    ofSetColor(255,255,255);
//	ofFill();
//    ofDrawBox(0, -351, 0, 2000, 1, 1000);
//	ofNoFill();
//	ofSetColor(0);
//	//ofDrawBox(30);
//	ofDrawBox(0, -351, 0, 2000, 1, 1000);
//	cam.end();
	
	// draw the fft results:
    ofSetColor(255, 255, 255);
    helvetica.drawString("alt-J\nTessellate", 100,100);
	
	//float width = (float)(10*128) / nBandsToGet;
    float width = ofGetWidth() / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		
		//ofRect(i*width,ofGetHeight(),width,-(fftSmoothed[i] * 200));
        //ofSetColor(255,255,255,(fftSmoothed[i] * 200)/ofGetHeight());
        //ofRect(i*width+5.0,ofGetHeight(),width-5.0,-(fftSmoothed[i] * 200));
        
        cam.begin();
        //ofRotateX(ofRadToDeg(.5));
        //ofRotateY(ofRadToDeg(-.5));
        ofSetColor(255,255,255);
        ofFill();
        // y origin, height and width stay the same, modify depth and x
        float depth = depths.at(i);
        float xorigin = -500 + i*width; // xorigins.at(i); //
        float yorigin = -350 + (fftSmoothed[i] * 500)/2.0;
        float height = -(fftSmoothed[i] * 500);
        ofDrawBox(xorigin, yorigin, depth, width, height, width);
        ofNoFill();
        ofSetColor(0);
        ofDrawBox(xorigin, yorigin, depth, width, height, width);
        cam.end();
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed  (int key){
    altj.play();
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

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

