/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** co2ampel.ch                                                                           **
 ** Sensor: sensirion scd30                                                               **
 **                                                                                       **
 ** Autor: Alf Müller                                                                     **
 ** Datum: 18.11.2020                                                                     **
 ** Version: 4.2                                                                   **
 *******************************************************************************************
  MIT Lizenz.*/

#include <ESP8266WiFi.h>                     //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>                    //https://github.com/tzapu/WiFiManager
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include "SparkFun_SCD30_Arduino_Library.h" //via librarymanager SparkFun_SCD30
#include <RunningMedian.h>                  //https://github.com/RobTillaart/RunningMedian
#include <ArduinoJson.h>                    // https://github.com/bblanchon/ArduinoJson
#include <WiFiClient.h>
#include <ESP8266HTTPClient.h>

//Neopixel
#define PIN D8 //NEOPIXEL ANSCHLUSS
#define NUMPIXELS 12 // ANZAHL NEOPIXEL
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

//sensirion scd30
SCD30 airSensor;

String outputState = "off";
char sensorurl[200] = "www.abcdefg.ch/sensor.php";
unsigned long startMillis = 560000; //900000
const unsigned long period = 600000;


//flag for saving data
bool shouldSaveConfig = false;
int sensorint;

//button menu
int menuselect = 0;
int previousMillisButton;
const unsigned long periodbutton = 10000; //Time to wait for further input

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}


int x;
int lux; // 60-200 (luminous value of the neopixels)
int co2wert;
int lx;
int previousMillis;
int interval = 1500; // Flashing time
int ledcheck = 0;

RunningMedian licht = RunningMedian(5);
RunningMedian co2 = RunningMedian(5);
RunningMedian temperatur = RunningMedian(5);
RunningMedian luftfeuchte = RunningMedian(5);

void setup() {
  Serial.begin(115200);
  Serial.println("Infos unter www.co2ampel.ch Software V4.2.beta");
  delay(1000);
  Serial.println("Infos unter www.co2ampel.ch Software V4.2.beta");
  Wire.begin();
  if (airSensor.begin(Wire, false) == false) //disable the auto-calibration
  {
    Serial.println("Air sensor not recognized. The sensor is defective.");
    while (1)
      ;
  }
  //airSensor.setAutoSelfCalibration(false); // Sensirion no auto calibration
  airSensor.setMeasurementInterval(5); //seconds 2 to 1800 possible

  pixels.begin();
  pixels.clear();
  pixels.setBrightness(200); //Set the BRIGHTNESS to about 1/5 (max = 255)
  pinMode(D3, INPUT_PULLUP);

  //File system
  //SPIFFS.format();

  //read configuration from FS json
  Serial.println("mounting FS...");

  if (SPIFFS.begin()) {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/config.json")) {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile) {
        Serial.println("opened config file");
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
          Serial.println("failed to load json config");
        }
      }
    }
  } else {
    Serial.println("failed to mount FS");
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
    Serial.print("button pressed :");
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
      Serial.print("co2(ppm):");
      Serial.print(co2.getMedian());
      co2wert = co2.getMedian();

      temperatur.add(airSensor.getTemperature());
      Serial.print(" Temperature(C):");
      Serial.print(temperatur.getMedian(), 1);

      luftfeuchte.add(airSensor.getHumidity());
      Serial.print(" Humidity(C):");
      Serial.print(luftfeuchte.getMedian(), 1);

      Serial.print(" Light:");
      Serial.print(licht.getMedian(), 0);

      Serial.print(" lux:");
      Serial.print(lux);
      Serial.println();

      delay(100);
      lichtwert();
      delay(100);
      callhttp();
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
  for ( int i = 6; i < NUMPIXELS; i++) { // green for wifi enable
    pixels.setPixelColor(i, 0, 255, 0);
    pixels.show();
  }
  WiFiManagerParameter custom_output("URL", "URL(kein https)", sensorurl, 200);
  WiFiManager wifiManager;
  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);
  wifiManager.addParameter(&custom_output);
  //wifiManager.resetSettings();
  wifiManager.setTimeout(120);
  wifiManager.autoConnect("co2ampel");
  Serial.println("Connected.");

  strcpy(sensorurl, custom_output.getValue());
  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["sensorurl"] = sensorurl;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }


  if (!wifiManager.startConfigPortal("co2ampel")) {
    Serial.println("Connection failed and timeout reached");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }
}
