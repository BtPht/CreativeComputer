#include "BrushLine.h"

BrushLine::BrushLine(vector<ofxMarking *>* _markings,ofColor _color,int thinkness,int opacity){

	markings = _markings;
	color = _color;
	path = new ofxSuperPath();
	path->setPathPressureType(OFX_PATH_PRESSURE_FIXED,10);
	paint = new ofxPaint(path, color,2);
	brush = new ofxRibbonBrush(path, paint);
	brush->setDynamic(false);

	marking = new ofxMarking(path, paint, brush);
	path->reset();

}

void BrushLine::lineStart(int x,int y){
	path->lineStart(x,y,0,color, ofGetFrameNum(), 0);
}

void BrushLine::lineTo(int x,int y){
	path->lineTo(x,y,0,color, ofGetFrameNum(), 0);
}

void BrushLine::lineEnd(){
	marking->pathFinished();
	markings->push_back(marking);
}
