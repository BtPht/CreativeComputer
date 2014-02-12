#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing();
	ofBackground(ofColor::black);

	internet = false;

	if(internet){
		std::string requete;
		std::cout << "Que voulez-vous dessiner ?" << std::endl;
		std::cin >> requete ;
	
		Flickr::downloadImageFromFlickr(requete);
		painting.loadImage("tmp.jpg");

	  	wt.setCity("Nantes") ;
	
		std::cout << "Temperature (kelvin) : " << wt.getTemperature() << std::endl;
		std::cout << "Temperature (celcius) : " << wt.getTemperature()-273 << std::endl;
		std::cout << "Humidity : " << wt.getHumidity() << std::endl;
		std::cout << "Pressure : " << wt.getPressure() << std::endl;
		std::cout << "Pressure (normalisation) : " << wt.getPressure()-1013 << std::endl;
	}
	else
		painting.loadImage("img/wolkswagen.jpg");

	painting.resize(500,600);
	it_treshold=0;
	screenImg.allocate(500, 600, OF_IMAGE_COLOR);
	allThresholdsDone = false;
	gifEncoder.setup(500,600,.25, 256);
	//ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
}

void testApp::update() {
	
	if(!allThresholdsDone){
		markings = contourPainting();
		screenImg.grabScreen(0,0,500,600);

		if(it_treshold%10 == 0)
		gifEncoder.addFrame(screenImg.getPixels(),500,600);
	
		if(markings.empty()){
			allThresholdsDone = true ;
			string name = "result";
			screenImg.saveImage(name+".jpg");
			std::cout << "Image saved as " << name+".jpg" << std::endl;
			std::cout << "Saving GIF ... " << std::endl; 
			gifEncoder.save(name+".gif");
		}
		
		//std::cout << it_treshold << std::endl;
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

vector<ofxMarking *> testApp::contourPainting(){

	vector<ofxMarking *> result;

	ofxCv::ContourFinder contourFinder;
	contourFinder.setThreshold(it_treshold);
	contourFinder.setFindHoles(true);
	contourFinder.findContours(painting);

	for(auto &c : contourFinder.getContours()){
	  
		BrushLine line;

		if(internet)
			line = BrushLine(ofColor::black,wt.getHumidity()/10,wt.getPressure()-1013);
		else
			line = BrushLine(ofColor::black,5,255);
		
		for(auto &p : c){
			
			ofColor color = painting.getColor(p.x,p.y);
			color.setSaturation((wt.getTemperature()-273)*255/30);
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

void testApp::onGifSaved(const std::string &fileName) {
    std::cout << "GIF saved as " << fileName << std::endl;
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
	//drawing.lineTo(mouseX,mouseY);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
	//drawing = BrushLine(ofColor::red,10,100);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
	//drawing.lineEnd();
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
