#include <iostream>
#include <string>
#include <curl/curl.h>

#include "ofURLFileLoader.h"
#include "ofXml.h"


/* Classe permettant la connexion à l'API Flickr
 * 
 * Cette API décrite ici http://www.flickr.com/services/api/
 * est une API à clé personnelle.
 * La notre est en dur dans le code pour simplifier les traitements maise
 * sera rendue invalide ultèrieurement étant donné que notre code est
 * publié en open source
 */
class Flickr
{
public:
	Flickr();
	
	/* Méthode de connexion à Flickr
	 * l'url est créé en fonction de la requete
	 * l'image est enregistrée dans le fichier dont le nom est donnée en paramètre
	 */
	static void downloadImageFromFlickr(std::string requete,const std::string filename="tmp.jpg");
private:
	/* Cette méthode permet de récupérer une image en ligne avec un url
	 */
	static void downloadImageFromUrl(std::string url,const std::string filename);

};
