
#include <ESP8266WiFi.h>
#include <MicroGear.h>
#include "dhtlib.h"

#define DEBUG

#define LAMP01 D4
#define LAMP02 D0

const char *ssid = ".....wifissid...";
const char *password = "...wifipassword...";


#define APPID "....yournetpie_appid..."
#define KEY "...yournetpiekey..."
#define SECRET "...yournetpiesecret..."

#define ALIAS_MY "esp8266-01"

#define ALIAS_FB01 "freeboard-01/"ALIAS_MY
#define ALIAS_FB01TEMP ALIAS_FB01"/temp"
#define ALIAS_FB01HUMI ALIAS_FB01"/humi"

#define NETPIE_FEED_SENSOR      "....yournetpiefeedid..."
#define NETPIE_FEED_SENSOR_KEY  "...yournetpiefeedkey..."

WiFiClient client;

int timer = 0;
MicroGear microgear(client);

double humi = 0;
double temp = 0;

void setup()
{
    Serial.println("Starting...");
    Serial.begin(115200);
    pinMode(LAMP01, OUTPUT);
    pinMode(LAMP02, OUTPUT);
    setup_dhtlib();
    setup_wifi();
    setup_microgear();
}

#define LOOPDELAY_MS (100)
void loop()
{
    // loop if microgear disconnect
    while (microgear.connected() == false)
    {
        Serial.println("connection lost, reconnect...");
        delay(3000);
        microgear.connect(APPID);
    }

    // Call this method regularly otherwise the connection may be lost
    microgear.loop();

    // get dht data
    dhtUpdatedata();

    // Process every 2 sec.
    if (timer >= 2000)
    {
        //microgear.chat(ALIAS, "Hello");
        //microgear.chat(ALIAS, 50);

        //Chat with the microgear named ALIAS_FB01TEMP
        Serial.printf("Publish to %s with %f oC\n", ALIAS_FB01TEMP, temp);
        microgear.chat(ALIAS_FB01TEMP, temp);

        //Chat with the microgear named ALIAS_FB01HUMI
        Serial.printf("Publish to %s with %f %%\n", ALIAS_FB01HUMI, humi);
        microgear.chat(ALIAS_FB01HUMI, humi);

        //Chat with the microgear named ALIAS_FB01
        String freeboardChatStr = (String)temp + "," + (String)humi;
        Serial.printf("Publish to %s\n", ALIAS_FB01);
        microgear.chat(ALIAS_FB01, freeboardChatStr);

        // writeFeed every 16 sec.
        static int count = 0;
        count = count + 2;
        if(count >= 16) 
        {
            count = 0;
            String netpiefeeddat = "{temp01:" + (String)temp 
                                    + ",humi01:" + (String)humi 
                                    + "}";
            microgear.writeFeed(NETPIE_FEED_SENSOR, netpiefeeddat, NETPIE_FEED_SENSOR_KEY);
            Serial.println("TX to netpie feed");
        }
        
        timer = 0;
    }
    else
    {
        timer += LOOPDELAY_MS;
    }
    delay(LOOPDELAY_MS);
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
        microgear.chat(ALIAS_FB01"/LAMP01", "ON");
    }
    else if (lampStatus == "LAMP01=OFF")
    {
        digitalWrite(LAMP01, HIGH);
        microgear.chat(ALIAS_FB01"/LAMP01", "OFF");
    }
    else if (lampStatus == "LAMP02=ON")
    {
        digitalWrite(LAMP02, LOW);
        microgear.chat(ALIAS_FB01"/LAMP02", "ON");
    }
    else if (lampStatus == "LAMP02=OFF")
    {
        digitalWrite(LAMP02, HIGH);
        microgear.chat(ALIAS_FB01"/LAMP02", "OFF");
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

void setup_wifi()
{
    // Initial WIFI, this is just a basic method to configure WIFI on ESP8266.
    // You may want to use other method that is more complicated, but provide better user experience
    if (WiFi.begin(ssid, password))
    {
        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }
    }

    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
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
