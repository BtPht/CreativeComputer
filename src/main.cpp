#include "testApp.h"
#include "Weather.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  
	if(argc>1)
	  Weather test(argv[1]) ;
	else
	  Weather test("Nantes") ;

	ofSetupOpenGL(800, 500, OF_WINDOW);
	ofRunApp(new testApp());
}
