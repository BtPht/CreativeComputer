#include "testApp.h"

using namespace ofxCv;
using namespace cv;
using namespace std;

void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing();

	ofBackground(ofColor::white);

	//downloadImageFromUrl("http://wallpapers.wallbase.cc/rozne/wallpaper-1853128.jpg");

	downloadImageFromUrl("http://spinoff.comicbookresources.com/wp-content/uploads/2013/09/american-psycho.jpg");
	
	painting.loadImage("img/tmp.jpg");
	painting.resize(500,600);
	it=0;

}

void testApp::downloadImageFromUrl(string url){
	
	CURL *image; 
	CURLcode imgresult; 
	FILE *fp; 

	image = curl_easy_init(); 
	if(image){ 
		// Open file 
		fp = fopen("data/img/tmp.jpg", "wb"); 
		if( fp == NULL ) cout << "File cannot be opened"; 

		curl_easy_setopt(image, CURLOPT_URL, url.c_str()); 
		curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL); 
		curl_easy_setopt(image, CURLOPT_WRITEDATA, fp); 


		// Grab image 
		imgresult = curl_easy_perform(image); 
		if( imgresult ){ 
		    cout << "Cannot grab the image!\n"; 
		} 
	} 

	// Clean up the resources 
	curl_easy_cleanup(image); 
	// Close the file 
	fclose(fp); 

}

void testApp::update() {

	while(it%10 != 0){
		contourPainting(it);
		it++;
	}
	cout << it << endl;
	it++;

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
	contourFinder.setThreshold(x);
	contourFinder.setFindHoles(true);
	contourFinder.findContours(painting);

	for(auto &c : contourFinder.getContours()){

		BrushLine* line = new BrushLine(&markings);

		for(auto &p : c){

			ofColor color = painting.getColor(p.x,p.y);
			line->lineTo(p.x,p.y,color);
		}
		line->lineEnd();
		
		delete line;
	}
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