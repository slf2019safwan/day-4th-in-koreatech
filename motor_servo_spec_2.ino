//******************************************************//
// Servo Motor
// Sample Code 1 [Control the servo motor]
//                                      - Kyung-Sik Jang//
//******************************************************//

// Servo Motor
//  - Servo motor is different from general motor,
//    and since it is fixed in rotation, it is used when accurate
//    movement is needed.
// How to use
// VCC Pin - Red
// GND Pin - Brown
// PWM Pin - PWM

// What is PWM?
//  - Abbreviation for pulse width modulation, a method of controlling
//    the average voltage by varying the Duty ratio within a certain period.
//
//        (t1)       (t2)
//      ┌------┐           ┌------
// -----┘      └-----------┘
//    t1 : High state of waveform
//    t2 : Low state of waveform
//
//  - duty cycle calculation
//      duty ratio : t1 / (t1 + t2)
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <Servo.h>
Servo myServo;
//int data = 0;
int angle = 0;
IoTMakers g_im;

#define deviceID    "koreatD1566888016848"
#define authnRqtNo  "laxa5s1nw"
#define extrSysID   "OPEN_TCP_001PTL001_1000007605"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

// ************************************************************************ //
// Very Important!!!!
// IoTMakers tag stream id must be the same below !!!
#define TAG_ID "Servo"
// ************************************************************************ //

void init_iotmakers()
{
  while(1)
  {
    Serial.print(F("Connect to AP..."));
    while(g_im.begin(WIFI_SSID, WIFI_PASS) < 0)
    {
      Serial.println(F("retrying"));
      delay(100);
    }

    Serial.println(F("Success"));

    g_im.init(deviceID, authnRqtNo, extrSysID);
  
    Serial.print(F("Connect to platform..."));
    while(g_im.connect() < 0)
    {
      Serial.println(F("retrying."));
      delay(100);
    }
    Serial.println(F("Success"));
  
    Serial.print(F("Auth..."));
    if(g_im.auth_device() >= 0)
    {
      Serial.println(F("Success..."));
      return;
    }
  }
}

void setup() {
  Serial.begin(9600);
  init_iotmakers();
  myServo.attach(3);
}

void loop() {
  // scan from 0 to 180 degrees
  for(angle = 0; angle < 180; angle++) 
  { 
    myServo.write(angle); 
    delay(15); 
    send_position();
  } 
  // now scan back from 180 to 0 degrees
  for(angle = 180; angle > 0; angle--) 
  { 
    myServo.write(angle); 
    delay(15); 
    send_position();
  } 
  
  
static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 500)
  {
    send_position();
    tick = millis();
  }

  g_im.loop();
}

int send_position()
{
  // This Scope is package of light sensor
  
  //Serial.print("POSITION : ");
  //Serial.print(angle);
    
  if(g_im.send_numdata(TAG_ID, (double)angle) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
