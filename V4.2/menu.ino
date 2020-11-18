void buttonpressed() {
  //counts 10 seconds the pressed buttons and then does something
  if (menuselect == 0) { // pressed the first time
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
  if (millis() - previousMillisButton >= periodbutton) { // the period has elapsed
    switch (menuselect) {
      case 1: //the button was pressed 1 time it is calibrated
        menuselect = 0; //reset menu
        makecalibrate();
        break;
      case 2: // the button was pressed 3 times wifi starts
        menuselect = 0; //reset menu
        makewifi();
        break;
      default:
        menuselect = 0;
        break;
    }
  }
}
