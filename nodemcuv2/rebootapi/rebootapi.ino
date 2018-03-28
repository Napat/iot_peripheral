void setup()
{
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    int count = 0;

    while (true)
    {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(500);
        digitalWrite(LED_BUILTIN, LOW);
        delay(500);
        Serial.printf("count: %d\n", count);

        if (count == 5)
        {
            Serial.println("Call software reset function...");
            ESP.restart(); //ESP.reset();
        }
        count++;
    }
}
