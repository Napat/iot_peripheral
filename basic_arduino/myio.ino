#include "myio.h"


void setup_blink(){
  pinMode(LED_RED, OUTPUT);
}

void blink(){
    // put your main code here, to run repeatedly:
  digitalWrite(13, HIGH);
  delay(DELAY_MS);
  digitalWrite(13,LOW);
  delay(DELAY_MS);
}

/////////////////////////////////////////////////

void setup_blinker(){
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}

void rgb_blinker(){
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, LOW);
  delay(DELAY_MS);
  
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, HIGH);
  digitalWrite(LED_BLUE, LOW);
  delay(DELAY_MS);

  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_BLUE, HIGH);
  delay(DELAY_MS);
}

/////////////////////////////////////////////////

void setup_led_switcher(){
  setup_blinker();
  pinMode(SWITCH_01, INPUT);
  pinMode(SWITCH_02, INPUT);
}

void led_switcher(){
  static int button_state = 0;
  button_state = digitalRead(SWITCH_01);
  if(button_state == HIGH){
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_BLUE, LOW);
  }else{
    digitalWrite(LED_RED, LOW);
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
  delay(DELAY_MS);
}

