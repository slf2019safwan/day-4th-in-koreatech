#include <WiFi.h>

#include <IoTStarterKit_WiFi.h>



#define trigPin 11

#define echoPin 12

#define BUZZER  6

#define LED     7



IoTMakers im;



#define deviceID      "slf201D1566351533494"

#define authRqtNo     "rhqw4l3zc"

#define extrSysID     "OPEN_TCP_001PTL001_1000007606"



#define WIFI_SSID     "ICT-LAB-2.4G"

#define WIFI_PASS     "12345678"



#define TAG_ID        "ULTRASONIC"



void setup() {

  // put your setup code here, to run once:

  Serial.begin(9600);

  

  initIoTMakers();



  pinMode(trigPin,  OUTPUT);

  pinMode(echoPin,  INPUT);

  pinMode(LED,      OUTPUT);



  digitalWrite(LED, HIGH);

}



int count = 0;

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

  

  im.send_numdata(TAG_ID, distance);

  

  if (distance >= 200 || distance <= 0){

    Serial.println("Unable to measure distance");

  }else{

    Serial.print(distance);

    Serial.println(" cm");

    

    if (distance<60){

      tone(BUZZER, 400);

      delay(100);

      noTone(BUZZER);

      delay(100);

    }

  }

}



void initIoTMakers(){



  while (1){

    Serial.print(F("Connecting to AP . . ."));



    while (im.begin(WIFI_SSID, WIFI_PASS) <0 ) {

      Serial.println(F("Retrying..."));

      delay (100);

    }



    Serial.println("Success");

    im.init(deviceID, authRqtNo, extrSysID);

    Serial.println(F("Connect to platform ..."));



    while (im.connect() <0 ){

      Serial.println(F("Retrying..."));

      delay (100);

    }



    Serial.println(F("Success"));

    Serial.println(F("Auth..."));





    if (im.auth_device() >= 0){

      Serial.println(F("Success"));

      return;

    }

  }

}