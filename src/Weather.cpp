#include "Weather.h"

Weather::Weather(const std::string& city)
{
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
  
  std::string meteo_url = "http://api.openweathermap.org/data/2.5/weather?q=";
  meteo_url += city ;
  meteo_url += "&mode=xml" ;
  
  ofHttpResponse resp = ofLoadURL(meteo_url);
  
  std::cout << resp.data << std::endl ;
  
}
