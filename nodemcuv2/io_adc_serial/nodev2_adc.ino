
#define POT   (A0)

void setup_nodev2_adc(){
  Serial.begin(9600);
}

void loop_nodev2_adc(){
  static int adc_val;
  adc_val = analogRead(POT);
  Serial.println(adc_val);
  delay(500);
}
