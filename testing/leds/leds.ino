/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** Test sketch for the LEDs of a CO2-Ampel                                               **
 ** https://www.co2ampel.ch                                                               **
 **                                                                                       **
 **                                                                                       **
 ** Author:  Fabian Affolter                                                              **
 ** Date:    2020-11-20                                                                   **
 ** Version: 0.2                                                                          **
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
  pixels.setBrightness(100);  // Set the brightness to about 1/5 (max = 255)
}

void loop() {
  pixel_test();
  smiley_green();
  smiley_orange();
  smiley_red();
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
  pixels.setPixelColor(6, 0, 255, 0);
  pixels.setPixelColor(5, 0, 255, 0);
  pixels.show();
  delay(5000);
}

void smiley_orange() {
  Serial.println("Show the orange smiley for 5 seconds");
  pixels.clear();
  pixels.setPixelColor(8, 0, 255, 0);
  pixels.setPixelColor(9, 0, 255, 0);
  pixels.show();
  delay(5000);
}

void smiley_red() {
  Serial.println("Show the orange smiley for 5 seconds");
  pixels.clear();
  pixels.setPixelColor(10, 0, 255, 0);
  pixels.setPixelColor(11, 0, 255, 0);
  pixels.show();
  delay(5000);
}
