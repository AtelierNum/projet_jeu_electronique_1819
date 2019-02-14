void temps() {
int randA = 3000;// les temps pour 0 à 5 de score, c'est le temps que les servos vont rester en haut pour être tirer
int randB = 5000;
  if( score > 5 ) {// on reduit le temps on fonction du score....
    int randA = 3000;
    int randB = 4000;
  }
    else if( score >10 ) {
     randA = 2000;
    randB = 3000;
  }
    else if( score > 15 ) {
     randA = 2000;
     randB = 2500;
  }
    else if( score > 25 ) {
    randA = 1500;
    randB = 2000;
  }
    else if( score > 35 ) {
    randA = 1000;
    randB = 2000;
  }
    else if( score > 50 ) {
    randA = 1000;
    randB = 1500;
  }
  int tempsA = random(randA, randB*2); //Déterminer le temps où le servo moteur sera en haut en aléatoire avec les temps determinés plus haut
  int tempsB = random(randA+(randA/2), randB);
  int tempsC = random(randA+(randB/4), randB);


  /// CYCLE DE TEMPS COPIER POUR CHAQUE SERVOMOTEUR

  if (millis() > tempsA + temps_faitA) { //Compare le temps avec le temps actuel
    temps_faitA = millis(); //Actualise le compteur de temps
    etatA = 0; // on reset les variables à chaque cycle haut/bas
    testvieA = 0;
    testshootA = 0;
    if (servostateA == 1) { // variable reset que quand le servomoteur est haut
      servostateA = 0;
      testshooterA = 0;
    } else {//reset quand le servo est bas
      servostateA = 1;
      testfinA = 0;
    }
    if (compshootA == 1) {// compteur se score
      score++;
      testvieA = 1;
      compshootA = 0;
    }

  }
/////////////////////////////

  if (millis() > tempsB + temps_faitB) { //Compare le temps avec le temps actuel
    temps_faitB = millis(); //Actualise le compteur de temps
    etatB = 0;
    testvieB = 0;
    testshootB = 0;
    if (servostateB == 1) {
      servostateB = 0;
      testshooterB = 0;
    } else {
      servostateB = 1;
      testfinB = 0;
    }
    if (compshootB == 1) {
      score++;
      testvieB = 1;
      compshootB = 0;
    }

  }

  if (millis() > tempsC + temps_faitC) { //Compare le temps avec le temps actuel
    temps_faitC = millis(); //Actualise le compteur de temps
    etatC = 0;
    testvieC = 0;
    testshootC = 0;
    if (servostateC == 1) {
      servostateC = 0;
      testshooterC = 0;
    } else {
      servostateC = 1;
      testfinC = 0;
    }
    if (compshootC == 1) {
      score++;
      testvieC = 1;
      compshootC = 0;
    }
  }
}
