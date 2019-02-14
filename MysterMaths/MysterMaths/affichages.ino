void piquej2(){ // programme pour piqué le joueur 2
  myservo2.write(130); // le bras tourne vers la gauche
    delay(1500);
   myservo.write(180);
    delay(1500);
    myservo.write(90); // le servo2 descend
    delay(1500);
    myservo2.write(90); // le servo 1 revient
    delay(1500);
}

void piquej1(){
  myservo2.write(50);
    delay(1500);
   myservo.write(180);
    delay(1500);
    myservo.write(0);
    delay(1500);
    myservo2.write(90);
    delay(1500);
}

void piques(){
   myservo2.write(130);
    delay(1500);
   myservo.write(180);
    delay(1500);
    myservo.write(20);
    delay(1500);
    myservo2.write(90);
    delay(1500);
     myservo2.write(50);
    delay(1500);
   myservo.write(180);
    delay(1500);
    myservo.write(20);
    delay(1500);
    myservo2.write(90);
    delay(1500);
}

void affichage_questionMult(int n1, int n2){ // affichage de la question version multiplications
  SeeedOled.clearDisplay();
  SeeedOled.setTextXY(0, 6);
  SeeedOled.putNumber(n1);
  SeeedOled.putString("x");
  SeeedOled.putNumber(n2);
}

void affichage_question(int n1, int n2) { // affichage de la question version additions
  SeeedOled.clearDisplay();
  SeeedOled.setTextXY(0, 3);
  SeeedOled.putString("(");
  SeeedOled.putNumber(n1);
  SeeedOled.putString(")");
  SeeedOled.putString("+");
  SeeedOled.putString("(");
  SeeedOled.putNumber(n2);
  SeeedOled.putString(")");
}

void affichage_reponses(int r1, int r2, int r3, int r4) { // affichage des propositions
  SeeedOled.setTextXY(3, 2);
  SeeedOled.putString("a)");
  SeeedOled.putNumber(r1);
  SeeedOled.setTextXY(3, 9);
  SeeedOled.putString("b)");
  SeeedOled.putNumber(r2);
  SeeedOled.setTextXY(5, 2);
  SeeedOled.putString("c)");
  SeeedOled.putNumber(r3);
  SeeedOled.setTextXY(5, 9);
  SeeedOled.putString("d)");
  SeeedOled.putNumber(r4);
}
