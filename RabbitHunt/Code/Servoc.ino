void servoc(){

  if ( valC > valeurbaseC && servostateC == 1  || testshooterC == 1) {
        Serial.println("shoot");
        testshooterC = 1;
        compshootC = 1;
        if ( testshooterC == 1 && testfinC == 0) {
          if (etatC == 1) {
            startTimeC = millis();
          }
          etatC = 2;
          if ( millis() >= 600 + startTimeC) {
            servoC.write(90);
            testfinC = 1;
          } else {
            servoC.write(180);
          }
        }
      }
    if (servostateC == 1 && testshootC == 0 && testshooterC == 0) {
      Serial.println("haut");
      if (etatC == 0) {
        startTimeC = millis();
      }
      etatC = 1;
      if ( etatC == 1 ) {
        if ( millis() >= 1000 + startTimeC) {
          servoC.write(90);
          testshootC == 1;
        } else {

          servoC.write(180);
        }
      }
    } else if (servostateC == 0 && testshootC == 0 && testshooterC == 0) {
      Serial.println("Cas");
      if (etatC == 0) {
        startTimeC = millis();
      }
      etatC = 1;
      if ( etatC == 1 ) {
        if ( millis() >= 850 + startTimeC) {
          servoC.write(90);
          if ( testvieC == 0) {
            vie = vie - 1;
            testvieC = 1;
          }
          testshootC == 1;
        } else {
          servoC.write(0);
        }
      }
    }
}
