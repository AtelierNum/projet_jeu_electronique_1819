
#include <EasyButton.h>

#define BUTTON_PIN_1 2
#define BUTTON_PIN_2 4

// On déclare les 2 objets EasyButton, on leur donne un nom et on les associent.
EasyButton button1(BUTTON_PIN_1);
EasyButton button2(BUTTON_PIN_2);

void setup() {
  Serial.begin(9600);
  button1.begin();
  button1.onPressed(onPressed1);
  button2.begin();
  button2.onPressed(onPressed2);
}

void onPressed1() {
  Serial.println("BOUTON 1");
}

void onPressed2() {
  Serial.println("BOUTON 2");
}

void loop() {
  button1.read();
  button2.read();
}
