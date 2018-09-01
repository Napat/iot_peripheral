#ifndef __WIFICLIENTLIB_H__
#define __WIFICLIENTLIB_H__

#include <ESP8266WiFi.h>

#ifdef __WIFICLIENTLIB_CPP__
    WiFiClientSecure client;
#else
    extern WiFiClientSecure client;
#endif

void setup_wificlient(const char *ssid, const char *pwd);
bool https_verifyhost(const char *host, const int httpsport, const char *fingerprint);
void https_getsample(const char *host, const char *url);

#endif /* __WIFICLIENTLIB_H__ */
