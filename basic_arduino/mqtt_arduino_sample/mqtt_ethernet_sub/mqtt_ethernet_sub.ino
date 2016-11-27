#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

//char MQTT_SERVER[] = "broker.mqttdashboard.com";
//char MQTT_SERVER[] = "neutron.it.kmitl.ac.th";
char MQTT_SERVER[] = "161.246.38.16";

char inTopic[]    = "iot/napat/1";
char outTopic[]   = "iot/napat/2";

char buffer_str[40];

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x30 }; // แต่ละ device ต้องไม่ซ้ำกัน

unsigned long lastPub = 0;

void callback(char* topic, byte* payload, unsigned int length) {
  String payload_str = "";
  String topic_str = String(topic);
  for (int i = 0; i < length; i++) {
    payload_str += (char)payload[i];
  }
  Serial.print("Message arrived [");
  Serial.print(topic_str);
  Serial.print("] ");
  Serial.println(payload_str);
}

EthernetClient ethClient; // Ethernet object
PubSubClient client( MQTT_SERVER, 1883, callback, ethClient); // MQTT object

void setup() {
  Serial.begin(9600);
  Serial.println("Net begin");
  
  if (Ethernet.begin(mac) == 0) { // Get connected!
    Serial.println("Failed to configure Ethernet using DHCP");
    return;
  }

  Serial.print("IP: "); // A little debug.. show IP address
  Serial.println(Ethernet.localIP());

  while (true) {
    char clientID[15];
    String("iot-" + String(random(1000000))).toCharArray(clientID, 15); //Random Client ID
    if (client.connect(clientID)) {
      Serial.println("Successfully connected with MQTT");
      Serial.print("Client: ");
      Serial.println(clientID);

      client.subscribe(inTopic);
      break;
    }
    else {
      Serial.println("cant connected with MQTT");
      delay(200);
    }
  }
}

void loop() {
  long now = millis();
  if (now - lastPub > 5000) {
    lastPub = now;
    
    String outPayload = "Hello, I'm Arduino...";
    outPayload.toCharArray(buffer_str,40);
    client.publish(outTopic, buffer_str);
  }
  client.loop();
}
