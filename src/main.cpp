#include "testApp.h"
#include "Weather.h"

#include <iostream>

using namespace std;

int main(int argc, char* argv[]) {
  
	Weather test;
  
	if(argc>1)
	  test.setCity(argv[1]) ;
	else
	  test.setCity("Nantes") ;
	
	std::cout << test.getTemperature() << " " << test.getHumidity() << " " << test.getPressure() << std::endl ;

	ofSetupOpenGL(800, 500, OF_WINDOW);
	ofRunApp(new testApp());
}
