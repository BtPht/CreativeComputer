#include "testApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing();
	ofBackground(ofColor::black);

	bool internet = false;

	if(internet){
		std::string requete;
		std::cin >> requete ;
	
		Flickr::downloadImageFromFlickr(requete);
		painting.loadImage("tmp.jpg");

		Weather wt;
	  	wt.setCity("Nantes") ;
	
		std::cout << wt.getTemperature() << " " << wt.getHumidity() << " " << wt.getPressure() << std::endl ;
	}
	else
		painting.loadImage("img/wolkswagen.jpg");

	painting.resize(500,600);
	it_treshold=0;
	screenImg.allocate(500, 600, OF_IMAGE_COLOR);
	allThresholdsDone = false;
}

void testApp::update() {
	
	if(!allThresholdsDone){
		markings = contourPainting(painting,it_treshold);
		screenImg.grabScreen(0,0,500,600);
	
		if(markings.empty()){
			allThresholdsDone = true ;
			string name = "result.jpg";
			cout << "Image enregistrer : " << name << endl; 
			screenImg.saveImage(name);
		}
		
		cout << it_treshold << endl;
		it_treshold++;
	}
}

void testApp::draw() {
    
    screenImg.draw(0,0);
	painting.draw(ofGetWidth()/2,0);

    for(auto i = 0u; i < markings.size(); i++)
    {
	markings[i]->draw();
	delete markings[i];
    }
    markings.clear();
    
    
}

vector<ofxMarking *> testApp::contourPainting(ofImage image,int treshold){

	vector<ofxMarking *> result;

	ofxCv::ContourFinder contourFinder;
	contourFinder.setThreshold(treshold);
	contourFinder.setFindHoles(true);
	contourFinder.findContours(image);

	for(auto &c : contourFinder.getContours()){

		BrushLine line;

		for(auto &p : c){

			ofColor color = image.getColor(p.x,p.y);
			line.lineTo(p.x,p.y,color);
		}
		line.lineEnd(&result);	
	}

	return result;
}

ofColor testApp::filterColor(int x,int y,int width_filter){

	int size_filter = width_filter*width_filter*4+1;
	ofColor color = painting.getColor(x,y)/size_filter;

	for(int i=1;i<=width_filter;i++){
		for(int j=1;j<=width_filter;j++){				
			color += painting.getColor(x+i,y+j)/size_filter;
			color += painting.getColor(x-i,y-j)/size_filter;
			color += painting.getColor(x+i,y)/size_filter;
			color += painting.getColor(x,y-j)/size_filter;
		}	
	}
	return color;
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
