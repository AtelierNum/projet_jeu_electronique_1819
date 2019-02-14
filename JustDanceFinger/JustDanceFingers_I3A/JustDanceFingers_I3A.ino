//Just Dance Fingers
  //Connectivité

//I3A EDNA 2018/19
//Alia ElKayar, Sophie Le Gallo & Virginie Souffoy




//COMPTEUR

    // inclure la bibliothèque dédiée à l'afficheur 4 digit
      #include "TM1637.h"
    // définir les pins de connexion pour la clock et la donnée
      #define CLK 8
      #define DIO 9
      TM1637 tm1637(CLK, DIO); //Attacher de manière effective nos pin et notre écran

    // définir les caractères disponibles
      int8_t NumTab[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};

    //définir timer start que l'on va augmenter petit à petit pour calculer en temps
      int t = 0; //temps initial affiché à droite

    //définir la variable/ score que l'on va diminuer/augmenter selon la performance du joueur
      int num1 = 5; //score initial du player1 affiché à gauche



//MILLIS
    // Generally, you should use "unsigned long" for variables that hold time
    // The value will quickly become too large for an int to store
      unsigned long prev_millis = 0;  //stocker la derniere fois Neopixel.ring a été mis à jour

    //constante ne change pas
      const long intervalle = 1000;  //intervalle à quel clignoter (en milliseconds)


//NEOPIXEL.RING
    //inclure la bibliothèque,  Basic sine wave animation for NeoPixel Ring Bangle Bracelet
      #include <Adafruit_NeoPixel.h>

    //On instancie les neopixels
      int BROCHE_LED  = 4; //lire neopixel.ring sur la pin 4 et la stocker dans une variable entière
      int BROCHE_LED2 = 5; //lire neopixel.ring sur la pin 5 et la stocker dans une variable entière
      int BROCHE_LED3 = 6; //lire neopixel.ring sur la pin 6 et la stocker dans une variable entière

    // On instancie l'état initial des neopixels
      int ledState1 = LOW;
      int ledState2 = LOW;
      int ledState3 = LOW;



//Variables BOOLEAN pour le score et la pression

    bool scoreChanged = false;
  //Alltime
    bool pressed0 = false;
    bool scoreChanged0 = false;


  //Neopixel.ring 1
    bool pressed1 = false;
    bool scoreChanged1 = false;

  //Neopixel.ring 2
    bool pressed2 = false;
    bool scoreChanged2 = false;

  //Neopixel.ring 3
    bool pressed3 = false;
    bool scoreChanged3 = false;

// Déclaration de la variable previousMillis
    unsigned long previousMillis = 0; //will store last time Neopixel.ring  was updated

  // Neopixel.ring  time
    long OnTime;  // = 1000; //milliseconds de on-time, temps de neopixel.ring allumé
    long OffTime; // = 1000; //milliseconds de off-time, temps de neopixel.ring éteint

   // définir le nombre de leds
    #define NUM_LEDS 13



// Paramètre 1 = nombre de pixels dans ruban/ring
// Paramètre 2 = pin number à laquelle elle est branchée
// Paramètre 3 = type de pixel
//   NEO_GRB  Pixels en GRB bitstream

    Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(12, BROCHE_LED,  NEO_GRB); //neopixel.ring1
    Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(12, BROCHE_LED2, NEO_GRB); //neopixel.ring2
    Adafruit_NeoPixel strip3 = Adafruit_NeoPixel(12, BROCHE_LED3, NEO_GRB); //neopixel.ring3

    uint32_t color1 = strip1.Color(0, 155, 5);    //vert, neopixel.ring1
    uint32_t color2 = strip2.Color(0, 25, 255);   //bleu, neopixel.ring2
    uint32_t color3 = strip3.Color(255, 0, 100);  //rose, neopixel.ring3



void setup() {

  //CAPTEUR DE FORCE
    Serial.begin(9600); //Ouvrir la connexion série (capteur de force)

  //COMPTEUR
    //Initialiser l'écran et spécifier sa luminosité
    tm1637.init();
    tm1637.set(BRIGHTEST); //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;


  //Neopixel.rings
    pinMode(BROCHE_LED,  OUTPUT);
    pinMode(BROCHE_LED2, OUTPUT);
    pinMode(BROCHE_LED3, OUTPUT);



  //Neopixel.ring 1
  strip1.begin();
  strip1.show();           // Initialize tous les pixels à 'off'
  strip1.setBrightness(5); // 40/255 brightness/luminosité (autour de 15%)

  for (int i = 0; i < 12; i++) {
    strip1.setPixelColor(i, strip1.Color(0, 0, 0)); //La Neopixel n'affiche aucune couleur
  }


  //Neopixel.ring 2
  strip2.begin();
  strip2.show();
  strip2.setBrightness(5);

  for (int i = 0; i < 12; i++) {
    strip2.setPixelColor(i, strip2.Color(0, 0, 0)); //La Neopixel n'affiche aucune couleur
  }


  //Neopixel.ring 3
  strip3.begin();
  strip3.show();  // Initialize all pixels to 'off'
  strip3.setBrightness(5);

  for (int i = 0; i < 12; i++) {
    strip3.setPixelColor(i, strip3.Color(0, 0, 0));//La Neopixel n'affiche aucune couleur
  }

    randomSeed(analogRead(A5)); //On crée un random sur la pin sans sortie


}




void loop() {


  //CAPTEUR DE FORCE

    //Player1
    //Récupération de la valeur du capteur de force 1
     int value1 = analogRead(0); //lire la valeur sur la pin A0 et la stocker dans une variable entière

    //Récupération de la valeur du capteur de force 2
     int value2 = analogRead(1); //lire la valeur sur la pin A1 et la stocker dans une variable entière

    //Récupération de la valeur du capteur de force 3
     int value3 = analogRead(2); //lire la valeur sur la pin A2 et la stocker dans une variable entière



  //TIMER avec l'afficheur à 4 digits

    // calculer le chiffre à afficher pour chaque colone du tableau de numération
    // car même si notre chiffre à moins de 4 valeurs (0 pour les milliers, centaines et dizaines)
    // on veut afficher les zéros précédent notre valeur.
      int milles = int((t / 1000) % 10);
      int cents  = int((t / 100)  % 10);

      tm1637.display(2, NumTab[milles]); //Afficher le chiffre des milliers sur l'ensemble de segment avant les centaines, placé en troisième.
      tm1637.display(3, NumTab[cents]); //Afficher le chiffre des centaines sur l'ensemble de segment le plus à droite.

      t += 1 ; // augmenter la valeur de t de 1

      if (t < 99) t = 99; //Lorsque t arrive à 99, recommence à compter.




  //SCORE
    tm1637.display(0, num1); //Afficher le score sur l'ensemble de segment le plus à gauche.






  //BOUTON, réinitialiser le jeu

    // définir le bouton
    int buttonVal;

    if (buttonVal == 1) { //Si on appui sur le bouton

      //revenir au score initial (5)/ réinitialise le jeu
      num1 = 5; //score=5
      t = 0; //temps à 0
    }


  //NEOPIXEL.RING.RING + SCORE

   unsigned long currentMillis = millis();



  //Neopixel.ring 1
  if ((ledState1 == LOW)) { //Si le Neopixel.ring  est éteint
    if (value1 > 20 && scoreChanged1 == false) { //si on appuit sur le capteur
      num1 -= 1; //le score baisse de 1 point
      scoreChanged1 = true;
       if (num1 < 0) num1 = 0; //score à 0, afficher 0 (pas de chiffres après le 0)
    }

    //Timer
      if (currentMillis - previousMillis >= OnTime)  {
        scoreChanged1 = false;
        ledState1 = HIGH; //Neopixel.ring allumée
        Serial.println("ON"); //Afficher ON
        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) { //Caractéristiques de la neopixel.ring
          strip1.setPixelColor(i, color1);
        }
        strip1.show();
      }
    }
    if ((ledState1 == HIGH)) { //si Neopixel.ring est allumée

      if (value1 > 20 && scoreChanged1 == false ) { //et que l'on appui sur le capteur
        //Change score
        num1 += 1; //gagner un point
        scoreChanged1 = true;
         if (num1 >9) num1 = 9; //score à 0, afficher 0 (pas de chiffres après le 0)

        pressed1 = true;
      }

    //Timer
      if (currentMillis - previousMillis >= OffTime) {

        ledState1 = LOW; //Si Neopixel.ring est éteint
        Serial.println("OFF");

        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) { //Caractéristiques de la neopixel.ring
          strip1.setPixelColor(i, strip1.Color(0, 0, 0));
        }
        scoreChanged1 = false;

        OnTime = random(500, 1000); //Les Neopixel.rings s'allument en random, entre 500 2000 millisecondes
        OffTime = random(500, 1000); //Les Neopixel.rings s'é-teignent en random, entre 500 2000 millisecondes
      }
    }






  //Neopixel.ring 2
  if ((ledState2 == LOW)) {
    if (value2 > 20 && scoreChanged2 == false) {
      num1 -= 1;
      scoreChanged2 = true;
       if (num1 < 0) num1 = 0; //score à 0, afficher 0 (pas de chiffres après le 0)
    }

    //Timer
      if (currentMillis - previousMillis >= OnTime)  {
        scoreChanged2 = false;
        ledState2 = HIGH;
        Serial.println("ON");
        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) {
          strip2.setPixelColor(i, color2);
        }
        strip2.show();
      }
    }
    if ((ledState2 == HIGH)) {
      if (value2 > 20 && scoreChanged2 == false ) {
        num1 += 1;
        pressed2 = true;
        scoreChanged2 = true;
         if (num1 > 9) num1 = 9; //score à 0, afficher 0 (pas de chiffres après le 0)

      }
      if (currentMillis - previousMillis >= OffTime) {
        ledState2 = LOW;
        Serial.println("OFF");

        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) {
          strip2.setPixelColor(i, strip2.Color(0, 0, 0));
        }
        scoreChanged2 = false;

        OnTime = random(500, 1000);
        OffTime = random(500, 1000);
      }
    }






  //Neopixel.ring 3
  if ((ledState3 == LOW)) {
    if (value3 > 20 && scoreChanged3 == false) {
      num1 -= 1;
      scoreChanged3 = true;
        if (num1 < 0) num1 = 0; //score à 0, afficher 0 (pas de chiffres après le 0)
    }

    //Timer
      if (currentMillis - previousMillis >= OnTime)  {
        scoreChanged3 = false;
        ledState3 = HIGH;
        Serial.println("ON");
        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) {
          strip3.setPixelColor(i, color3);
        }
        strip3.show();
      }
    }
    if ((ledState3 == HIGH)) {
      if (value3 > 20 && scoreChanged3 == false ) {
        num1 += 1;
        pressed2 = true;
          if (num1 > 9) num1 = 9; //score à 0, afficher 0 (pas de chiffres après le 0)
        scoreChanged3 = true;
      }
      if (currentMillis - previousMillis >= OffTime) {
        ledState3 = LOW;
        Serial.println("OFF");

        previousMillis = currentMillis;
        for (int i = 0; i < 12; i++) {
          strip3.setPixelColor(i, strip2.Color(0, 0, 0));
        }
        scoreChanged3 = false;

        OnTime  = random(500, 1000);
        OffTime = random(500, 1000);
      }
    }




  // Si un des scores est égal a 0

    //Neopixel.ring 1
      if (num1 == 0) {
        for (int i = 0; i < 12; i++) {
          strip1.setPixelColor(i, strip1.Color(0, 0, 0));
        }
        Serial.println("Game Over");
      }

    //Neopixel.ring 2
      if (num1 == 0) {
        for (int i = 0; i < 12; i++) {
          strip2.setPixelColor(i, strip2.Color(0, 0, 0));
        }
        Serial.println("Game Over");
      }

    //Neopixel.ring 3
      if (num1 == 0) {
        for (int i = 0; i < 12; i++) {
          strip3.setPixelColor(i, strip3.Color(0, 0, 0));
        }
        Serial.println("Game Over");
      }




  // Draw 'head' pixel
    strip1.show();
    strip2.show();
    strip3.show();



}
