void servob(){
  if ( valB > valeurbaseB && servostateB == 1 || testshooterB == 1) {
        Serial.println(testshooterB);
        testshooterB = 1;
        compshootB = 1;
        if ( testshooterB == 1 && testfinB == 0) {
          if (etatB == 1) {
            startTimeB = millis();
          }
          etatB = 2;
          if ( millis() >= 600 + startTimeB) {
            servoB.write(90);
            testfinB = 1;
          } else {
            servoB.write(180);
          }
        }
      }
    if (servostateB == 1 && testshootB == 0 && testshooterB == 0) {
      Serial.println("haut");
      if (etatB == 0) {
        startTimeB = millis();
      }
      etatB = 1;
      if ( etatB == 1 ) {
        if ( millis() >= 1000 + startTimeB) {
          servoB.write(90);
          testshootB == 1;
        } else {

          servoB.write(180);
        }
      }
    } else if (servostateB == 0 && testshootB == 0 && testshooterB == 0) {
      Serial.println("bas");
      if (etatB == 0) {
        startTimeB = millis();
      }
      etatB = 1;
      if ( etatB == 1 ) {
        if ( millis() >= 850 + startTimeB) {
          servoB.write(90);
          if ( testvieB == 0) {
            vie = vie - 1;
            testvieB = 1;
          }
          testshootB == 1;
        } else {
          servoB.write(0);
        }
      }
    }
}
