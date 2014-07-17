//
//  ofxIRKit.h
//
//  Created by TORU URAKAWA on 7/15/14.
//
//

#pragma once
#include "ofMain.h"
#include "ofxHttpUtils.h"
#include "ofxRegex.h"

class ofxIRKit {
    ofxHttpUtils httpUtils;
    ofxRegex regx;
    
    string irid, ip, data;

    pid_t popen2(const char *command, const char *filename);
    string getMatchedStrings(string fileName, string s);
    void execCmdAndOutputToFile(string cmd, string filename, int timeout);
    string fetchId();
    string fetchIp();
    string fetchIpWithId(string irid);
    
public:
    void setup();
    void setupWithId(string id);
    void setupWithIp(string ip);

    bool ouputSignal(string signalName);
    void sendSignal(string signalName);
};
