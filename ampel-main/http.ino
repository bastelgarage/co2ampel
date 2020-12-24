void callhttp(){
  // Calculate difference to previously stored CO2 value
  float diff = 0;
  int co2wert = co2.getMedian();
  if (co2wert != 0) {
    diff = (float)(abs(co2wert - previousCO2)) / co2wert *100;
  }
  if ( (millis() - startMillis >= period) || (diff >= 5) )  // the period has elapsed OR the change is larger 5 percent
  {
    WiFiClient client;
    HTTPClient http;
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://" + String(sensorurl) + "?id=" + WiFi.macAddress() + "&c=" + co2.getMedian() +"&t=" + temperatur.getMedian() +"&h=" + luftfeuchte.getMedian() + "&l=" + licht.getMedian())) {  // HTTP
      Serial.println("http://" + String(sensorurl) + "?id=" + WiFi.macAddress() + "&c=" + co2.getMedian() +"&t=" + temperatur.getMedian() +"&h=" + luftfeuchte.getMedian() + "&l=" + licht.getMedian());
      Serial.print("[MAC]" +  WiFi.macAddress() + "\n");
      Serial.print("[HTTP] GET...\n");
      // Start connection and send HTTP header
      int httpCode = http.GET();

      // HTTP code will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // File found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
      delay(1000);
    } else {
      Serial.printf("[HTTP} Unable to connect\n");
    }
    startMillis = millis();
  }
}
