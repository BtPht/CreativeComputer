#include "testApp.h"
#include "Weather.h"

#include <iostream>

using namespace std;

int main() {
  
	Weather test("London");

	ofSetupOpenGL(1200, 500, OF_WINDOW);
	ofRunApp(new testApp());
}
