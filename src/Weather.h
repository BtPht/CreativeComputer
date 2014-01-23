#include <iostream>
#include <string>
#include <curl/curl.h>

#include "ofURLFileLoader.h"
#include "ofXml.h"

class Weather
{
public:
  Weather();
  Weather(const std::string& city);
  
  void setCity(const std::string& city) ;
  
  float getTemperature();
  float getHumidity();
  float getPressure();

private :
  float temperature ;
  float humidity ;
  float pressure ;
};