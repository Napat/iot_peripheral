#ifndef __DHTLIB_H__
#define __DHTLIB_H__

#include "DHT.h"

/*
https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.h
DHT11:      dht11
DHT22:      dht22 or am2302
DHT21:      dht21 or am2301
AM2301:     dht21 or am2301
*/
#define DHTTYPE   DHT22     // DHT22 or AM2302
#define DHTPIN    D2

#ifdef __DHTLIB_CPP__
    DHT dht(DHTPIN, DHTTYPE);   
#else
    extern DHT dht;
#endif /* __DHTLIB_CPP__ */

void setup_dhtlib();
//void loop_dhtlib();

#endif /* __DHTLIB_H__ */
