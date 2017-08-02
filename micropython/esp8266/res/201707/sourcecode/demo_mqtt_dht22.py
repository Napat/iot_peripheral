from umqtt.simple import MQTTClient
import ubinascii, machine, time, dht
from machine import Pin

_dht22 = dht.DHT22(Pin(12))
_broker = '192.168.0.100'
_port = 1883
_topic = b'mqtt/report'
_msg = b'I am ESP8266'
_alias = ubinascii.hexlify(machine.unique_id())
_client = MQTTClient(client_id=_alias,server=_broker,port=_port)
_client.connect()

try:
	for i in range(10):
		_dht22.measure()
		_t = _dht22.temperature()
		_h = _dht22.humidity()
		_msg = 'sta:{},temp:{:.2f},humd:{:.2f}'.format(_alias,_t,_h)		
		_client.publish(_topic,_msg)
		time.sleep_ms(2000)
finally :	
	_client.disconnect()
