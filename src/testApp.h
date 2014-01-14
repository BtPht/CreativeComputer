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
	void allContourPainting();
	void contourPainting(int x);
	
	int it;
	ofImage painting;

	ofxMarking* marking;
    ofxSuperPath* path;
   	ofxPaint* paint;
   	ofxRibbonBrush* brush;
    
    vector<ofxMarking *> markings;
	ofxCv::ContourFinder contourFinder;

	vector<vector<vector<cv::Point> > > allContours;
};
