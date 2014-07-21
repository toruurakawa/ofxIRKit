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
    virtual void foundService(const string &type, const string &name, const string &ip, const string &domain);
    
public:
    void setup();
    void setupWithIp(const string &ip);
    
    bool outputSignal(const string &signalName);
    void sendSignal(const string &signalName);
    
    bool isRequestable() const;
};
