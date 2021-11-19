/*
 *
 * HIT_SYSTEM_ESP
 *
*/

#include "FirebaseESP8266.h" //FirebaseESP8266.h must be included before ESP8266WiFi.h
#include <ESP8266WiFi.h>
#include <OneWire.h>

#include <EEPROM.h>
#include <DNSServer.h>                  // ??? realy need?
#include <WiFiClient.h>                 // ??? realy need?
#include <ESP8266WebServer.h>

#define FIREBASE_HOST "hmclimatecontrol-default-rtdb.firebaseio.com"  
 //"hmclimatecontrol.firebaseapp.com" //Do not include https:// in FIREBASE_HOST
#define FIREBASE_AUTH "Vuvabs76VwpbiTCNxIQFrXakCAvdqZG14rx6XYJr"

//-------------====___SET your ID device__=====------------------
          String path = "/testDevice";
//---------------------------------------------------------------

OneWire ds(4); // Создаем объект OneWire для шины 1-Wire, с помощью которого будет осуществляться работа с датчиком

String jsonStr;
char uartOut[20];
int sens=250,hold=350,front=50,
    sensTemp=0,holdTemp=0, frontTemp=0;

long timer = 0;

    String incomingByte ="";
    String message ="0";
    String simbol = "";

// AP acscess point param
const IPAddress apIP(192, 168, 1, 1);
const char* apSSID = "ESP8266_SETUP";
boolean settingMode;
String ssidList;


//Define FirebaseESP8266 data object
FirebaseData firebaseData;
//Local server
DNSServer dnsServer;                     // ??? realy need?
ESP8266WebServer webServer(80);

    String webPage = "";
    int count =1; 

  int gpio2_pin = 2;
//---------------------------------------------------------------------------------------------------------------
//===================================================__SETUP__===================================================
//---------------------------------------------------------------------------------------------------------------
void setup()
{

  Serial.begin(115200);
  EEPROM.begin(512);
  delay(100);

  // подготавливаем GPIO-контакты:
  pinMode(gpio2_pin, OUTPUT);
  digitalWrite(gpio2_pin, LOW);
 
     incomingByte+="HIT "+String(count)+" : ";

  if (restoreConfig()) {             // check SSID and pass in EEPROM
    if (checkConnection()) {         // ckeck  WI-FI connect
      settingMode = false;
      startWebServer();              // run normal page
     
      Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
      Firebase.reconnectWiFi(true);

          Serial.println("----------Begin Set Test-----------");
          Serial.println();

          firebasePushIp();
          firebasePush("0");
          delay(2000);
          getAllParam();
      return;
    }
  }
  settingMode = true;
  setupMode();                       // run page set SSID and pass
}

void loop()
{
  timer++;
  delay(10);
  if(timer > 90000){
    firebasePush(String(temperature()));
    timer = 0;
  }
  if (settingMode) { 
      dnsServer.processNextRequest(); 
      }
  webServer.handleClient();
  
//  if (Serial.available() > 0) { //если есть доступные данные
//        // считываем байт
//    simbol = String(Serial.read() - 48);
//  
//    if ( checkChar() ) {
//        
//          webPage += incomingByte+" "+ message + "<br>";
//          Serial.println(message);
//    
//      if(message=="re"){
//           resetEeprom();
//      }
//      else {
//
//          firebasePush();
//
//         // getAllParam();
//          
//          simbol = "";
//          count++;
//          incomingByte = "";
//          message="";
//          incomingByte += "HIT " + String(count) + " : ";
//        }
//     }
//     else {
//          message += simbol;
//        }
//  }
}


void startWebServer() {
  if (settingMode) {
    Serial.println("webPageSetupMode...");
    webPageSetupMode();}
  else {
    Serial.println("webPageStandardMode...");
    webPageStandardMode();
  }  
  Serial.println("web begin...");
  webServer.begin();
  
}

float temperature() {
    byte data[2]; // Место для значения температуры
  
  ds.reset(); // Начинаем взаимодействие со сброса всех предыдущих команд и параметров
  ds.write(0xCC); // Даем датчику DS18b20 команду пропустить поиск по адресу. В нашем случае только одно устрйоство 
  ds.write(0x44); // Даем датчику DS18b20 команду измерить температуру. Само значение температуры мы еще не получаем - датчик его положит во внутреннюю память
  
  delay(5000); // Микросхема измеряет температуру, а мы ждем.  
  
  ds.reset(); // Теперь готовимся получить значение измеренной температуры
  ds.write(0xCC); 
  ds.write(0xBE); // Просим передать нам значение регистров со значением температуры

  // Получаем и считываем ответ
  data[0] = ds.read(); // Читаем младший байт значения температуры
  data[1] = ds.read(); // А теперь старший

  // Формируем итоговое значение: 
  //    - сперва "склеиваем" значение, 
  //    - затем умножаем его на коэффициент, соответсвующий разрешающей способности (для 12 бит по умолчанию - это 0,0625)
  float temperature =  ((data[1] << 8) | data[0]) * 0.0625;
  
  // Выводим полученное значение температуры в монитор порта
  Serial.println(temperature);
  return temperature;
  }

  
