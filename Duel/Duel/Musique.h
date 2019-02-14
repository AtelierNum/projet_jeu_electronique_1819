//BIBLIOTHEQUES

#include "notes.h"



// BROCHES

#define Piezo 10



// VARIABLES




// MELODIE

// Nombre de notes qui composent la mélodie
long nombreNotesMelodie;

// Définir les notes de la mélodie
int melodie[] = {
  NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_DO5, NOTE_RE5, NOTE_LA4, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_DO5, NOTE_RE5, NOTE_SOL5, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_LA5, NOTE_DO6,
  NOTE_SI5, NOTE_LA5, NOTE_SOL5, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, 0, NOTE_RE5, NOTE_LA4, NOTE_LA4
};

// Définir la durée de chaque note
int dureeNoteMelodie[] = {
  16, 16, 16, 16, 2, 4, 4, 2/*random(1, 16)*/, 4, 16, 16, 16, 16, 2, 4, 4, 2, 4, 16, 16, 16, 16, 2, 4,
  8, 8, 2, 4, 16, 16, 16, 16, 4, 8, 4, 8, 1
};



// JOUER LA MUSIQUE

void JouerMelodie() {

  nombreNotesMelodie = random(8, 37);
  Serial.println(nombreNotesMelodie);

  // Jouer les notes l'une après l'autre
  for (int note_a_jouer = 0; note_a_jouer < nombreNotesMelodie; note_a_jouer++) {

    // La durée de chaque note est calculée en divisant 1 seconde par le type de note
    // ex : une noire = 1000 millisecondes / 4, une croche = 1000 / 8, etc.

    int duree_note_a_jouer = 1500 / dureeNoteMelodie[note_a_jouer];
    tone(Piezo, melodie[note_a_jouer], duree_note_a_jouer);

    // Pour distinguer les notes, on laisse une petite pause entre chaque
    //  qui équivaut à la durée de la note + 30%

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(Piezo);
  }
}



// BANG

// Nombre de notes qui composent la mélodie
int nombreNotesBang = 5;

// Définir les notes de la mélodie
int bang[] = {
  NOTE_FA7, NOTE_MI7, NOTE_RE7, NOTE_DO7, NOTE_SOL4
};

// Définir la durée de chaque note
int dureeNoteBang[] = {
  16, 16, 16, 16, 1
};


void TirerBang() {

  // Jouer les notes l'une après l'autre
  for (int note_a_jouer = 0; note_a_jouer < nombreNotesBang; note_a_jouer++) {

    // La durée de chaque note est calculée en divisant 1 seconde par le type de note
    // ex : une noire = 1000 millisecondes / 4, une croche = 1000 / 8, etc.

    int duree_note_a_jouer = 200 / dureeNoteBang[note_a_jouer];
    tone(Piezo, bang[note_a_jouer], duree_note_a_jouer);

    // Pour distinguer les notes, on laisse une petite pause entre chaque
    //  qui équivaut à la durée de la note + 30%

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(Piezo);
  }
}
