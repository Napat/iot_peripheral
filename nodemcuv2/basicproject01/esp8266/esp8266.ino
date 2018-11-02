//#include <ESP8266WiFi.h>

#include <MicroGear.h>
#include "lineapi_notify.h"
#include "dhtlib.h"
#include "scheduler_millis.h"

#define HWSWITCH D8

#define LAMP01 D4
#define LAMP02 D0
#define LOAD01 D1
#define LOAD02 D2

const char *ssid = "JNOTE9";
const char *password = "xxxxx";
//const char *ssid = "Neung";
//const char *password = "xxxxx";

#define APPID "xxxxxxxxxxx"
#define KEY "xxxxxxxxxxxxxx"
#define SECRET "xxxxxxxxxxxxxxxxxx"

#define ALIAS_MY "esp8266-01"

#define ALIAS_FB01 "freeboard-01/"ALIAS_MY
#define ALIAS_FB01TEMP ALIAS_FB01"/temp"
#define ALIAS_FB01HUMI ALIAS_FB01"/humi"
#define ALIAS_FB01LAMP01 ALIAS_FB01"/LAMP01"
#define ALIAS_FB01LAMP02 ALIAS_FB01"/LAMP02"
#define LINEMSG_MAILS "/linemails"

#define NETPIE_FEED_SENSOR "feedsensor001"
#define NETPIE_FEED_SENSOR_KEY "xxxxxxxxxxxxxxxxxxxxx"

WiFiClient netpieWifiClient;

int timer = 0;
MicroGear microgear(netpieWifiClient);

double humi = 0;
double temp = 0;

int linenotifyTempNotReady = 0;

void setup()
{
    Serial.println("Initial...");
    Serial.begin(115200);

    pinMode(HWSWITCH, INPUT_PULLUP);

    pinMode(LAMP01, OUTPUT);
    pinMode(LAMP02, OUTPUT);

    setup_dhtlib();
    setup_wificlient(ssid, password);
    setup_microgear();

    Serial.println("Starting...");

    // netpie: init freeboard values
    microgear.chat(ALIAS_FB01LAMP01, "OFF");
    digitalWrite(LAMP01, HIGH);
    microgear.chat(ALIAS_FB01LAMP02, "OFF");
    digitalWrite(LAMP02, HIGH);

}

void loop()
{
    // loop if microgear disconnect
    while (microgear.connected() == false)
    {
        Serial.println("connection lost, reconnect...");
        delay(3000);
        microgear.connect(APPID);
    }

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
        static uint16_t cnt_2sec = 0;
        cnt_2sec++;
        
        static uint16_t cnt_10sec = 0;
        cnt_10sec++;
        
        Serial.println("1sec");
        
        // Call this method regularly otherwise the connection may be lost
        microgear.loop();

        // line notify temp alarm count
        linenotifyTempNotReadySecCount(&linenotifyTempNotReady);

        if (cnt_2sec >= 2)
        {
            Serial.println("[2 sec]");
            cnt_2sec = 0;

            // get dht data
            dhtUpdatedata();
        }

        if (cnt_10sec >= 10)
        {
            Serial.println("[10 sec]");
            cnt_10sec = 0;

            //Chat with the microgear named ALIAS_FB01TEMP
            Serial.printf("Publish to %s with %f oC\n", "/gearname/"ALIAS_FB01TEMP, temp);
            microgear.publish("/gearname/"ALIAS_FB01TEMP, temp, true);    //microgear.chat(ALIAS_FB01TEMP, temp);
            

            //Chat with the microgear named ALIAS_FB01HUMI
            Serial.printf("Publish to %s with %f %%\n", "/gearname/"ALIAS_FB01HUMI, humi);
            microgear.publish("/gearname/"ALIAS_FB01HUMI, humi, true);   //microgear.chat(ALIAS_FB01HUMI, humi);

            //Chat with the microgear named ALIAS_FB01
            String freeboardChatStr = (String)temp + "," + (String)humi;
            Serial.printf("Publish to %s\n", ALIAS_FB01);
            microgear.chat(ALIAS_FB01, freeboardChatStr);

            // writeFeed 
            String netpiefeeddat = "{temp01:" + (String)temp 
                                    + ",humi01:" + (String)humi 
                                    + "}";
            microgear.writeFeed(NETPIE_FEED_SENSOR, netpiefeeddat, NETPIE_FEED_SENSOR_KEY);

            // line notify too hot
            if( temp >= 25)
            {
                Serial.printf("linenotifyTempNotReady: %d\n", linenotifyTempNotReady);
                if(linenotifyTempNotReady <= 0)
                {
                    String str = "อุณหภูมิ " + (String)temp + " oC มันร้อนไปนะ เร่งแอร์หน่อยมั้ย";
                    LineNotify(str);
                    Serial.printf("%s\n", str.c_str());
                    microgear.publish(LINEMSG_MAILS, str, true);
                    // alarm every 60 sec
                    linenotifyTempNotReady = 60;
                }
            } 
            //LineNotifySticker("นอนเถอะ", 1, 1);
        }
    }

}


// If a new message arrives, do this
void onMsghandler(char *topic, uint8_t *msg, unsigned int msglen)
{
    //Serial.printf("Incoming topic: %s, message --> ", topic);
    //msg[msglen] = '\0';
    //Serial.println((char *)msg);

    Serial.print("Incoming message --> ");
    Serial.print(topic);
    Serial.print(": ");
    char strState[msglen];
    for (int i = 0; i < msglen; i++)
    {
        strState[i] = (char)msg[i];
        Serial.print((char)msg[i]);
    }
    Serial.println();

    String lampStatus = String(strState).substring(0, msglen);

    processMsg(lampStatus);
}

void processMsg(String lampStatus)
{
    if (lampStatus == "LAMP01=ON")
    {
        digitalWrite(LAMP01, LOW);
        microgear.publish("/gearname/"ALIAS_FB01LAMP01, "ON", true); //microgear.chat(ALIAS_FB01LAMP01, "ON");
    }
    else if (lampStatus == "LAMP01=OFF")
    {
        digitalWrite(LAMP01, HIGH);
        microgear.chat(ALIAS_FB01LAMP01, "OFF");
    }
    else if (lampStatus == "LAMP02=ON")
    {
        digitalWrite(LAMP02, LOW);
        microgear.chat(ALIAS_FB01LAMP02, "ON");
    }
    else if (lampStatus == "LAMP02=OFF")
    {
        digitalWrite(LAMP02, HIGH);
        microgear.chat(ALIAS_FB01LAMP02, "OFF");
    }
}

void onFoundgear(char *attribute, uint8_t *msg, unsigned int msglen)
{
    Serial.print("Found new member --> ");
    for (int i = 0; i < msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

void onLostgear(char *attribute, uint8_t *msg, unsigned int msglen)
{
    Serial.print("Lost member --> ");
    for (int i = 0; i < msglen; i++)
        Serial.print((char)msg[i]);
    Serial.println();
}

// When a microgear is connected, do this
void onConnected(char *attribute, uint8_t *msg, unsigned int msglen)
{
    Serial.println("Connected to NETPIE...");
    // Set the alias of this microgear ALIAS_MY
    microgear.setAlias(ALIAS_MY);
}

void setup_microgear()
{
    // Add Event listeners

    // Call onMsghandler() when new message arraives
    microgear.on(MESSAGE, onMsghandler);

    // Call onFoundgear() when new gear appear
    microgear.on(PRESENT, onFoundgear);

    // Call onLostgear() when some gear goes offline
    microgear.on(ABSENT, onLostgear);

    // Call onConnected() when NETPIE connection is established
    microgear.on(CONNECTED, onConnected);

    // Initial with KEY, SECRET and can also set the ALIAS_MY here
    microgear.init(KEY, SECRET, ALIAS_MY);

    // connect to NETPIE to a specific APPID
    microgear.connect(APPID);
}

void dhtUpdatedata()
{
    float buf;
    buf = dht.readHumidity();
    if (isnan(buf))
    {
#ifdef DEBUG
        Serial.println("Failed to read from DHT sensor!");
#endif
        return;
    }
    humi = utilFloatprecision((double)buf, 2); // set precision for pretty dashboard output

    buf = dht.readTemperature();
    if (isnan(buf))
    {
#ifdef DEBUG
        Serial.println("Failed to read from DHT sensor!");
#endif
        return;
    }
    temp = utilFloatprecision((double)buf, 2); // set precision for pretty dashboard output
}

double utilFloatprecision(double value, double precision)
{
    return (floor((value * pow(10, precision) + 0.5)) / pow(10, precision));
}


void linenotifyTempNotReadySecCount(int* linenotifyTempNotReady)
{
    if(*linenotifyTempNotReady > 0 )
    {
        *linenotifyTempNotReady = *linenotifyTempNotReady-1;
    }
}