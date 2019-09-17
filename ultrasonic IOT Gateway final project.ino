#include "ESP8266.h"

#include <SoftwareSerial.h>



#define SSID        "ICT-LAB-2.4G"

#define PASSWORD    "12345678"

#define HOST_NAME   "192.168.0.250"

#define HOST_PORT   9999



#define trigPin 11

#define echoPin 12

#define BUZZER  6



#define MY_ID       "ULTRA %d"



SoftwareSerial mySerial(8, 9);

ESP8266 wifi(mySerial);



void setup(void)

{

    Serial.begin(9600);

    Serial.print("setup begin\r\n");



    pinMode(echoPin, INPUT);

    pinMode(trigPin, OUTPUT);

    pinMode(BUZZER, OUTPUT);



    bool conn = 0;

    while (!conn){

      if (wifi.setOprToStationSoftAP()) {

        Serial.print("to station + softap ok\r\n");

      } else {

          Serial.print("to station + softap err\r\n");

      }

  

      if (wifi.joinAP(SSID, PASSWORD)) {

          Serial.print("Join AP success\r\n");

          Serial.print("IP:");

          Serial.println( wifi.getLocalIP().c_str());       

      } else {

          Serial.print("Join AP failure\r\n");

      }

      

      if (wifi.disableMUX()) {

          Serial.print("single ok\r\n");

      } else {

          Serial.print("single err\r\n");

      }

      

      Serial.print("setup end\r\n");

  

      if (wifi.createTCP(HOST_NAME, HOST_PORT)) {

          Serial.print("create tcp ok\r\n");

          conn = 1;

      } else {

          Serial.print("create tcp err\r\n");

      }

    }

    

}





void loop() {

  // put your main code here, to run repeatedly:

  long duration, distance;



  digitalWrite(trigPin, LOW);

  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);

  delayMicroseconds(10);



  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  distance = duration * 17 / 1000;



  

  

  if (distance >= 200 || distance <= 0){

    //Serial.println("Unable to measure distance");

  }else{ 

    Serial.print(distance);

    Serial.println(" cm");

    

    if (distance<60){

      tone(BUZZER, 400);

      delay(100);

      noTone(BUZZER);

      delay(100);

    }



    char _data[10] = "123";

    sprintf(_data, MY_ID, distance);

    //Serial.println(distance);

    //Serial.println(_data);



    wifi.send((const uint8_t*)_data, strlen(_data));

  }



  //delay(250);

}