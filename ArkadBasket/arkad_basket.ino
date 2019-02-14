//Projet Basketball Arcade en Arduino par Théo Monnin et Bastien ADAM


//importation des bibliothèques

#include "EasyButton.h" //EasyButton pour utiliser le bouton Start
#include "SevenSegmentTM1637.h" //Seven Segment pour utiliser les afficheurs

//On définit les différents composants reliés à Arduino (Bouton, Piezo, afficheurs et capteur à ultrason)

EasyButton BUTTON_START(8);

#define BROCHE_HP 12

#define BROCHE_CLK 2
#define BROCHE_DIO 3

SevenSegmentTM1637 afficheur_time(BROCHE_CLK, BROCHE_DIO);

#define BROCHE_CLK2 6
#define BROCHE_DIO2 7

SevenSegmentTM1637 afficheur_score(BROCHE_CLK2, BROCHE_DIO2);

//Le capteur à ultrason servira à capter la distance dans le panier de basket

#define BROCHE_DECLENCHEMENT 4 //Envoie l'impulsion
#define BROCHE_ECHO 5 //Reçoit l'echo ultrason

//On définit les différentes variables qui nous serviront par la suite

float vitesse = 331.5 + (0.6 * 20); // vitesse du son a 20°C

int distance;
int compteur_point;
int decompte;

unsigned long previousMillis = 0;

const long interval_decompte = 1000;

boolean nouvelle_partie = false;
boolean sondefin = false;

long last_point;

void setup() {

  pinMode(BROCHE_DECLENCHEMENT, OUTPUT);
  pinMode(BROCHE_ECHO, INPUT);
  pinMode(BROCHE_HP, OUTPUT);

  //Initialise le bouton START et sa fonction BUTTON_PRESS lorsque l'on appuie
  BUTTON_START.begin();
  BUTTON_START.onPressed(BUTTON_PRESS);

  //Initialise les afficheurs
  afficheur_score.begin();
  afficheur_score.setBacklight(100);
  afficheur_score.print("GAME");

  afficheur_time.begin();
  afficheur_time.setBacklight(100);
  afficheur_time.print("BALL");

  Serial.begin(9600);

}

void loop() {

  //Démarrage d'une nouvelle partie
  if (nouvelle_partie) {
    afficheur_time.clear();
    afficheur_score.clear();

    //Remet le compteur de points à zéro et le compteur de temps à 31.
    decompte = 31;
    compteur_point = 0;
    nouvelle_partie = false;
    afficheur_score.print(compteur_point);

    //Affiche "3, 2, 1, GO !" avant le début de la partie
    afficheur_time.print(3);
    tone(BROCHE_HP, 440, 400);
    delay(800);
    afficheur_time.print(2);
    tone(BROCHE_HP, 440, 400);
    delay(800);
    afficheur_time.print(1);
    tone(BROCHE_HP, 440, 400);
    delay(800);
    afficheur_time.print("GO !");
    tone(BROCHE_HP, 840, 400);
    delay(800);
    noTone(BROCHE_HP);

  }

  //Boucle durant laquelle le jeu fonctionne les points sont comptés à chaque fois
  //que la distance capté est inférieure a 5cm et le decompte diminue chaque seconde


  while (decompte > 0) {

    unsigned long currentMillis = millis();

    distance = calculDistanceCM();
    Serial.println(distance);
    delay(100);

    //Si distance inférieure à 5 et dernier point marqué il y a plus de 500ms on ajoute un point
    if (distance < 5) {
      if ((millis() - last_point) > 500) {
        tone(BROCHE_HP, 600, 300);
        compteur_point ++;
        last_point = millis();
      }
    }

    //Décompte des secondes sur l'écran secondes en fonction de l'interval du setup "interval_decompte"
    if (currentMillis - previousMillis >= interval_decompte) {
      previousMillis = currentMillis;
      decompte --;
      afficheur_time.clear();
      afficheur_time.print(decompte);
    }

    afficheur_score.print(compteur_point);
    sondefin = true;
  }

  //Son de fin se jouant une fois le décompte terminé, on ne peut plus marquer de point
  if (sondefin) {
    tone(BROCHE_HP, 100, 1000);
    sondefin = false;
  }

  BUTTON_START.read(); //On lit l'état du bouton jusqu'a ce qu'il soit déclenché et relance une nouvelle partie
}

//Permet de démarrer une nouvelle partie lorsque l'on appuie sur le Bouton Start
void BUTTON_PRESS() {
  Serial.println("Nouvelle partie");
  nouvelle_partie = true;
}

// calculDistanceCM permet de récuprer les impulsions du capteur de distance et de les transformer en centimètres
float calculDistanceCM() {

  //envoyer une impulsion
  digitalWrite(BROCHE_DECLENCHEMENT, LOW);
  delayMicroseconds(3);
  digitalWrite(BROCHE_DECLENCHEMENT, HIGH);
  delayMicroseconds(5);
  digitalWrite(BROCHE_DECLENCHEMENT, LOW);

  //recuperer le temps mis par cette impulsion pour un A/R
  float temps_microsecondes = pulseIn(BROCHE_ECHO, HIGH);
  float temps = temps_microsecondes / 1000.0 / 1000.0 / 2;
  float distance = temps * vitesse;

  return distance * 100; //renvoyer distance en cm
}
