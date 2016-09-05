#include "ofMain.h"
#include "ofApp.h"
#include "ofAppGLFWWindow.h"

//========================================================================
int main( ){
    //	ofSetupOpenGL(500,250,OF_WINDOW);			// <-------- setup the GL context
    //
    //	// this kicks off the running of my app
    //	// can be OF_WINDOW or OF_FULLSCREEN
    //	// pass in width and height too:
    //	ofRunApp(new ofApp());
    
    ofGLFWWindowSettings settings;
    settings.width = 500;
    settings.height = 250;
    settings.setPosition(ofVec2f(300,0));
    settings.resizable = true;
    shared_ptr<ofAppBaseWindow> mainWindow = ofCreateWindow(settings);
    
    settings.width = 300;
    settings.height = 300;
    settings.setPosition(ofVec2f(0,0));
    settings.resizable = false;
    // uncomment next line to share main's OpenGL resources with gui
    //settings.shareContextWith = mainWindow;
    shared_ptr<ofAppBaseWindow> guiWindow = ofCreateWindow(settings);
    guiWindow->setVerticalSync(false);
    
    shared_ptr<ofApp> mainApp(new ofApp);
    mainApp->setupMonitor();
    ofAddListener(guiWindow->events().draw,mainApp.get(),&ofApp::drawMonitor);
    
    ofRunApp(mainWindow, mainApp);
    ofRunMainLoop();
    
}
