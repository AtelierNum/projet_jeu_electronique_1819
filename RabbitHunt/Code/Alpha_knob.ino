/* Librarie du servo moteur */
#include <Servo.h>
Servo servoA;
Servo servoB;
Servo servoC;

//inclure la bibliothèque dédiée à l'afficheur 4 digit
#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"
const byte PIN_CLK = 3;   // define CLK pin (any digital pin)
const byte PIN_DIO = 2;   // define DIO pin (any digital pin)
SevenSegmentExtended      display(PIN_CLK, PIN_DIO);




/* Définition des variables */
int photoresA = 0;  // Sortie de la photo-résistance , une pour chaque lapin
int photoresB = 1;
int photoresC = 2;


int valA; // valeur actuelle de la photorésistance
int valeurbaseA = 0; //valeur de calibration de la photorésistance

int valB; // valeur actuelle de la photorésistance
int valeurbaseB = 0; //valeur de calibration de la photorésistance

int valC; // valeur actuelle de la photorésistance
int valeurbaseC = 0; //valeur de calibration de la photorésistance


//////////// LES VARIABLES SI DESSOUS SONT COPIER POUR CHAQUE LAPIN

long temps_faitA = 0; //Référentiel de temps
int servostateA = 0;// Variable de l'état du servo moteur, =1 le servo monte, =0 le servo baisse
int testshootA = 0;// Variable qui quand est égal a 0, le lapin peut être tirer
int testshooterA = 0;// variable quand est egal a 1, est tirer
int testfinA = 0;// Variable qui met fin à la période de tire ( bloque le score pour éviter que le lapin soit tirer plusieurs fois quand il peut être tirer)
int compshootA = 0;// Variable ui actionne le compteur de score
int etatA = 0;// variable qui permet de d'ajouter millis() a startTimeB à certain moment pour relancer le "delay"
int testvieA = 0; // Variable qui permet d'enlever une seul vie quand le lapin se baisse
unsigned long startTimeA = 0;// variable qui prend la valeur de millis pour relncer le "delay"

////////////////

long temps_faitB = 0;
int servostateB = 0;
int testshootB = 0;
int testshooterB = 0;
int testfinB = 0;
int compshootB = 0;
int etatB = 0;
int testvieB = 0;
unsigned long startTimeB = 0;

long temps_faitC = 0;
int servostateC = 0;
int testshootC = 0;
int testshooterC = 0;
int testfinC = 0;
int compshootC = 0;
int etatC = 0;
int testvieC = 0;
unsigned long startTimeC = 0;

int vie = 3;
int startgame = 0;
int endgame = 0;
int score = 0;


void setup() {
  Serial.begin(9600); //afficher les valeurs dans moniteur de série
  display.begin();            // initializes the display
  display.setBacklight(100);  // set the brightness to 100 %

  servoA.attach(8); //Sortie du servo moteur A
  servoA.write(90);

  servoB.attach(11); //Sortie du servo moteur B
  servoB.write(90);

  servoC.attach(10); //Sortie du servo moteur C
  servoC.write(90);

  calibration(); // lance la calibration
}

void loop() {
  valA = analogRead(photoresA); //Lecture de la valeur de la photorésistance A
  valB = analogRead(photoresB);// ...B
  valC = analogRead(photoresC);//....C

  digit(); // lance l'affichage et le lancement et fin de partie

  if ( endgame == 0 && startgame == 1) { //  condition pour savoir si la partie va commencer ou se finir
    temps(); // lance le système de delay d'apparition des lapin et de la vitesse d'apparition en fonction du score
   servoa(); // on lance la monter et descente du servo A en fonction du temps
   servob();//...B
   servoc();//...C
  }
}
