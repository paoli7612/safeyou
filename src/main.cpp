#include <Wire.h>
#include <Arduino.h>

const uint8_t MPU_addr = 0x68;  // Cast a uint8_t se usato in funzioni che lo richiedono

int16_t AcX, AcY, AcZ, GyX, GyY, GyZ;

void setup() {
  Wire.begin(21, 22);  // SDA, SCL su ESP32
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);  // Scrive nel registro PWR_MGMT_1 per svegliare il sensore
  Wire.write(0);     // Imposta a zero (sveglia con clock interno)
  Wire.endTransmission(true);
  Serial.begin(9600);
}
void loop() {
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x3B);  // Inizia la lettura dal registro ACCEL_XOUT_H
  Wire.endTransmission(false);
  Wire.requestFrom((uint8_t)MPU_addr, (size_t)14, true);  // Legge 14 byte

  if (Wire.available() == 14) {  // Controlla se i dati sono disponibili
    AcX = Wire.read() << 8 | Wire.read();  // Combina due byte in un int16_t
    AcY = Wire.read() << 8 | Wire.read();
    AcZ = Wire.read() << 8 | Wire.read();
    GyX = Wire.read() << 8 | Wire.read();
    GyY = Wire.read() << 8 | Wire.read();
    GyZ = Wire.read() << 8 | Wire.read();
  }
  
  Serial.print("AcX = "); Serial.print(AcX);
  Serial.print("\tAcY = "); Serial.print(AcY);
  Serial.print("\tAcZ = "); Serial.print(AcZ);
  Serial.print("\tGyX = "); Serial.print(GyX);
  Serial.print("\tGyY = "); Serial.print(GyY);
  Serial.print("\tGyZ = "); Serial.println(GyZ);
  
  delay(333);  // Aggiusta questo valore per modificare la frequenza di campionamento
}