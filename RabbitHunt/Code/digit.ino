void digit() {
  if ( startgame == 0) {// pour commencer une partie...
        if( valA > valeurbaseA){ // on tire sur le lapin A pour lancer la partie//
      startgame=1; // pour ne pas relancer la condition
      display.setColonOn(false);// pour ne pas avoir les deux petits points au milieu de l'afficheur digital
      display.clear();// on nettoie l'afficheur
      display.print("3333");// on affiche 3333
      delay(1000);// 1sec
      display.clear();//on nettoie l'ecran
      display.print("2222");// le cycle se répète.....
      delay(1000);
      display.clear();
      display.print("1111");
      delay(1000);
      display.clear();
      display.print("0000");
      delay(1000);
      valB = valeurbaseB;// pour ue le tire pour lancer la partie ne soit pas compter comme score
    }
    display.print("GO ?"); // on affiche tant qu'on a pas lancer la partie
  }else {
      display.printDualCounter(vie, score);// quand la partie est commencer on affiche notre vie et le score
    }

    if ( vie <= 0){// quand on a plus de vie
      servoA.write(90);// on stop les servomoteur
      servoB.write(90);
      servoC.write(90);
      display.clear();// on nettoie l'ecran
      display.print("GAME END");// on affiche game end
      delay(1000);
      display.clear();
      display.print("SCORE");
      delay(1000);
      display.clear();
      display.print(score);// on affiche le score
      display.blink(); // le score clignote
      delay(2000);
      endgame=0;// on remet les variables à zero pour relancer la partie
      startgame=0;
      vie = 3;
      score = 0;
      etatA=0;
      etatB=0;
      etatC=0;
      calibration();// on recalibre les servomoteur
    }
  }
