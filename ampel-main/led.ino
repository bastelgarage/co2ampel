void makeled() {
  if (menuselect == 0) {
    if (co2wert >= 0 && co2wert <= 800) {

      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(4, 0, 255, 0);
      pixels.setPixelColor(5, 0, 255, 0);
      pixels.show();

    } else if (co2wert > 800 && co2wert <= 900) {
      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(7, 0, 255, 0);
      pixels.setPixelColor(4, 0, 255, 0);
      pixels.setPixelColor(5, 0, 255, 0);
      pixels.show();

    } else if (co2wert > 900 && co2wert <= 1000) {
      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(7, 0, 255, 0);
      pixels.setPixelColor(8, 255, 255, 0);
      pixels.setPixelColor(2, 255, 255, 0);
      pixels.setPixelColor(3, 255, 255, 0);
      pixels.show();

    } else if (co2wert > 1000 && co2wert <= 1100) {
      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(7, 0, 255, 0);
      pixels.setPixelColor(8, 255, 255, 0);
      pixels.setPixelColor(9, 255, 255, 0);
      pixels.setPixelColor(2, 255, 255, 0);
      pixels.setPixelColor(3, 255, 255, 0);
      pixels.show();

    } else if (co2wert > 1100 && co2wert <= 1200) {
      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(7, 0, 255, 0);
      pixels.setPixelColor(8, 255, 255, 0);
      pixels.setPixelColor(9, 255, 255, 0);
      pixels.setPixelColor(10, 255, 0, 0);
      pixels.setPixelColor(0, 255, 0, 0);
      pixels.setPixelColor(1, 255, 0, 0);
      pixels.show();

    } else if (co2wert > 1100 && co2wert <= 1200) {
      pixels.clear();
      pixels.setPixelColor(6, 0, 255, 0);
      pixels.setPixelColor(7, 0, 255, 0);
      pixels.setPixelColor(8, 255, 255, 0);
      pixels.setPixelColor(9, 255, 255, 0);
      pixels.setPixelColor(10, 255, 0, 0);
      pixels.setPixelColor(11, 255, 0, 0);
      pixels.setPixelColor(0, 255, 0, 0);
      pixels.setPixelColor(1, 255, 0, 0);
      pixels.show();

    } else if (co2wert > 1200) { // blink rotes Smiley
      if (millis() - previousMillis > interval)
      {
        pixels.clear();
        pixels.setPixelColor(6, 0, 255, 0);
        pixels.setPixelColor(7, 0, 255, 0);
        pixels.setPixelColor(8, 255, 255, 0);
        pixels.setPixelColor(9, 255, 255, 0);
        pixels.setPixelColor(10, 255, 0, 0);
        pixels.setPixelColor(11, 255, 0, 0);
        pixels.show();
        previousMillis = millis();
      } else {
        pixels.clear();
        pixels.setPixelColor(6, 0, 255, 0);
        pixels.setPixelColor(7, 0, 255, 0);
        pixels.setPixelColor(8, 255, 255, 0);
        pixels.setPixelColor(9, 255, 255, 0);
        pixels.setPixelColor(10, 255, 0, 0);
        pixels.setPixelColor(11, 255, 0, 0);
        pixels.setPixelColor(0, 255, 0, 0);
        pixels.setPixelColor(1, 255, 0, 0);
        pixels.show();
      }
    }
  } else {
    menulight();
  }
}


void pixeltest() {
  pixels.clear();
  pixels.setPixelColor(6, 0, 255, 0);
  pixels.setPixelColor(7, 0, 255, 0);
  pixels.setPixelColor(8, 255, 255, 0);
  pixels.setPixelColor(9, 255, 255, 0);
  pixels.setPixelColor(10, 255, 0, 0);
  pixels.setPixelColor(11, 255, 0, 0);
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.setPixelColor(1, 255, 0, 0);
  pixels.setPixelColor(2, 255, 255, 0);
  pixels.setPixelColor(3, 255, 255, 0);
  pixels.setPixelColor(4, 0, 255, 0);
  pixels.setPixelColor(5, 0, 255, 0);
  pixels.show();
  delay(5000);
}

void menulight() {

  if (menuselect == 1) {
    pixels.clear();
    for ( int i = 0; i < NUMPIXELS; i++) { //all blue for calibration
      pixels.setPixelColor(i, 0, 0, 255);
      pixels.show();
    }
  }
  if (menuselect == 2) { // all green for Wifi select
    pixels.clear();
    for ( int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 0, 255, 0);
      pixels.show();
    }
  }
}
