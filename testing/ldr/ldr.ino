/*******************************************************************************************
 **                 www.bastelgarage.ch  - purecrea GmbH                                  **
 ** Der Onlineshop mit Videoanleitungen und kompletten Bausätzen für Anfänger und Profis! **
 *******************************************************************************************
 ** Test sketch for the LDR of a CO2-Ampel                                                **
 ** https://www.co2ampel.ch                                                               **
 **                                                                                       **
 **                                                                                       **
 ** Author:  Fabian Affolter                                                              **
 ** Date:    2020-12-03                                                                   **
 ** Version: 0.1                                                                          **
 ** License: MIT                                                                          **
 ******************************************************************************************/
#define ANALOG_PIN A0

void setup() {
  Serial.begin(115200);
  Serial.println("Test firmware for the LDR of the CO2-Ampel");
  Serial.println("------------------------------------------");
  delay(1000);
}

void loop() {
  int sensorValue = analogRead(ANALOG_PIN);
  Serial.println(sensorValue);
  delay(500);
}
