#include <Wire.h>
#include <Arduino.h>

const uint8_t MPU_addr = 0x68;

int16_t AcX_prev, AcY_prev, AcZ_prev, GyX_prev, GyY_prev, GyZ_prev;
int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

// Function declaration
void readSensorData();

void setup() {
  Wire.begin(21, 22);
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0);   
  Wire.endTransmission(true);
  Serial.begin(9600);
  

  readSensorData();
  AcX_prev = AcX;
  AcY_prev = AcY;
  AcZ_prev = AcZ;
  GyX_prev = GyX;
  GyY_prev = GyY;
  GyZ_prev = GyZ;
}

void loop() {
  readSensorData();

  int16_t dAcX = AcX - AcX_prev;
  int16_t dAcY = AcY - AcY_prev;
  int16_t dAcZ = AcZ - AcZ_prev;
  int16_t dGyX = GyX - GyX_prev;
  int16_t dGyY = GyY - GyY_prev;
  int16_t dGyZ = GyZ - GyZ_prev;
  

  AcX_prev = AcX;
  AcY_prev = AcY;
  AcZ_prev = AcZ;
  GyX_prev = GyX;
  GyY_prev = GyY;
  GyZ_prev = GyZ;

  Serial.print("dAcX = "); Serial.print(dAcX);
  Serial.print("\tdAcY = "); Serial.print(dAcY);
  Serial.print("\tdAcZ = "); Serial.print(dAcZ);
  Serial.print("\tdGyX = "); Serial.print(dGyX);
  Serial.print("\tdGyY = "); Serial.print(dGyY);
  Serial.print("\tdGyZ = "); Serial.println(dGyZ);
  
  delay(333);
}

void readSensorData() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)MPU_addr, (size_t)14, true);

  if (Wire.available() == 14) {
    AcX = Wire.read() << 8 | Wire.read();
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();
  }
}