//
//  ofxIRKit.h
//
//  Created by TORU URAKAWA on 7/15/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxBonjour.h"

class ofxIRKit : public ofxBonjourBrowserFoundNotificationReceiverInterface {
    static const string LogTag;
    
    ofxHttpUtils httpUtils;
    ofxBonjourBrowser bb;
    
    string ip;        
    void foundService(string type, string name, string ip, string domain);
    
public:
    void setup();
    void setupWithIp(string ip);
    
    bool outputSignal(string signalName);
    void sendSignal(string signalName);
    
    bool isRequestable() const;
};
