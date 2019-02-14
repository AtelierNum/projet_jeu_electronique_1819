#include <EasyButton.h> //ajouter bibliothèque pour écouter boutons
#include "SevenSegmentTM1637.h" //ajouter bibliothèque pour afficher segments sur les afficheurs

#define BROCHE_CLK1    5 //position de la broche CLK de l'afficheur1
#define BROCHE_DIO1    4 //position de la broche DIO de l'afficheur1

#define BROCHE_CLK2    7 //position de la broche CLK de l'afficheur2
#define BROCHE_DIO2    6 //position de la broche DIO de l'afficheur2

SevenSegmentTM1637 afficheur1(BROCHE_CLK1, BROCHE_DIO1); //associer la position des broches de l'afficheur 1
SevenSegmentTM1637 afficheur2(BROCHE_CLK2, BROCHE_DIO2);  //associer la position des broches de l'afficheur 2

EasyButton btn1(2);  //position du bouton 1 sur la pin 2
EasyButton btn2(3);   //position du bouton 2 sur la pin 3

// initialisation
int n1 = 0;
int n2 = 0;

// initialisation
unsigned long previousMillis = 0;

boolean reset_manche = true;
long manche_start;
long maintenant;
long duree_bleu;
long duree_rouge;
int score_modifieur = 0;
int compteur = 0;

// inclure la bibliothèque fast-led
#include <FastLED.h>
#define NUM_LEDS 64 // définir le nombre de leds
CRGBArray<NUM_LEDS> leds; // définir un tableau de données chaque entrée du tableau représentera une led.

// on reprend la matrice de led de la plaque Adafruit. 0 signifi led éteinte et 1 led allumée.

// le chiffre 1
int one[64] = {0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 1, 1, 0, 0, 0,
               0, 0, 1, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0
              };

// le chiffre 2
int two[64] = {0, 0, 0, 1, 1, 0, 0, 0,
               0, 0, 1, 0, 0, 1, 0, 0,
               0, 0, 1, 0, 0, 1, 0, 0,
               0, 0, 0, 0, 1, 0, 0, 0,
               0, 0, 0, 1, 0, 0, 0, 0,
               0, 0, 1, 0, 0, 0, 0, 0,
               0, 0, 1, 0, 0, 0, 0, 0,
               0, 0, 1, 1, 1, 1, 0, 0
              };

// le chiffre 3
int three[64] = {0, 0, 1, 1, 1, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 0,
                 0, 0, 1, 1, 1, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 0,
                 0, 0, 0, 0, 0, 1, 0, 0,
                 0, 0, 1, 1, 1, 1, 0, 0
                };


void setup() {

  // on initialise notre strip de led sur la pin 9
  FastLED.addLeds<NEOPIXEL, 9>(leds, NUM_LEDS);


  //initialisation de l'afficheur
  afficheur1.begin();
  afficheur2.begin();
  afficheur1.setBacklight(100);
  afficheur2.setBacklight(100);
  afficheur1.print(" GO ");
  delay(50);
  afficheur2.print(" GO ");
  delay(50);

  Serial.begin(9600);

  //initialisation du bouton 1
  btn1.begin();
  btn1.onPressed(jePresse); //déclencher fonction jepresse quand on clic

  //initialisation du bouton 2
  btn2.begin();
  btn2.onPressed(jePresse2); //déclencher fonction jepresse quand on clic

}

void loop() {

  btn1.read(); // Lire en boucle l'état du bouton 1
  btn2.read(); // Lire en boucle l'état du bouton 2

  if (reset_manche) {
    duree_bleu = random(500, 8400); //Durée de la couleur bleu selon une fourchette de temps en millisecondes
    duree_rouge = random(300, 2300); //Durée de la couleur rouge selon une fourchette de temps en millisecondes
    reset_manche = false;
    manche_start = millis();
  }

  maintenant = millis() -  manche_start;

  if (maintenant < duree_bleu) {
    // Serial.println("on est en période bleue");
    score_modifieur = 1;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(160, 255, 50);
    }
    FastLED.show();
    //delay(100);
  }

  if ( (maintenant > duree_bleu) && (maintenant < duree_bleu + duree_rouge) ) {
    //Serial.println("on est en période rouge");
    score_modifieur = -10;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(0, 255, 50);
    }
    FastLED.show();
    //delay(100);
  }

  if (maintenant > duree_bleu + duree_rouge) {
    score_modifieur = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200, 255, 50);
    }
    FastLED.show();
    reset_manche = true;
  }

}

//fonction jepresse pour joueur 1
void jePresse() {



  n1 += score_modifieur;
  afficheur1.clear();  // initialisation de l’afficheur 1
  afficheur1.print(n1);  //afficher le score n1 sur l’afficheur
  if (n1 >= 100) {  //quand le joueur atteind 100pts
    afficheur1.print("TOP");  //il gagne
    afficheur2.print("NUL");  //l’autre perd
    score_modifieur = 0;  //initialiser le score_modifieur
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * three[i], 255, 70*three[i]);
    }
    FastLED.show();
    delay(2500);
    afficheur1.clear();   // initialisation de l’afficheur 1
    afficheur2.clear(); // initialisation de l’afficheur 2
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * two[i], 255, 70*two[i]);
    }
    FastLED.show();
    delay(2500);
    n1 = 0; //initialiser les scores
    n2 = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * one[i], 255, 70*one[i]);
    }
    FastLED.show();
    delay(2500);
    afficheur1.print(" GO "); //afficher “GO” sur les afficheurs
    afficheur2.print(" GO ");
    reset_manche = true;
  }



}


//fonction jepresse pour joueur 2
void jePresse2() {

  n2 += score_modifieur;
  afficheur2.clear(); // initialisation de l’afficheur 2
  afficheur2.print(n2); //on affiche le score sur l’afficheur
  if (n2 >= 100) {  //quand joueur 2 atteint 100pts
    afficheur1.print("NUL");  //l’autre perd
    afficheur2.print("TOP");  //lui gagne
    score_modifieur = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * three[i], 255, 70*three[i]);
    }
    FastLED.show();
    delay(2500);
    afficheur1.clear(); // initialisation de l’afficheur 1
    afficheur2.clear(); // initialisation de l’afficheur 2
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * two[i], 255, 70*two[i]);
    }
    FastLED.show();
    delay(2500);
    n1 = 0; // initialisation des scores
    n2 = 0;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CHSV(200 * one[i], 255, 70*one[i]);
    }
    FastLED.show();
    delay(2500);
    afficheur1.print(" GO ");    //afficher “GO” sur les afficheurs
    afficheur2.print(" GO ");
    reset_manche = true;
  }


