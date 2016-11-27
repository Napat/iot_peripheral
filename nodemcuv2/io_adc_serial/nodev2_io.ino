
#include "nodev2_io.h"

void setup_nodev2_op(){
  pinMode( LED_RED, OUTPUT);
}

void loop_nodev2_op(){
  digitalWrite( LED_RED, LOW);
  delay(500);
  digitalWrite( LED_RED, HIGH);
  delay(500);
}

void setup_nodev2_iop(){
  //Serial.begin(9600);
  pinMode( LED_RED, OUTPUT);
  pinMode( BUTTON_01, INPUT);
}

void loop_nodev2_iop(){
  if( digitalRead(BUTTON_01)){
    digitalWrite( LED_RED, LOW);  
  }else{
    digitalWrite( LED_RED, HIGH);
  }
  //Serial.println(100);
  delay(100);
}
