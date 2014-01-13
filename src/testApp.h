#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "ofxDrawnetic.h"
#include <iostream>

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();

	void exit(); 

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);
	
	ofVideoGrabber cam;
	ofPixels gray;
	ofImage edge;
	ofImage painting;

	ofxMarking* marking;
    ofxSuperPath* path;
   	ofxPaint* paint;
   	ofxRibbonBrush* brush;
    
    vector<ofxMarking *> markings;
	ofxCv::ContourFinder contourFinder;
};
