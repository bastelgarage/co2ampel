
/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** https://www.co2ampel.ch                                                               **
 **                                                                                       **
 ** Sensor: Sensirion SCD30                                                               **
 **                                                                                       **
 ** Author: Fabian Affolter                                                               **
 ** Date:  2020-11-23                                                                     **
 ** Version: 0.0.1                                                                        **
 ** License: MIT                                                                          **
 ******************************************************************************************/
/*
Based on the examples provided by https://github.com/sparkfun/SparkFun_SCD30_Arduino_Library
*/

#include <Wire.h>

#include "SparkFun_SCD30_Arduino_Library.h"

SCD30 airSensor;

void setup()
{
  Serial.begin(115200);
  Serial.println("SCD30 sensor test");
  Wire.begin();

  if (airSensor.begin() == false)
  {
    Serial.println("SCD30 not detected. Please check wiring");
    while (1)
      ;
  }
  // Change number of seconds between measurements
  airSensor.setMeasurementInterval(5);
  // Set altitude of the sensor in m
  airSensor.setAltitudeCompensation(560);
  // Current ambient pressure in mBar
  airSensor.setAmbientPressure(835);

  float offset = airSensor.getTemperatureOffset();
  Serial.println("");
  Serial.println("");
  Serial.print("Current temperature offset: ");
  Serial.print(offset, 2);
  Serial.println(" °C");
  // Optionally we can set temperature offset
  airSensor.setTemperatureOffset(0);
  // Recalibrate the sensor
  airSensor.setForcedRecalibrationFactor(400); // 400 = fresh air
  Serial.print("Start SCD30 calibration, please wait 30 s ...");
  Serial.println("");
  delay(30000);
}

void loop(){
  if (airSensor.dataAvailable())
  {
    Serial.print(" CO2 (ppm): ");
    Serial.print(airSensor.getCO2());

    Serial.print(", Temperature (°C): ");
    Serial.print(airSensor.getTemperature(), 1);

    Serial.print(", Humidity (%): ");
    Serial.print(airSensor.getHumidity(), 1);

    Serial.println();
  }
  else {
    Serial.print(".");
  }
  delay(1000);
}
