#include "dhtlib.h"

#define LED_ALARM D1

bool ledstatus = true;
float humi = 0;
float temp = 0;

void setup()
{
    Serial.begin(115200);
    setup_dhtlib();
    pinMode(LED_ALARM, OUTPUT);
}

void loop()
{
    float buf;
    buf = dht.readHumidity();
    if (isnan(buf))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    humi = buf;

    buf = dht.readTemperature();
    if (isnan(buf))
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }
    temp = buf;

    Serial.printf("Humidity: %f %% Temperature: %f oC\n", humi, temp);
    toggleLed();

    delay(1000);
}

void toggleLed()
{
    ledstatus = !ledstatus;
    digitalWrite(LED_ALARM, ledstatus);
}
