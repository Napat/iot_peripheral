#include "temp_ds1621.h"

static int ds1621_dev[2];
 
static void init_ds1621(int ds1621_dev){
  Wire.begin();
  Wire.beginTransmission(ds1621_dev);
  Wire.write(DS1621_CONFIG_REGISTER);
  Wire.write(0x02);                   //config to continuous conversion mode
  Wire.beginTransmission(ds1621_dev);
  Wire.write(DS1621_START_TEMPING);
  Wire.endTransmission();
}

static int ds1621_addr_to_cmd(boolean A2, boolean A1, boolean A0){
  return ( DS1621_BASEADDR | ((A2==true)?0x04:0x00) | ((A1==true)?0x02:0x00) | ((A0==true)?0x01:0x00));
}

static float ds1621_read_byte(int ds1621_dev){
  int8_t firstByte;
  int8_t secondByte;
  float temp = 0;

  Wire.beginTransmission(ds1621_dev);
  Wire.write(DS1621_READ_TEMP);
  Wire.endTransmission();
  Wire.requestFrom(ds1621_dev, 2);

  firstByte = Wire.read();
  secondByte = Wire.read();
  temp = firstByte;
  if( secondByte){
    temp += 0.5;
  }
  return (temp);
}

////////

void setup_temp_ds1621(){
  Serial.begin(9600);
  ds1621_dev[0] = ds1621_addr_to_cmd(true,  false, false); 
  ds1621_dev[1] = ds1621_addr_to_cmd(false,  false, false); 
  init_ds1621(ds1621_dev[0]);
  init_ds1621(ds1621_dev[1]);
}

void temp_ds1621_task(){
  Serial.println(ds1621_read_byte(ds1621_dev[0]));
  Serial.println(ds1621_read_byte(ds1621_dev[1]));
  delay(1000);
}
