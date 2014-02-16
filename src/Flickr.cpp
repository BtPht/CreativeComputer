#include "Flickr.h"

Flickr::Flickr(){}

void Flickr::downloadImageFromFlickr(const std::string requete,const std::string filename){
  
	/* La première étape est de construire l'URL
	 */
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
	
	/* Le fichier XML récupéré ne contient pas d'url directe vers des images.
	 * Il faut le parcourir afin de récupérer les attributs qui vont eux permettre
	 * de créer un lien vers l'image
	 */
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
	
	/* Une fois l'url créé nous appelons la méthode de téléchargement d'image
	 */
	downloadImageFromUrl(imageUrl,filename);
  
}


void Flickr::downloadImageFromUrl(const std::string url,const std::string filename){
	
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

