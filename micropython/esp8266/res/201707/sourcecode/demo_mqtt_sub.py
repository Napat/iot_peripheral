def mqtt_sub():
	import time
	from umqtt.simple import MQTTClient
	# Received messages from subscriptions will be delivered to this callback
	def sub_callback(topic, msg):
		print((topic, msg))		

	_broker = '192.168.0.100'
	_port = 1883
	_topic = b'Debug'

	_client = MQTTClient(client_id="ESP8266",server=_broker,port=_port)
	_client.set_callback(sub_callback)
	_client.connect()
	_client.subscribe(_topic)
	while True:
		if True:
			# Blocking wait for message
			_client.wait_msg()
		else:
			# Non-blocking wait for message
			_client.check_msg()
			
			# Sleep to avoid 100% CPU usage 
			time.sleep_ms(500)
	_client.disconnect()	

