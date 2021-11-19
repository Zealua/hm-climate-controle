void setupMode() {
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
  int n = WiFi.scanNetworks();
  delay(100);
  Serial.println("");
  for (int i = 0; i < n; ++i) {
    ssidList += "<option value=\"";
    ssidList += WiFi.SSID(i);
    ssidList += "\">";
    ssidList += WiFi.SSID(i);
    ssidList += "</option>";
  }
  delay(100);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP(apSSID);
  dnsServer.start(53, "*", apIP);
  startWebServer();
  Serial.print("Starting Access Point at \"");
  Serial.print(apSSID);
  Serial.println("\"");
}


void webPageSetupMode(){
    Serial.print("Starting Web Server at ");
    Serial.println(WiFi.softAPIP());
    
    webServer.on("/settings", []() {
          Serial.println("/settings");

        String s = "<h1>Wi-Fi Settings</h1><p>Please enter your password by selecting the SSID.</p>";
        s += "<form method=\"get\" action=\"setap\"><label>SSID: </label><select name=\"ssid\">";
        s += ssidList;
        s += "</select><br>Password: <input name=\"pass\" length=64 type=\"password\"><input type=\"submit\"></form>";
        webServer.send(200, "text/html", makePage("Wi-Fi Settings", s));
      });
    
    webServer.on("/setap", []() {
                Serial.println("/setap");

        resetEeprom();

        String ssid = urlDecode(webServer.arg("ssid"));
        Serial.print("SSID: ");
        Serial.println(ssid);
        String pass = urlDecode(webServer.arg("pass"));
        Serial.print("Password: ");
        Serial.println(pass);
  
        Serial.println("Writing SSID to EEPROM...");
        for (int i = 0; i < ssid.length(); ++i) {
          EEPROM.write(i, ssid[i]);
        }
  
        Serial.println("Writing Password to EEPROM...");
        for (int i = 0; i < pass.length(); ++i) {
          EEPROM.write(32 + i, pass[i]);
        }
        EEPROM.commit();
        Serial.println("Write EEPROM done");
  
        String s = "<h1>Setup complete.</h1><p>device will be connected to \"";
        s += ssid;
        s += "\" after the restart.";
        webServer.send(200, "text/html", makePage("Wi-Fi Settings", s));
        ESP.restart();
      });

    webServer.onNotFound([]() {
        String s = "<h1>AP mode</h1><p><a href=\"/settings\">Wi-Fi Settings</a></p>";
        webServer.send(200, "text/html", makePage("AP mode", s));
      });
  }
