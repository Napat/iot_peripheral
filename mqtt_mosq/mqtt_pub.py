import paho.mqtt.client as mqtt
import time

server_addr = "127.0.0.1"
topic1 = "napat/channel1"

mqttc = mqtt.Client()
mqttc.connect(server_addr, 1883)

while True:
    mqttc.publish(topic1, "Halo")
    time.sleep(1)
