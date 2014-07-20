//
//  ofxIRKit.mm
//
//  Created by TORU URAKAWA on 7/15/14.
//
//

#include "ofxIRKit.h"

void ofxIRKit::setup()
{
    bb.setup();
    bb.setFoundNotificationReceiver(this);
    bb.startBrowse("_irkit._tcp");
}

void ofxIRKit::setupWithIp(string _ip) {
    ip = _ip;
}

void ofxIRKit::foundService(string type, string name, string _ip, string domain) {
    ip = _ip;
    ofLogVerbose(LogTag) << "found: " << type << " : " << name << " = " << ip;
    bb.stopBrowse();
}

bool ofxIRKit::outputSignal(string signalName) {
    ofFile f;
    f.open(ofToDataPath(signalName += ".json"), ofFile::WriteOnly);
    stringstream urlSs;
    urlSs << "http://" << ip << "/messages";
    ofxHttpResponse responce = httpUtils.getUrl(urlSs.str());
    
    return f.writeFromBuffer(responce.responseBody);
}

void ofxIRKit::sendSignal(string signalName) {
    stringstream ss;
    ss << signalName << ".json";
    ofBuffer data = ofBufferFromFile(ss.str());
    stringstream ss2;
    ss2 << "http://" << ip << "/messages";
    cout << ss2.str() << endl;
    httpUtils.postData(ss2.str(), data);
}