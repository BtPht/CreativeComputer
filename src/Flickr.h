#include <iostream>
#include <string>
#include <curl/curl.h>

#include "ofURLFileLoader.h"
#include "ofXml.h"

class Flickr
{
public:
	Flickr();
	
	static void downloadImageFromFlickr(std::string requete,std::string filename="tmp.jpg");
	static void downloadImageFromUrl(std::string url,std::string filename);

};
