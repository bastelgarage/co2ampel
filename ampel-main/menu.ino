void buttonpressed() {
  // Counts 10 seconds the pressed buttons and then does something
  if (menuselect == 0) { // Pressed the first time
    previousMillisButton = millis();
    menuselect = 1;
    pixels.setBrightness(220);
    menulight();
  } else {
    menuselect = menuselect + 1;
    pixels.setBrightness(220);
    menulight();
  }
  if (menuselect > 3) {
    menuselect = 0;
  }
}

void checkmenu() {
  if (millis() - previousMillisButton >= periodbutton) { // The period has elapsed
    switch (menuselect) {
      case 1: // The button was pressed one time, starts calibration
        menuselect = 0; // Reset menu
        makecalibrate();
        break;
      case 2: // The button was pressed two times, starts Wifi
        menuselect = 0; // Reset menu
        makewifi();
        break;
      default:
        menuselect = 0;
        break;
    }
  }
}
