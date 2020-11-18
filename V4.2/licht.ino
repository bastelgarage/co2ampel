void lichtwert() {

  if (lx >= 0 && lx <= 500) {
    lux = 50;
    pixels.setBrightness(30);
  } else if (lx > 500 && lx <= 600) {
    lux = 80;
    pixels.setBrightness(80);
  } else if (lx > 600 && lx <= 700) {
    lux = 120;
    pixels.setBrightness(120);
  } else if (lx > 700 && lx <= 800) {
    lux = 150;
    pixels.setBrightness(150);
  } else if (lx > 800 && lx <= 900) {
    lux = 170;
    pixels.setBrightness(170);
  } else { /* grösser als 1000 */
    lux = 190;
    pixels.setBrightness(220);
  }
}
