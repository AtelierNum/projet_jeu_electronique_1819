#include "pitches.h"

//unsigned long previousMillis = 0; //le moment juste avant l'instant t
//boolean outputTone = false; // le boolean de si y'a du bruit

// BOOLEANS

boolean fun = false; // la boolean de NON
boolean playing = false; // la boolean de NON
boolean game_on = false; // la boolean de NON
boolean party_on = false; //le boolean de si la partie est on

long int goTime, stopTime; // les timings qui règlent les notes

// INT DES PINS

int led = 13; //la pin où est la led
int piezo = 0; //la pin A0 du piezo
int buzzer = 8; //la pin ou est le buzzer
int button = 4; //la pin ou est le bouton;

// INT DES VARIABLES

int seuilMinimum = 80; //valeur moyenne de détection du piezo, à modifier en fonction environnement
int etatButton = 0; //initialise l'état du bouton
int score = 0; //initialiser le score
int niveau = 0; //initialiser le niveau
int note = 0;  // la note sur laquelle on commence (initialement c'était à 1 mais le tableau commence à zero)
int nbNotes = 4; //initialise nb de notes
int nbNotesWin = 10; //initialise nb de notes
int nbNotesLost = 3; //initialise nb de notes

// MELODIES

int lost_melody[] = { //mélodie de loose
  NOTE_DO5, NOTE_DO3, NOTE_DO3
};

int lost_melody_note[] = {
  4, 4, 2
};



int win_melody[] = { //mélodie de win
  NOTE_SOL4, NOTE_SOL4, NOTE_SI4, NOTE_RE5, NOTE_MI5, NOTE_FA5, NOTE_MI5, NOTE_RE5, NOTE_DOD5, NOTE_RE5
};

int win_melody_note[] = {
  8, 4, 4, 2, 8, 8, 8, 8, 8, 2
};



int melody2[3][2][5] = { //les mélodies en fonction du niveau
  {
    { NOTE_DO4, NOTE_MI4, NOTE_SOL4, NOTE_SI4, NOTE_DO5 },
    { 4, 1, 2, 2, 4 },
  },
  {
    { NOTE_DO4, NOTE_MI4, NOTE_SOL4, NOTE_SI4, NOTE_DO5 },
    { 1, 4, 2, 2, 4 },
  },
  {
    { NOTE_DO4, NOTE_MI4, NOTE_SOL4, NOTE_SI4, NOTE_DO5 },
    { 4, 4, 4, 8, 4},
  }
};


int nextTime1 = 1000 / melody2[niveau][1][note]; // le temps que dure une note
int nextTime2 = nextTime1 * 1.30; // le temps de l'espace entre les notes


void setup() {

  Serial.begin(9600); // pour le moniteur là
  pinMode(buzzer, OUTPUT); //cc le buzzer
  pinMode(piezo, INPUT); // cc le piezo
  pinMode(led, OUTPUT); // cc la led
  pinMode(button, INPUT); // cc le bouton

  goTime = millis(); // initialise les trucs
  stopTime = millis();

}


void loop() {

  if (digitalRead(button) == HIGH) {
    niveau = 0;
    playing = true;
    Serial.println("playing true");
  }

  while (0 <= niveau < 2) {

    if (playing = true) {
      jouerMelodie();
      playing = false;
    }

    while (score <= 4) {
      piezoFun();

      if (fun == true)   {

        if (millis() >= goTime) { // si l'instant t est plus grand que l'initialisation ? ça lance la première note
          melodyLedOn();
        }

        if (millis() >= stopTime) { // si l'instant t est plus grand que l'initialisation
          melodyLedOff();
        }

      }
    }
  }
}


// ----------- Melodie par le buzzer ---------------------------------------------------------

void melodyOn() { //ça joue la mélodie

  tone(buzzer, melody2[niveau][0][note]); //fais jouer la note "note" du niveau "niveau" (vu que ce sont des variables qui évolue au fur et a mesure qu'on évolue dans le code)
  nextTime1 = 1000 / melody2[niveau][1][note]; //fais que la durée c'est le temps correspondant à la note "note" du bon niveau
  goTime = millis() + nextTime1; //fais que le gotime est l'instant t + le temps de la note
  if (analogRead(piezo) > seuilMinimum) {
    score++; //si le piezo est enclenché, le score augmente
  }
}


void melodyOff() { //ça arrête/fais une pause

  noTone(buzzer); //éteint la led
  note++; //passe à la note d'après

  if (note >= nbNotes) { //si il reste pas de notes
    note = 0; // retour à zero
    fun = false;

  nextTime2 = nextTime1 * 1.30;
  stopTime = millis() + nextTime2; //fais que le stoptime est l'instant t + le temps de l'arrêt
}



// ----------- Melodie (rythme) par la led ---------------------------------------------------------

void melodyLedOn() { //ça joue la mélodie

  digitalWrite(led, HIGH); //allume la led
  nextTime1 = 1000 / melody2[niveau][1][note];
  goTime = millis() + nextTime1; //fais que le gotime est l'instant t + le temps de la note
  if (analogRead(piezo) > seuilMinimum) {
    score++;
  }
}


void melodyLedOff() { //ça arrête/fais une pause

  digitalWrite(led, LOW); //éteint la led
  note++; //passe à la note d'après

  if (note >= nbNotes) { //si il ne reste pas de note
    note = 0; //on réinitialise le note
    fun = false;
    party_on = false;
    if (score == nbNotes - 1) { // si le score est quasi le nb de notes (soit presque chaque note était on time)
      playing = true; // on continue à jouer
      niveau++; // on augmente le niveau
      score = 0; // le score est réinitialisé
      jouerWin(); // ça fait le son du win
      if (niveau == 3) { // si c'est le dernier niveau
        jouerWin(); // ça fait deux fois le son du win
        jouerWin();
        playing = false; // on arrête de jouer
      }
    } else { // pas le bon score
      jouerLost(); // ça fait le son de la loose
      playing = true; // on rejoue
    }
  }

  nextTime2 = nextTime1 * 1.30;
  stopTime = millis() + nextTime2; //fais que le stoptime est l'instant t + le temps de l'arrêt
}


// ----------- Melodie -----------------------------------------------------

void jouerWin() { //joue la mélodie de la win

  // Jouer les notes l'une après l'autre
  for (int note = 0; note < nbNotesWin; note++) {

    int duree_note_a_jouer = 1000 / win_melody_note[note];
    tone(buzzer, win_melody[note], duree_note_a_jouer);

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(buzzer);
  }
}

void jouerLost() { //joue la mélodie de la loose

  // Jouer les notes l'une après l'autre
  for (int note = 0; note < nbNotesLost; note++) {

    int duree_note_a_jouer = 1000 / lost_melody_note[note];
    tone(buzzer, lost_melody[note], duree_note_a_jouer);

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(buzzer);
  }
}


void jouerMelodie() { //joue la mélodie du niveau

  // Jouer les notes l'une après l'autre
  for (int note = 0; note < nbNotes; note++) {

    int duree_note_a_jouer = 1000 / melody2[niveau][1][note];
    tone(buzzer, melody2[niveau][0][note], duree_note_a_jouer);

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(buzzer);
  }
}

// ----------- Test de partie en cours ou non -----------------------------------------------------

void piezoFun() {

  if (analogRead(piezo) > seuilMinimum) { //faire en sorte que ça déclenche un booléen
    if (party_on == true) {
      fun = !fun; //si party_on, fun change d'état

    } else party_on = true; //sinon il est on
  }
}
