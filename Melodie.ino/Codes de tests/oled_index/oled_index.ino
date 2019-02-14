
#include <Arduino.h>
#include <U8x8lib.h>
#include <Wire.h>
#include <EasyButton.h>

U8X8_SSD1306_128X64_NONAME_HW_I2C ecran(/* reset=*/ U8X8_PIN_NONE);

int index = 0;
byte compteur = 0;
#define BUTTON_PIN 2

EasyButton button(BUTTON_PIN);


void setup(void) {
  // Pour le débugage. 
  Serial.begin(115200);
  // Initialisation du bouton.
  button.begin();
  // La fonction appelée quand le bouton sera pressé. 
  button.onPressed(onPressed);
  // Initialisation de l'écran
  ecran.begin();
}

void onPressed() {
  index += 1;
}


void loop(void) {
 // On lit l'état du bouton, s'il est pressé ou non 
 button.read();
 // On définie ce qui apparaît sur l'écran en fonction de l'index, avec une boucle si
  if (index == 0) {
    Serial.println("étape 1");
    // Importation de la font
    ecran.setFont(u8x8_font_chroma48medium8_r);
    // On compose le message affiché sur l'écran en indiquant sa taille et ses coordonnées. 
    ecran.drawString(0, 0, "Bienvenue au blind test");
  }

  else if (index == 1) {
    Serial.println("étape 1");
    ecran.setFont(u8x8_font_chroma48medium8_r);
    ecran.draw2x2String(0, 0, "TEXTE 2");
  }


}
