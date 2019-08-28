
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>

#define VIB_SENSOR A0
#define TOUCH 1
int isTouch;
IoTMakers g_im;


#define deviceID    "safwanD1566955928453"
#define authnRqtNo  "gnzmqgrpl"
#define extrSysID   "OPEN_TCP_001PTL001_1000007670"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

// ************************************************************************ //
// Very Important!!!!
// IoTMakers tag stream id must be the same below !!!
#define TAG_ID "PIEZO"
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
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(VIB_SENSOR,INPUT);
init_iotmakers();
}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.println(analogRead(VIB_SENSOR));
int isTouch = analogRead(VIB_SENSOR);
if(isTouch == TOUCH)
Serial.println("TOUCH");

delay(100); 

 
static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 500)
  {
    send_TOUCH();
    tick = millis();
  }

  g_im.loop();
}

int send_TOUCH()
{
  // This Scope is package of light sensor
  
  //Serial.print("POSITION : ");
  //Serial.print(angle);
    
  if(g_im.send_numdata(TAG_ID, (double)TOUCH) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
