/*
   setStationHostname
*/
bool setStationHostname(const char* p_pcHostname) {

  if (p_pcHostname) {
    WiFi.hostname(p_pcHostname);
    Serial.printf("setDeviceHostname: Station hostname is set to '%s'\n", p_pcHostname);
  }
  return true;
}


/*
   MDNSDynamicServiceTxtCallback

   Add a dynamic MDNS TXT item 'ct' to the clock service.
   The callback function is called every time, the TXT items for the clock service
   are needed.
   This can be triggered by calling MDNS.announce().

*/
/*
void MDNSDynamicServiceTxtCallback(const MDNSResponder::hMDNSService p_hService) {
  Serial.println("MDNSDynamicServiceTxtCallback");
  if (hMDNSService == p_hService) {
    Serial.print(String("Updating TXT item to: ") + co2.getMedian() + "\n");
    MDNS.addDynamicServiceTxt(p_hService, "co2ppm",(String("")+co2.getMedian()).c_str());
  }
}
*/

/*
   MDNSProbeResultCallback

   Probe result callback for the host domain.
   If the domain is free, the host domain is set and the clock service is
   added.
   If the domain is already used, a new name is created and the probing is
   restarted via p_pMDNSResponder->setHostname().

*/
void hostProbeResult(String p_pcDomainName, bool p_bProbeResult) {

  Serial.println("MDNSProbeResultCallback");
  Serial.printf("MDNSProbeResultCallback: Host domain '%s.local' is %s\n", p_pcDomainName.c_str(), (p_bProbeResult ? "free" : "already USED!"));
  if (true == p_bProbeResult) {
    // Set station hostname
    setStationHostname(pcHostDomain);
    if (!bHostDomainConfirmed) {
      // Hostname free -> setup clock service
      bHostDomainConfirmed = true;
      if (!hMDNSService) {
        // Add a 'clock.tcp' service to port 'SERVICE_PORT', using the host domain as instance domain
        hMDNSService = MDNS.addService(0, "co2ampel", "tcp", SERVICE_PORT);
        /*
         if (hMDNSService) {
          // Add a simple static MDNS service TXT item
          MDNS.addServiceTxt(hMDNSService, "tcpport", SERVICE_PORT);
          // Set the callback function for dynamic service TXTs
          MDNS.setDynamicServiceTxtCallback(MDNSDynamicServiceTxtCallback);
        }
        */
      }
    }
  } else {
    // Change hostname, use '-' as divider between base name and index
    if (MDNSResponder::indexDomain(pcHostDomain, "-", 0)) {
      MDNS.setHostname(pcHostDomain);
    } else {
      Serial.println("MDNSProbeResultCallback: FAILED to update hostname!");
    }
  }
}


/*
   handleHTTPClient
*/

void handleHTTPRequest() {
  Serial.println("");
  Serial.println("HTTP Request");
  String s;
  s = String("{\"co2\": ") + co2.getMedian() +String(",")
    + String("\"temperature\": ") + temperatur.getMedian() +String(",")
    + String("\"humidity\": ") + luftfeuchte.getMedian() + String(",")
    + String("\"brightness\": ") + licht.getMedian() + String("}\n");
  Serial.println("Sending 200");
  server.send(200, "application/json", s);
}

void setupMDNS() {
   // Setup MDNS responder
  MDNS.setHostProbeResultCallback(hostProbeResult);
  if ((!MDNSResponder::indexDomain(pcHostDomain, 0, mdnsname)) ||
      (!MDNS.begin(pcHostDomain))) {
    Serial.println("Error setting up MDNS responder!");
    return;
  }
  Serial.println("MDNS responder started");
  // Setup HTTP server
  server.on("/", handleHTTPRequest);
  server.begin();
  Serial.println("HTTP server started");
}

void loopMDNS() {
// Check if a request has come in
  server.handleClient();
  // Allow MDNS processing
  MDNS.update();
  /*
  static esp8266::polledTimeout::periodicMs timeout(UPDATE_CYCLE);
  if (timeout.expired()) {

    if (hMDNSService) {
      // Just trigger a new MDNS announcement, this will lead to a call to
      // 'MDNSDynamicServiceTxtCallback', which will update the time TXT item
      MDNS.announce();
    }
  }
  */
}
