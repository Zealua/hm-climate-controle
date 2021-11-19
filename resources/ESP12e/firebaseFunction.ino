void firebasePush(){
    if (Firebase.pushJSON(firebaseData, path, message))   {

            Serial.println("----------Push HIT-----------");
            Serial.println("PATH: " + firebaseData.dataPath());
            Serial.print("PUSH NAME: ");
            Serial.println(firebaseData.pushName());
            Serial.println("--------------------------------");
            Serial.println();
    }
    else {
            Serial.println("----------Can't push data--------");
            Serial.println("REASON: " + firebaseData.errorReason());
            Serial.println("--------------------------------");
            Serial.println();
    }
}

void firebasePush(String text) {
        if (Firebase.pushJSON(firebaseData, path, text))   {

            Serial.println("----------Push HIT-----------");
            Serial.println("PATH: " + firebaseData.dataPath());
            Serial.print("PUSH NAME: ");
            Serial.println(firebaseData.pushName());
            Serial.println("--------------------------------");
            Serial.println();
    }
    else {
            Serial.println("----------Can't push data--------");
            Serial.println("REASON: " + firebaseData.errorReason());
            Serial.println("--------------------------------");
            Serial.println();
    }
}
void firebasePushIp(){
  uint32_t ip1,ip2,ip3,ip4;
  uint32_t ip=(uint32_t)WiFi.localIP();
  ip1=ip<<24;
  ip1=ip1>>24;
  ip2=ip<<16;
  ip2=ip2>>24;
  ip3=ip<<8;
  ip3=ip3>>24;
  ip4=ip>>24;
  char ipStr[16];
  sprintf(ipStr,"%lu.%lu.%lu.%lu",ip1,ip2,ip3,ip4);
  if(Firebase.setString(firebaseData, path+"/IP", ipStr)){

            Serial.println("----------__Push_IP__-----------");
        //    Serial.println("PATH: " + firebaseData.dataPath());
        //    Serial.print("PUSH NAME: ");
        //    Serial.println(firebaseData.pushName());
        //    Serial.println("--------------------------------");
            Serial.println();
    }
    else {
            Serial.println("----------Can't push data--------");
            Serial.println("REASON: " + firebaseData.errorReason());
            Serial.println("--------------------------------");
            Serial.println();
    }
  }

int firebaseGetParam(String paramType){
     int param;

        if (Firebase.getInt(firebaseData, path + "/param/"+paramType)){
           if (firebaseData.dataType() == "int"){
               param=firebaseData.intData();
               //Serial.println(param);
               return param;
            }
        } else {
            Serial.println("firebase get  false");
            return 0;
        }
}
