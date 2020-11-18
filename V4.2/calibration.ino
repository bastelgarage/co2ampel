void makecalibrate() {
  // Forced Calibration Sensirion SCD 30
  airSensor.setAltitudeCompensation(0); // Altitude in m ü NN
  airSensor.setForcedRecalibrationFactor(400); // fresh air
  Serial.print("Start SCD 30 calibration, please wait 30 s ...");
  pixels.setBrightness(220);
  pixels.clear();
  for ( int i = 6; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  pixels.clear();
  for ( int i = 7; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  pixels.clear();
  for ( int i = 8; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  pixels.clear();
  for ( int i = 9; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  pixels.clear();
  for ( int i = 10; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  pixels.clear();
  for ( int i = 11; i < NUMPIXELS; i++) { //all blue for calibration
    pixels.setPixelColor(i, 0, 0, 255);
    pixels.show();
  }
  delay(5000);
  Serial.println("calibration done");
  Serial.println("reboot Device");
  ESP.reset();
  delay(5000);
}
