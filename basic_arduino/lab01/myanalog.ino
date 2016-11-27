
#include "myanalog.h"


void setup_pwdout(){
  pinMode(LED_RED, OUTPUT);

}

void pwdout(){
	static int val =0;
  analogWrite(LED_RED, val);
  delay(DELAY_MS);

  if(val<1000){
    val++;
  }else{
    val = 0;
  }
}

/////////////////////////////////////

void setup_vr_analoginput(){
  pinMode(LED_RED, OUTPUT);//setup_blinker();

}
static int val =0;
void vr_analoginput(){
  
  val = analogRead(POT_01);
  val = val/4;
  analogWrite(LED_RED, val);
  delay(0);
}


