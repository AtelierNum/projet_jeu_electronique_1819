//BIBLIOTHEQUES

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#include <EasyButton.h>

#include <Servo.h>

#include "Musique.h"



//BROCHES

EasyButton boutonReset(4);

#define boutonRouge 2
#define boutonBleu 3

#define ServoBleu 8
#define ServoRouge 9
Servo servoB;
Servo servoR;

#define rubanLed 6
#define nombrePixel 5
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nombrePixel, rubanLed, NEO_GRB + NEO_KHZ800);



// VARIABLES

boolean mancheFinie = false;
boolean manche = false;
boolean victoireDuel = false;

int posServoInitiale = 0;
int posServoMort = 90;

int numLedR; // Numéro de la led dans l'avancement des points du joueur rouge
int numLedB; // Numéro de la led dans l'avancement des points du joueur bleu
//int lumR = 30; // Lumière joueur rouge
//int lumB = 30; // Lumière joueur bleu

int ledVictoire; // Animation des leds lors d'une victoire
float a;



// SETUP

void setup() {
  Serial.begin(9600);

  randomSeed(analogRead(0));

  boutonReset.begin(); // Initialisation du BoutonReset
  boutonReset.onPressed(PresseBoutonReset);

  pinMode(boutonRouge, INPUT);
  pinMode(boutonBleu, INPUT);

  servoB.attach(ServoBleu);
  servoR.attach(ServoRouge);

  servoR.write(posServoInitiale);
  servoB.write(posServoInitiale);

  pinMode(Piezo, OUTPUT);

  numLedR = 0; // n° de la led du joueur rouge au début
  numLedB = 4; // n° de la led du joueur bleu au début

  pixels.begin();
  pixels.setBrightness(100);
  for (int i = 0; i < nombrePixel; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();



}



// LOOP

void loop() {

  boutonReset.read();

  if (manche) {

    // Si je joueur rouge tire en premier
    if (digitalRead(boutonRouge) == HIGH) {

      // Le pistolet tire
      TirerBang();

      // Le Cowboy bleu meurt
      servoR.write(posServoMort);


      // On ajoute un point au joueur rouge
      numLedR++;

      Serial.println(numLedR);
      Serial.println(numLedB);

      // On affiche les points sur les leds
      for (int i = 0; i <= numLedR; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();

      delay(4000);
      // La manche est finie
      mancheFinie = true;
      manche = false;
    }

    // Si le joueur bleu tire en premier
    if (digitalRead(boutonBleu) == HIGH) {

      // Le pistolet tire
      TirerBang();

      // Le Cowboy rouge meurt
      servoB.write(posServoMort);


      // On ajoute un point au joueur bleu
      numLedB--;

      Serial.println(numLedR);
      Serial.println(numLedB);

      // On affiche les points sur les leds
      for (int i = 4; i >= numLedB; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
      pixels.show();

      delay(4000);
      // La manche est finie
      mancheFinie = true;
      manche = false;
    }

  }


  if (mancheFinie) {

    if (numLedR >= 2 || numLedB <= 2) { // Si un des deux joueurs est à 3 points
      victoireDuel = true;
    }

    else {
      // On relève les cowboys
      servoR.write(posServoInitiale);
      servoB.write(posServoInitiale);
      delay(1000);

      // On lit la musique qui a une durée random
      JouerMelodie();

      // On passe à la manche suivante
      manche = true;
      mancheFinie = false;
    }
  }


  if (victoireDuel) {
    ledVictoire = abs(cos(a) * 255); // Note cos() renvoie une valeur entre -1 et 1 et abs() renvoie une valeur absolue (tjs positive)
    a += .01;

    if (numLedR >= 2) { // Victoire joueur rouge
      for (int i = 0; i < nombrePixel; i++) {
        pixels.setPixelColor(i, pixels.Color(ledVictoire, 0, 0));
      }
    }

    if (numLedB <= 2) { // Victoire joueur bleu
      for (int i = 0; i < nombrePixel; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, ledVictoire));
      }
    }
    pixels.show();
  }
}



void PresseBoutonReset() {

  // On remet les Servo à leur position d'origine pour relever les Cowboys
  servoB.write(posServoInitiale);
  servoR.write(posServoInitiale);
  delay(1000);

  // On éteint les leds qui servent à compter les points
  for (int i = 0; i < nombrePixel; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();

  numLedR = -1; // n° de la led du joueur rouge au début (score)
  numLedB = 5; // n° de la led du joueur bleu au début (score)

  // On lance le jeu

  // On lit la musique qui a une durée random
  JouerMelodie();

  // On lance la première manche
  manche = true;

}
