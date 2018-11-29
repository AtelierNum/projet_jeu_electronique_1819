void startLeds(int n, int d) { // n : nb de leds, d : delai en ms entre le 3, 2 et 1

  // "3" en rouge
  for (int i = 2; i < n / 5 + 2; i++) {
    strip.setPixelColor(i, 255, 0, 0); // strip.setPixelColor(quelle led ?, rouge, vert, bleu); la première led c'est la 0, etc.
  }
  for (int i = n / 2 - n / 10; i < n / 2 + n / 10; i++) {
    strip.setPixelColor(i, 255, 0, 0);
  }
  for (int i = n - 3; i > n - 3 - n / 5; i--) {
    strip.setPixelColor(i, 255, 0, 0);
  }


  strip.show(); // Pour envoyer les données dans le ruban, sans l'appel de cette fonction, le ruban ne change pas de couleur
  delay(d);

  strip.clear(); // On éteint toutes les leds
  strip.show();
  delay(1); // Pour avoir le temps d'envoyer les données dans les leds

  // "2" en orange
  for (int i = n / 3 - n / 10; i < n / 3 + n / 10; i++) {
    strip.setPixelColor(i, 255, 165, 0);
  }
  for (int i = 2 * (n / 3) - n / 10; i < 2 * (n / 3) + n / 10; i++) {
    strip.setPixelColor(i, 255, 200, 0);
  }
  strip.show();
  delay(d);

  strip.clear();
  strip.show();
  delay(1);

  // "1" en vert
  for (int i = n / 2 - n / 10; i < n / 2 + n / 10; i++) {
    strip.setPixelColor(i, 0, 255, 0);
  }
  strip.show();
  delay(d);

  strip.clear();
  strip.show();
  delay(1);


}
