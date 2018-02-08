#include <SoftwareSerial.h>

SoftwareSerial Ser2(14, 12, false, 256);  // RX, TX, inverse_logic, buffSize  
SoftwareSerial Ser3(5, 4, false, 256);  // RX, TX, inverse_logic, buffSize  

void setup() {
  
  Serial.begin(9600);
  Ser2.begin(9600);
  Ser3.begin(57600);

  Serial.println("\nSoftware serial test started");
}

void loop() {

  // Write
  Serial.write("A");
  Ser2.write("B");
  Ser3.write("C");

  // Read
  while (Serial.available()) {
    Serial.write(Serial.read());
  }
  while (Ser2.available()) {
    Serial.write(Ser2.read());
  }
  while (Ser3.available()) {
    Serial.write(Ser3.read());
  }

   delay(1000); 
}
