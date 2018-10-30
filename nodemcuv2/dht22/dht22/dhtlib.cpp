#define __DHTLIB_CPP__

#include "dhtlib.h"

//int max_hum = 60;
//int max_temp = 30;

void setup_dhtlib() {
    dht.begin();

    //pinMode(LED_ALARM, OUTPUT);
    //pinMode(fan, OUTPUT);
    //Serial.begin(9600); 
}

void loop_dhtlib() {
/*     
    // Wait a few seconds between measurements.
    delay(2000);

    // Reading temperature or humidity takes about 250 milliseconds!
    // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
    float h = dht.readHumidity();
    // Read temperature as Celsius
    float t = dht.readTemperature();

    // Check if any reads failed and exit early (to try again).
    if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
    }

    if(h > maxHum || t > maxTemp) {
        digitalWrite(fan, HIGH);
    } else {
        digitalWrite(fan, LOW); 
    }

    toggleLed();

    Serial.print("Humidity: "); 
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: "); 
    Serial.print(t);
    Serial.println(" *C "); 
    */
}
