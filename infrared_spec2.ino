void setup() {
  // put your setup code here, to run once:
  pinMode(A0, INPUT);
  Serial.begin(9600);
  pinMode(6, OUTPUT);
}

void loop() 
{
  int volt;
  volt = map(analogRead(A0),0,1023,0,5000);
  Serial.print(0.0001936428309 * volt *volt + 0.06987226424 * volt - 14.32575223);
  Serial.println(" ");
  tone(6,400);
  delay(200);
  noTone(6);
  delay(300);
}
