#include "testApp.h"

using namespace ofxCv;
using namespace cv;

/* Boucle appelée par le moteur de OpenFrameworks et dans laquelle
 * toutes les variables et tous les objets sont initialisés.
 */
void testApp::setup() {

	ofSetVerticalSync(true); 
	ofEnableSmoothing();
	ofBackground(ofColor::black);

	internet = false;
	
	/* En raison des problèmes liés au proxy imposé dans les locaux de Polytech
	* toutes les interactions avec l'environnement doivent posséder une
	* alternative
	*/
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
	ofAddListener(ofxGifEncoder::OFX_GIF_SAVE_FINISHED, this, &testApp::onGifSaved);
	
	contourFinder.setFindHoles(true);
	contourFinder.findContours(painting);
	
	currentContour=0;
	contours.clear();
}

/* Boucle appelée par le moteur de OpenFrameworks et dans laquelle
 * les modifications du modèle sont effectuées.
 * Dans notre cas nous créons le chemin qui va être ensuite dessinée dans draw()
 */
void testApp::update() {
	
	/* On détecte qu'il reste des bords à détecter
	 * la variable allThresholdsDone est modifiée lorsque aucun nouveau contour est 
	 * détecté
	 */
	if(!allThresholdsDone){
		markings = contourPainting();
		screenImg.grabScreen(0,0,500,600);

		if(it_treshold%10 == 0)
		gifEncoder.addFrame(screenImg.getPixels(),500,600);
	
		if(markings.empty()){
			/* Une fois que tous les contours ont été détectés on 
			 * sauvegarde le résultat sous la forme d'un .gif animé
			 */
			allThresholdsDone = true ;
			string name = "result";
			screenImg.saveImage(name+".jpg");
			std::cout << "Image saved as " << name+".jpg" << std::endl;
			std::cout << "Saving GIF ... " << std::endl; 
			gifEncoder.save(name+".gif");
		}
		
		//std::cout << it_treshold << std::endl;

	}
}

/* Boucle appelée par le moteur de OpenFrameworks et dans laquelle
 * sont appelées toutes les méthodes modifiant le motif affiché
 */
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

/*
 * Dans cette méthode nous avons deux implémentations différentes du dessin.
 * La première va créer pour chaque seuil de détection des contours l'intégralité du
 * dessin correspondant. C'est la version la plus simple à mettre en oeuvre mais
 * elle ce n'est pas la plus fidèle d'un point de vue imitation du travail d'un artiste.
 * 
 * La seconde va à chaque boucle dessiner le trait correspondant au contour détecté.
 * Le résultat obtenu est assez décevant puisqu'au final un trait dans le dessin final correspond
 * à une somme de traits dans les différentes couches.
 * 
 * Pour obtenir le résultat recherché il faudrait construire tous les seuils posibles,
 * puis les parcourir en regroupant ceux qui ont des trajectoires similaires, les combiner
 * puis réaliser le dessint sur les nouveaus traits obtenus. Nous n'avons pas eu le temps
 * dans le cadre imparti d'obtenir une version fonctionnelle.
 */

vector<ofxMarking *> testApp::contourPainting(){

	vector<ofxMarking *> result;

	ofxCv::ContourFinder contourFinder;
	contourFinder.setThreshold(it_treshold);
	contourFinder.setFindHoles(true);
	contourFinder.findContours(painting);

	/* version fonctionnant seuil par seuil
	 */
	for(auto &c : contourFinder.getContours()){

		BrushLine line;

		/* En raison des problèmes liés au proxy imposé dans les locaux de Polytech
		 * toutes les interactions avec l'environnement doivent posséder une
		 * alternative
		 */
		if(internet)
			line = BrushLine(ofColor::black,wt.getHumidity()/10,wt.getPressure()-1013);
		else
			line = BrushLine();

		for(auto &p : c){

			ofColor color = painting.getColor(p.x,p.y);
			if(internet)
			color.setSaturation((wt.getTemperature()-273)*255/30);
			line.lineTo(p.x,p.y,color);
		}
		line.lineEnd(&result);
	}
	
	it_treshold++;
	
	/*Version fonctionnant trait par trait
	 */
	
	//le dessin trait par trait est assez lent, nous avons ajouté cette boucle pour accelerer le traitement.
	/*for(int i = 0 ; i < 20 ; ++i){
	  
		BrushLine line;
	  
		if(currentContour < contours.size()){
			
			if(internet)
				line = BrushLine(ofColor::black,wt.getHumidity()/10,wt.getPressure()-1013);
			else
				line = BrushLine();
			
			for(auto &p : contours[currentContour]){
				
				ofColor color = painting.getColor(p.x,p.y);
				if(internet)
					color.setSaturation((wt.getTemperature()-273)*255/30);
				line.lineTo(p.x,p.y,color);
			}
			line.lineEnd(&result);
			
		}
		else{
			it_treshold++;
			
			contourFinder = ofxCv::ContourFinder();
			
			contourFinder.setFindHoles(true);
			contourFinder.findContours(painting);
			contourFinder.setThreshold(it_treshold);
			
			contours = contourFinder.getContours();
			currentContour = 0 ;

			if(internet)
				line = BrushLine(ofColor::black,wt.getHumidity()/10,wt.getPressure()-1013);
			else
				line = BrushLine();
			
			for(auto &p : contours[currentContour]){
				
				ofColor color = painting.getColor(p.x,p.y);
				if(internet)
					color.setSaturation((wt.getTemperature()-273)*255/30);
				line.lineTo(p.x,p.y,color);
			}
			line.lineEnd(&result);
			
		}
		currentContour++;
	}*/

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

void testApp::onGifSaved(std::string &fileName) {
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
