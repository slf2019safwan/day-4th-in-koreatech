#include <SoftwareSerial.h>

#define BT_TX 2
#define BT_RX 3

#define rLED  11
#define gLED  10
#define bLED  9

SoftwareSerial serialSW(BT_TX, BT_RX);
String stringIn = "";

void setup() {
  Serial.begin(9600);
  serialSW.begin(9600);

  pinMode(rLED, OUTPUT);
  pinMode(gLED, OUTPUT);
  pinMode(bLED, OUTPUT);

  setColor(255,0,0);
}

void loop() {
  
  while (serialSW.available()){
    char charIn = (char)serialSW.read();
    stringIn += charIn;
    delay(5);
  }

  if(!stringIn.equals("")){
    Serial.println("Recieved: " + stringIn);
    //ATCommand(stringIn); //commit AT command
    setLED(stringIn);
    stringIn = "";
  }
}

//void ATCommand(String atCommand){
//  if (atCommand.startsWith("AT+")){
//    serialSW.write(atCommand);
//  }
//}

void setLED(String command){
  if (command=="R"){
    setColor(255, 0, 0);
  }else if (command=="G"){
    setColor(0, 255, 0);
  }else if (command=="B"){
    setColor(0, 0, 255);
  }else if (command=="AUTO"){
    while (!serialSW.available()){
      setColor(255, 0, 0); 
      delay(100);
      setColor(0, 255, 0); 
      delay(100);
      setColor(0, 0, 255); 
      delay(100);
    }
  }
}

void setColor(int r, int g, int b){
  analogWrite(rLED, 255-r);
  analogWrite(gLED, 255-g);
  analogWrite(bLED, 255-b);
}
