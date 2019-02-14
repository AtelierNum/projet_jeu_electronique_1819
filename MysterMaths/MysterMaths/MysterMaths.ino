#include <Wire.h>
#include <SeeedOLED.h> // bibliothèque écran oled
#include <Servo.h> // bibliothèque servomoteur
#include <Adafruit_NeoPixel.h> // bibliothèque rubans led
#ifdef __AVR__
#include <avr/power.h>
#endif

// Sur quel pin est branché le ruban leds
#define PIN            3
#define PIN2            2

// Indication du nombre de leds par rubans
#define NUMPIXELS      3
#define NUMPIXELS2      3

// initialisation pour la librairie neopixel, prend en paramètre le nombre de leds et le pin sur lequel envoyer le signal
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixels2 = Adafruit_NeoPixel(NUMPIXELS2, PIN2, NEO_GRB + NEO_KHZ800);



//definition des pins pour les boutons. les boutonX2 sont les boutons du joueur 2.
#define BROCHE_BOUTONA  6
#define BROCHE_BOUTONB  7
#define BROCHE_BOUTONC  8
#define BROCHE_BOUTOND  9
#define BROCHE_BOUTONA2  10
#define BROCHE_BOUTONB2  11
#define BROCHE_BOUTONC2  12
#define BROCHE_BOUTOND2  13

//définition des servomoteurs
Servo myservo;
Servo myservo2;

int lvl; // variable pour le choix du niveau (1 addition, 2 multiplication)
boolean bResult; //bouléen pour tester la validité d'une réponse.
int j=0; // variable jouer
int etape = 0; // initialisation des étapes
boolean start_etape = false; // initialisation début d'étape
long etape_debut = 0; // variable pour délais non bloquant
long maintenant; // variable pour délais non bloquant
int compteur = 0; // compteur pour affichage retour temps
int rnd; // initialisation pour une variable aléatoire
int ScoreJ1=0; // score joueur1
int ScoreJ2=0; // score joueur2
int delayval = 1000; // delay pour l'allumage des leds

void setup() {
  Wire.begin();
  pixels.begin(); //initialisation led 1
  pixels2.begin(); //initialisation led 2
  SeeedOled.init();  //initialisation écran oled
  pinMode(4, OUTPUT); // pin définie en sortie
  myservo.attach(4);  // servo moteur attaché à la pin 4
  pinMode(5, OUTPUT);  // pin définie en sortie
  myservo2.attach(5); // servo moteur attaché à la pin 5

  SeeedOled.clearDisplay();           //(ré)initialise l'écran oled
  SeeedOled.setNormalDisplay();       //Set display to Normal mode
  SeeedOled.setPageMode();            //Set addressing mode to Page Mode
  pinMode(BROCHE_BOUTONA, INPUT);   // pin définie en entrée
  pinMode(BROCHE_BOUTONB, INPUT);
  pinMode(BROCHE_BOUTONC, INPUT);
  pinMode(BROCHE_BOUTOND, INPUT);
  pinMode(BROCHE_BOUTONA2, INPUT);
  pinMode(BROCHE_BOUTONB2, INPUT);
  pinMode(BROCHE_BOUTONC2, INPUT);
  pinMode(BROCHE_BOUTOND2, INPUT);
  Serial.begin(9600);
  start_etape = true; //start_etape initialisé
}

void loop() {
  maintenant = millis() - etape_debut; // initialisation variable maintenant


  if (etape == 0){ // étape d'initialisation du jeu
    if (compteur % 100 == 0) Serial.print("étape 0 démarrée depuis ");  // retour sur le temps passé dans cette étape
    if (compteur % 100 == 0) Serial.println(maintenant);
    // affichage du choix des deux niveaux
    SeeedOled.setTextXY(0, 0);      // affiche sur la première ligne colonne 1
    SeeedOled.putString("Press A"); // la chaine de caractère "Press A"
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("for lvl 1");
    SeeedOled.setTextXY(3, 0);
    SeeedOled.putString("Press B");
    SeeedOled.setTextXY(4, 0);
    SeeedOled.putString("for lvl 2");
    if ((digitalRead(BROCHE_BOUTONA) == HIGH )||(digitalRead(BROCHE_BOUTONA2) == HIGH )){ // si l'on choisit le niveau 1
      randomSeed(millis()); // millis() est utilisé pour que la clé soit aléatoire et que le random ne soit pas prévisible.
      etape = 1; // passage à l'étape 1
      lvl=1; // le  niveau addition est chosi
      start_etape = true;
    }
    if ((digitalRead(BROCHE_BOUTONB) == HIGH )||(digitalRead(BROCHE_BOUTONB2) == HIGH )){ // si l'on choisit le niveau 2
      randomSeed(millis()); // millis() est utilisé pour que la clé soit aléatoire et que le random ne soit pas prévisible.
      etape = 1; // passage à l'étape 1
      lvl=2; // le  niveau multiplication est chosi
      start_etape = true;

    }
  }


  if (etape == 1) { // dans cette étape on vérifie que personne n'a gagné et on lance une nouvelle manche
    if (start_etape) {
      Serial.print("initialisation étape 1 démarrée à ");
      etape_debut = millis();
      Serial.println(etape_debut);
      start_etape = false;
    }
    if (compteur % 100 == 0) Serial.print("étape 1 démarrée depuis ");
    if (compteur % 100 == 0) Serial.println(maintenant);
    if ((maintenant >= 1000)&&(ScoreJ1<5)&&(ScoreJ2<5)) { // si personne n'a encore gagné on lance l'étape 2
      etape = 2;
      start_etape = true;
    }
    if (ScoreJ2==5){ // si le joueur 2 a gagné
    SeeedOled.setTextXY(1, 0); // on affiche qu'il a gagné
    SeeedOled.putString("felicitation");
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("J2 gagne !");
    for (int i = 0; i < NUMPIXELS; i++) { // on allume 1 led après l'autre
      pixels2.setPixelColor(i, pixels.Color(0, 150, 0)); // on allume en vert les leds de joueur 2
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));  // on allume en rouge les leds de joueur 1
      pixels.show(); // This sends the updated pixel color to the hardware.
      pixels2.show();
      delay(delayval);

    }
    for (int i = 0; i < NUMPIXELS; i++) {
-
      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // on éteint les leds de joueur 1
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0)); // on éteint les leds de joueur 2
      pixels.show();
      pixels2.show();

    }
    if (maintenant >= 10000){ // si 10 secondes se sont écoulées on réinitialise le jeu
      ScoreJ1=0;
      ScoreJ2=0;
      etape=0;
      SeeedOled.clearDisplay();
    }
    }
    if (ScoreJ1==5){ // si le joueur 1 a gagné
    SeeedOled.clearDisplay();
    SeeedOled.setTextXY(1, 0);
    SeeedOled.putString("felicitation");
    SeeedOled.setTextXY(2, 0);
    SeeedOled.putString("J1 gagne !");
    for (int i = 0; i < NUMPIXELS; i++) {
      pixels2.setPixelColor(i, pixels.Color(150, 0, 0)); // on allume en rouge les leds de joueur 2
      pixels.setPixelColor(i, pixels.Color(0, 150, 0)); // on allume en vert les leds de joueur 1
      pixels.show();
      pixels2.show();
      delay(delayval);

    }
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // on éteint les leds de joueur 1
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0)); // on éteint les leds de joueur 2
      pixels.show();
      pixels2.show();

    }
    if (maintenant >= 10000){ // si 10 secondes se sont écoulées on réinitialise le jeu
      ScoreJ1=0;
      ScoreJ2=0;
      etape=0;
      SeeedOled.clearDisplay();
    }
    }
  }


  if (etape == 2) { // étape d'affichage des questions
    if (start_etape) {
      Serial.print("initialisation étape 2 démarrée à ");
      etape_debut = millis();
      Serial.println(etape_debut);
      rnd = random(1, 4); // tirage aléatoire entre 1 et 4.
      if (lvl==1){
      affichage_addition(); // lancement de la fonction affichage_addition
      }
       if (lvl==2){
      affichage_multi(); // lancement de la fonction affichage_multi
      }
      start_etape = false;
    }
    if (compteur % 100 == 0) Serial.print("étape 2 démarrée depuis ");
    if (compteur % 100 == 0) Serial.println(maintenant);
    // si le joueur 1 appuie sur un bouton
    if ((maintenant >= 20000) || (digitalRead(BROCHE_BOUTONA) == HIGH ) || (digitalRead(BROCHE_BOUTONB) == HIGH ) || (digitalRead(BROCHE_BOUTONC) == HIGH ) || (digitalRead(BROCHE_BOUTOND) == HIGH )) {
      j=1; // la variable j enregistre qu'il a appuyer en premier

      // on regarde sous quel bouton était la bonne réponse en fonction du rnd tiré.
      if (rnd == 1) {
        if (digitalRead(BROCHE_BOUTONC) == HIGH) {
          bResult = true; // le résultat est bon
        } else{
          bResult = false; // le résultat est faux
        }
      }
      if (rnd == 2) {
        if (digitalRead(BROCHE_BOUTOND) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      if (rnd == 3) {
        if (digitalRead(BROCHE_BOUTONA) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      if (rnd == 4) {
        if (digitalRead(BROCHE_BOUTONB) == HIGH) {
          bResult = true;
        }
      }
      etape = 3; // on passent à l'étape 3
      start_etape = true;
    }
    // si le joueur 2 appuie sur un bouton
    if ((digitalRead(BROCHE_BOUTONA2) == HIGH ) || (digitalRead(BROCHE_BOUTONB2) == HIGH ) || (digitalRead(BROCHE_BOUTONC2) == HIGH ) || (digitalRead(BROCHE_BOUTOND2) == HIGH )) {
      j=2; // la variable j enregistre qu'il a appuyer en premier

      // on regarde sous quel bouton était la bonne réponse en fonction du rnd tiré.
      if (rnd == 1) {
        if (digitalRead(BROCHE_BOUTONC2) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      if (rnd == 2) {
        if (digitalRead(BROCHE_BOUTOND2) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      if (rnd == 3) {
        if (digitalRead(BROCHE_BOUTONA2) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      if (rnd == 4) {
        if (digitalRead(BROCHE_BOUTONB2) == HIGH) {
          bResult = true;
        } else{
          bResult = false;
        }
      }
      etape = 3; // passage étape 3
      start_etape = true;
    }else if (maintenant >= 20000){ // si personne n'appuie avant 20 seconde
      bResult = false; // le résultat est faux
      j=0; // personne n'a appuyé
    }
  }


  if (etape == 3) { //étape d'affichage du gagnant
    if (start_etape) {
      SeeedOled.clearDisplay();
      Serial.print("initialisation étape 3 démarrée à ");
      etape_debut = millis();
      Serial.println(etape_debut);
      start_etape = false;
      test(); // lancement du programme test qui permet d'afficher le gagnant
    }
    if (compteur % 100 == 0) Serial.print("étape 3 démarrée depuis ");
    if (compteur % 100 == 0) Serial.println(maintenant);
    if ((digitalRead(BROCHE_BOUTONC) == HIGH) || (maintenant >= 5000)) { // bouton pour passer rapidement à l'étape 1 ( mode debug)
      etape = 1;
      SeeedOled.clearDisplay();
      start_etape = true;
    }
  }
  compteur++;
}


void affichage_multi(){ //fonction affichage_multi
  int n1 = random(1, 20); // initailisation des variable
  int n2 = random(1, 20);

  int result=n1*n2; // calcul du résultat
  int rp1 = (n1 - (n1 - random(20)))*n2; // calcul de la réponse proche du résultat
  if ((rp1==result)||(rp1==0)){
   while ((rp1==result)||(rp1==0)){ // tant que le résultat est égale à 0 ou à la bonne réponse le calcul recommence
    rp1 = (n1 - (n1 - random(20)))*n2;
   }}
  int rp2 = (n1+random(-10,10))*n2;
  if ((rp2==result)||(rp2==0)){
    while ((rp2==result)||(rp2==0)){
    rp2 = (n1+random(-10,10))*n2;
  }}
  int rp3 = (n1 * n2) + (random(-10, 10));
  if ((rp3==result)||(rp3==0)){
    while ((rp3==result)||(rp3==0)){
    rp3 = (n1 * n2) + (random(-10, 10));
  }}
  affichage_questionMult(n1,n2); // fonction qui affiche les positions de result et des différente autres réponses en fonction du rnd tiré
  if (rnd == 1) {
    affichage_reponses(rp3, rp1, result, rp2);
  }
  if (rnd == 2) {
    affichage_reponses(rp2, rp3, rp1, result);
  }
  if (rnd == 3) {
    affichage_reponses(result, rp2, rp3, rp1);
  }
  if (rnd == 4) {
    affichage_reponses(rp1, result, rp3, rp2);
  }
}

void affichage_addition() { // fonction affichage_addition

  int n1 = random(-20, 20); // initialisation variables
  int n2 = random(-20, 20);

  int result = n1 + n2; // calcul de la bonne réponse
  int rp1 = n1 + n2 + random(-5, 5); // calcul de la réponse proche du résultat
  if (rp1 == result) {
    while (rp1==result){ // tant que le résultat est égale à la bonne réponse le calcul recommence
    rp1 = n1 + n2 + random(-5, 5);
    }
  }
  int rp2 = n1 + n2 - random(-5, 5);
  if (rp2 == result) {
    while (rp2==result){
    rp2 = n1 + n2 - random(-5, 5);
    }
  }
  int rp3 = (n1 + random(-1, 1)) + (n2 + random(-1, 1));
  if (rp3 == result) {
    while (rp3==result){
    rp3 = (n1 + random(-1, 1)) + (n2 + random(-1, 1));
    }
  }

  affichage_question(n1, n2); // fonction qui affiche les positions de result et des différente autres réponses en fonction du rnd tiré

  if (rnd == 1) {
    affichage_reponses(rp3, rp1, result, rp2);
  }
  if (rnd == 2) {
    affichage_reponses(rp2, rp3, rp1, result);
  }
  if (rnd == 3) {
    affichage_reponses(result, rp2, rp3, rp1);
  }
  if (rnd == 4) {
    affichage_reponses(rp1, result, rp3, rp2);
  }
}

void test() {
  if ((bResult) && (j==1)) { // si le joueur 1 a appuyé et a bon

    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("j1 gagne"); // on affiche qu'il gagne
    for (int i = 0; i < NUMPIXELS; i++) {

      // on allume les leds en conséquence
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels2.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.show();
      pixels2.show();

      delay(delayval);


    }
    piquej2(); // on lance le programme piquej2
    for (int i = 0; i < NUMPIXELS; i++) {

      // on éteint les leds
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      pixels2.show();
    }
  ScoreJ1=ScoreJ1+1; // le score de j1 est incrémenté de 1
  }
  if ((bResult==false) && (j==1)){ // si le joueur 1 a appuyé et a faux
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("j1 perdu"); // ont affiche qu'il a faux
    for (int i = 0; i < NUMPIXELS; i++) {

      // on allume les leds en conséquence
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.show();
      pixels2.show();

      delay(delayval);

    }
    piquej1(); // le joueur 1 est piqué
    for (int i = 0; i < NUMPIXELS; i++) {

      // on éteint les leds
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      pixels2.show();

    }

  }

 if ((bResult) && (j==2)) { // si le joueur 2 a appuyé et a bon
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("J2 gagne");
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels2.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.show();
      pixels2.show();
      delay(delayval);


    }
    piquej1(); // le joueur 1 est piqué.
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      pixels2.show();

    }
  ScoreJ2=ScoreJ2+1; // le score de j2 est incrémenté de 1
  }
  if ((bResult==false) && (j==2)) { // si le joueur 2 a appuyé et a faux
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("j2 perdu");
    for (int i = 0; i < NUMPIXELS; i++) {

      pixels2.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.setPixelColor(i, pixels.Color(0, 150, 0));
      pixels.show();
      pixels2.show();

      delay(delayval);

    }
    piquej2(); // le joueur 2 est piqué
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      pixels2.show();
    }

  }
  if (j==0){ // si personne n'a appuyé
    SeeedOled.setTextXY(0, 0);
    SeeedOled.putString("bande de nuls"); //ont les insultent
    for (int i = 0; i < NUMPIXELS; i++) {

      // tous le monde passe au rouge
      pixels2.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.setPixelColor(i, pixels.Color(150, 0, 0));
      pixels.show();
      pixels2.show();

      delay(delayval);

    }
    piques();// tous le monde est piqué
    for (int i = 0; i < NUMPIXELS; i++) {


      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels2.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
      pixels2.show();

    }
  }

}
