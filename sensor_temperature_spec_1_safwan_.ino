
#include <WiFi.h>
#include <IoTStarterKit_WiFi.h>
#include <OneWire.h>
#include <DallasTemperature.h>

IoTMakers g_im;

// For example...
// #define deviceID    "nch207D1565936279095"
// #define authnRqtNo  "6hhkxlhrq"
// #define extrSysID   "OPEN_TCP_001PTL001_1000007578"
//
// #define WIFI_SSID   "jangLab"
// #define WIFI_PASS   "emsys2019"

#define deviceID    "slf201D1566795761590"
#define authnRqtNo  "ixy22m8ml"
#define extrSysID   "OPEN_TCP_001PTL001_1000007607"

#define WIFI_SSID   "ICT-LAB-2.4G"
#define WIFI_PASS   "12345678"

#define ONE_WIRE_BUS 2
#define TAG_ID "Temperature"

// ************************************************************************ //
// Very Important!!!!
// IoTMakers tag stream id must be the same below !!!
#define TAG_ID "Temperature"
// ************************************************************************ //

OneWire ourWire(ONE_WIRE_BUS);
DallasTemperature sensors(&ourWire);

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

  sensors.begin();
 
  init_iotmakers();
}

void loop() {
  static unsigned long tick = millis();

  if(g_im.isServerDisconnected() == 1)
  {
    init_iotmakers();
  }

  if((millis() - tick) > 2000)
  {
    send_temperature();
    tick = millis();
  }

  g_im.loop();
}

int send_temperature()
{
  // This Scope is package of temperature sensor
  // Raw coding (with register address) look at "5_Temperature_Sensor Project"
  sensors.requestTemperatures();
  int data = sensors.getTempCByIndex(0);

  Serial.print("Temperature : ");
  Serial.print(data);
  Serial.println(" Celsius");
  
  if(g_im.send_numdata(TAG_ID, (double)data) < 0)
  {
    Serial.println(F("fail"));
    return -1;
  }

  return 0;
}
