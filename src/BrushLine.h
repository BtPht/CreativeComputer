#pragma once

#include "ofxDrawnetic.h"

class BrushLine  {
public:

	BrushLine(vector<ofxMarking *>* _markings,ofColor _color=ofColor::black,int thinkness=10,int opacity=2);

	void lineStart(int,int);
	void lineTo(int,int);
	void lineEnd();

	ofColor color;
	ofxMarking* marking;
    ofxSuperPath* path;
   	ofxPaint* paint;
   	ofxRibbonBrush* brush;
	vector<ofxMarking *>* markings;
};
