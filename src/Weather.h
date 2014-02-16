#ifndef WEATHER_H
#define WEATHER_H

#include <iostream>
#include <string>
#include <curl/curl.h>

#include "ofURLFileLoader.h"
#include "ofXml.h"

/* Classe qui va prendre en charge l'interaction avec l'API météo
 * 
 * L'API  utilisée est celle du site http://openweathermap.org/API#weather
 * Cette API est libre et ne demande pas de clé
 */
class Weather
{
public:
  Weather();
  
  /* Ce constructeur est le plus intéressant,
   * en effet il permet de sélectionner la ville que dont on souhaite
   * obtenir les informations météorologiques
   */
  Weather(const std::string& city);
  
  /* Une fois instanciée on peut changer la ville courante
   */
  void setCity(const std::string& city) ;
  
  float getTemperature() const;
  float getHumidity() const;
  float getPressure() const;

private :
  float temperature ;
  float humidity ;
  float pressure ;
};

#endif