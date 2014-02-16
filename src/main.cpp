#include "testApp.h"


int main(int argc, char* argv[]) {

	ofSetupOpenGL(1000, 600, OF_WINDOW);
	
	/* Instancier testApp qui est dérivé de ofbaseApp entraine le lancement de la boucle
	 * principale de OpenFrameworks
	 */
	ofRunApp(new testApp());
}
