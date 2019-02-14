
#include "notes.h"
// #include "sons.ino"
#include <EasyButton.h>
#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>


U8X8_SSD1306_128X64_NONAME_HW_I2C ecran(/* reset=*/ U8X8_PIN_NONE);


#define BROCHE_HP 12
#define BUTTON_PIN_1 8
#define BUTTON_PIN_2 4
#define BUTTON_PIN_3 2

EasyButton buttonA(BUTTON_PIN_1);
EasyButton buttonB(BUTTON_PIN_2);
EasyButton button3(BUTTON_PIN_3);

int index = -1;
int score = 0;
int buttonState = 0;




// 1 - COMPOSITION DES MELODIES -----------------------------------------------------------------------------------


/* MELODIE 1 - NOKIA -----------------------------------------------------------------------------------*/

/* Nokia - Vraie */

// Nombre de notes qui composent la mélodie
int nombre_notes_melo1vraie = 13;

// Définir les notes de la mélodie
int melodie_1vraie[] = {
  NOTE_MI6, NOTE_RE6, NOTE_FAD5, NOTE_SOLD5, NOTE_DOD6, NOTE_SI5, NOTE_RE5, NOTE_MI5, NOTE_SI5, NOTE_LA5, NOTE_DOD5, NOTE_MI5, NOTE_LA5,
};

// Définir la durée de chaque note
int duree_note_melo1vraie[] = {
  8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4,
};



/* Nokia - Fausse */

int nombre_notes_melo1fausse = 13;

int melodie_1fausse[] = {
  NOTE_MI6, NOTE_RE6, NOTE_FAD5, NOTE_SOLD5, NOTE_DOD6, NOTE_DOD5, NOTE_RE5, NOTE_MI5, NOTE_SI5, NOTE_LA5, NOTE_DOD5, NOTE_MI5, NOTE_LA5,
};

int duree_note_melo1fausse[] = {
  8, 8, 4, 4, 8, 8, 4, 4, 8, 8, 4, 4, 4,
};



/* MÉLODIE 2 - LETTRE A ELISE ------------------------------------------------------------------------------------ */

/* Lettre à Elise - Vraie */

int nombre_notes_melo2vraie = 9;

int melodie_2vraie[] = {
  NOTE_MI5, NOTE_RED5, NOTE_MI5, NOTE_RED5, NOTE_MI5, NOTE_SI4, NOTE_RE5, NOTE_DO5, NOTE_LA4,
};

int duree_note_melo2vraie[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4,
};

/* Lettre à Elise - Fausse */

int nombre_notes_melo2fausse = 9;

int melodie_2fausse[] = {
  NOTE_MI5, NOTE_MI5, NOTE_MI5, NOTE_RED5, NOTE_MI5, NOTE_SI4, NOTE_RE5, NOTE_DO5, NOTE_LA4,
};

int duree_note_melo2fausse[] = {
  4, 4, 4, 4, 4, 4, 4, 4, 4,
};



/* MÉLODIE 3 - MISTRAL GAGNANT ------------------------------------------------------------------------------------ */

/* Mistral Gagnant - Vraie */

int nombre_notes_melo3vraie = 13;

int melodie_3vraie[] = {
  NOTE_SI4, NOTE_RE5, NOTE_SI5, NOTE_SI5, NOTE_LA5, NOTE_MI5, NOTE_DOD5, NOTE_MI5, NOTE_DOD6, NOTE_DOD6, NOTE_RE6, NOTE_DOD6, NOTE_SI5,
};

int duree_note_melo3vraie[] = {
  4, 4, 2, 2, 2, 1, 4, 4, 2, 2, 2, 2, 1,
};

/* Mistral Gagnant - Fausse */

int nombre_notes_melo3fausse = 13;

int melodie_3fausse[] = {
  NOTE_SI4, NOTE_RE5, NOTE_SI5, NOTE_SI5, NOTE_LA5, NOTE_MI5, NOTE_DOD5, NOTE_MI5, NOTE_DOD6, NOTE_DOD6, NOTE_RE6, NOTE_RE6, NOTE_SI5,
};

int duree_note_melo3fausse[] = {
  4, 4, 2, 2, 2, 1, 4, 4, 2, 2, 2, 2, 1,
};



/* MÉLODIE 4 - AMELIE POULAIN ------------------------------------------------------------------------------------ */

/* Amelie Poulain - Vraie */

int nombre_notes_melo4vraie = 13;

int melodie_4vraie[] = {
  NOTE_SOL5, NOTE_FAD5, NOTE_SOL5, NOTE_SI5, NOTE_DO6, NOTE_SI5, NOTE_FAD5, NOTE_SOL5, NOTE_FAD5, NOTE_SOL5, NOTE_LA5, NOTE_SOL5,
};

int duree_note_melo4vraie[] = {
  8, 8, 2, 8, 8, 2, 8, 8, 2, 8, 8, 2,
};

/* Amelie Poulain - Fausse  */

int nombre_notes_melo4fausse = 12;

int melodie_4fausse[] = {
  NOTE_SOL5, NOTE_FAD5, NOTE_SOL5, NOTE_SOL5, NOTE_DO6, NOTE_SI5, NOTE_FAD5, NOTE_SOL5, NOTE_FAD5, NOTE_SOL5, NOTE_LA5, NOTE_SOL5,
};

int duree_note_melo4fausse[] = {
  8, 8, 2, 8, 8, 2, 8, 8, 2, 8, 8, 2,
};



/* MÉLODIE 5 - SOURIS VERTE ------------------------------------------------------------------------------------ */

/* Souris Verte - Vraie */

int nombre_notes_melo5vraie = 16;

int melodie_5vraie[] = {
  NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, 0, NOTE_RE4, 0, NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, 0, NOTE_RE4, 0
};

int duree_note_melo5vraie[] = {
  4, 4, 4, 4, 4, 5, 4, 5, 4, 4, 4, 4, 4, 5, 4, 5, 5,
};

/* Souris Vertes - Fausse  */

int nombre_notes_melo5fausse = 17;

int melodie_5fausse[] = {
  NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, 0, NOTE_RE4, 0, NOTE_SOL4, NOTE_SOL4, NOTE_SOL4, NOTE_LA4, NOTE_SOL4, NOTE_SOL4, 0, NOTE_RE4, 0,
};

int duree_note_melo5fausse[] = {
  4, 4, 4, 4, 4, 5, 4, 5, 4, 4, 4, 4, 4, 5, 4, 5, 5,
};




/* MELODIE VICTOIRE --------------------------------------------------------------------------------------------------- */

int nombre_notes_victoire = 3;

int melodie_victoire[] = {
  NOTE_RE5, NOTE_LA5, NOTE_RE6,
};

int duree_note_victoire[] = {
  8, 8, 8,
};


/* MELODIE DÉFAITE --------------------------------------------------------------------------------------------------- */

int nombre_notes_defaite = 4;

int melodie_defaite[] = {
  NOTE_RE5, NOTE_DOD5, NOTE_DO5, NOTE_SI4,
};

int duree_note_defaite[] = {
  2, 2, 2, 2,
};



/* JOUER LES MÉLODIES ---------------------------------------------------------------------------------------------------*/


#include "notes.h"


void jouerMelodie_universel(int nb_notes , int mel[] , int dur[] ) {

  // Jouer les notes l'une après l'autre
  for (int note_a_jouer = 0; note_a_jouer < nb_notes; note_a_jouer++) {

    // La durée de chaque note est calculée en divisant 1 seconde par le type de note
    // ex : une noire = 1000 millisecondes / 4, une croche = 1000 / 8, etc.

    int duree_note_a_jouer = 1000 / dur[note_a_jouer];
    tone(BROCHE_HP, mel[note_a_jouer], duree_note_a_jouer);

    // Pour distinguer les notes, on laisse une petite pause entre chaque
    //  qui équivaut à la durée de la note + 30%

    int pause_entre_notes = duree_note_a_jouer * 1.30;
    delay(pause_entre_notes);

    // Arrêter la note qui joue
    noTone(BROCHE_HP);
  }

}



// 2 - MISE EN PLACE DES INTÉRACTIONS ---------------------------------------------------------------------------------------------------


void setup() {
  Serial.begin(9600);

  // Initialisation des 3 boutons :
  buttonA.begin();
  buttonB.begin();
  button3.begin();

  // Quand un bouton est pressé,
  // on appelle une fois une fonction dédiée ) :
  buttonA.onPressed(onPressed_bon);
  buttonB.onPressed(onPressed_mauvais);
  button3.onPressed(onPressed_continuer);

  // Initialisation de l'écran
  ecran.begin();

  pinMode(BROCHE_HP, INPUT);
}

//fonction appelées quand on appuie sur les boutons :

void onPressed_bon() {
  // pour les éventuel bugs
  Serial.println("BONNE RÉPONSE");

  // Augmenté le score dès que le bouton est pressé
  score = score + 5;

  //réinitialiser l'écran pour n'avoir que le message qui correspond qui s'affiche.
  ecran.clearDisplay();

  // Message afficher sur l'écran une fois le bouton pressé
  ecran.draw2x2String(0, 0, "BONNE");
  ecran.draw2x2String(0, 2, "REPONSE");
  // Affichage de la variable score, pour tenir informé le joueur de son score.
  ecran.drawString(0, 5, "Score=");
  ecran.setCursor(200, 300);
  ecran.print(score);

  // Jouer la mélodie qui correspond au bouton
  jouerMelodie_universel( nombre_notes_victoire, melodie_victoire, duree_note_victoire );
  delay(4000);

  // Augmenter l'index pour passer à l'étape suivante / la mélodie suivante
  index += 1 ;

  // Continuer le déroulement du jeu
  gamelogic();
}

void onPressed_mauvais() {
  Serial.println("MAUVAISE RÉPONSE");
  ecran.clearDisplay();
  ecran.draw2x2String(0, 0, "MAUVAISE");
  ecran.draw2x2String(0, 2, "REPONSE");
  ecran.drawString(0, 5, "Score=");
  ecran.setCursor(200, 300);
  ecran.print(score);
  jouerMelodie_universel( nombre_notes_defaite, melodie_defaite, duree_note_defaite );
  delay(4000);
  index += 1;
  gamelogic();
}

void onPressed_continuer() {
  Serial.println("BOUTON CONTINUER");
  index += 1;
  gamelogic();
}




// 3 - DÉROULEMENT DE JEU ---------------------------------------------------------------------------------------------------


void gamelogic() {

  if (index == 0) {
    // Pour aider à débuger
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);

    // Reset de l'écran pour afficher un nouveau message
    ecran.clearDisplay();

    // Importation de la font
    ecran.setFont(u8x8_font_chroma48medium8_r);

    // Composition du message avec sa taille et ses coordonnées
    ecran.drawString(0, 2, "BIENVENUE SUR");
    ecran.drawString(0, 4, "MELODIE.INO");

    Serial.println(index);
  }

  else if (index == 1) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "Le but du jeu :");
    ecran.drawString(0, 1, "                ");
    ecran.drawString(0, 2, "A CHAQUE TOUR");
    ecran.drawString(0, 3, "2 MELODIES VONT");
    ecran.drawString(0, 4, "SE JOUER L'UNE");
    ecran.drawString(0, 5, "APRES L'AUTRE");
  }

  else if (index == 2) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "Le but du jeu :");
    ecran.drawString(0, 1, "                ");
    ecran.drawString(0, 2, "LA MELODIE A,");
    ecran.drawString(0, 3, "PUIS LA");
    ecran.drawString(0, 4, "MELODIE B");
  }

  else if (index == 3) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "Le but du jeu :");
    ecran.drawString(0, 1, "                ");
    ecran.drawString(0, 2, "ENSUITE APPUYEZ");
    ecran.drawString(0, 3, "SUR LE BOUTON");
    ecran.drawString(0, 4, "A OU B POUR");
    ecran.drawString(0, 5, "SELECTIONNER");
  }

  else if (index == 4) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "Commencer le jeu");
    ecran.draw2x2String(0, 2, "BONNE");
    ecran.draw2x2String(0, 4, "CHANCE");
  }

  else if (index == 5) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "1/NOKIA");
    delay(1000);
    ecran.drawString(0, 3, "Melodie A");
    jouerMelodie_universel(nombre_notes_melo1vraie, melodie_1vraie, duree_note_melo1vraie );
    delay(1000);
    ecran.drawString(0, 5, "Melodie B");
    jouerMelodie_universel(nombre_notes_melo1fausse, melodie_1fausse, duree_note_melo1fausse );
    buttonA.onPressed(onPressed_bon);
    buttonB.onPressed(onPressed_mauvais);
  }

  else if (index == 6) {
    // Pour aider à débuger
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);

    // Reset de l'écran
    ecran.clearDisplay();

    // Importation de la font
    ecran.setFont(u8x8_font_chroma48medium8_r);

    // Composition du message, ici le nom de la mélodie
    ecran.drawString(0, 0, "2/LETTRE A");
    ecran.drawString(0, 1, "ELISE");

    // On attend 1 seconde, puis la mélodie A est joué en même temps que l'affiche du message "Mélodie A"
    delay(1000);
    ecran.drawString(0, 4, "Melodie A");
    // On appelle le fonction jouerMelodie_universel en lui indiquant quel paramètres appliquer pour chaque mélodie
    jouerMelodie_universel(nombre_notes_melo2fausse, melodie_2fausse, duree_note_melo2fausse );

    // Pareil pour la mélodie B
    delay(1000);
    ecran.drawString(0, 6, "Melodie B");
    jouerMelodie_universel(nombre_notes_melo2vraie, melodie_2vraie, duree_note_melo2vraie );

    // On attribue les bonnes et mauvaises réponses aux boutons
    buttonA.onPressed(onPressed_mauvais);
    buttonB.onPressed(onPressed_bon);
  }

  else if (index == 7) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "3/MISTRAL");
    ecran.drawString(0, 1, "GAGNANT");
    delay(1000);
    ecran.drawString(0, 4, "Melodie A");
    jouerMelodie_universel(nombre_notes_melo3fausse, melodie_3fausse, duree_note_melo3fausse );
    delay(1000);
    ecran.drawString(0, 6, "Melodie B");
    jouerMelodie_universel(nombre_notes_melo3vraie, melodie_3vraie, duree_note_melo3vraie );
    buttonA.onPressed(onPressed_mauvais);
    buttonB.onPressed(onPressed_bon);
  }

  else if (index == 8) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "4/AMELIE POULAIN");
    delay(1000);
    ecran.drawString(0, 3, "Melodie A");
    jouerMelodie_universel(nombre_notes_melo4vraie, melodie_4vraie, duree_note_melo4vraie );
    delay(1000);
    ecran.drawString(0, 5, "Melodie B");
    jouerMelodie_universel(nombre_notes_melo4fausse, melodie_4fausse, duree_note_melo4fausse );
    buttonA.onPressed(onPressed_bon);
    buttonB.onPressed(onPressed_mauvais);
  }

  else if (index == 9) {
    Serial.println("SCORE ="); Serial.println(score);
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.drawString(0, 0, "5/SOURIS VERTE");
    delay(1000);
    ecran.drawString(0, 3, "Melodie A");
    jouerMelodie_universel(nombre_notes_melo5fausse, melodie_5fausse, duree_note_melo5fausse );
    delay(1000);
    ecran.drawString(0, 5, "Melodie B");
    jouerMelodie_universel(nombre_notes_melo5vraie, melodie_5vraie, duree_note_melo5vraie );
    buttonB.onPressed(onPressed_bon);
    buttonA.onPressed(onPressed_mauvais);
  }

  // On affiche un message personnalisé en fonction du score
  else if (index == 10) {
    ecran.clearDisplay();
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    if ( score == 0) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "AIE ...");
      ecran.draw2x2String(0, 4, "LA");
      ecran.draw2x2String(0, 6, "BULLE");
    }
    else if (score == 5) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "PAS OUF");
      ecran.draw2x2String(0, 4, "DIS DONC");
    }
    else if (score == 10) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "VA AU");
      ecran.draw2x2String(0, 4, "SOLFEGE");
    }
    else if (score == 15) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "PEU");
      ecran.draw2x2String(0, 4, "MIEUX");
      ecran.draw2x2String(0, 6, "FAIRE");
    }
    else if (score == 20) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "T ES");
      ecran.draw2x2String(0, 4, "MOITIE");
      ecran.draw2x2String(0, 6, "CHAUD");
    }
    else if (score == 25) {
      ecran.drawString(0, 0, "Score=");
      ecran.setCursor(200, 0);
      ecran.print(score);
      ecran.draw2x2String(0, 2, "GENIE");
      ecran.draw2x2String(0, 4, "DES");
      ecran.draw2x2String(0, 6, "MELODIES");
    }

    // Si le joueur à réussit à avoir un score supérieur à 25 en appuyant sur le
    // bouton bonne réponse pendant l'explication du début, un Easter Egg
    // apparaît dans le message de fin
    // (mis en commentaire car ce bout de code provoque des bugs, comme expliqué dans la documentation MacDown.
    /* if (score == 30) {
      ecran.setFont(u8x8_font_chroma48medium8_r);
      ecran.drawString(0, 0, "EASTER");
      ecran.drawString(0, 1, "EGG      oooo   ");
      ecran.drawString(0, 2, "        o     o ");
      ecran.drawString(0, 3, "       o       o");
      ecran.drawString(0, 4, "       o       o");
      ecran.drawString(0, 5, "       o       o");
      ecran.drawString(0, 6, "        o     o ");
      ecran.drawString(0, 7, "         oooo   ");
    }
    if (score == 35) {
      ecran.setFont(u8x8_font_chroma48medium8_r);
      ecran.drawString(0, 0, "EASTER");
      ecran.drawString(0, 1, "EGG      oooo   ");
      ecran.drawString(0, 2, "        o     o ");
      ecran.drawString(0, 3, "       o       o");
      ecran.drawString(0, 4, "       o       o");
      ecran.drawString(0, 5, "       o       o");
      ecran.drawString(0, 6, "        o     o ");
      ecran.drawString(0, 7, "         oooo   ");
    }
    if (score == 40) {
      ecran.setFont(u8x8_font_chroma48medium8_r);
      ecran.drawString(0, 0, "EASTER");
      ecran.drawString(0, 1, "EGG      oooo   ");
      ecran.drawString(0, 2, "        o     o ");
      ecran.drawString(0, 3, "       o       o");
      ecran.drawString(0, 4, "       o       o");
      ecran.drawString(0, 5, "       o       o");
      ecran.drawString(0, 6, "        o     o ");
      ecran.drawString(0, 7, "         oooo   ");
    }
    // ... */
  }

  else if (index == 11) {
    Serial.println("INDEX ="); Serial.println(index);
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.draw2x2String(0, 0, "BOUTON");
    ecran.draw2x2String(0, 2, "BLEU");
    ecran.drawString(0, 5, "POUR RECOMMENCER");
    Serial.println(index);
  }

  // Une fois le message de fin personnalisé affiché on recommence une partie
  else if (index == 12) {
    // l'index et le score reviennent à 0
    index = 0;
    score = 0;
    Serial.println("INDEX ="); Serial.println(index);
    ecran.clearDisplay();
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.drawString(0, 2, "BIENVENUE SUR");
    ecran.drawString(0, 4, "MELODIE.INO");
    Serial.println(index);
  }

}


void loop() {
  //
  buttonA.read();
  buttonB.read();
  button3.read();

  // 2 e manière de déclencher l'Easter Egg, en mettant une pichenette sur le micro (piezo)
  // On lit l'état du piezo dans le loop
  /* buttonState = digitalRead(BROCHE_HP); */
  // si l'input est HIGH, c'est à dire si le piezo reçoit du son, on affiche donc le message d'Easter Egg.
  // (mis en commentaire pour la même raison que plus haut, ce bout de code provoque des bugs inépliqués.
  /* if (buttonState == HIGH) {
    Serial.println("EASTER EGG");
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.clearDisplay();
    ecran.draw2x2String(0, 2, "EASTER EGG");
    ecran.drawString(0, 0, "EASTER");
    ecran.drawString(0, 1, "EGG      oooo   ");
    ecran.drawString(0, 2, "        o     o ");
    ecran.drawString(0, 3, "       o       o");
    ecran.drawString(0, 4, "       o       o");
    ecran.drawString(0, 5, "       o       o");
    ecran.drawString(0, 6, "        o     o ");
    ecran.drawString(0, 7, "         oooo   ");
    delay(2000);
  } */
}
