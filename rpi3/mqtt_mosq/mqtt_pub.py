import paho.mqtt.client as mqtt
import time

server_addr = "127.0.0.1"
topic1 = "napat/channel1"
topic2 = "napat/channel2"

mqttc = mqtt.Client()
mqttc.connect(server_addr, 1883)

while True:
    mqttc.publish(topic1, "Halo")
    mqttc.publish(topic2, "Haloo")
    time.sleep(1)
