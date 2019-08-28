#include<Wire.h>
const int MPU = 0x68;  // I2C address of MPU-6050
int16_t AcX, AcY, AcZ, Tmp, GyX, GyY, GyZ;
 
void setup() {
  Serial.begin(9600);
  
  Wire.begin();
  Wire.beginTransmission(MPU);
  Wire.write(0x6B);  // PWR_MGMT_1 register
  Wire.write(0);     // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
 
  // gyro scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1B);
  Wire.write(0xF8);
  Wire.endTransmission(true);
 
  // acc scale
  Wire.beginTransmission(MPU);
  Wire.write(0x1C);
  Wire.write(0xF8);
  Wire.endTransmission(true);
}

void loop() {
  Wire.beginTransmission(MPU);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 14, true);
  
  AcX = Wire.read() << 8 | Wire.read();  // ACCEL_X
  AcY = Wire.read() << 8 | Wire.read();  // ACCEL_Y
  AcZ = Wire.read() << 8 | Wire.read();  // ACCEL_Z
  Tmp = Wire.read() << 8 | Wire.read();  // Temperature
  GyX = Wire.read() << 8 | Wire.read();  // GYRO_X
  GyY = Wire.read() << 8 | Wire.read();  // GYRO_Y
  GyZ = Wire.read() << 8 | Wire.read();  // GYRO_Z
 
  int xAxis = (AcX - 1090);
  int yAxis = (AcY - 930);
  int zAxis = (AcZ - 1000);

  Serial.print("Gyro (x, y, z): ");
  Serial.print(xAxis);
  Serial.print(" ");
  Serial.print(yAxis);
  Serial.print(" ");
  Serial.print(zAxis);
  Serial.println(" ");

  float tempC = (float) Tmp/340+36.53;
  Serial.print("Temperature: ");
  Serial.println(tempC);
 
  delay(250);
}
© 2019 GitHub, Inc.
