#include "SevenSegmentTM1637.h"                // On inclu the SevenSegmentTM1637 library
#include "notes.h"                             // On inclu notes.h

// moteur
#include <Servo.h>                             // on inclu le servo moteur
#define BROCHE_SERVO 10                      // on défini le port sur lequel est le servo moteur
#define BROCHE_HP    7                    // on defini le port sur lequel est la piezo
Servo servo;                                   //le servo s'appelle servo

// circuit avec les capteurs pressions
int pression = A0;                             //définir le port sur lequel est branché le capteur de pression
int pression2 = A2;                            //définir le port sur lequel est branché le capteur de pression
int etatPression;
int etatPression2;//définir l'état du capter pression (cliqué ou non cliqué)
int state = LOW;                               //définir l'état dans lequel est notre circuit (allumé ou éteint en locurence) par défaut il est éteint
int etatPressionBefore;                        //variable pour stocké l'état précédent dans lequel était notre circuit (selon etatButton)
int etatPressionBefore2;
// musique
int nombre_notes = 4;                          // Nombre de notes qui composent la mélodie
int melodie[] = {  NOTE_FAD3, NOTE_MI3, NOTE_RE3, NOTE_DO3 }; // Définir les notes de la mélodie
int duree_note[] = {  4, 4, 4, 64 };           // Définir la durée de chaque note

// écran
const byte PIN_CLK = 4;                        // define CLK pin (any digital pin)
const byte PIN_DIO = 3;                        // define DIO pin (any digital pin)
SevenSegmentTM1637    display(PIN_CLK, PIN_DIO);
// temps
unsigned long maxtime = 10000;
bool gameover = false;
bool newgame = true;
bool displayTime = true;


unsigned long currentMillis;
int timeToDisplay;


unsigned long previousMillis = 0;
const long interval = 10000;



void setup() {

  // on déclare le pinMode de notre led est rus trus er et de nos capteurs pressions 1 et 2  pinMode(led, OUTPUT);
  pinMode(pression, INPUT);
  pinMode(pression2, INPUT);
  // écran
  Serial.begin (9600);                         // initialise la connection avec le serial 9600
  display.begin();                             // initialise l'écran
  display.setBacklight(100);                   // luminosité à 100 %
  // servo
  servo.attach(BROCHE_SERVO);
  servo.write(90);
  //servo brancher sur la broche servo oui
  pinMode(BROCHE_HP, OUTPUT);

}


void loop() {

  //servo.write(random(80, 100));
  etatPression = analogRead(pression);
  etatPression2 = analogRead(pression2);

  //si on est en phase de démarrage
  if (newgame == true) {
    //si on commence le jeu, il n'est plus en phase de démarrage
    if (etatPression2 > 300) {

      newgame = false;
      delay(500);
      previousMillis = millis();
    }
    // si on le démarre pas on écrit press to start
    else {
      servo.write(90);
      display.print("PRESS 2 START 3 2 1 . ");
    }

    Serial.println(etatPression);
  }
  //si on est pas en phase de démarrage
  else {

    // si on a pas perdu : le jeu joue
    if ( gameover == false) {                               //si le circuit est "allumé"

      //jouerMelodie();                                 //lancer la mélodie
      servo.write(random(80, 110));

      currentMillis = millis();

      // si le temps arrive au bout : on a perdu
      if (currentMillis - previousMillis >= interval) {

        servo.write(90);
        display.print("NOT FAST ENOUGH ! TRY AGAIN !");
        delay(500);
        gameover = true; // t'as perdu ! t'es nul

      }
      // si on a pas perdu et que le temps n'est pas au bout
      else if (displayTime) {

        timeToDisplay = (10800 - (currentMillis - previousMillis)) ;
        if (timeToDisplay > 0) {
          display.print(timeToDisplay); //on affiche le temps
        }
        else {
          display.print("0000");
        }

        // si on arrive au bout avant la fin du temps on a gagné
        if (etatPression > 300) {
          servo.write(90);
          displayTime = false;
          display.print(timeToDisplay);
          delay(2500);
          display.print("CONGRATULATIONS !  ");
          // delay(500);
          gameover = false; //on relance
          newgame = true;


        }
      }

    }
    else { //si gameover = true

      servo.write(90);
      display.print("game over");

      if (etatPression2 > 300) { //si on rappuis on relance

        newgame = true;
        gameover = false;
        delay(1000);
      }
    }

  }
}
