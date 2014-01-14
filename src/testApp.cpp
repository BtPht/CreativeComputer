#include "testApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 

	painting.loadImage("img/tree.jpg");
	painting.resize(400,500);

	it=0;

}

void testApp::update() {

	contourPainting(it);
	it++;
	cout << it << endl;
}

void testApp::draw() {

    for(auto i = 0u; i < markings.size(); i++)
    {
        markings[i]->draw();
    }

	painting.draw(ofGetWidth()/2,0);

}

void testApp::contourPainting(int x){

	ofxCv::ContourFinder contourFinder;
	contourFinder.setThreshold(ofMap(x, 0, ofGetWidth(), 0, 255));
	contourFinder.findContours(painting);

	for(auto &c : contourFinder.getContours()){

		BrushLine* line = new BrushLine(&markings);
		line->lineStart(c[0].x,c[0].y);

		for(auto &p : c){
			line->lineTo(p.x,p.y);
		}

		line->lineEnd();
	}
}

void testApp::allContourPainting(){


	ofxCv::ContourFinder contourFinder;
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

			BrushLine* line= new BrushLine(&markings);
			line->lineStart(c[0].x,c[0].y);

			for(auto &p : c){
				line->lineTo(p.x,p.y);
			}

			line->lineEnd();
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
