//
// Copyright 2015 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

// FirebaseDemo_ESP8266 is a sample that demo the different functions
// of the FirebaseArduino API.

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "esp8266-firebasedemo.firebaseio.com"
#define FIREBASE_AUTH "xxxxxxxxxx"

#define WIFI_SSID "JNOTE9"
#define WIFI_PASSWORD "ymgf1612"

void setup()
{
    Serial.begin(115200);

    // connect to wifi.
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    Serial.print("connecting");
    while (WiFi.status() != WL_CONNECTED)
    {
        Serial.print(".");
        delay(500);
    }
    Serial.println();
    Serial.print("connected: ");
    Serial.println(WiFi.localIP());

    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.set("pushbutton", 1);
}

int n = 0;

void loop()
{
    int state_1 = Firebase.getInt("abc");
    Serial.printf("state_1: %d\n", state_1);

    Firebase.setInt("theInt", n++);
    if (Firebase.failed())
    {
        Serial.print("setting /theInt failed:");
        Serial.println(Firebase.error());
        return;
    }

    delay(1000);   

    // set value
    Firebase.setFloat("number", 42.0);
    // handle error
    if (Firebase.failed())
    {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
    }
    delay(1000);

    // update value
    Firebase.setFloat("number", 43.0);
    // handle error
    if (Firebase.failed())
    {
        Serial.print("setting /number failed:");
        Serial.println(Firebase.error());
        return;
    }
    delay(1000);

    // get value
    Serial.print("number: ");
    Serial.println(Firebase.getFloat("number"));
    delay(1000);

    // remove value
    Firebase.remove("number");
    delay(1000);

    // set string value
    Firebase.setString("message", "hello world");
    // handle error
    if (Firebase.failed())
    {
        Serial.print("setting /message failed:");
        Serial.println(Firebase.error());
        return;
    }
    delay(1000);

    // set bool value
    Firebase.setBool("truth", false);
    // handle error
    if (Firebase.failed())
    {
        Serial.print("setting /truth failed:");
        Serial.println(Firebase.error());
        return;
    }
    delay(1000);

    // append a new value to /logs
    String name = Firebase.pushInt("logs", n++);
    // handle error
    if (Firebase.failed())
    {
        Serial.print("pushing /logs failed:");
        Serial.println(Firebase.error());
        return;
    }
    Serial.print("pushed: /logs/");
    Serial.println(name);
    delay(1000);

}