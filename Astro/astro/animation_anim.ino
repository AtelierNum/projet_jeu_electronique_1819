// inclure la bibliothèque fast-led
#include <FastLED.h>
#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#ifdef __AVR__
#include <avr/power.h>
#endif
#include "notes.h"

#ifndef PSTR
 #define PSTR // Make Arduino Due happy
#endif



#define NUM_LEDS 64 // définir le nombre de leds pour la matrice 8x8
#define NUM_LEDS2 3 // définir le nombre de leds pour le ruban de led

#define BROCHE_HP 7 // définir la pin où est branchée le buzer piezo

#define PIN            2 // définir la pin où est branchée la matrice 8x8
#define NUMPIXELS      64 // définir le nombre de leds pour NeoPixels

//definition de la matrice 8x8 avec la bibliothèque NeoMatrix et GFX
Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_LEFT +
  NEO_MATRIX_ROWS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

//initialisation de la matrice 8x8 avec la bibliothèque NeoPixel
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//initialisation du ruban de led
const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

//définition du nombre de notes pour les fonctions jouerMelodie et jouerMelodie2
int nombre_notes = 1;
int nombre_notes2 = 8;

//définition du blink sans delay
unsigned long previousMillis = 0;        // will store last time LED was updated
int interval = 1000;           // interval at which to blink (milliseconds)

// définition de la durée des notes jouées
int duree_note[] = {
  4
};
int duree_not2e[] = {
  4, 20, 8, 4, 4, 4, 4, 4
};

// définition des notes jouées
int melodie[] = {
  NOTE_DO4
};
int melodie2[] = {
   NOTE_LA3, NOTE_SOL3, NOTE_LA3, 0, NOTE_SI3, NOTE_DO4
};

// définir la pin où est son branchés les boutons
const int buttonPinr = 8;
const int buttonPinl = 9;

int buttonStater = 0;
int buttonStatel = 0;

CRGBArray<NUM_LEDS> leds; // définir un tableau de données chaque entrée du tableau représentera une led.
CRGBArray<NUM_LEDS2> leds2; // définir un tableau de données chaque entrée du tableau représentera une led.

// définition de chaque ligne de la matrice 8x8, 0 = led éteinte et 1 = led allumée
int z[] = {0, 0, 0, 0, 0, 0, 0, 0};
int a[] = {0, 1, 1, 1, 1, 1, 1, 1};
int b[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int c[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int d[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int e[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int f[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int g[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int h[] = {0, 0, 0, 0, 0, 0, 0 , 0};
int j[] = {0, 0, 0, 0, 0, 0, 0 , 0};


int index = 0;
int u = 59; //position de la led du joueur
bool gameover = false;
int lives = 3; //initialisation du nombre de vies du joueur
int compteur = 0; // valeur pour donner la vitesse du joueur




void setup() {
  Serial.begin(9600);
  // on initialise la matrice 8x8 sur la pin 2 et le ruban de led sur la pin 5
  FastLED.addLeds<NEOPIXEL, 2>(leds, NUM_LEDS);
  FastLED.addLeds<NEOPIXEL, 5>(leds2, NUM_LEDS2);

  matrix.begin(); // initiatialisation de la bibliothèque NeoMatrix
  matrix.setTextWrap(false);
  matrix.setBrightness(40); //définition de la luminosité de la matrice 8x8
  matrix.setTextColor(colors[0]);

  pinMode(buttonPinr, INPUT);
  pinMode(buttonPinl, INPUT);

  pixels.begin(); // initiatialisation de la bibliothèque NeoPixel
  pixels.setBrightness(25);

// initialisation des vies sur le ruban de led
  for (int i = 0; i < 3; i++) {
    leds2[i] = CHSV(250, 240, 60);
  }
  pinMode(BROCHE_HP,     OUTPUT);
}

int x = matrix.width();
int pass = 0;

void loop() {

//on débute par une condition, si lives est supérieur à 0 alors
//on continu la loop
  if (lives > 0) {
    compteur++;
    // on lit la valeur des boutons
    buttonStater = digitalRead(buttonPinr);
    buttonStatel = digitalRead(buttonPinl);

// si le bouton de droite est appuyé on incrémente 1 à u ce qui
// bouge la led à droite
    if (buttonStater == HIGH) {
      if (compteur % 27 == 0) u++;
    }

// si le bouton de droite est appuyé on enlève 1 à u ce qui
// bouge la led à gauche
    if (buttonStatel == HIGH) {
      if (compteur % 27 == 0) u--;
    }
// on bloque la valeur de u entre 56 et 63 pour que le joueur reste sur la dernière ligne de la matrice
    if (u < 56) u = 56;
    if (u > 63) u = 63;
// on éteind toutes les leds sur la dernière ligne
    for (int i = 56 ; i < 64 ; i++) {
      leds[i] = CHSV(0, 0, 0);
    }
    leds[u] = CHSV(250, 240, 60); // on défini la couleur de la led du joueur


    unsigned long currentMillis = millis();

// blink() : boucle dans la loop selon le temps passé dans la loop pour éviter d'utiliser delay
    if (currentMillis - previousMillis >= interval) {
      previousMillis = currentMillis;
      if (interval > 300) interval = interval - 7; //accélération de la vitesse de descente des astéroïdes



      index += 1;

/// on défini la couleur de chaque led sur chaque ligne de la matrice 8x8
      for (int i = 0; i < 8; i++) {
        leds[i + (0 * 8)] = CHSV(180, 240, 60 * a[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (1 * 8)] = CHSV(180, 240, 60 * b[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (2 * 8)] = CHSV(180, 240, 60 * c[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (3 * 8)] = CHSV(180, 240, 60 * d[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (4 * 8)] = CHSV(180, 240, 60 * e[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (5 * 8)] = CHSV(180, 240, 60 * f[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (6 * 8)] = CHSV(180, 240, 60 * g[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (7 * 8)] = CHSV(180, 240, 60 * h[i]);
      }
      for (int i = 0; i < 8; i++) {
        leds[i + (7 * 8)] = CHSV(180, 240, 60 * j[i]);
      }

 // on descend toutes les lignes d'un rang
      memcpy(j , h , 16);
      memcpy(h , g , 16);
      memcpy(g , f, 16);
      memcpy(f , e, 16);
      memcpy(e , d, 16);
      memcpy(d , c, 16);
      memcpy(c , b, 16);
      memcpy( b , a, 16);

// condition de collision entre le joueur et chaque led de la dernière ligne
      if (j[u % 8] == 1) {
        lives--;
        if (lives == 3) {
        }
        else if (lives == 2) { //si 2 vies alors on éteint la 3ème led
          leds2[2] = CHSV(0, 0, 0);
        }
        else if (lives == 1) { //si 1 vies alors on éteint la 2ème led
          leds2[1] = CHSV(0, 0, 0);
        }
        else if (lives == 0) { //si 0 vies alors on éteint la 1ère led
          leds2[0] = CHSV(0, 0, 0);
        }
        FastLED.show(); // on actualise le ruban de led pour afficher les vies
        jouerMelodie(); // joue une note pour indiquer la collision


      }
      int zed[8];
/// permet d'afficher un mur de leds, une ligne sur deux
      if (index % 2 == 0) {
        for (int i = 0 ; i < 8 ; i++) {
          zed[i] = random(0, 2);
          //Serial.print(zed[i]);
        }

      }
      else {
        for (int i = 0 ; i < 8 ; i++) {
          zed[i] = 0;
        }
      }
      memcpy(a , zed, 16);
    }


     FastLED.show(); // on actualise le ruban de led

// si on perd toutes les vies on lance la melodie2
    if (lives == 0) {
      jouerMelodie2();
    }
// on lance l'animation du game over
  } else {
  matrix.fillScreen(0);
  matrix.setCursor(x, 0);
  matrix.print(F("GAME OVER"));
  if(--x < -84) {
    x = matrix.width();
    if(++pass >= 3) pass = 0;
    }
    matrix.show();
  delay(100);
  }
}

//fonction pour jouer des notes sur le buzer piezo
  void jouerMelodie2() {

  for (int note_a_jouer = 0; note_a_jouer < nombre_notes2; note_a_jouer++) {

    int duree_note_a_jouer2 = 1000 / duree_note[note_a_jouer];
    tone(BROCHE_HP, melodie2[note_a_jouer], duree_note_a_jouer2);

    int pause_entre_notes = duree_note_a_jouer2 * 1.30;
    delay(pause_entre_notes);

    noTone(BROCHE_HP);
  }
}


//fonction pour jouer des notes sur le buzer piezo
void jouerMelodie() {

  for (int note_a_jouer = 0; note_a_jouer < nombre_notes; note_a_jouer++) {

    int duree_note_a_jouer = 1000 / duree_note[note_a_jouer];
    tone(BROCHE_HP, melodie[note_a_jouer], duree_note_a_jouer);

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    noTone(BROCHE_HP);
  }
}
