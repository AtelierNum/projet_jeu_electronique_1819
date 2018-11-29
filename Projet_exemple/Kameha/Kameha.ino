// Kameha //////////////
// 15.11.2018 - Clément Gault
/*
  Petit jeu inspiré d'un célèbre manga/anim dramatique :
  Deux joueurs s'affrontent en lançant chacun
  un rayon d'énergie (kamehas) symbolisé par un ruban de leds (jaune pour le joueur 1 et bleu pour le joueur 2) :
  La puissance du rayon d'énergie est basé sur le principe d'appuyer
  de manière frénétique sur un bouton.
  -
  Montage :
    - Un bouton en pin 2
    - Un bouton en pin 4
    - Signal (DIN) du ruban en pin 6
    - 5v du ruban sur le + d'une alimentation externe en 5v
    - Masse (GND) du ruban sur le - de l'alim externe ET une pin GND de la carte Arduino
   Note : il faut aussi alimenter la carte (en USB par exemple)
   (voir Kameha_montage.jpg)
*/

// Ajout des bibliothèques :
#include <EasyButton.h>
#include <Adafruit_NeoPixel.h>

// Déclaration de deux objets EasyButton :
EasyButton button1(2);
EasyButton button2(4);

int nbLeds = 30; // nb de leds
// On déclare un objet Adafruit_NeoPixel "nommé strip" :
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nbLeds, 6, NEO_GRB + NEO_KHZ800);

unsigned long p_millisJ1 = 0; // Temps où le ruban a changé d'état pour joueur 1
unsigned long p_millisJ2 = 0; // Pareil pour j2
unsigned long currentMillis = 0; // Temps actuel

int nLedJ1; // Numéro de la led dans l'avancement du rayon du joueur 1
int nLedJ2; // Pareil pour j2

int scTarget = 10; // Le nombre de fois qu'il faut appuyer sur un bouton pour mettre à jour le ruban
int sc1; // Score j1
int sc2; // etc.
int lumJ1 = 30; // Lumière Joueur 1
int lumJ2 = 30; // etc.
int delayJ1, delayJ2; // Intervalle animation leds j1 et j2

float a; // animation fin de partie
int ledWin;

// Variables booléennes pour passer d'une étape à l'autre durant une partie :
boolean chargeKameha = true; // Chargement : on appuie comme une brute pour charger son kameha
boolean launchKameha = false; // Lancement des kamehas des joueurs
boolean clashKameha = false; // Affrontement des kamehas (coeur du jeu)
boolean winKameha = false; // Animation de fin de partie

void setup() {
  Serial.begin(9600);
  // Initialisation des deux objets EasyButon :
  button1.begin();
  button2.begin();
  // Quand un bouton est pressé,
  // on appelle une fois une fonction dédiée (voir après le loop()) :
  button1.onPressed(onPressed1);
  button2.onPressed(onPressed2);

  nLedJ1 = 0; // n° de la led du joueur 1 au début
  nLedJ2 = strip.numPixels() - 1; // etc.

  strip.begin(); // Initialisation du ruban
  strip.setBrightness(255); // Configuration de la luminosité (entre 0 et 255)

  strip.setPixelColor(nLedJ1, lumJ1, lumJ1, 0); // Allume led du Joueur 1 au début
  strip.setPixelColor(nLedJ2, 0, 0, lumJ2); // Pareil j2

  // Animation du début du jeu, "3, 2, 1 !" lumineux
  startLeds(strip.numPixels(), 1000); // Voir onglet startLeds

}

void loop() {

  // On lit en boucle l'état du bouton :
  // quand il est pressé, il va lire la fonction
  // appelée en retour (voir après le loop()) :
  button1.read();
  button2.read();

  // Chargement des kameha de chaque joueur :
  if (chargeKameha == true) {
    strip.setPixelColor(0, lumJ1, lumJ1, 0); // la valeur des lumJ1 est donnée dans la fonction onPressed1()
    strip.setPixelColor(1, lumJ1 / 4, lumJ1 / 4, 0);
    strip.setPixelColor(2, lumJ1 / 6, lumJ1 / 6, 0);
    strip.setPixelColor(nLedJ2, 0, 0, lumJ2); // J2 // la valeur des lumJ2 est donnée dans la fonction onPressed2()
    strip.setPixelColor(nLedJ2 - 1, 0, 0, lumJ2 / 4);
    strip.setPixelColor(nLedJ2 - 2, 0, 0, lumJ2 / 6);
  }

  // Animation de lancement des kamehas de chaque joueur :
  if (launchKameha == true) {
    currentMillis = millis();
    if (currentMillis - p_millisJ1 >= delayJ1) { // delayJ1 est dans onPressed1(), dans if (chargeKameha == true) {
      p_millisJ1 = currentMillis;
      nLedJ1++; // quelle led j1
    }
    if (currentMillis - p_millisJ2 >= delayJ2) { // etc. pour j2
      p_millisJ2 = currentMillis;
      nLedJ2--; // quelle led j2
    }
    if (nLedJ1 + 1 == nLedJ2) { // Quand les deux leds des joueurs sont en contact, on passe à l'étape suivante
      launchKameha = false;
      clashKameha = true;
    }
    // Mise à jour des données des leds :
    for (int i = 0; i < strip.numPixels(); i++) { // la boucle for() est lue pour toutes les leds
      if (i == 0 || i == nLedJ1) { // Leds début rayon et fin de rayon j1
        strip.setPixelColor(i, lumJ1, lumJ1, 0);
      }
      if (i == strip.numPixels() - 1 || i == nLedJ2) { // Pareil j2
        strip.setPixelColor(i, 0, 0, lumJ2);
      }
      if (i < nLedJ1 && i != 0) { // Leds entre début et fin j1 (lunJ1/12 => intensité lumineuse moins forte)
        strip.setPixelColor(i, lumJ1 / 12, lumJ1 / 12, 0);
      }
      if (i > nLedJ2 && i != strip.numPixels() - 1) { // Pareil j2
        strip.setPixelColor(i, 0, 0, lumJ2 / 12);
      }
    }
  }

  // Affrontement des kamehas :
  if (clashKameha == true) {
    if (sc1 >= scTarget / 2 || sc2 >= scTarget / 2) { // Si un joueur a appuyé "scTarget/2 fois" sur son bouton
      if (sc1 > sc2) { // Si c'est le j1…
        nLedJ1++; // Rayon J1 se déplace vers la droite
        nLedJ2++; // Rayon J2 se déplace vers la gauche
        sc1 = 0; // On remet scores à jour
        sc2 = 0;
      } else if (sc2 > sc1) { // Si c'est le j2…
        nLedJ1--;
        nLedJ2--;
        sc1 = 0;
        sc2 = 0;
      }
    }

    // Mise à jour des données des leds :
    for (int i = 0; i < strip.numPixels(); i++) {
      if (i == 0 || i == nLedJ1) {
        strip.setPixelColor(i, lumJ1, lumJ1, 0);
      }
      if (i == strip.numPixels() - 1 || i == nLedJ2) {
        strip.setPixelColor(i, 0, 0, lumJ2);
      }
      if (i < nLedJ1 && i != 0) {
        strip.setPixelColor(i, lumJ1 / 12, lumJ1 / 12, 0);
      }
      if (i > nLedJ2 && i != strip.numPixels() - 1) {
        strip.setPixelColor(i, 0, 0, lumJ2 / 12);
      }
    }

    // Conditions de victoire :
    if (nLedJ1 >= strip.numPixels() - 4 || nLedJ2 <= 3) { // Si led fin de j1 est à 3 leds de led début j2, et réciproquement…
      winKameha = true;
    }
  }

  // Animation de fin :
  if (winKameha == true) {
    ledWin = abs(cos(a) * 255); // Note cos() renvoie une valeur entre -1 et 1 et abs() renvoie une valeur absolue (tjs positive)
    a += .01;
    if (nLedJ1 >= strip.numPixels() - 4) { // Victoire joueur 1
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, ledWin, ledWin, 0);
      }
    }
    if (nLedJ2 <= 3) { // Victoire joueur 2
      for (int i = 0; i < strip.numPixels(); i++) {
        strip.setPixelColor(i, 0, 0, ledWin);
      }
    }
  }

  strip.show(); // Pour envoyer les données dans le ruban, sans l'appel de cette fonction, le ruban ne change pas de couleur
}


// Fonction appelée quand on appuie sur le bouton 1 :
void onPressed1() {
  if (chargeKameha == true) {
    sc1++;
    lumJ1 = map(sc1, 0, scTarget, 30, 255);
    if (sc1 >= scTarget) { // Condition pour sortir de chargeKameha et aller à l'étape suivante
      delayJ1 = map(sc1, 0, scTarget, 120, 40); // l'intervalle pour passer à
      delayJ2 = map(sc2, 0, scTarget, 120, 40);
      sc1 = 0;
      sc2 = 0;
      chargeKameha = false;
      launchKameha = true;
    }
  }

  if (clashKameha == true) {
    sc1++;
  }

  Serial.print("Button 1 : ");
  Serial.print(sc1);
  Serial.print(" | Button 2 : ");
  Serial.println(sc2);

}

// Fonction appelée quand on appuie sur le bouton 2 :
// (voir les commentaires pour le bouton 1)
void onPressed2() {
  if (chargeKameha == true) {
    sc2++;
    lumJ2 = map(sc2, 0, scTarget, 30, 255);
    if (sc2 >= scTarget) {
      delayJ1 = map(sc1, 0, scTarget, 120, 40);
      delayJ2 = map(sc2, 0, scTarget, 120, 40);
      sc2 = 0;
      sc1 = 0;
      chargeKameha = false;
      launchKameha = true;
    }
  }

  if (clashKameha == true) {
    sc2++;
  }

  Serial.print("Button 1 : ");
  Serial.print(sc1);
  Serial.print(" | Button 2 : ");
  Serial.println(sc2);

}
