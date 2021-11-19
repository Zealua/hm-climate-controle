
String urlDecode(String input) {
  String s = input;
  s.replace("%20", " ");
  s.replace("+", " ");
  s.replace("%21", "!");
  s.replace("%22", "\"");
  s.replace("%23", "#");
  s.replace("%24", "$");
  s.replace("%25", "%");
  s.replace("%26", "&");
  s.replace("%27", "\'");
  s.replace("%28", "(");
  s.replace("%29", ")");
  s.replace("%30", "*");
  s.replace("%31", "+");
  s.replace("%2C", ",");
  s.replace("%2E", ".");
  s.replace("%2F", "/");
  s.replace("%2C", ",");
  s.replace("%3A", ":");
  s.replace("%3A", ";");
  s.replace("%3C", "<");
  s.replace("%3D", "=");
  s.replace("%3E", ">");
  s.replace("%3F", "?");
  s.replace("%40", "@");
  s.replace("%5B", "[");
  s.replace("%5C", "\\");
  s.replace("%5D", "]");
  s.replace("%5E", "^");
  s.replace("%5F", "-");
  s.replace("%60", "`");
  return s;
}

String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s +="<style type=\"text/css\">H1{font-size: 120%;text-align: center; font-family: Verdana, Arial, Helvetica, sans-serif;color: RED;}&nbsp; </style>";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}


boolean checkConnection() {
  int count = 0;
  Serial.print("Waiting for Wi-Fi connection");
  while ( count < 30 ) {
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println();
      Serial.println("Connected!");
      return (true);
    }
    delay(500);
    Serial.print(".");
    count++;
  }
  Serial.println("Timed out.");
  return false;
}

boolean restoreConfig() {
  Serial.println("Reading EEPROM...");
  String ssid = "";
  String pass = "";
  if (EEPROM.read(0) != 0) {
    for (int i = 0; i < 32; ++i) {
      ssid += char(EEPROM.read(i));
    }
    Serial.print("SSID: ");
    Serial.println(ssid);
    for (int i = 32; i < 96; ++i) {
      pass += char(EEPROM.read(i));
    }
    Serial.print("Password: ");
    Serial.println(pass);
    WiFi.begin(ssid.c_str(), pass.c_str());
    return true;
  }
  else {
    Serial.println("Config not found.");
    return false;
  }
}

boolean checkChar(){
        if (simbol == "49")   { simbol = "a";  }
        if (simbol == "51")   { simbol = "c";  }
        if (simbol == "53")   { simbol = "e";  }
        if (simbol == "55")   { simbol = "g";  }
        if (simbol == "57")   { simbol = "i";  }
        if (simbol == "60")   { simbol = "l";  }
        if (simbol == "61")   { simbol = "m";  }
        if (simbol == "62")   { simbol = "n";  }
        if (simbol == "63")   { simbol = "o";  }
        if (simbol == "64")   { simbol = "p";  }
        if (simbol == "66")   { simbol = "r";  }
        if (simbol == "68")   { simbol = "t";  }
        if (simbol == "71")   { simbol = "w";  }
        if (simbol == "10")   { simbol = ":";  }
        if (simbol == "75")   { simbol = "{";  }
        if (simbol == "77")   { simbol = "}";  }
        if (simbol == "-4")   { simbol = ",";  }
        if (simbol == "-2")   { simbol = ".";  }
        if (simbol == "-14")  { simbol = "\""; }
        if (simbol == "-38")  { simbol = "";   }
        if (simbol == "-48")  { simbol = "";   }
        if (simbol == "-16")  { simbol = "";   }   //take _
        if (simbol == "-35")  {return true;}
        
        return false; 
}

void resetEeprom(){
   for (int i = 0; i < 96; ++i) {
        EEPROM.write(i, 0);
        }
    EEPROM.commit();
    Serial.println("Eeprom erase");
}
