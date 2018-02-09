
#include "scheduler_millis.h"

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  scheduler_milis_atom();

  if(scheduler_1msec)
  {
    static uint16_t cnt_1msec = 0;
    cnt_1msec++;
    if(cnt_1msec > 999)
    {
      Serial.print("[1msec x 1000]");
      cnt_1msec = 0;
    }
  }

  if(scheduler_10msec)
  {
    Serial.print(".");
  }
  
  if(scheduler_100msec)
  {
    Serial.println("100 msec");   
  }

  if(scheduler_1sec)
  {
    Serial.println("1sec");   
  }  
}

