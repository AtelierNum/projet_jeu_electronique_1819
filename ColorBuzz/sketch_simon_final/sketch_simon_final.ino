//Code Simon
int vitesse = 100;
#include <Servo.h>
Servo monServo;
int positionDuServo = 0;



//Initialisation des LEDs et boutons buzzer.
int led1 = 2; //LED rouge
int led2 = 3; //LED verte
int led3 = 4; //LED bleue
int led4 = 5; //LED jaune
int bouton1 = 6; //Bouton rouge
int bouton2 = 7; //Bouton vert
int bouton3 = 8; //Bouton bleu
int bouton4 = 9; //Bouton jaune
int speaker = 10; //Speaker

bool servoAGauche = true;

//Les numéros sont les numéros d'entrées/sorties.

//Fréquences des sons en fonction des couleurs des led.
int son[] = {261, 330, 392, 523};
//           Do,  Mi, Sol,  Do

//Tableau de séquence à jouer.
int sequence[50];
//Personne ne dépasse le niveau 50



// Routine d'initialisation.

void setup()

{
  //Initialisation entrées/sorties
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(bouton1, INPUT);
  pinMode(bouton2, INPUT);
  pinMode(bouton3, INPUT);
 // pinMode(bouton4, INPUT); Le bouton 4 a été retiré.
  pinMode(speaker, OUTPUT);

  Serial.begin(9600);

  // Le servomoteur est branché à la broche D9.
  monServo.attach(12); // connecte sur D9
  monServo.write(positionDuServo); //connecte a position initiale
}



// Par rapport à la boucle principale.
// La loop tournera jusqu'à extinction ou reset.



void loop()


{


  //Rotation
  for (positionDuServo = 0; positionDuServo <= 180; positionDuServo++)
  {
    monServo.write(positionDuServo);
    delay(15);
  }
  //rotation dans l'autre sens
  for (positionDuServo = 180; positionDuServo >= 0; positionDuServo--)
  {
    monServo.write(positionDuServo);
    delay(15);
  }






  randomSeed(analogRead(A0));

  //Attente de pression sur une touche.
  lectureBouton();

  //Témoin de lancement du jeu.
  melodieLancement();
  delay(vitesse * 20);

  //Début du jeu
  boolean gameOver = false;
  int presse;
  int niveau = 0;
  while (!gameOver)
  {
    nouvelleNote(niveau); //Rajoute une note à la séquence.
    jouerSequence(niveau); //Joue la séquence

    for (int i = 0; i <= niveau; i++) //Attend que le joueur tape chaque note de la séquence
    {
      presse = lectureBouton(); //Lecture du bouton appuyé par le joueur
      Serial.print("bouton appuyé : ");
      Serial.println(presse);
      jouerNote(presse); //Joue la note du joueur
      if (presse != sequence[i]) //Si la note est bonne, on continue, sinon GameOver
      {
        gameOver = true;
        melodieGameOver();
      }
      if (gameOver) {
        break;
      }
    }
    niveau++;
    delay(1000);
  }
}



//La fonction de lecture des boutons.
//L'arduino vérifie les boutons un par un, mais comme la vitesse d'une vérification
//est de l'ordre de la nanoseconde, l'ensemble est presque instantané.
int lectureBouton()
{
  int boutonPresse = 0;

  while (!boutonPresse)
  {
    if (digitalRead(bouton1))
    {
      boutonPresse = 1;
      if (servoAGauche == true){
       monServo.write(180);
       servoAGauche = false;
      }
      else {
         monServo.write(0);
         servoAGauche = true;
      }

    }
    if (digitalRead(bouton2))
    {
      boutonPresse = 2;


    }
    if (digitalRead(bouton3))
    {
      boutonPresse = 3;
    }
    /*
    if (digitalRead(bouton4))
    {
      boutonPresse = 4;
    }*/
  }
  return boutonPresse;
}


//Fonction de lumière et de son
void jouerNote(int numero)
{
  switch (numero)
  {
    case 1:
      digitalWrite(led1, HIGH);
      break;
    case 2:
      digitalWrite(led2, HIGH);
      break;
    case 3:
      digitalWrite(led3, HIGH);
      break;
    case 4:
      digitalWrite(led4, HIGH);
      break;
  }
  Serial.println(numero);
  tone(speaker, son[numero - 1]); //Le tableau commence à 0 (non à 1)
  delay(800);

  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  noTone(speaker);

  delay(200);
}



//la boucle joue toute la séquence
void jouerSequence(int niveau)
{
  for (int i = 0; i <= niveau; i++)
  {
    jouerNote(sequence[i]);
  }
}


//La nouvelle note aléatoire
void nouvelleNote(int niveau)
{
  sequence[niveau] = (int)random(1, 4);
}



//Les témoins de lancement (petite séquence lumineuse)
void melodieLancement()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[0]);
  delay(300);
  tone(speaker, son[1]);
  delay(300);
  tone(speaker, son[2]);
  delay(300);
  tone(speaker, son[3]);
  delay(300);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  noTone(speaker);
}


//Game Over, led et sons.
void melodieGameOver()
{
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[3]);
  delay(150);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[2]);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[1]);
  delay(150);
  digitalWrite(led1, HIGH);
  digitalWrite(led2, HIGH);
  digitalWrite(led3, HIGH);
  digitalWrite(led4, HIGH);
  tone(speaker, son[0]);
  delay(50);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(led3, LOW);
  digitalWrite(led4, LOW);
  delay(500);
  noTone(speaker);
}
