#define __WIFICLIENTLIB_CPP__

#include "wificlientlib.h"

void setup_wificlient(const char *ssid, const char *pwd)
{
    // Explicitly set the ESP8266 to be a WiFi-client, otherwise, it by default,
    // would try to act as both a client and an access-point and could cause
    // network-issues with your other WiFi-devices on your WiFi-network.
    Serial.printf("Connecting to %s\n", ssid);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pwd);

    Serial.println("Connecting to wifi...");
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    Serial.printf("\nWiFi connected! IP address: %s\n", WiFi.localIP().toString().c_str());
}

bool https_verifyhost(const char *host, const int httpsport, const char *fingerprint)
{
    // Use WiFiClientSecure class to create TLS connection
    Serial.print("connecting to ");
    Serial.println(host);
    if (!client.connect(host, httpsport))
    {
        Serial.println("connection failed");
        return false;
    }

    if (!client.verify(fingerprint, host))
    {
        Serial.println("certificate doesn't match");
        return false;
    }
    Serial.println("certificate matches");
    return true;
}

void https_getsample(const char *host, const char *url)
{
    //String url = "/";
    //Serial.printf("requesting URL: %s%s\n", host, url.c_str());

    Serial.printf("Requesting URL: %s%s\n", host, url);

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "User-Agent: BuildFailureDetectorESP8266\r\n" +
                 "Connection: close\r\n\r\n");

    Serial.println("request sent");
    while (client.connected())
    {
        String line = client.readStringUntil('\n');
        if (line == "\r")
        {
            Serial.println("headers received");
            break;
        }
    }
    String line = client.readStringUntil('\n');

    if(! line.startsWith("{\"current_user_url\":\"https://api.github.com/user\""))
    {
        Serial.println("Failed! something wrong");
    }
    else
    {
        Serial.println("Successfull get current_user_url");
    }
    Serial.println("reply was:");
    Serial.println(line);
    Serial.println("==========");
    Serial.printf("closing connection\n\n");    
}