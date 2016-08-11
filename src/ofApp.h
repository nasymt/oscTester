#pragma once

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxGui.h"

/*-------OSC---------*/
#define RECEIVER_PORT 9000
#define SENDER_PORT 9001
#define HOST "localhost"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
    
        string getArg(int index , ofxOscMessage m);
        void sendOscMessage(string str);
    
    ofxOscReceiver receiver;
    ofxOscSender sender;
    int current_msg_string;
    
    int sender_port = 9001;
    int receiver_port = 9000;
    /*----receive_param----*/
    string receive_address;
    
    bool bSendOsc;
    string send_address_manual;
    vector<string> r_args;
    vector<string> tag;
    int r_argNums;
    bool bReceive;
    string r_address;
    string r_remoteIp;

    /*----send_param----*/
    string s_address;
    string s_remoteIp;
    int send_time;
    
    bool edit_rPort;
    bool edit_sPort;
    bool edit_sIp;
    bool edit_sAddress;
    bool edit_arg[3];
    string arg[3];
    string arg_1;
    bool send_bang;
    
};
