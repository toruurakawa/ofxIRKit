#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetLogLevel(OF_LOG_VERBOSE);

    bOuputSignal = false;
    irkit.setup();
//    irkit.setupWithIp("192.168.11.18");   // setup with IRKit's IP address
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(100);
    
    ofSetColor(255);
    ofDrawBitmapString("press \'o\' to output the signal data your IRKit memorizes", ofVec2f(20, 20));
    ofDrawBitmapString("press \'s\' to send the signal from the IRKit", ofVec2f(20, 40));
    if (bOuputSignal) {
        ofSetColor(0, 255, 0);
        ofDrawBitmapString("\t the signal data has been successfully saved as \"signal.json\" !", ofVec2f(20, 70));
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if (key == 'o') {
        bOuputSignal = irkit.outputSignal("signal");
    }
    else if (key == 's') {
        irkit.sendSignal("signal");
    }
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
