void webPageStandardMode(){
  Serial.print("Starting Web Server at ");
  Serial.println(WiFi.localIP());

  webPage += "<p>LED <a href=\"socket2On\"><button>OFF</button></a>&nbsp;<a href=\"socket2Off\"><button>ON</button></a></p>";
  webPage += "<p> Reset Log <a href=\"reset\"><button>RESET</button></a></p>";
  webPage += "<p> Get param from Api <a href=\"sendParam\"><button>SEND to Device</button></a></p>";
  webPage += "<p><h1>STA mode</h1><p><a href=\"/resetPass\">Reset Wi-Fi Settings</a></p>";
   

    webServer.on("/", [](){
     webServer.send(200, "text/html",  makePage("HIT SYSTEM", webPage));
  });
webServer.on("/socket2Off", [](){
        Serial.println("IN socket2Off");
     Serial.println("socket Off");
     webServer.send(200, "text/html", makePage("HIT SYSTEM", webPage));
     digitalWrite(gpio2_pin, LOW);
      delay(1000);
  });
webServer.on("/socket2On", [](){
     Serial.println("socket On");
     webServer.send(200, "text/html", makePage("HIT SYSTEM", webPage));
     digitalWrite(gpio2_pin, HIGH);
      delay(1000);
  });
webServer.on("/sendParam", [](){
  
          getAllParam();
          
          webServer.send(200, "text/html", makePage("HIT SYSTEM", webPage));
          delay(1000);
  });
webServer.on("/reset", [](){
     webPage = "";
     webPage += "<p>LED <a href=\"socket2On\"><button>OFF</button></a>&nbsp;<a href=\"socket2Off\"><button>ON</button></a></p>";
     webPage += "<p> Reset Log <a href=\"reset\"><button>RESET</button></a></p>";
     webPage += "<p> Get param from Api <a href=\"sendParam\"><button>SEND to Device</button></a></p>";
     webPage += "<p><h1>STA mode</h1><p><a href=\"/resetPass\">Reset Wi-Fi Settings</a></p>";
     
     webServer.send(200, "text/html", makePage("HIT SYSTEM", webPage));
     delay(100);
  });

    webServer.on("/resetPass", []() {
      resetEeprom();
      String s = "<h1>Wi-Fi settings was reset.</h1><p>Please reset device.</p>";
      webServer.send(200, "text/html", makePage("Reset Wi-Fi Settings", s));
    });
  }



void getAllParam(){
  
    frontTemp=firebaseGetParam("Front");
    sensTemp=firebaseGetParam("PARAM");
    holdTemp=firebaseGetParam("HOLD");

    if(frontTemp!=front||sensTemp!=sens||holdTemp!=hold){
       if(holdTemp>50&&holdTemp<1000&&sensTemp>50&&sensTemp<1000&&frontTemp>50&&frontTemp<1000){
           front=frontTemp;
           sens=sensTemp;
           hold=holdTemp;
    
           sprintf(uartOut,"!?%03d:%03d:%03d\r\n",sens,front,hold);
           Serial.println(uartOut);
       }
    }
}
