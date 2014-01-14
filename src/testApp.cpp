#include "testApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 

	painting.loadImage("img/tree.jpg");
	painting.resize(400,500);

	marking = NULL;
	brush = NULL;
	paint = NULL;
	it=0;

}

void testApp::update() {

	contourPainting(it);
	it++;
	cout << it << endl;
}

void testApp::draw() {

	if(marking != NULL)
    {
        marking->draw();
    }
    
    for(auto i = 0u; i < markings.size(); i++)
    {
        markings[i]->draw();
    }

	painting.draw(ofGetWidth()/2,0);

}

void testApp::contourPainting(int x){

	contourFinder.setThreshold(ofMap(x, 0, ofGetWidth(), 0, 255));
	contourFinder.findContours(painting);

	for(auto &c : contourFinder.getContours()){

		ofColor color = ofColor::black;

		path = new ofxSuperPath();
		path->setPathPressureType(OFX_PATH_PRESSURE_FIXED,10);
		paint = new ofxPaint(path, color,2);
		brush = new ofxRibbonBrush(path, paint);
		brush->setDynamic(false);

		marking = new ofxMarking(path, paint, brush);
		path->reset();
		path->lineStart(c[0].x,c[0].y,0,color, ofGetFrameNum(), 0);

		for(auto &p : c){
			path->lineTo(p.x,p.y,0,color, ofGetFrameNum(), 0);
		}

		marking->pathFinished();		
		markings.push_back(marking);
		marking = NULL;
	}
}

void testApp::allContourPainting(){

	for(int i=0; i<500; i++){
		contourFinder.setThreshold(ofMap(i, 0, ofGetWidth(), 0, 255));
		contourFinder.findContours(painting);

		allContours.push_back(contourFinder.getContours());
	}
	
	for(auto &m : markings)
		delete m;

	markings.clear();

	for(auto &all : allContours){

		for(auto &c : all){

			ofColor color = ofColor::black;
	
			path = new ofxSuperPath();
			path->setPathPressureType(OFX_PATH_PRESSURE_FIXED,10);
			paint = new ofxPaint(path, color,2);
			brush = new ofxRibbonBrush(path, paint);
			brush->setDynamic(false);

			marking = new ofxMarking(path, paint, brush);
			path->reset();
			path->lineStart(c[0].x,c[0].y,0,color, ofGetFrameNum(), 0);

			for(auto &p : c){
				path->lineTo(p.x,p.y,0,color, ofGetFrameNum(), 0);
			}

			marking->pathFinished();		
			markings.push_back(marking);
			marking = NULL;
		}
	}
}

void testApp::exit()
{
    for(auto i = 0u; i < markings.size(); i++)
    {
        delete markings[i];
    }
    markings.clear();
    
    if(marking != NULL)
    {
        delete marking;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{

}
