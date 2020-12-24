/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** https://www.co2ampel.ch                                                               **
 **                                                                                       **
 ** Sensor: sensirion scd30                                                               **
 **                                                                                       **
 ** Author:  Alf Müller                                                                   **
 ** Date:    02.12.2020                                                                   **
 ** Version: 4.4-dev                                                                      **
 ** License: MIT                                                                          **
 ******************************************************************************************/

#include <ESP8266WiFi.h>                     // https://github.com/esp8266/Arduino
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>                    // https://github.com/tzapu/WiFiManager
#include <Adafruit_NeoPixel.h>              // https://github.com/adafruit/Adafruit_NeoPixel_ZeroDMA
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" // via librarymanager SparkFun_SCD30
#include <RunningMedian.h>                  // https://github.com/RobTillaart/RunningMedian
#include <ArduinoJson.h>                    // https://github.com/bblanchon/ArduinoJson (Version 5.10.0 only)
#include <ESP8266HTTPClient.h>

// NeoPixels
#define PIN D8       // NeoPixels pin
#define NUMPIXELS 12 // Number of NeoPixels
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// Sensirion SCD30
SCD30 airSensor;

String outputState = "off";
char sensorurl[200] = "www.mydomain.tld/sensor.php";
unsigned long startMillis = 560000; //900000
const unsigned long period = 600000;

// Flag for saving data
bool shouldSaveConfig = false;
int sensorint;

// Button menu
int menuselect = 0;
int previousMillisButton;
const unsigned long periodbutton = 10000; // Time to wait for further input

// Callback notifying us of the need to save configuration
void saveConfigCallback () {
  Serial.println("Should save configuration");
  shouldSaveConfig = true;
}


int x;
int lux; // 60-200 (Luminous value of the NeoPixels)
int co2wert;
int lx;
int previousMillis;
int previousCO2 = 0;
int interval = 1500; // Flashing time
int ledcheck = 0;

RunningMedian licht = RunningMedian(5);
RunningMedian co2 = RunningMedian(5);
RunningMedian temperatur = RunningMedian(5);
RunningMedian luftfeuchte = RunningMedian(5);

void setup() {
  Serial.begin(115200);
  Serial.println("");
  Serial.println("");
  Serial.println("Further details can be found at https://www.co2ampel.ch");
  Serial.println("Firmware release: 4.4-dev");
  Serial.println("Please report issues at https://github.com/bastelgarage/co2ampel/issues");
  delay(1000);
  Wire.begin();
  if (airSensor.begin(Wire, false) == false) // Disable the auto-calibration
  {
    Serial.println("Air sensor not recognized. The sensor is defective.");
    while (1)
      ;
  }
  //airSensor.setAutoSelfCalibration(false); // Sensirion no auto calibration
  airSensor.setMeasurementInterval(5); // Seconds 2 to 1800 possible

  pixels.begin();
  pixels.clear();
  pixels.setBrightness(200); // Set the brightness to about 1/5 (max = 255)
  pinMode(D3, INPUT_PULLUP);

  // File system
  //SPIFFS.format();

  // Read configuration from file system JSON
  Serial.println("Mounting file system...");

  if (SPIFFS.begin()) {
    Serial.println("Mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("Reading configuration file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("Opened configuration file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);

        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success()) {
          Serial.println("\nparsed json");
          strcpy(sensorurl, json["sensorurl"]);
          sensorint = jsonBuffer.size();
        } else {
          Serial.println("Failed to load JSON configuration");
        }
      }
    }
  } else {
    Serial.println("Failed to mount file system");
  }
  if (sensorint > 5) {
    //wenn die variable sensorurl grösser 5 ist
    WiFiManager wifiManager;
  }
}

void loop() {
  if (ledcheck == 0) {
    pixeltest();
    ledcheck = 1;
  }
  boolean btnPressed = !digitalRead(D3);
  if (btnPressed == true) {
    buttonpressed();
    Serial.print("Button pressed: ");
    Serial.println(menuselect);
    delay(300);
  }
  if (menuselect == 0) {
    x = analogRead(A0);
    //Serial.println(x);
    licht.add(x);
    lx = licht.getMedian();

    if (airSensor.dataAvailable())
    {
      co2.add(airSensor.getCO2());
      Serial.print("CO2 (ppm): ");
      Serial.print(co2.getMedian());
      co2wert = co2.getMedian();

      temperatur.add(airSensor.getTemperature());
      Serial.print(" Temperature (C): ");
      Serial.print(temperatur.getMedian(), 1);

      luftfeuchte.add(airSensor.getHumidity());
      Serial.print(" Humidity (%): ");
      Serial.print(luftfeuchte.getMedian(), 1);

      Serial.print(" Light: ");
      Serial.print(licht.getMedian(), 0);

      Serial.print(" Lux: ");
      Serial.print(lux);
      Serial.println();

      delay(100);
      lichtwert();
      delay(100);
      callhttp();
    }else{
      Serial.print(".");
       delay(400);
    }
  } else {
    menulight();
    checkmenu();
  }
  makeled();
}

void makewifi() {
  pixels.setBrightness(220);
  pixels.clear();
  for ( int i = 6; i < NUMPIXELS; i++) { // Green for wifi enable
    pixels.setPixelColor(i, 0, 255, 0);
    pixels.show();
  }
  WiFiManagerParameter custom_output("URL", "URL (kein HTTPS)", sensorurl, 200);
  WiFiManager wifiManager;
  // Set configuration save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.addParameter(&custom_output);
  //wifiManager.resetSettings();
  wifiManager.setTimeout(120);
  wifiManager.autoConnect("co2ampel");
  Serial.println("Connected");

  strcpy(sensorurl, custom_output.getValue());
  // Save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("Saving configuration");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["sensorurl"] = sensorurl;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("Failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    // End save
  }


  if (!wifiManager.startConfigPortal("co2ampel")) {
    Serial.println("Connection failed and timeout reached");
    delay(3000);
    // Reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
}
