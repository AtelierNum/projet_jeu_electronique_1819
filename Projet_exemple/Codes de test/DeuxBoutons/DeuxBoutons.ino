// DeuxBoutons //////////////
// 15.11.2018 - Clément Gault
/*
   Essai de la bibliothèque EasyButton d'Evert Arias,
   disponible dans le gestionnaire de bibliothèque.
   Menu : Croquis/Inclure une biliothèque/Gérer les biliothèques
   -
   Quand on appuie une fois sur un bouton, cela incrémente
   une valeur propre à chaque bouton. Les valeurs s'affichent
   dans le moniteur série.
   -
   Montage :
     - Un bouton en pin 2
     - Un bouton en pin 4
   (voir DeuxBoutons_montage.jpg) 
  
*/

// On indique à Arduino qu'on va utiliser
// la bibliothèque EasyButton :
#include <EasyButton.h>

// On déclare deux objets EasyButton :
EasyButton button1(2); // Le premier nommé button1, entre parenthèse la pin
EasyButton button2(4); // etc…

int n1, n2; // Les compteurs pour chaque bouton

void setup() {
  Serial.begin(9600);

  // Initialisation des deux objets EasyButon :
  button1.begin();
  button2.begin();

  // Quand un bouton est pressé,
  // on appelle une fois une fonction dédiée (voir après le loop()) :
  button1.onPressed(onPressed1);
  button2.onPressed(onPressed2);
} // Fin du setup();

void loop() {
  // On lit en boucle l'état du bouton :
  // quand il est pressé, il va lire la fonction
  // appelée en retour (voir après le loop()) :
  button1.read();
  button2.read();
} // Fin du loop()

// Fonction appelée quand on appuie sur le bouton 1 :
void onPressed1() {
  n1++; // On incrémente le compteur pour button1
  Serial.print("Button 1 : ");
  Serial.print(n1);
  Serial.print(" | Button 2 : ");
  Serial.println(n2);
}

// Pareil pour le second bouton :
void onPressed2() {
  n2++;
  Serial.print("Button 1 : ");
  Serial.print(n1);
  Serial.print(" | Button 2 : ");
  Serial.println(n2);
}
