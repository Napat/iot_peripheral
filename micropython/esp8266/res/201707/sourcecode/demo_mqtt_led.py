from umqtt.simple import MQTTClient
from machine import Pin
import ubinascii
import machine

_alias = ubinascii.hexlify(machine.unique_id())
_broker = '192.168.0.100'
_port = 1883
_topic = b'LED'
_led = Pin(5, Pin.OUT, value=1)	 #D1

def sub_callback(topic,msg):
	if topic == b'on':
		_led.value(1)
	elif topic == b'off':
		_led.value(0)
	elif topic == b'toggle':
		v = _led.value()
		_led.value(1-v)
	
_client = MQTTClient(_alias,server=_broker,port=_port)
_client.set_callback(sub_callback)
_client.subscribe(_topic)
try:
	while True:
		_client.wait_msg()
finally:
	_client.disconnect()

