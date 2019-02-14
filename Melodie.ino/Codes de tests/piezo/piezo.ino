#include "notes.h"
#include <EasyButton.h>

#define BROCHE_HP 12    

EasyButton button1(BUTTON_PIN_1);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // Jouer la méldoie
  jouerMelodie();
}

// COMPOSITION DE LA MÉLODIE -------------------------------------------------------------------

// Nombre de notes qui composent la mélodie
int nombre_notes = 15;

// Définir les notes de la mélodie
int melodie[] = {
  NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, 0, NOTE_RE4, 0, NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, 0, NOTE_RE4, 0 
};

// Définir la durée de chaque note
int duree_note[] = {
  4, 4, 4, 4, 4, 5, 4, 5, 4, 4, 4, 4, 4, 5, 4, 5,
};



// FONCTION QUI PERMET DE JOUEUR LA MÉLODIE -------------------------------------------------------------------

void jouerMelodie() { 

  // Jouer les notes l'une après l'autre
  for (int note_a_jouer = 0; note_a_jouer < nombre_notes; note_a_jouer++) {
    
    // La durée de chaque note est calculée en divisant 1 seconde par le type de note
    // ex : une noire = 1000 millisecondes / 4, une croche = 1000 / 8, etc.
    int duree_note_a_jouer = 1000 / duree_note[note_a_jouer];
    tone(BROCHE_HP, melodie[note_a_jouer], duree_note_a_jouer);
    
    // Pour distinguer les notes, on laisse une petite pause entre chaque
    //  qui équivaut à la durée de la note + 30% 
    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(BROCHE_HP);
  }
}
