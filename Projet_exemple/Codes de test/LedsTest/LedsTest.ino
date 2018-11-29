// ledsTest //////////////
// 15.11.2018 - Clément Gault
/*
   Essai de la biliothèque NeoPixel d'Adafruit
   qui permet de piloter un ruban RVB de leds.
   Elle est disponible dans le gestionnaire de biliothèque.
   Menu : Croquis/Inclure une biliothèque/Gérer les biliothèques
   -
   Voir ce tuto également :
   https://learn.adafruit.com/adafruit-neopixel-uberguide/the-magic-of-neopixels
   -
   Un décompte lumineux : "3, 2, 1 !"
   Le code comprend un onglet avec la fonction dédiée (startLeds)
   -
   Montage :
    - Signal (DIN) du ruban en pin 6
    - 5v du ruban sur le + d'une alimentation externe en 5v
    - Masse (GND) du ruban sur le - de l'alim externe ET une pin GND de la carte Arduino
   Note : il faut aussi alimenter la carte (en USB par exemple)
   (voir ledStrip_montage.jpg)
*/

// On indique à Arduino qu'on va utiliser
// la bibliothèque NeoPixel :
#include <Adafruit_NeoPixel.h>

int nbLeds = 30; // nb de leds
// On déclare un objet Adafruit_NeoPixel "nommé strip" :
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nbLeds, 6, NEO_GRB + NEO_KHZ800); // => nbLeds : nb de leds, 6 car connecté en pin 6

void setup() {
  strip.begin(); // Initiatisation du ruban
  strip.setBrightness(255); // Configuration de la luminosité (entre 0 et 255)
}

void loop() {
  // Voir onglet startLeds pour l'explication de la fonction startLeds() :
  startLeds(strip.numPixels(), 1000); // Note : strip.numPixels() renvoie le nb de leds configuré
  delay(1000);
  startLeds(strip.numPixels(), 250);
  delay(1000);
}
