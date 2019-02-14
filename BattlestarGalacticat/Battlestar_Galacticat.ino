

#include "SevenSegmentTM1637.h"&

#include "SevenSegmentExtended.h"

SevenSegmentExtended afficheur_joueur1(9, 10);
SevenSegmentExtended afficheur_joueur2(12, 13);

// l'élément piézoélectrique est connecté en broche analogique 0
const char piezo1 = 1;
const char piezo2 = 2;
// seuil de détection en tension et non plus en nombre entre 0 et 1023
const float seuil_detection = 2;

// variable qui va contenir la valeur lue en broche analogique 0
float lecture_capteur1 = 0;
float lecture_capteur2 = 0;
// variable qui va contenir le résultat du calcul de la tension
float tension1 = 0;
float tension2 = 0;
// variable utilisée pour allumer ou éteindre la LED à chaque "Toc"

int score_joueur1 = 0;
int score_joueur2 = 0;


#include <Servo.h>


Servo servo1;
Servo servo2;

int buttonPin1 = 7;
int buttonPin2 = 8;
int buttonState1 = 0;
int buttonState2 = 0;



void setup() {

  */
  afficheur_joueur1.begin();            // On initialse le display
  afficheur_joueur1.setBacklight(100);  // On règle la luminosité sur 100%
  afficheur_joueur2.begin();            // On initialse le display
  afficheur_joueur2.setBacklight(100);  // On règle la luminosité sur 100%

  afficheur_joueur1.print(score_joueur1);
  afficheur_joueur2.print(score_joueur2);
  delay(1000); // délai de 1000 ms


  // on définit les deux pin des servos
  servo1.attach(2);
  servo2.attach(4);

  // On initialise le button comme un input
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
  Serial.begin(9600);
}

void loop() {

  //on lit la valeur du bouton
  //Serial.println(digitalRead(buttonPin1));
  //Serial.println(digitalRead(buttonPin2));
  afficheur();
  if ((digitalRead(buttonPin1) == 0) && (digitalRead(buttonPin2) == 0)) {
    // on définit les cycles de mouvement du servo1
    servo1.write(90);
    //on définit les cycles de mouvement du servo2
    servo2.write(90);
  }
  else {
    servo1.write(0); //sinon le moteur s'arrête
    servo2.write(0); //sinon le moteur s'arrête
  }
}

void afficheur(){

  //afficheur_joueur1.clear();
  //afficheur_joueur2.clear();
  // lecture de la valeur en sortie du capteur
  lecture_capteur1 = analogRead(piezo1);
  lecture_capteur2 = analogRead(piezo2);
  // conversion de cette valeur en tension
  tension1 = (lecture_capteur1 * 5.0) / 1024;
  tension2 = (lecture_capteur2 * 5.0) / 1024;


  if (tension1 >= seuil_detection)  // comparaison de deux tensions
  {
    // on modifie l'état de la LED pour le passer à son état opposé
    // application du nouvel état en broche 2
    // envoi vers l'ordinateur, via la liaison série,
    // des données correspondant au Toc et à la tension
    Serial.println("Toc !");
    Serial.print("Tension = ");
    Serial.print(tension1);
    Serial.println(" V");
    score_joueur1 ++;
    afficheur_joueur1.clear();
    afficheur_joueur1.print(score_joueur1);
    delay(200);
  }

  if (tension2 >= seuil_detection)  // comparaison de deux tensions
  {
    Serial.println("Lol !");
    Serial.print("Tension = ");
    Serial.print(tension2);
    Serial.println(" V");
    score_joueur2 ++;
    afficheur_joueur2.clear();
    afficheur_joueur2.print(score_joueur2);
    delay(200);
  }

}
