from umqtt.simple import MQTTClient

_broker = '192.168.0.100'
_port = 1883
_topic = b'Debug'
_msg = b'I am ESP8266'
_alias = b'ESP8266'
_client = MQTTClient(client_id="ESP8266",server=_broker,port=_port)
_client.connect()

#topic,message
_client.publish(_topic,_msg)
_client.disconnect()
