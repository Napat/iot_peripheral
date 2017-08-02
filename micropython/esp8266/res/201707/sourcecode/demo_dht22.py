from machine import  Pin
import dht
import time

_pin = Pin(12)
_dht = dht.DHT22(_pin)

for  i in range(10):
	_dht.measure()
	print("Temperature {}".format(_dht.temperature()))
	print("Humidity {}".format(_dht.humidity()))
	time.sleep_ms(500)
