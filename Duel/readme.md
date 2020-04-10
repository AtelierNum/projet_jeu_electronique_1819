[**home**](../README.md)

# Duel

Petit jeu électronique utilisant arduino - 2 joueurs

Réalisé par Lengliang Li et Morgane Thomas

Interaction design, L’École de design Nantes Atlantique - 22 janvier 2019


## Le principe

**Duel** est un jeu opposant deux joueurs, ou plutôt deux cowboys. Ils se regardent de loin en plissant les yeux. Une musique du far west se joue.
Nyanyanyan Nayn Nyan Nyan …
Dès que la musique s’arrête, les cowboys dégainent leur arme et tirent le plus vite possible. Le plus rapide gagne la manche, au bout de trois manches gagnée, c’est la victoire.

![](media/gif.gif)

## Le circuit

### Liste du matériel
* 1 carte Arduino Uno
* 1 cable USB
* des cables
* 1 bread board
* 2 Servo Moteurs
* 3 boutons
* Un ruban de 5 Leds
* Un buzzer (ou piezzo)

### Connecter les Servo Moteurs
![](media/servo.png)

On connecte d’abord les deux moteurs qui nous serviront à faire l’animation de mort des cowboys, puis on teste notre branchement avec un code simple.

On appelle nos Servomoteurs et les associe à la broche correspondante.

```
#include <Servo.h>

#define ServoBleu 8
#define ServoRouge 9
Servo servoB;
Servo servoR;
```

On définit les positions de notre cowboy debout et de notre cowboy mort.

```
int posServoInitiale = 0;
int posServoMort = 90;
```
On initialise tout ça en connectant les Servo créés à la pin correspondante et en positionnant nos moteurs sur l’angle 0, nos cowboys sont en vie.

```
void setup() {
  servoB.attach(ServoBleu);
  servoR.attach(ServoRouge);
  
  servoR.write(posServoInitiale);
  servoB.write(posServoInitiale);
}
```
Pour tester tout ça, on leur dit de mourir dans la boucle.

```
void loop() {
  servoB.write(posServoMort);
  servoR.write(posServoMort);
  delay(4000);
}
```

### Connecter les Boutons
![](media/boutons.png)
On connecte ensuite les boutons. Un pour lancer la partie et les deux autres pour les cowboys. On teste ensuite leur bon fonctionnement.

On définit les broches correspondant à nos boutons.

```
#define boutonRouge 2
#define boutonBleu 3
#define boutonReset 4
```

On définit leur rôle dans le setup

```
void setup() {
  pinMode(boutonRouge, INPUT);
  pinMode(boutonBleu, INPUT);
  pinMode(boutonReset, INPUT);
}
```
Dans la loop, modifie le code précédent pour que les boutons agissent sur les moteurs. On définit donc des actions à effectuer lorsque l’on appuie sur chacun des boutons.

```
void loop() {
  
  // Si on appuie sur le bouton rouge
  if (digitalRead(boutonRouge) == HIGH) {
    servoR.write(posServoMort);
  }

  // Si on appuie sur le bouton bleu
  if (digitalRead(boutonBleu) == HIGH) {
    servoB.write(posServoMort);
  }

  // Si on appuie sur le bouton reset
  if (digitalRead(boutonReset) == HIGH) {
    servoR.write(posServoInitiale);
    servoB.write(posServoInitiale);
  }
}
```
### Connecter les Leds
![](media/Leds.png)
Les leds vont nous servir à compter les points.
On commence par appeler la librairie Adafruit que l’on va utiliser pour contrôler le ruban Leds. On appelle ensuite notre ruban en l’associant à la pin correspondante et en définissant son nombre de Leds.

```
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define rubanLed 6
#define nombrePixel 5
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(nombrePixel, rubanLed, NEO_GRB + NEO_KHZ800);
```

On définit en plus de cela deux variables qui vont nous permettre de connaître la position de la dernière led de chaque joueur.

```
int numLedR;
int numLedB;
```
Dans le setup, on définit la led de départ de chaque joueur. On en veut un à chaque extrémité et les points gagnés les feront avancer vers le centre du ruban. On initialise ensuite le ruban en éteignant chacune des Leds grâce à une boucle.

```
void setup() {
  numLedR = 0; // n° de la led du joueur rouge au début
  numLedB = 4; // n° de la led du joueur bleu au début
  
  pixels.begin();
  pixels.setBrightness(100);
  for (int i = 0; i < nombrePixel; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
}
```
On va ensuite faire en sorte que quand un cowboy tire, donc quand on appuie sur un  bouton, un point s’ajoute pour celui ci en puis de l’action sur le moteur que l’on avait déjà réglée.

```
void loop() {
  
  // Si on appuie sur le bouton rouge
  if (digitalRead(boutonRouge) == HIGH) {
    servoR.write(posServoMort);

    // Le joueur rouge gagne un point
    numLedR++;

    // On allume les leds allant de 0 au nombre de points du joueur en rouge
    for (int i = 0; i <= numLedR; i++) {
        pixels.setPixelColor(i, pixels.Color(255, 0, 0));
      }
      pixels.show();
  }

  // Si on appuie sur le bouton bleu
  if (digitalRead(boutonBleu) == HIGH) {
    servoB.write(posServoMort);

    // Le joueur rouge gagne un point
    numLedB++;

    // On allume les leds allant de 0 au nombre de points du joueur en bleu
    for (int i = 4; i >= numLedB; i--) {
        pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      }
      pixels.show();
  }
}
```

### Connecter le buzzer
![](media/piezo.png)
Le buzzer va nous servir à jouer de la musique.

Pour ce faire il faut une bibliothèque de notes que nous enregistrons sous un autre onglet de notre projet appelé “notes.h”. Celle ci se construit de cette façon

```
#define NOTE_DO1   33
#define NOTE_DOD1  35
#define NOTE_RE1   37
#define NOTE_RED1  39
#define NOTE_MI1   41
#define NOTE_FA1   44
#define NOTE_FAD1  46
#define NOTE_SOL1  49
#define NOTE_SOLD1 52
#define NOTE_LA1   55
#define NOTE_LAD1  58
#define NOTE_SI1   62
…
```
Et ainsi de suite. Vous en trouverez des pré-faîtes sur internet. Si ce sont des versions anglaises, alors les notes sont nommées différemment
Français   do   ré   mi   fa   sol   la   si
Anglais     C    D    E    F    G     A   B

On crée ensuite un nouvel onglet sur lequel on retrouvera notre mélodie. Il s’appelle “Musique.h”.
Dans celui-ci, on commence par y inclure notre bibliothèque de notes. et lui attribuer le piezo.

```
#include "notes.h"
#define Piezo 10
```

On crée ensuite les variables qui nous permettront de créer la mélodie. La première sera définie plus tard et correspond au nombre de notes qui composent la mélodie, la seconde c’est notre mélodie, retranscrite en se référant à notre fichier “notes.h”. Enfin la dernière c’est la durée que chaque notes va avoir suivant le tableau :
  1 : ronde
  2 : blanche
  4 : noire
  8 : croche
16 : double croche
32 : triple croche
64 : quadruple croche
La mélodie que l’on utilise ici est le célèbre thème issu du film “Le bon, la brute et le truand”.
Nyanyanyan Nayn Nyan Nyan …

long nombreNotesMelodie;

```
int melodie[] = {
  NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_DO5, NOTE_RE5, NOTE_LA4, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_DO5, NOTE_RE5, NOTE_SOL5, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_LA5, NOTE_DO6, 
  NOTE_SI5, NOTE_LA5, NOTE_SOL5, 0, NOTE_MI5, NOTE_LA5, NOTE_MI5, NOTE_LA5, NOTE_MI5, 0, NOTE_RE5, NOTE_LA4, NOTE_LA4
};

int dureeNoteMelodie[] = {
  16, 16, 16, 16, 2, 4, 4, 2, 4, 16, 16, 16, 16, 2, 4, 4, 2, 4, 16, 16, 16, 16, 2, 4,
  8, 8, 2, 4, 16, 16, 16, 16, 4, 8, 4, 8, 1
};
```

On crée ensuite notre fonction qui va nous permettre de jouer la mélodie lorsqu’on l’appelle. Je vous laisse regarder, tout est expliqué dans le code.

```
void JouerMelodie() {

  nombreNotesMelodie = random(8, 37);

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
```
On va maintenant dire que la musique se lance quand on appuie sur notre bouton reset. Pour cela, on retourne dans notre onglet principal et on commence par y inclure notre fichier contenant la mélodie et on appelle notre piezo dans le setup.

```
#include "Musique.h"

void setup() {
  pinMode(Piezo, OUTPUT);
}

Ensuite, on va dans la partie des actions liées au bouton reset et on lui dit de lire notre mélodie.

void loop() {

  // Si on appuie sur le bouton reset
  if (digitalRead(boutonReset) == HIGH) {
    servoR.write(posServoInitiale);
    servoB.write(posServoInitiale);

    JouerMelodie()
  }
}
```

##Duel.ino
###Montage global
Vous avez maintenant le montage global de ce jeu de duel avec en prime une bonne partie du code, et normalement tout est testé et tout fonctionne.

![](media/Montage.png)

###Logique du jeu

On va séparer le programme en 3 parties qui vont nous permettre de séparer les différentes étapes du jeux, comme sur le schéma suivant.

![](media/Flowchart.png)

Pour ce faire on va créer des booléens qui évolueront au fil de la partie selon les action réalisées. On les initialise tout d’abord au début de notre code.

```
boolean mancheFinie = false;
boolean manche = false;
boolean victoireDuel = false;
```
Ensuite, On va réorganiser nos action en fonction de ces booléens dans la loop. 
Tout d’abord, si l’on appuie sur le bouton reset, on lance la manche, mais il va aussi nous permettre de remettre les points à zéro pour recommencer une partie.

```
void loop() {
  
  // Si on appuie sur le bouton reset
  if (digitalRead(boutonReset) == HIGH) {
    servoR.write(posServoInitiale);
    servoB.write(posServoInitiale);
    delay(1000);

    // On éteint les leds qui servent à compter les points
    for (int i = 0; i < nombrePixel; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
    pixels.show();

    numLedR = -1; // n° de la led du joueur rouge au début (score)
    numLedB = 5; // n° de la led du joueur bleu au début (score)

  // On lance le jeu

  // On lit la musique qui a une durée random
  JouerMelodie();

  // On lance la première manche
  manche = true;
  }
}
```
Puis on va organiser la manche en y mettant les actions sur nos boutons rouge et bleu dedans. Lorsque l’un de ces deux boutons est pressé, “manche” se termine et “mancheFinie” commence
En en a profité pour ajouter un petit son lorsque l’on tire, il est construit de la même manière que notre mélodie.

```
void loop() {
  if (manche) {

    // Si je joueur rouge tire en premier
    if (digitalRead(boutonRouge) == HIGH) {

      // Le pistolet tire
     TirerBang();
      
      …
      
      delay(4000);

      // La manche est finie
      mancheFinie = true;
      manche = false;
    }

    // idem pour le bouton bleu

  }
}
```

Ensuite, la partie “mancheFinie” nous permet de compter les points. On va alors regarder si un des joueurs ont 3 points pour savoir si la partie est terminée.
Sinon, on relance une nouvelle manche en relevant les cowboys et en remettant la musique.

```
if (mancheFinie) {

    if (numLedR >= 2 || numLedB <= 2) { // Si un des deux joueurs est à 3 points
      victoireDuel = true;
    } 
    
    else {
      // On relève les cowboys
      servoR.write(posServoInitiale);
      servoB.write(posServoInitiale);
      delay(1000);

      // On lit la musique qui a une durée random
      JouerMelodie();

      // On passe à la manche suivante
      manche = true;
      mancheFinie = false;
    }
}
```

Enfin, pour la partie “victoireDuel”, on crée une animation afin d’indiquer le vainqueur.

```
if (victoireDuel) {
    ledVictoire = abs(cos(a) * 255); // Note cos() renvoie une valeur entre -1 et 1 et abs() renvoie une valeur absolue (tjs positive)
    a += .01;
    
    if (numLedR >= 2) { // Victoire joueur rouge
      for (int i = 0; i < nombrePixel; i++) {
        pixels.setPixelColor(i, pixels.Color(ledVictoire, 0, 0));
      }
    }
    
    if (numLedB <= 2) { // Victoire joueur bleu
      for (int i = 0; i < nombrePixel; i++) {
        pixels.setPixelColor(i, pixels.Color(0, 0, ledVictoire));
      }
    }
    pixels.show();
  }
```
Voilà ! Le jeu est terminé, maintenant c’est à vous de mettre la main à la pâte pour décorer un peu tout ça. Nous on avait fait une boite avec des trous pour les câbles des moteurs, pour le bouton reset et pour les leds. On avait camouflé nos moteur avec de faux rocher et fixé nos boutons rouge et bleu à des pistolets pour enfants.

![](media/WechatIMG12.jpeg)
![](media/WechatIMG15.jpeg)
![](media/WechatIMG21.jpeg)

[**home**](../README.md)





