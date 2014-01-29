#include "BrushLine.h"

BrushLine::BrushLine(ofColor _color,int thickness,int opacity){

	color = _color;
	path = new ofxSuperPath();
	path->setPathPressureType(OFX_PATH_PRESSURE_FIXED,thickness);

	colors = new vector<ofColor>();
	colors->push_back(_color);

	paint = new ofxDynamicPalettePaint(path, *colors,opacity);
	paint->setDynamic(false);
	
	brush = new ofxRibbonBrush(path, paint);
	brush->setDynamic(false);

	marking = new ofxMarking(path, paint, brush);
	path->reset();

}

void BrushLine::lineTo(int x,int y,ofColor _color){
	path->lineTo(x,y,0,color, ofGetFrameNum(), 0);

	if(_color != NULL){
		colors->push_back(_color);
		paint->colors = *colors;
	}
}

void BrushLine::lineEnd(){
	marking->pathFinished();
}

void BrushLine::lineEnd(vector<ofxMarking *>* markings){
	marking->pathFinished();
	markings->push_back(marking);
}
