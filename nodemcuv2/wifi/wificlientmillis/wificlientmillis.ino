
#include "scheduler_millis.h"
#include "wificlientlib.h"

const char *ssid = "xxxxxxxxxxxxxx";
const char *password = "xxxxxxxxxxxxxxxxxxxxxxx";

const char *host = "api.github.com";
const char *url = "/";
const int httpsport = 443;
// SHA1 fingerprint of the certificate
// - Use web browser to view and copy (Thumbprint)
// - Or https://www.grc.com/fingerprints.htm
const char *fingerprint = "5F F1 60 31 09 04 3E F2 90 D2 B0 8A 50 38 04 E8 37 9F BC 76";

void setup()
{
    Serial.begin(115200);

    setup_wificlient(ssid, password);
}

//int value = 0;

void loop()
{
    scheduler_milis_atom();

    if (scheduler_1msec)
    {
        static uint16_t cnt_1msec = 0;
        cnt_1msec++;
        if (cnt_1msec > 999)
        {
            //Serial.print("[1msec x 1000]");
            cnt_1msec = 0;
        }
    }

    if (scheduler_10msec)
    {
        //Serial.print(".");
    }

    if (scheduler_100msec)
    {
        //Serial.println("100 msec");
    }

    if (scheduler_1sec)
    {
        Serial.println("1sec");

        if(https_verifyhost(host, httpsport, fingerprint) == true)
        {
            https_getsample(host, url);
        }
        
    }
}

