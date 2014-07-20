//
//  ofxIRKit.mm
//
//  Created by TORU URAKAWA on 7/15/14.
//
//

#include "ofxIRKit.h"

const string ofxIRKit::LogTag = "ofxIRKit";

void ofxIRKit::setup()
{
    ip = "";
    
    bb.setup();
    bb.setFoundNotificationReceiver(this);
    bb.startBrowse("_irkit._tcp");
}

void ofxIRKit::setupWithIp(const string &_ip) {
    ip = _ip;
}

void ofxIRKit::foundService(string type, string name, string _ip, string domain) {
    ip = _ip;
    ofLogVerbose(LogTag) << "found: " << type << " : " << name << " = " << ip;
    bb.stopBrowse();
}

bool ofxIRKit::outputSignal(const string &signalName) {
    if(isRequestable()) {
        ofFile f;
        f.open(ofToDataPath(signalName + ".json"), ofFile::WriteOnly);
        stringstream urlSs;
        urlSs << "http://" << ip << "/messages";
        ofxHttpResponse responce = httpUtils.getUrl(urlSs.str());
        
        return f.writeFromBuffer(responce.responseBody);
    } else {
        ofLogError(LogTag) << "ip is not known.";
        return false;
    }
}

void ofxIRKit::sendSignal(const string &signalName) {
    if(isRequestable()) {
        stringstream ss;
        ss << signalName << ".json";
        ofBuffer data = ofBufferFromFile(ss.str());
        stringstream ss2;
        ss2 << "http://" << ip << "/messages";
        ofLogVerbose(LogTag) << ss2.str();
        httpUtils.postData(ss2.str(), data);
    } else {
        ofLogError(LogTag) << "ip is not known.";
    }
}

bool ofxIRKit::isRequestable() const {
    return ip != "";
}