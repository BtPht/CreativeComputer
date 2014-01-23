#pragma once

#include "ofxDrawnetic.h"

class BrushLine  {
public:

	BrushLine(vector<ofxMarking *>* _markings,ofColor _color=ofColor::black,int thinkness=10,int opacity=2);

	void lineTo(int x,int y,ofColor _color=NULL);
	void lineEnd();

	ofColor color;
	ofxMarking* marking;
    ofxSuperPath* path;
    ofxDynamicPalettePaint* paint;
   	ofxRibbonBrush* brush;
	vector<ofxMarking *>* markings;
	vector<ofColor>* colors;
};
