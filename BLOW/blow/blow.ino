//-----LIBRAIRIES-----//
#include <FastLED.h>
//#include "SevenSegmentTM1637.h"


//-----DIGIT-----//
const byte PIN_CLK_1 = 13;   // define CLK pin (any digital pin)
const byte PIN_DIO_1 = 12;   // define DIO pin (any digital pin)
const byte PIN_CLK_2 = 11;   // define CLK pin (any digital pin)
const byte PIN_DIO_2 = 10;   // define DIO pin (any digital pin)
//SevenSegmentTM1637    //afficheur_1(PIN_CLK_1, PIN_DIO_1);
//SevenSegmentTM1637    //afficheur_2(PIN_CLK_2, PIN_DIO_2);
int compteur = 0;
int score_1 = 0;
int score_2 = 0;


//-----MICRO-----//
#define pinMicroJoueur1     A1
#define pinMicroJoueur2     A2
int threshold = 350;
int cri_1 = 0;
int cri_2 = 0;
long sum_1 = 0;
long sum_2 = 0;
int premier_souffle = true;



//-----LEDS-----//
#define ledNombre           130
#define ledPin              8

//position de la led
int ledPosition =  ledNombre / 2;

// sens du mouvement
int sens = -1;
int vitesse_initiale = 25;
int vitesse = vitesse_initiale;

//taille des bases
int base = 9;



CRGB leds[ledNombre];



//-----FONCTIONNEMENT-----//
//manche gagné
int joueur_1_manche = false;
int joueur_1_partie = false;

int joueur_2_manche = false;
int joueur_2_partie = false;

int premier_tour = true;


void setup() {
  //Serial.begin(9600);
  //Serial.println("setup");

  //---INIT LEDS---//
  FastLED.addLeds<NEOPIXEL, ledPin>(leds, ledNombre);
  LEDS.setBrightness(255);
  FastLED.clear();

  //---INIT DIGIT---//
  //afficheur_1.begin();
  //afficheur_1.setBacklight(85);
  //afficheur_1.print("INIT");
  //afficheur_2.begin();
  //afficheur_2.setBacklight(85);
  //afficheur_2.print("INIT");
  //delay(1000);

}

void loop() {

  black();
  affichage_bases();

  //-----Début du Jeux-----//
  //Loop que qu'une manche est en cours
  if (joueur_1_manche == false && joueur_2_manche == false) {


    //-----ANNONCE DE LA DIRECTION DE LA BALLE EN DEBUT DE TOUR-----//
    if ( ( premier_tour == true ) && sens == -1 ) {
      envoi_Player_1();
      //Serial.println("Premier tour");
    }

    if ( ( premier_tour == true ) && sens == 1 ) {
      envoi_Player_2();
      //Serial.println("Premier tour");
    }

    //-----AFFICHAGE DU NOMBRE D'ECHANGES--------//
    affichage_compteur();




    //-----PROJECTILE-----//
    leds[ledPosition] = CHSV(0, 0, 255);
    FastLED.show();




    //-----ANALYSE DU SON-----//
    //Player 1//
    for (int i = 0; i < 32; i++)
    {
      sum_1 += analogRead(pinMicroJoueur1);
    }

    sum_1 >>= 5;

    if (sum_1 > threshold) {
      cri_1 = 1;
    } else {
      cri_1 = 0;
    }

    //Player 2//
    for (int i = 0; i < 32; i++)
    {
      sum_2 += analogRead(pinMicroJoueur2);
    }

    sum_2 >>= 5;

    if (sum_2 > threshold) {
      cri_2 = 1;
    } else {
      cri_2 = 0;
    }



    //---GESTION DU SENS DU PROJECTILE---//
    ledPosition += sens;

    //Player 1
    if ( ( ledPosition < base ) && ( cri_1 == 1 ) ) {
      sens = 1;
      //Serial.println("Renvoie de 1 vers 2");
    }

    //Player 2
    if ( (ledPosition > ledNombre - base) && (cri_2 == 1) ) {
      sens = -1;
      //Serial.println("Renvoie de 2 vers 1");
    }

    //Si le projectile change de sens on augmente sa vitesse et on ajoute un échange au compteur
    if ( (ledPosition > ledNombre - base) && (cri_2 == 1) && ( premier_souffle == true ) || (ledPosition < base) && (cri_1 == 1) && ( premier_souffle == true ) ) {
      compteur += 2;
      vitesse *= 0.60;
      premier_souffle = false;
      //Serial.println(vitesse);
      //Serial.println("Renvoie donc ajout vitesse et compteur");
      //Serial.print("compteur : ");
      //Serial.println(compteur);
    }


    //Lorsque la LED est dans la base il est possible que le son atteigne plusieurs fois "threshold" ce qui additionnerait plusieurs échanges et augmenterait la vitesse plusieurs fois.
    //"premier_souffle" permet d'empêcher que l'on rentre plusieurs fois dans la boucle au dessus.
    if ( ( ledPosition == ledNombre / 2 ) ) {
      premier_souffle = true;
    }

    //On vérifie que le premier tour est passé pour ne pas jouer plusieurs fois l'animation de début de manche.
    premier_tour = false;
  }




  //---DETECTION DE BALLE DANS BASE---//
  //Correspond au moment où la LEDs touche la base de l'un des deux joueurs
  //Player 1
  if ( (ledPosition < 1) ) {
    joueur_1_manche = true;

    //Serial.println("balle touche base 1");
    //Serial.println("Donc ajout des scores");
    //Serial.print("Score joueur 1 : ");
    //Serial.print(score_1);
    //Serial.print(", Score joueur 2 : ");
    //Serial.println(score_2);
  }
  //Player 2
  if ( (ledPosition > ledNombre - 1) ) {
    joueur_2_manche = true;

    //Serial.println("balle touche base 2");
    //Serial.println("Donc ajout des scores");
    //Serial.print("Score joueur 1 : ");
    //Serial.print(score_1);
    //Serial.print(", Score joueur 2 : ");
    //Serial.println(score_2);
  }




  //-----SI LA PARTIE EST FINI-----//

  //On vérifie d'abord si la partie est gagnée pour ne pas jouer l'animation de fin de manche + l'animation de fin de partie

  if ( ( score_1 + compteur >= (ledNombre / 2) ) && ( joueur_2_manche ==  true ) || ( score_2 + compteur >= (ledNombre / 2) ) && ( joueur_1_manche ==  true ) ) {
    //On annonce la fin de la partie
    //Serial.println("__________");
    //Serial.println("Fin de la Partie");
    //Serial.print("Score joueur 1 : ");
    //Serial.print(score_1);
    //Serial.print("bada");
    //Serial.print(", Score joueur 2 : ");
    //Serial.println(score_2);

    //On détermine qui a gagné la partie et on lance l'animation de fin de partie

    FastLED.clear();
    FastLED.show();

    //Player 1 à perdu la partie
    if ( ( joueur_1_manche ==  true ) ) {
      //On met à jours les paramètres
      joueur_1_partie = true;

      //On lance l'animation des LEDs fin de partie

      //Serial.println("anim fin de partie joueur 2 winner");

      //-----------------------------------------------------ICI anim fin partie----------------------------------------------------
      animation_partie_win_2();

    }

    //Player 2 à perdu la partie
    if ( ( joueur_2_manche ==  true ) ) {
      joueur_2_partie = true;

      //Serial.println("anim fin de partie joueur 1 winner");

      //-----------------------------------------------------ICI anim fin partie----------------------------------------------------
      animation_partie_win_1();


    }


    //On attend
    //Serial.println("delay de fin de partie");
    delay(6000);



    //On annonce la nouvelle partie
    //Serial.println();
    //Serial.println();
    //Serial.println("////////////////////");
    //Serial.println("Nouvelle partie");
    //Serial.println();


    //On réinitialise les paramètres pour la nouvelle partie
    ledPosition = ledNombre / 2;
    premier_souffle = true;
    vitesse = vitesse_initiale;
    joueur_1_partie = false;
    joueur_1_manche = false;
    joueur_2_partie = false;
    joueur_2_manche = false;
    compteur = 0;
    score_1 = 0;
    score_2 = 0;
    sens = 1;
    premier_tour = true;
    //Serial.println("parametres de partie reinitialisés");

  }



  //-----SI LA MANCHE EST FINI-----//

  if ( ( joueur_2_manche == true && joueur_2_partie == false ) || ( joueur_1_manche == true && joueur_1_partie == false) ) {
    //On annonce la fin de la manche
    //Serial.println("Fin de la manche");
    //Serial.print("compteur : ");
    //Serial.print(compteur);

    //On éteint toutes les LEDs
    FastLED.clear();
    FastLED.show();

    //Player 1 a perdu la manche
    if ( joueur_1_manche == true ) {
      //On lance l'animation de fin de manche
      // blink_Player_1();
      //Serial.println("anim fin de manche joueur 2 winner");


      animation_manche_win_2();

      score_2 += compteur;
    }

    //Player 2 a perdu la manche
    if ( joueur_2_manche == true ) {
      //blink_Player_2();


      //anime fin manche :

      animation_manche_win_1();

      score_1 += compteur;

      //Serial.println("anim fin de manche joueur 1 winner");
    }

    if (compteur > 0) {
      //On attend
      //Serial.println("delay fin de manche 3s");
      delay(3000);
    } else {
      //Serial.println("delay fin de manche 3s");
      delay(1000);
    }




    //On annonce la nouvelle manche
    //Serial.println();
    //Serial.println();
    //Serial.println("Nouvelle manche");

    //On réinitialise les paramètres pour la nouvelle manche
    ledPosition = ledNombre / 2;
    premier_souffle = true;
    vitesse = vitesse_initiale;
    joueur_1_manche = false;
    joueur_2_manche = false;
    compteur = 0;
    premier_tour = true;
    //Serial.println("parametres de manche reinitialisés");
  }



  //On attend, vitesse détermine la vitesse du projectile
  delay(vitesse);
}


//_____FRONT_____//
void black() {
  //on met toutes les LEDs noir (sans les afficher) pour ne pas avoir de trainé de LEDs
  for (int i = 0; i < ledNombre; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
}

//-----ANIMATION ENVOI-----//
//Player 1
void envoi_Player_1() {
  for (int j = 0; j < 3; j++) {

    for (int i = (ledNombre / 2) ; i > (ledNombre / 2) - 5 ; i--) {
      leds[i] = CHSV(0, 0, 255);
      affichage_bases();
      FastLED.show();
      delay(100);
    }

    FastLED.clear();
    affichage_bases();
    FastLED.show();
  }
}

//Player 2
void envoi_Player_2() {
  for (int j = 0; j < 3; j++) {

    for (int i = (ledNombre / 2) ; i < (ledNombre / 2) + 5 ; i++) {
      leds[i] = CHSV(0, 0, 255);
      affichage_bases();
      FastLED.show();
      delay(100);
    }
    FastLED.clear();
    affichage_bases();
    FastLED.show();
  }
}





void affichage_points() {
  //Serial.print("Score joueur 1 : ");
  //Serial.print(score_1);
  //Serial.print(", Score joueur 2 : ");
  //Serial.println(score_2);
  //affichage points :
  for (int i = 0; i < score_1; i++) {
    leds[i] = CHSV(0, 255, 255);
  }
  for (int i = ledNombre - 1; i > ledNombre - score_2 - 1; i--) {
    leds[i] = CHSV(170, 255, 255);
  }

  leds[ledNombre / 2] = CHSV(0, 0, 255);
  FastLED.show();
}


void animation_manche_win_1() {
  affichage_compteur();
  //quand on est juste à la fin d'une manche normale
  for (int depart = ( ( ledNombre / 2 ) - ( compteur / 2 ) ); depart > score_1 - 1; depart--) {
    FastLED.clear();
    // //Serial.print("depart = ");
    //Serial.println(depart);
    for (int i = 0; i < compteur; i++) {
      //Serial.print("i = ");
      //Serial.println(i);
      //   map( depart, ( ( ledNombre / 2 ) - ( compteur / 2 ) ),score_1 - 1,0,255)
      leds[depart + i] = CHSV(0, map( depart, ( ( ledNombre / 2 ) - ( compteur / 2 ) ), score_1 - 1, 0, 255), 255);
    }
    affichage_points();
    FastLED.show();
  }
}


void animation_manche_win_2() {
  affichage_compteur();
  for (int depart = ( ( ledNombre / 2 ) - ( compteur / 2 ) ) ; depart < ledNombre - score_2 - compteur + 1; depart++) {
    FastLED.clear();
    // //Serial.print("depart = ");
    //Serial.println(depart);
    for (int i = 0; i < compteur; i++) {
      //Serial.print("i = ");
      //Serial.println(i);
      leds[depart + i] = CHSV(170, map( depart, ( ( ledNombre / 2 ) - ( compteur / 2 ) ), ledNombre - score_2 - compteur + 1, 0, 255), 255);
    }
    affichage_points();
    FastLED.show();
  }
}


void animation_partie_win_1() {
  //quand on est a la fin d'une manche de fin de partie
  //Serial.println("anim win 1");
  FastLED.clear();

  for (int i = 0; i < ledNombre; i++) {
    leds[i] = CHSV(0, 255, 255);;
    FastLED.show();
    delay(15);
  }
}


void animation_partie_win_2() {
  //quand on est a la fin d'une manche de fin de partie
  //Serial.println("anim win 2");
  FastLED.clear();

  for (int i = ledNombre; i > 0; i--) {
    leds[i] = CHSV(170, 255, 255);;
    FastLED.show();
    delay(15);
  }
}






void affichage_compteur() {

  int depart = ( ( ledNombre / 2 ) - ( compteur / 2 ) );
  //print("depart = ");
  //Serial.println(depart);
  for (int i = 0; i < compteur; i++) {
    //Serial.print("i = ");
    //Serial.println(i);
    leds[depart + i] = CHSV(0, 0, 100);
  }
}



void affichage_bases() {
  //-----BASE PLAYER 1-----//
  //BASE//
  leds[0] = CHSV(0, 255, 255);
  //ETENDUE//
  for (int i = 1; i < base ; i++) {
    leds[i] = CHSV(0, 255, 80);
  }

  //-----BASE PLAYER 2-----//
  //BASE//

  leds[ledNombre - 1] = CHSV(170, 255, 255);
  //ETENDUE//
  for (int i = ledNombre - 2; i >= ledNombre - base ; i--) {
    leds[i] = CHSV(170, 255, 80);
  }
}
