

#define VIB_SENSOR A0
#define TOUCH 1

void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(VIB_SENSOR,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
//Serial.println(analogRead(VIB_SENSOR));
int isTouch = analogRead(VIB_SENSOR);
if(isTouch == TOUCH)
Serial.println("TOUCH");

delay(100); 

}
