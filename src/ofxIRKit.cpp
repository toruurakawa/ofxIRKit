//
//  ofxIRKit.cpp
//
//  Created by TORU URAKAWA on 7/15/14.
//
//

#include "ofxIRKit.h"

pid_t ofxIRKit::popen2(const char *command, const char *filename) {
    pid_t pid;
    
    pid = fork();
    if (pid < 0)
        return pid;
    else if (pid == 0)
    {
        int fd = open(filename, O_RDWR | O_CREAT, S_IREAD | S_IWRITE);
        dup2(fd, 1);
        close(fd);
        
        execl("/bin/sh", "sh", "-c", command, NULL);
        perror("execl");
        exit(1);
    }
    
    return pid;
}

void ofxIRKit::execCmdAndOutputToFile(string cmdStr, string filename, int timeout) {
    ofFile f;
    const char *cmd = cmdStr.c_str();
    pid_t pid = popen2(cmd, filename.c_str());
    time_t sTime = INFINITY;
    bool bCheckFile = false;
    while (1) {
        if (f.doesFileExist(filename) && !bCheckFile) {
            sTime = time(0);
            bCheckFile = true;
        }
        else if (f.doesFileExist(filename)) {
            if (time(0) - sTime > timeout) {
                break;
            }
        }
    }
    kill(pid, SIGINT);
}

string ofxIRKit::getMatchedStrings(string fileName, string s) {
    ofFile f;
    ifstream file(fileName.c_str());
    string temp, matchedStr = "";
    while(getline(file, temp)) {
        cout << temp << endl;
        vector<string> matches;
        matches = regx.getMatchedStrings(temp, s);
        if (matches.size() > 0) {
            cout << matches[0] << endl;
            matchedStr = matches[0];
            break;
        }
    }
    f.removeFile(fileName);
    
    try {
        if (matchedStr == "") {
            if (fileName == ofToDataPath("irkitId")) {
                throw "failed to get id";
            }
            else if (fileName == ofToDataPath("irkitIp")) {
                throw "failed to get ip";
            }
        }
    } catch (char const *str) {
        cout << str << endl;
    }
    
    return matchedStr;
}

string ofxIRKit::fetchId() {
    string tmpFileNameGetId = ofToDataPath("irkitId");
    execCmdAndOutputToFile("dns-sd -B _irkit._tcp", tmpFileNameGetId, 3);
    
    return getMatchedStrings(tmpFileNameGetId,  "([Ii][Rr][Kk][Ii][Tt])[^\.].{3}");
}

string ofxIRKit::fetchIpWithId(string irid) {
    stringstream cmdSS;
    cmdSS << "dns-sd -G v4 " << irid << ".local;";
    string cmdStrGetIp = cmdSS.str();
    string tmpFileNameGetIp = ofToDataPath("irkitIp");
    execCmdAndOutputToFile(cmdStrGetIp, tmpFileNameGetIp, 3);
    return getMatchedStrings(tmpFileNameGetIp, "[0-9]{3}\.[0-9]{3}\.[0-9]*\.[0-9]*");
}

string ofxIRKit::fetchIp() {
    string irid = fetchId();
    return fetchIpWithId(irid);
}

void ofxIRKit::setup()
{
    ip = fetchIp();
}

void ofxIRKit::setupWithId(string id) {
    ip = fetchIpWithId(id);
}

void ofxIRKit::setupWithIp(string _ip) {
    ip = _ip;
}


bool ofxIRKit::ouputSignal(string signalName) {
    ofFile f;
    stringstream cmdGetDataSS;
    cmdGetDataSS << "curl -i http://" << ip << "/messages";
    string cmdGetDataStr = cmdGetDataSS.str();
    string filename = ofToDataPath("irkitCmd");
    execCmdAndOutputToFile(cmdGetDataStr, filename, 3);
    
    string dataStr = getMatchedStrings(filename, "{.*}");
    
    string dataName = ofToDataPath(signalName += ".json");
    fstream dataFile;
    dataFile.open(dataName.c_str(), ios::out);
    if (!dataFile.is_open()) {
        return EXIT_FAILURE;
    }
    dataFile << dataStr << endl;
    dataFile.close();
    
    return f.doesFileExist(dataName.c_str());
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