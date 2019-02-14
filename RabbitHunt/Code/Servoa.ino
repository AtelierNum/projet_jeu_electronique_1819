void servoa(){
// LES COMMENTAIRES S'APPLIQUE POUR LES 3 SERVO-MOTEURS

 if ( valA > valeurbaseA && servostateA == 1  || testshooterA == 1) { // condition si le tire est valider
        testshooterA = 1; // permet de ne pas rentrer dans les boucles du cycle monter/descente du lapin
        compshootA = 1; //  ajoute 1 au score
        if ( testshooterA == 1 && testfinA == 0) {
          if (etatA == 1) { // condition pour relancer le "delay"
            startTimeA = millis(); // ajoute millis a la variable
          }
          etatA = 2; // permet de ne pas relancer la condition pour relancer le "delay"
          if ( millis() >= 600 + startTimeA) { // condition qui fait office de delay
            servoA.write(90);// le servomoteur s'arrête
            testfinA = 1; // permet de ne pas relancer la condition
          } else {
            servoA.write(180); // le servomoteur monte
          }
        }
      }
    if (servostateA == 1 && testshootA == 0 && testshooterA == 0) { // cycle haut du servo moteur, il monte et se stop ou bout de 1000ms

      if (etatA == 0) {// condition pour relancer le "delay"
        startTimeA = millis();// ajoute millis a la variable
      }
      etatA = 1; // permet de ne pas relancer la condition pour relancer le "delay"
      if ( etatA == 1 ) { // permet de lancer la condition delay au deuxième tour
        if ( millis() >= 1000 + startTimeA) { // condition qui fait office de delay
          servoA.write(90); // le servomoteur se stop
          testshootA == 1; //permet de ne pas relancer la boucle de monter
        } else {
          servoA.write(180); // le servomoteur monte
        }
      }
    } else if (servostateA == 0 && testshootA == 0 && testshooterA == 0) { // cycle bas du servo moteur...
      if (etatA == 0) { // condition pour relancer le "delay"
        startTimeA = millis(); //ajoute millis a la variable
      }
      etatA = 1; // permet de ne pas relancer la condition pour relancer le "delay"
      if ( etatA == 1 ) { // permet de lancer la condition delay au deuxième tour
        if ( millis() >= 850 + startTimeA) {// condition qui fait office de delay
          servoA.write(90);// le servo moteur se stop
          if ( testvieA == 0) {// condition qui évite de perdre plusieurs fois de la vie en un seul tour
            vie = vie - 1;// on enlève un point de vie
            testvieA = 1;// pour ne pas revenir dans cette condition
          }
          testshootA == 1; // pour ne pas relancer le cycle bas
        } else {
          servoA.write(0); // le moteur se baisse
        }
      }
    }
}
