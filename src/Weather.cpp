#include "Weather.h"

Weather::Weather() :
temperature(0),
humidity(0),
pressure(0)
{}

Weather::Weather(const std::string& city)
{  
  setCity(city); 
}

void Weather::setCity(const std::string& city){

/* En raison des problèmes de proxy nous avons réalisé une implémentation
 * à l'aide de la librairie libcurl offrant la possibilité de sélectionner
 * un serveur proxy
 */  
//   CURL *curl;
//   CURLcode res;
//  
//   curl = curl_easy_init();
//   if(curl) {
//     
//     std::string meteo_url = "http://api.openweathermap.org/data/2.5/weather?q=";
//     meteo_url += city ;
//     meteo_url += "&mode=xml" ;
//     
//     std::cout << meteo_url << std::endl ; 
//     
//     curl_easy_setopt(curl, CURLOPT_URL, meteo_url.c_str());
//     curl_easy_setopt(curl,CURLOPT_PROXY ,"http://cache.wifi.univ-nantes.fr:3128");
//     
//     /* example.com is redirected, so we tell libcurl to follow redirection */ 
//     //curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
//  
//     /* Perform the request, res will get the return code */ 
//     res = curl_easy_perform(curl);
//         
//     /* Check for errors */ 
//     if(res != CURLE_OK)
//       fprintf(stderr, "curl_easy_perform() failed: %s\n",
//               curl_easy_strerror(res));
//       
//     /* always cleanup */ 
//     curl_easy_cleanup(curl);
//   }
  
  
  /* La première étape est de créer une url
   */
  std::string meteo_url = "http://api.openweathermap.org/data/2.5/weather?q=";
  meteo_url += city ;
  meteo_url += "&mode=xml" ;

  /* On récupère ensuite le fichier xml renvoyé par le serveur
   */
  ofHttpResponse resp = ofLoadURL(meteo_url);
  
  ofXml file ;
  file.loadFromBuffer(resp.data) ;
  
  /* On parcour enfin le fichier d'après la DTD donnée par le site fournisseur de l'API
   * afin de récupérer toutes les informations désirées
   */
  file.setTo("current");
  file.setTo("temperature");
  
  //std::cout << "name : " << file.getName() << std::endl ;
  
  //std::cout << "temperature : " << file.getAttribute("value") << std::endl ;
  
  temperature = std::atof(file.getAttribute("value").c_str()) ;
  
  file.setToParent();
  file.setTo("humidity");
  
  humidity = std::atof(file.getAttribute("value").c_str()) ;
  
  file.setToParent();
  file.setTo("pressure");
  
  pressure = std::atof(file.getAttribute("value").c_str()) ;
  
}

float Weather::getTemperature() const{
  return temperature;
}

float Weather::getHumidity() const{
  return humidity;
}

float Weather::getPressure() const{
  return pressure;
}




