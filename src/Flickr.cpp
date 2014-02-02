#include "Flickr.h"

Flickr::Flickr(){}

void Flickr::downloadImageFromFlickr(std::string requete,std::string filename){
  
	string flickr = "http://api.flickr.com/services/rest/?method=flickr.photos.search&api_key=d9ebe546133e6c7ef96438a246dd1087&text=";
	
	flickr += requete ;
	
	ofHttpResponse resp = ofLoadURL(flickr);
	
	ofXml file ;
	file.loadFromBuffer(resp.data) ;
	
	file.setTo("rsp");
	file.setTo("photos");
	
	int rand = ofRandom(0,10) ;
	
	string child = "photo[";
	child +=  to_string(rand) ;
	child += "]";
	
	file.setTo(child);
	
	//http://farm{farm-id}.staticflickr.com/{server-id}/{id}_{secret}.jpg
	
	string imageUrl = "http://farm" ;
	imageUrl += file.getAttribute("farm") ;
	imageUrl += ".staticflickr.com/" ;
	imageUrl += file.getAttribute("server");
	imageUrl += "/";
	imageUrl += file.getAttribute("id");
	imageUrl += "_";
	imageUrl += file.getAttribute("secret");
	imageUrl += ".jpg" ;
	
	std::cout << "imageUrl = " << imageUrl << std::endl ;
	
	downloadImageFromUrl(imageUrl,filename);
  
}


void Flickr::downloadImageFromUrl(std::string url,std::string filename){
	
	CURL *image; 
	CURLcode imgresult; 
	FILE *fp; 

	image = curl_easy_init(); 
	if(image){ 
		// Open file 
		fp = fopen(("data/"+filename).c_str(), "wb"); 
		if( fp == NULL ) cout << "File cannot be opened"; 

		curl_easy_setopt(image, CURLOPT_URL, url.c_str()); 
		curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL); 
		curl_easy_setopt(image, CURLOPT_WRITEDATA, fp); 


		// Grab image 
		imgresult = curl_easy_perform(image); 
		if( imgresult ){ 
		    cout << "Cannot grab the image!\n"; 
		} 
	} 

	// Clean up the resources 
	curl_easy_cleanup(image); 
	// Close the file 
	fclose(fp); 
}

