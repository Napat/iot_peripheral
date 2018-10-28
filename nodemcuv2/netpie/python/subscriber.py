import microgear.client as microgear
import logging
import time

appid = "............yourappid........."
gearkey = "...........yourgearkey........"
gearsecret = "..............yourgearsecret.........."

aliasmy = "python01"

netpiefeedkey = "................yournetpiefeedkey............"

microgear.create(gearkey, gearsecret,appid, {'debugmode': True})

def connection():
    logging.info("Now I am connected with netpie")

def subscription(topic, message):
    logging.info(topic+"--"+message)

def disconnect():
    logging.info("disconnected")

def writefeed():
    data = int(time.time()) % 10
    feeddat = {
        "var1": data,
        "var2": (data-1)*10,
        "var3": (data+5)*20,
    }
    microgear.writeFeed("feed0001", feeddat, feedkey=netpiefeedkey)

microgear.setalias(aliasmy)
microgear.on_connect = connection
microgear.on_message = subscription
microgear.on_disconnect = disconnect
microgear.subscribe("/mails", qos=0)
microgear.connect(False)

while True:
    if(microgear.connected == False):
        time.sleep(0.5)
        continue
    
    microgear.chat(aliasmy,"Hello world."+str(int(time.time())))
    microgear.publish('/mails', "Halo")
    writefeed() 

    time.sleep(3)
