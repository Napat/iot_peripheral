
#include <SimpleTimer.h>
#include <BlynkSimpleEsp8266.h>
#include "wificlientlib.h"

const char *ssid = "xxxxx";
const char *password = "xxxxxxxx";

#define BLYNK_PRINT Serial // Comment this out to disable prints and save space
char blynkAuth[] = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";

SimpleTimer timer;

float temp, humi;

void setup()
{
    temp = 20;
    humi = 100;

    Serial.begin(115200);
    setup_wificlient(ssid, password); // no need to use this if you don't want to see "."
    
    Blynk.begin(blynkAuth, "", "");
    //Blynk.begin(blynkAuth, ssid, password);

    // Setup a function to be called every second
    timer.setInterval(5000L, sendUptime);
    
}

void loop()
{
    Blynk.run();
    timer.run();
}

void sendUptime()
{
    //Blynk.virtualWrite(V5, millis() / 1000);

    if(temp < 50)
    {
        temp = temp + 1;
        humi = humi - 1.5;
    }
    else
    {
        temp = 20;
        humi = 100;
    }

    Serial.printf("temp: %f oC, humi: %f %%\n", temp, humi);
    Blynk.virtualWrite(V1, temp);
    Blynk.virtualWrite(V2, humi);
}
