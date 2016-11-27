
#include "myserial.h"
#include "myanalog.h"


void setup_serial01(){
  setup_vr_analoginput();
  Serial.begin(19200);
}

static char ch = 0;
void serial01(){  
  
  if(Serial.available()){
    Serial.print("Halo print");
    ch = Serial.read();
    Serial.println("Halo println");
    Serial.print(">> ");
    Serial.println(ch);
  }

}

////////////////////////////

void setup_serial02(){
  setup_vr_analoginput();
  setup_serial01();
}

static byte buf[255];
void serial02(){  
  Serial.readBytesUntil('\n', buf, 255 ); //Serial.readBytesUntil(character, buffer, length)
  Serial.println((char*)buf);
}


////////////////////////

int potPin = A2;
void test_value(){
  Serial.println(potPin, BIN);
}

