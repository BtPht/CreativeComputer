#ifndef BRUSHLINE_H
#define BRUSHLINE_H

#include "ofxDrawnetic.h"

class BrushLine  {
public:

	BrushLine(ofColor _color=ofColor::black,int thickness=10,int opacity=2);

	void lineTo(int x,int y,ofColor _color=NULL);
	void lineEnd(vector<ofxMarking *>* markings);
	void lineEnd();

	ofColor color;
	ofxMarking* marking;
    ofxSuperPath* path;
    ofxDynamicPalettePaint* paint;
   	ofxRibbonBrush* brush;
	vector<ofColor>* colors;
};


#endif