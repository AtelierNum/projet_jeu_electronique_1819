void calibration() {
  Serial.println("Début de la calibration");
  display.print("Wait");// on affiche wait sur l'afficheur digital

  servoA.write(180);// on fait monter les servomoteur en buté
  servoB.write(180);
  servoC.write(180);
  delay(1400); // pendant 1,4s
  servoA.write(0);// on baisse les servo-moteur
  servoB.write(0);
  servoC.write(0);
  delay(1000);//pendant 1 sec
  servoA.write(90);// on stop les servomoteur
  servoB.write(90);
  servoC.write(90);

  valA = analogRead(photoresA); //Lecture de la valeur de la photorésistance
  valB = analogRead(photoresB);
  valC = analogRead(photoresC);

  valeurbaseA = valA +70; //On lui ajoute 70 pour la marge d'erreur
  valeurbaseB = valB + 70;
  valeurbaseC = valC + 70;

  testshootA = 1; // pour ne pas les lancers dans le cycle bas pour la premier fois ( sinon ils sont trop bas )
  testshootB = 1;
  testshootC = 1;

  Serial.println("Calibration faite");
  delay(2000);
  display.clear(); // on nettoie l'afficheur digital

}
