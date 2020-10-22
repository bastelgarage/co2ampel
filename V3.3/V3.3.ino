/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** co2ampel.ch                                                                           **
 ** Sensor: sensirion scd30                                                               **
 **                                                                                       **
 ** Autor: Alf Müller                                                                     **
 ** Datum: 19.10.2020                                                                     **
 ** Version: 3.3                                                                         **
 *******************************************************************************************
 Creative Commons Namensnennung - Nicht-kommerziell - 
 Weitergabe unter gleichen Bedingungen 4.0 International Lizenz.*/
 
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" //via librarymanager SparkFun_SCD30
#include <RunningMedian.h>                  //https://github.com/RobTillaart/RunningMedian

//Neopixel
#define PIN D8 //NEOPIXEL ANSCHLUSS
#define NUMPIXELS 12 // ANZAHL NEOPIXEL
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//sensirion scd30
SCD30 airSensor;


int x;
int lux; // 60-200 (leuchtwert der Neopixel)
int co2wert;
int lx;
int previousMillis;
int interval =1500; // Blinkzeit 
int ledcheck = 0;

RunningMedian licht = RunningMedian(5);
RunningMedian co2 = RunningMedian(5);
RunningMedian temperatur = RunningMedian(5);
RunningMedian luftfeuchte = RunningMedian(5);

void setup() {
  Serial.begin(115200);
  Serial.println("Infos unter www.co2ampel.ch Software V3.3.1");
  delay(1000);
  Serial.println("Infos unter www.co2ampel.ch Software V3.3.1");
  Wire.begin();
  if (airSensor.begin() == false)
  {
    Serial.println("Luftsensor nicht erkannt. Der Sensor ist defekt.");
    while (1)
      ;
  }
  airSensor.setMeasurementInterval(4); //Sekunden 2 bis 1800 möglich
  airSensor.setAltitudeCompensation(800); //meter über Meer in m
  airSensor.setAmbientPressure(1000); //Luftdruck hPa: 700 to 1200
  float offset = airSensor.getTemperatureOffset();
  Serial.print("Aktueller Temperatur-Versatz: ");
  Serial.print(offset, 2);
  Serial.println("C");
  //airSensor.setTemperatureOffset(5); //Optional können wir den Temperatur-Offset auf 5°C einstellen
  
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(200); //Setzen Sie die HELLIGKEIT auf etwa 1/5 (max = 255)
}

void loop() {
  if (ledcheck == 0){
    pixeltest();
    ledcheck = 1;
  }
  x = analogRead(A0);
  //Serial.println(x);
  licht.add(x);
  lx = licht.getMedian();
  
  if (airSensor.dataAvailable())
  {
    co2.add(airSensor.getCO2());
    Serial.print("co2(ppm):");
    Serial.print(co2.getMedian());
    co2wert = co2.getMedian();

    temperatur.add(airSensor.getTemperature());
    Serial.print(" Temperatur(C):");
    Serial.print(temperatur.getMedian(), 1);

    luftfeuchte.add(airSensor.getHumidity());
    Serial.print(" Feuchtigkeit(C):");
    Serial.print(luftfeuchte.getMedian(), 1);

    Serial.print(" Licht:");
    Serial.print(licht.getMedian(), 0);

    Serial.print(" lux:");
    Serial.print(lux);
    Serial.println();
  }
  else
    Serial.print(".");
  delay(100);
  lichtwert();
  delay(100);
  makeled();
}
