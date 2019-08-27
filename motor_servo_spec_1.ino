#include <Servo.h>
Servo srv;
int angle = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  srv.attach(3);
}

static unsigned long tickStarted;
int motorLoop = 10;
void loop() {
  // put your main code here, to run repeatedly:
  
  for (angle=0; angle < 180; angle++){
    srv.write(angle);
    delay(15);
  }

  for (angle=180; angle >0; angle--){
    srv.write(angle);
    delay(15);
  }

  if (motorLoop < 10 ){
    motorLoop++;
    Serial.print("Loop: ");
    Serial.println(motorLoop);
  }else{
    long elapseTime = millis() - tickStarted;
    Serial.print(F("Elapse Time 10 loop: "));
    Serial.println(elapseTime);

    Serial.print(F("Elapse Time per Loop: "));
    Serial.println(elapseTime/10);
    
    motorLoop = 0;
    tickStarted = millis();
  }
}
