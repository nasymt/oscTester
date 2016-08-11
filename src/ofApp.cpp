#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(100);
    /*-------OSC--------*/
    cout << "listening for osc messages on port " << RECEIVER_PORT << "\n";
    receiver.setup(RECEIVER_PORT);
    sender.setup(HOST,SENDER_PORT);
    //    current_msg_string = 0;
    
    s_address = "/sound/time";
    receive_address = "/test";
    r_address = "/";
    s_remoteIp = "127.0.0.1";
    for(int i = 0; i < 3; i++ ){
        arg[i] = "i:";

    }
}

//--------------------------------------------------------------
void ofApp::update(){
    if(bReceive)bReceive = false;
    while(receiver.hasWaitingMessages()){
        ofxOscMessage m;
        receiver.getNextMessage(m);
            r_argNums = m.getNumArgs();
            r_address = m.getAddress();
            r_remoteIp = m.getRemoteIp();
            for(int i = 0; i < r_argNums; i++ ){
                tag.push_back(m.getArgTypeName(i));
                string str = getArg( i , m );
                r_args.push_back(str);
            }
        int a = m.getNumArgs();
        string str = m.getArgTypeName(0);
        cout << "type : " << str << endl;
        bReceive = true;
    }
    
    send_time=ofGetElapsedTimeMillis();
    
    if(send_bang){
        int message_num = 0;
        for(int i=0;i<3;i++){
            if(arg[i].size()>2)sendOscMessage(arg[i]);
        }
        cout << " -------------- " << endl;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    string isOscSend;
    if(bSendOsc)isOscSend="true";
    else isOscSend="false";
    
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("fps : "+ofToString(ofGetFrameRate()), 10, 220);

    //----------------------------
    // RECEIVER
    //----------------------------
    int add_y = 25;
    ofDrawBitmapString("RECEIVER", 10, 25);
    
    int y = 50;
    ofDrawBitmapString("message", 10, y);
    ofDrawBitmapString("ip", 210, y);
    ofDrawBitmapString("port", 360, y);
    ofDrawRectangle(75, y-15, 120, 20);

    for ( int i = 0; i < 3; i++ ){
        ofDrawBitmapString(ofToString(i)+":", i*160+10, 55+add_y);
    }
    if(r_args.size()){
        for(int i = 0; i < r_argNums; i++){
            ofDrawBitmapString(" ["+tag[i]+"] "+r_args[i],i*170+25,55+add_y);
        }
    }

  
    ofDrawRectangle(230, y-15, 120, 20);
    if(edit_rPort)ofSetColor(200);
    else ofSetColor(255);
    ofDrawRectangle(400, y-15, 80, 20);
    
    ofSetColor(0, 0, 0);
    ofSetRectMode(OF_RECTMODE_CENTER);
    ofDrawBitmapString(ofToString(receiver_port), 420, 25+add_y);
    ofDrawBitmapString(r_address, 80, 25+add_y);
    ofDrawBitmapString(r_remoteIp,250,y);
    ofSetRectMode(OF_RECTMODE_CORNER);
    
    if(bReceive){
        ofDrawEllipse(80, 20, 10, 10);
    }
    
    //----------------------------
    // SENDER
    //----------------------------
    int s_y = 150;
    ofSetColor(255);
    ofDrawBitmapString(send_address_manual,10,200);
    
    ofDrawBitmapString("SENDER", 10, s_y-25);
    ofDrawBitmapString("BANG" , 100 , s_y-25);
    ofDrawBitmapString("message", 10, s_y);
    ofDrawBitmapString("ip", 210, s_y);
    ofDrawBitmapString("port", 360, s_y);
    for ( int i = 0; i < 3; i++ ){
        ofDrawBitmapString(ofToString(i)+":",i*160+10,s_y+35);
        if(edit_arg[i])ofSetColor(200);
        else ofSetColor(255);
        ofDrawRectangle(i*160+30, s_y+20, 120, 20);
        ofSetColor(0);
        ofDrawBitmapString( arg[i] , i * 160 + 40 , s_y+35 );
        ofSetColor(255);
    }
    if(edit_sAddress)ofSetColor(200);
    else ofSetColor(255);
    ofDrawRectangle(75, s_y-15, 120, 20);
    if(edit_sIp)ofSetColor(200);
    else ofSetColor(255);
    ofDrawRectangle(230, s_y-15, 120, 20);
    if(edit_sPort)ofSetColor(200);
    else ofSetColor(255);
    ofDrawRectangle(400, s_y-15, 80, 20);
    if(send_bang)ofSetColor(0);
    else ofSetColor(255);
    ofDrawRectangle(140,s_y-37,15,15);//bang
    ofSetColor(0);
    ofDrawBitmapString( s_address , 80 , s_y );
    ofDrawBitmapString(ofToString(sender_port), 420, s_y);
    ofDrawBitmapString(ofToString(s_remoteIp),235,s_y);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(edit_rPort){
        string tmp = ofToString(receiver_port);
        if((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) && tmp.size()){
            tmp.pop_back();
        }else if(key == OF_KEY_RETURN){
            if(edit_rPort && receiver_port > 1024 ){
                edit_rPort = false;
                receiver.setup(receiver_port);
            }
        }else {
            tmp.push_back(key);
        }
        receiver_port = ofToInt(tmp);
    }
    if(edit_sPort){
        string tmp = ofToString(sender_port);
        if((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) && tmp.size()){
            tmp.pop_back();
        }else if(key == OF_KEY_RETURN){
            if(edit_sPort && sender_port > 1024 ){
                edit_sPort = false;
                sender.setup(s_remoteIp, sender_port);
            }
        }else {
            tmp.push_back(key);
        }
        sender_port = ofToInt(tmp);
    }
    if(edit_sIp){
        if((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) && s_remoteIp.size()){
            s_remoteIp.pop_back();
        }else if(key == OF_KEY_RETURN){
            if(edit_sIp){
                edit_sIp = false;
                sender.setup(s_remoteIp, sender_port);
            }
        }else {
            s_remoteIp.push_back(key);
        }
    }
    if(edit_sAddress){
        if((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) && s_address.size()){
            s_address.pop_back();
        }else if(key == OF_KEY_RETURN){
            if(edit_sAddress){
                edit_sAddress = false;
            }
        }else {
            s_address.push_back(key);
        }
    }
    for(int i = 0; i < 3; i++ ){
        if(edit_arg[i]){
            if((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL) && arg[i].size()){
                arg[i].pop_back();
            }else if(key == OF_KEY_RETURN){
                if(edit_arg[i]){
                    edit_arg[i] = false;
                }
            }else {
                arg[i].push_back(key);
            }
        }
    }
    if(key == 'b'){
        if(!send_bang)send_bang = true;
        else send_bang = false;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
    if(x > 400 && x < 480 && y > 35 && y < 55){
        if(!edit_rPort){
            edit_rPort = true;
            receiver_port = 0;
        }
    }else if(x > 400 && x < 480 && y > 135 && y < 155){
        if(!edit_sPort){
            edit_sPort = true;
            sender_port = 0;
        }
    }else if(x > 230 && x < 350 && y > 135 && y < 155){
        if (!edit_sIp){
            edit_sIp = true;
            s_remoteIp = "";
        }
    }else if(x > 75 && x < 195 && y > 135 && y < 155){
        if (!edit_sAddress){
            edit_sAddress = true;
            s_address = "";
        }
        
    }else if(x > 140 && x < 155 && y > 113 && y < 132){
        if (!send_bang){
            send_bang = true;
        }else {
            send_bang = false;
        }
    }

    for ( int i = 0; i < 3; i++){
        if ( x > i*160+30 && x < i*160 + 150 && y > 170 && y < 190 ){
            if(!edit_arg[i]){
                edit_arg[i] = true;
            }
        }
    }
}


string ofApp::getArg( int index , ofxOscMessage m){
    string tagName = m.getArgTypeName(index);
    string str;
    
    if ( tagName == "i" ){
        str = ofToString(m.getArgAsInt(index));
    }else if( tagName == "f"){
        str = ofToString(m.getArgAsFloat(index));
    }else if( tagName == "c" ){
        str = ofToString(m.getArgAsChar(index));
    }else if( tagName == "s" ){
        str = ofToString(m.getArgAsString(index));
    }else if( tagName == "d" ){
        str = ofToString(m.getArgAsBool(index));
    }
    return str;
}

void ofApp::sendOscMessage(string str){
    char c = str[0];
    str.erase(0, 2);
    
    ofxOscMessage m;
    m.setAddress(s_address);
    if ( c == 'i' ){
        m.addIntArg(ofToInt(str));
    }else if( c == 'f' ){
        m.addFloatArg(ofToFloat(str));
    }else if( c == 's' ){
        m.addStringArg(str);
    }else if( c == 'd' ){
        m.addDoubleArg(ofToDouble(str));
    }
    
    sender.sendMessage(m,false);
    cout << "send Osc Message : " << str << endl;

}