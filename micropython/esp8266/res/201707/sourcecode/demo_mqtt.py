import time
from umqtt.simple import MQTTClient

_broker = '192.168.0.100'
_port = 1883

c = MQTTClient("ESP8266", _broker)
c.connect()

#topic,message
c.publish(b"debug",b'Goodbye')
c.disconnect()


