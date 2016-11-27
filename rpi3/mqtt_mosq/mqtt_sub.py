import paho.mqtt.client as mqtt

server_addr = "127.0.0.1"
topic1 = "napat/channel1"
topic2 = "napat/channel2"

def on_connect(client, usrdat, rc):
    print("Connect with result code: " + str(rc))
    client.subscribe(topic1)
    client.subscribe(topic2)


def on_message(client, usrdat, msg):
    print(msg.topic + " " + str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect(server_addr, 1883)
client.loop_forever()
