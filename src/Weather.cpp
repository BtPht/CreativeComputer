#include "Weather.h"

Weather::Weather()
{
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init(std::String city);
  if(curl) {
    
    String meteo_url = "http://api.openweathermap.org/data/2.5/weather?q=";
    meteo_url + city ;
    meteo_url + "&mode=xml" ;
    
    curl_easy_setopt(curl, CURLOPT_URL, meteo_url);
    
    /* example.com is redirected, so we tell libcurl to follow redirection */ 
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
 
    /* Perform the request, res will get the return code */ 
    res = curl_easy_perform(curl);
    /* Check for errors */ 
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
 
    /* always cleanup */ 
    curl_easy_cleanup(curl);
  }
  
}
