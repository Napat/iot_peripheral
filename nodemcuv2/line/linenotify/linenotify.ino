#include "lineapi_notify.h"

const char *ssid = "...yourwifissid...";
const char *password = "...yourwifipassword...";

#define SW  D2

void setup()
{
    pinMode(SW, INPUT);

    Serial.begin(115200);

    setup_wificlient(ssid, password);

    LineNotify("สวัสดีชาวดอย");
    LineNotifySticker("นอนเถอะ", 1, 1);
    LineNotifyImageUrl("Roo you even lift?", "https://pics.me.me/roo-you-even-lift-16716962.png");
    LineNotifyImageUrl("", "https://roonation.org/wp-content/uploads/bb-plugin/cache/roo-logo-Maroon-300x182-panorama.png");
}

void loop()
{
    if (digitalRead(SW) == HIGH)
    {
        while (digitalRead(SW) == HIGH)
            delay(10);

        Serial.println("Enter !");

        LineNotify(message);

        // Serial.println();
    }
    delay(10);
}
