//#include <ESP8266WiFi.h>

#include <MicroGear.h>
#include "lineapi_notify.h"
#include "dhtlib.h"
#include "scheduler_millis.h"

enum button_status{
	BUTTON_STATUS_PUSH = LOW,
    BUTTON_STATUS_RELEASE = HIGH
} button_status_t;

#define BUTTON01 D8
#define BUTTON02 D7

#define LAMP01 D4
#define LAMP02 D0

enum load_control{
	LOAD_CONTROL_ACTIVE = LOW,
    LOAD_CONTROL_DEACTIVE = HIGH
} load_control_t;

#define LOAD01 D1
#define LOAD02 D2

const char *ssid = "JNOTE9";
const char *password = "xxxxx";


#define APPID "napat"
#define KEY "264hMyPUmYSrXxN"
#define SECRET "xxxxx"

#define APPIDPATH  "/napat"
#define ALIAS_MY "esp8266-01"               // subscribe /<appid>/gearname/ALIAS_MY by default
#define ALIAS_MY_LAMPS_ENABLE(appidpath)        appidpath"/gearname/"ALIAS_MY"/lamps/enable"        // subscribe: to enable lamps 
#define ALIAS_MY_LAMP01_LIGHTER_SET(appidpath)  appidpath"/gearname/"ALIAS_MY"/lamp01/lighter/set"  // subscribe: value 0-10
#define ALIAS_MY_LAMP02_LIGHTER_SET(appidpath)  appidpath"/gearname/"ALIAS_MY"/lamp02/lighter/set"  // subscribe: value 0-10
#define ALIAS_MY_SENSOR01(appidpath)            appidpath"/gearname/"ALIAS_MY"/sensor01"            // public: temp & humi
#define ALIAS_MY_LAMP01(appidpath)              appidpath"/gearname/"ALIAS_MY"/lamp01"              // public: get lamp01 status
#define ALIAS_MY_LAMP02(appidpath)              appidpath"/gearname/"ALIAS_MY"/lamp02"              // public: get lamp02 status
#define ALIAS_MY_LAMP01_LIGHTER(appidpath)      appidpath"/gearname/"ALIAS_MY"/lamp01/lighter"      // public: get lamp01 lighter
#define ALIAS_MY_LAMP02_LIGHTER(appidpath)      appidpath"/gearname/"ALIAS_MY"/lamp02/lighter"      // public: get lamp02 lighter

#define LINEMSG_MAILS "/linemails"                                    // public

#define NETPIE_FEED_SENSOR "feedsensor001"
#define NETPIE_FEED_SENSOR_KEY "xxxxx"

WiFiClient netpieWifiClient;

int timer = 0;
MicroGear microgear(netpieWifiClient);

double humi = 0;
double temp = 0;

int linenotifyTempNotReady = 0;

bool lamp01enable = false;
int lamplighter01 = 10;   // 0-10
bool lamp02enable = false;
int lamplighter02 = 10;   // 0-10

void setup()
{
    Serial.println("Initial...");
    Serial.begin(115200);

    pinMode(BUTTON01, INPUT_PULLUP);
    pinMode(BUTTON02, INPUT_PULLUP);

    pinMode(LAMP01, OUTPUT);
    pinMode(LAMP02, OUTPUT);

    pinMode(LOAD01, OUTPUT);
    pinMode(LOAD02, OUTPUT);

    setup_dhtlib();
    setup_wificlient(ssid, password);
    setup_microgear();

    Serial.println("Starting...");

    // netpie: init freeboard values
    microgear.publish(ALIAS_MY_LAMP01(), "OFF", true);    //microgear.chat(ALIAS_MY"/lamp01", "OFF");
    digitalWrite(LAMP01, HIGH);
    lamp01enable = false;
    microgear.publish(ALIAS_MY_LAMP02(), "OFF", true);    //microgear.chat(ALIAS_MY"/lamp02", "OFF");
    digitalWrite(LAMP02, HIGH);
    lamp02enable = false;

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
        buttonhandler();
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

            //Chat with the microgear named ALIAS_MY_SENSOR01
            String freeboardChatStr = (String)temp + "," + (String)humi;
            Serial.printf("Publish to %s with temp: %f oC humi: %f %%\n", ALIAS_MY_SENSOR01(), temp, humi);
            //microgear.chat(ALIAS_MY_SENSOR01(), freeboardChatStr);
            microgear.publish(ALIAS_MY_SENSOR01(), freeboardChatStr, true);

            // writeFeed 
            netpieWriteFeed(temp, humi);

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

void buttonhandler()
{
    if( digitalRead(BUTTON01) == BUTTON_STATUS_PUSH)
    {
        digitalWrite( LOAD01, LOAD_CONTROL_ACTIVE);  
    }
    else
    {
        digitalWrite( LOAD01, LOAD_CONTROL_DEACTIVE);  
    }

    if( digitalRead(BUTTON_02) == BUTTON_STATUS_PUSH)
    {
        digitalWrite( LOAD02, LOAD_CONTROL_ACTIVE);  
    }
    else
    {
        digitalWrite( LOAD02, LOAD_CONTROL_DEACTIVE);  
    }
}

void netpieWriteFeed(float temp, float humi)
{
    String feeddata = "{temp01:" + (String)temp 
                            + ",humi01:" + (String)humi 
                            + "}";
    microgear.writeFeed(NETPIE_FEED_SENSOR, feeddata, NETPIE_FEED_SENSOR_KEY);
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

    String strmsg = String(strState).substring(0, msglen);

    if(strcmp(topic, APPIDPATH"/gearname/"ALIAS_MY) == 0)
    {
        Serial.printf("!!!! default topic: %s\n", topic);
    }
    else if(strcmp(topic, ALIAS_MY_LAMPS_ENABLE(APPIDPATH)) == 0)
    {
        processMsgLamp(strmsg);
    }
    else if(strcmp(topic, ALIAS_MY_LAMP01_LIGHTER_SET(APPIDPATH)) == 0)
    {
        Serial.println("lamplighter01: 1023 - ( 100 x "+ strmsg + " )");
        lamplighter01 = 1023 - (100 * atoi(strmsg.c_str()));
        microgear.publish(ALIAS_MY_LAMP01_LIGHTER(), strmsg, true);
        if(lamp01enable == true)
        {
            analogWrite(LAMP01, lamplighter01);   // 0 to 1023
        }
        else
        {
            digitalWrite(LAMP01, HIGH);
        }
    }
    else if(strcmp(topic, ALIAS_MY_LAMP02_LIGHTER_SET(APPIDPATH)) == 0)
    {
        Serial.println("lamplighter02: 1023 - ( 100 x "+ strmsg + " )");
        lamplighter02 = 1023 - (100 * atoi(strmsg.c_str()));
        microgear.publish(ALIAS_MY_LAMP02_LIGHTER(), strmsg, true);
        if(lamp02enable == true)
        {
            analogWrite(LAMP02, lamplighter02);   // 0 to 1023
        }
        else
        {
            digitalWrite(LAMP02, HIGH);
        }
    }
    else
    {
        Serial.println("???????? unknown topic ???");
        Serial.println(topic);
        Serial.println(APPIDPATH"/gearname/"ALIAS_MY);
        Serial.println(ALIAS_MY_LAMPS_ENABLE(APPIDPATH));
        Serial.println(ALIAS_MY_LAMP01_LIGHTER_SET(APPIDPATH));
        Serial.println(ALIAS_MY_LAMP02_LIGHTER_SET(APPIDPATH));
    }
}

void processMsgLamp(String lampStatus)
{
    if (lampStatus == "LAMP01=ON")
    {   
        //digitalWrite(LAMP01, LOW);
        analogWrite(LAMP01, lamplighter01);   // 0 to 1023
        microgear.publish(ALIAS_MY_LAMP01(), "ON", true);    //microgear.chat(ALIAS_MY"/lamp01", "ON");
        lamp01enable = true;
    }
    else if (lampStatus == "LAMP01=OFF")
    {
        digitalWrite(LAMP01, HIGH);
        microgear.publish(ALIAS_MY_LAMP01(), "OFF", true);    //microgear.chat(ALIAS_MY"/lamp01", "OFF");
        lamp01enable = false;
    }
    else if (lampStatus == "LAMP02=ON")
    {
        //digitalWrite(LAMP02, LOW);
        analogWrite(LAMP02, lamplighter02);   // 0 to 1023
        microgear.publish(ALIAS_MY_LAMP02(), "ON", true);    //microgear.chat(ALIAS_MY"/lamp02", "ON");
        lamp02enable = true;
    }
    else if (lampStatus == "LAMP02=OFF")
    {
        digitalWrite(LAMP02, HIGH);
        microgear.publish(ALIAS_MY_LAMP02(), "OFF", true);    //microgear.chat(ALIAS_MY"/lamp02", "OFF");
        lamp02enable = false;
    }
    else
    {
        Serial.printf("Unknown message at %s(%d)\n", __FUNCTION__, __LINE__);
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
    microgear.subscribe(ALIAS_MY_LAMPS_ENABLE());
    microgear.subscribe(ALIAS_MY_LAMP01_LIGHTER_SET());
    microgear.subscribe(ALIAS_MY_LAMP02_LIGHTER_SET());
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