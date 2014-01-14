#include "testApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

void testApp::setup() {
	cam.initGrabber(ofGetWidth()/3,ofGetHeight());

	ofSetVerticalSync(true); 
	ofEnableSmoothing(); 

	marking = NULL;
	brush = NULL;
	paint = NULL;

}

void testApp::update() {

	cam.update();
	if(cam.isFrameNew()) {
		convertColor(cam, gray, CV_RGB2GRAY);
		Canny(gray, edge,mouseX,mouseY, 3);
		edge.update();
	}

	if(marking != NULL)
    {
        marking->update();
    }

    for(auto i = 0u; i < markings.size(); i++)
    {
        markings[i]->update();
    }

	if(cam.isFrameNew()) {
		contourFinder.setThreshold(ofMap(mouseX, 0, ofGetWidth(), 0, 255));
		contourFinder.findContours(cam);
	}

	vector<vector<cv::Point> > contours = contourFinder.getContours();


	for(auto &m : markings)
		delete m;

	markings.clear();

	for(auto &c : contours){

		ofColor color = ofColor::black;
	
		path = new ofxSuperPath();
		path->setPathPressureType(OFX_PATH_PRESSURE_FIXED,10);
		paint = new ofxPaint(path, color,100);
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

void testApp::draw() {

	//cam.draw(0, 0);
	edge.draw(ofGetWidth()/3, 0);
//	contourFinder.draw();


	if(marking != NULL)
    {
        marking->draw();
    }
    
    for(auto i = 0u; i < markings.size(); i++)
    {
        markings[i]->draw();
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
