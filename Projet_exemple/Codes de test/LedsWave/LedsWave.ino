// ledsWave //////////////
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
   Les leds s'allument les unes après les autres
   d'une couleur données aléatoirement.
   On n'utilise pas de fonction de delay() mais un timer.
   -
   Montage :
    - Signal (DIN) du ruban en pin 6
    - 5v du ruban sur le + d'une alimentation externe en 5v
    - Masse (GND) du ruban sur le - de l'alim externe ET une pin GND de la carte Arduino
   Note : il faut aussi alimenter la carte (en USB par exemple)
   (voir ledStrip_montage.jpg)
   -

*/

// On indique à Arduino qu'on va utiliser
// la bibliothèque NeoPixel :
#include <Adafruit_NeoPixel.h>

int nbLeds = 30; // nb de leds
// On déclare un objet Adafruit_NeoPixel "nommé strip" :
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nbLeds, 6, NEO_GRB + NEO_KHZ800); // +> nbLeds : nb de leds, 6 car connecté en pin 6

unsigned long p_millis = 0; // Temps où le ruban a changé d'état
int intervalle = 30; // En-dessous de 30, ça marche mal (allumage des leds est saccadé)
int nLed = 0; // Jusqu'à led le ruban s'allume
byte r, g, b; // Valeurs RVB


void setup() {
  strip.begin(); // Initiatlisation du ruban
  strip.setBrightness(255); // Configuration de la luminosité (entre 0 et 255)
  r = random(256);
  g = random(256);
  b = random(256);
}

void loop() {
  // Rappel : millis() renvoie depuis combien en temps en milliseconde
  // la carte exécute le programme !

  // On vérifie que la différence entre le temps présent ( millis())
  // et le dernier moment où le ruban a changé d'état (p_millis) est
  // supérieure à intervalle :
  if (millis() - p_millis >= intervalle) {
    p_millis = millis(); // Met à jour le moment où le ruban a changé d'état
    for (int i = 0; i < nLed; i++) { // On allume les leds juqu'a nLed
      strip.setPixelColor(i, r, g, b); // i : numéro de led, r, v et b : couleur
    }
    if (nLed < strip.numPixels()) { // strip.numPixels() renvoie le nb de leds dans le ruban
      nLed++;
    } else {
      nLed = 0;
      //strip.clear(); // On peut éteindre toutes les leds quand on arrive à la dernière
      r = random(256);
      g = random(256);
      b = random(256);
    }
    strip.show(); // Pour envoyer les données dans le ruban, sans l'appel de cette fonction, le ruban ne change pas de couleur
  }
}
