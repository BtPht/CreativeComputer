#pragma once

#include "ofMain.h"
#include "ofxCv.h"
#include "BrushLine.h"
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
	ofColor filterColor(int x,int y,int width_filter);
	
	int it;
	ofImage painting;

    vector<ofxMarking *> markings;

	vector<vector<vector<cv::Point> > > allContours;
};
