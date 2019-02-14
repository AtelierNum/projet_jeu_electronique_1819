int led[3] = {8, 9, 10};           // on déclare les leds
int bp[3] = {2, 3, 4};            // on déclare les bps
//int sol[2] = {0, 0};

int initLed = 0;
int i;
int randnumber ;
int tirage = 0;
int compteur;
int score;
unsigned long time;

boolean gameover = false; //On a perdu le jeu



void setup() {

  Serial.begin(9600);
  for (i = 0; i < 3; i++) {          //Boucle
    pinMode(bp[i], INPUT);        // les boutons poussoirs sont des entrées
    pinMode(led[i], OUTPUT);      // les leds sont des sorties
    digitalWrite(led[i], LOW);    // les leds sont éteintes
    //digitalWrite(bp[i],HIGH);     // les boutons poussoirs sont allumés
  }
  compteur = 0;
  randomSeed(analogRead(0));
}


void loop() {

  if (initLed == 0)  {                     // On initialise à 0
    //sol[0] = 0;
    //sol[1] = 0;
    randnumber = random(0, 3);            // Déclaration d'un premier nombre aléatoire de 0 à 1
    //sol[randnumber] = 1;
    digitalWrite(led[randnumber], HIGH);  // La led choisi aléatoirement s'allume
    compteur = compteur + 1;              // On ajoute au compteur 1 pour montrer qu'une boucle a été exécuté
    initLed = 1;                          // On indique au programme qu'on est plus à 0 (initialisation)
    tirage = 1;                           // Permet d'aller au test suivant
    Serial.print("valeur du random : ");
    Serial.println(randnumber);
    Serial.print("compteur : ");
    Serial.println(compteur);
  }


  if (tirage == 1 ) {
    // Deuxième test
    if (digitalRead(bp[randnumber]) == HIGH) {  // On lit si le bouton poussoir associé a la led est actif
      digitalWrite(led[randnumber], LOW);    // On éteint la led si on appuie sur le bp
      randnumber = random(0, 3);                // On cherche un autre nombre aléatoire
      Serial.print("valeur du random : ");
      Serial.println(randnumber);
      digitalWrite(led[randnumber], HIGH);   // On allume la led correspondant a ce nouveau nombre
      compteur += 1;
      Serial.print("compteur : ");
      Serial.println(compteur);
      delay(200);
    }
    else {
      if ( digitalRead(bp[(randnumber + 1) % 3]) == HIGH) {
        digitalWrite(led[randnumber], LOW);               //Si l'un des autres bp est activé on éteint la led
        tirage = 0;                                       //On allume le score à la fin
        Serial.println("perdu");
      }
    }
  }

  score = compteur - 1;                          // On calcul le score
  if (tirage == 0) {                             // On teste si la variable tirage est à 0
    allumer(score);                                // Permet d'allumer le score à l'aide des leds
  }


  if (tirage >= 25) {
    digitalWrite(led[0], LOW);
    digitalWrite(led[1], LOW);
    digitalWrite(led[2], LOW);
    //gameover = true;
    Serial.println("Game over");
  }

  Serial.println(digitalRead(0));

}


void allumer(int score) {                        // Fonction allumer qui prend en variable le score et qui ne retourne rien
  digitalWrite(led[0], LOW);                     // La led 0 est éteinte
  digitalWrite(led[1], LOW);                     // La led 1 est éteinte
  digitalWrite(led[2], LOW);                     // La led 1 est éteinte

  for (int j = score; j > 0; j--) {                //Boucle décrementant le score jusqu'à ce qu'il soit égal à 1
    digitalWrite(led[j % 3], HIGH);                //Allume la led modulo 2 (Un nombre entre 0 et 1)
    digitalWrite(led[j % 3], LOW);                 //Éteint la led modulo 2 (Un nombre entre 0 et 1)
    digitalWrite(led[j % 3], LOW);                 //Éteint la led modulo 2 (Un nombre entre 0 et 1)
  }
  digitalWrite(led[0], HIGH);                    // On allume la led 0
  digitalWrite(led[1], HIGH);                    // On allume la led 1
  digitalWrite(led[2], HIGH);                    // On allume la led 2
}
