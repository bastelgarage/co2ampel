/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** Test sketch for the LEDs of a CO2-Ampel                                               **
 ** https://www.co2ampel.ch                                                               **
 **                                                                                       **
 **                                                                                       **
 ** Author:  Fabian Affolter                                                              **
 ** Date:    2020-12-03                                                                   **
 ** Version: 0.3                                                                          **
 ** License: MIT                                                                          **
 ******************************************************************************************/

#include <ESP8266WiFi.h>
#include <Adafruit_NeoPixel.h>

// NeoPixels
#define PIN D8        // NeoPixels pin
#define NUMPIXELS 12  // Number of NeoPixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Serial.println("Test firmware for the LEDs of the CO2-Ampel");
  Serial.println("-------------------------------------------");
  delay(1000);

  pixels.begin();
  pixels.clear();
  pixels.setBrightness(50);  // Set the brightness to about 1/5 (max = 255)
}

void loop() {
  pixels.clear();
  pixel_loop();
  pixel_test();
  smiley_green();
  smiley_orange();
  smiley_red();
  pixel_bar();
}

void pixel_loop() {
  Serial.println("Cycle through all LEDs");
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(255, 0, 0));
    pixels.show();
    delay(250);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 255, 0));
    pixels.show();
    delay(250);
  }
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0, 0, 255));
    pixels.show();
    delay(250);
  }
}

void pixel_test() {
  Serial.println("Flashing the LEDS");
  pixels.clear();
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.setPixelColor(1, 255, 0, 0);
  pixels.setPixelColor(2, 255, 255, 0);
  pixels.setPixelColor(3, 255, 255, 0);
  pixels.setPixelColor(4, 0, 255, 0);
  pixels.setPixelColor(5, 0, 255, 0);
  pixels.setPixelColor(6, 0, 255, 0);
  pixels.setPixelColor(7, 0, 255, 0);
  pixels.setPixelColor(8, 255, 255, 0);
  pixels.setPixelColor(9, 255, 255, 0);
  pixels.setPixelColor(10, 255, 0, 0);
  pixels.setPixelColor(11, 255, 0, 0);
  pixels.show();
  delay(2000);
}

void smiley_green() {
  Serial.println("Show the green smiley for 5 seconds");
  pixels.clear();
  pixels.setPixelColor(4, 0, 255, 0);
  pixels.setPixelColor(5, 0, 255, 0);
  pixels.show();
  delay(2000);
}

void smiley_orange() {
  Serial.println("Show the orange smiley for 5 seconds");
  pixels.clear();
  pixels.setPixelColor(2, 255, 255, 0);
  pixels.setPixelColor(3, 255, 255, 0);
  pixels.show();
  delay(2000);
}

void smiley_red() {
  Serial.println("Show the orange smiley for 5 seconds");
  pixels.clear();
  pixels.setPixelColor(0, 255, 0, 0);
  pixels.setPixelColor(1, 255, 0, 0);
  pixels.show();
  delay(2000);
}

void pixel_bar() {
  Serial.println("Show the bar");
  pixels.clear();
  pixels.setPixelColor(6, 0, 255, 0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(7, 0, 255, 0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(8, 255, 255, 0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(9, 255, 255, 0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(10, 255, 0, 0);
  pixels.show();
  delay(500);
  pixels.setPixelColor(11, 255, 0, 0);
  pixels.show();
  delay(500);
  pixels.clear();
}
