#ifndef TESTAPP_H
#define TESTAPP_H

#include "ofMain.h"
#include "ofxCv.h"
#include "ofMath.h"
#include "ofxGifEncoder.h"

#include "BrushLine.h"
#include "Flickr.h"
#include "Weather.h"
#include <iostream>
#include <string>
#include <curl/curl.h>

/* Classe principale dans laquelle sont implémentées les méthodes
 * propres à OpenFrameworks
 * 
 * Selon notre modlisation il s'agit de du coeur de l'application
 */
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
	std::vector<ofxMarking *> contourPainting();
	ofColor filterColor(int x,int y,int width_filter);
	void onGifSaved(std::string &fileName);
	
	
	bool internet;
	int it_treshold;
	bool allThresholdsDone ;
	bool stillHaveContours;
	
	ofxCv::ContourFinder contourFinder;
	unsigned int currentContour;
	std::vector<std::vector<cv::Point>> contours;
	
	Weather wt;
	ofImage painting;
	std::vector<ofxMarking *> markings;
	ofImage screenImg;
	BrushLine drawing;
	ofxGifEncoder gifEncoder;

};

#endif
