#ifndef BRUSHLINE_H
#define BRUSHLINE_H

#include "ofxDrawnetic.h"

/* La classe BrushLine est la classe qui va se charger
 * de toutes les étapes du dessin.
 * 
 * Lors de l'appel par le moteur de OpenFrameworks des méthodes de dessin,
 * le chemin définit sera suivi et dessiné en fonction des paramètres
 * données lors de l'instanciation de la classe.
 */
class BrushLine  {
public:

	BrushLine(ofColor _color=ofColor::black,int thickness=10,int opacity=2);
	
	/* Les méthodes lineTo et lineEnd permettent de créer
	 * le chemin qui sera suivi par le pinceau
	 */
	void lineTo(int x,int y,ofColor _color=ofFloatColor(0));
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