#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

byte LEDpin = 9;

//char MQTT_SERVER[] = "broker.mqttdashboard.com";
char MQTT_SERVER[] = "neutron.it.kmitl.ac.th";

char inTopic[]    = "iot/inTopic";
char outTopic[]   = "iot/outTopic";

char buffer_str[40];

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // แต่ละ device ต้องไม่ซ้ำกัน

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

  if (payload_str.endsWith("on")) {
    Serial.println("LED ON");
    digitalWrite(LEDpin,HIGH);
  }
  else if (payload_str.endsWith("off")) {
    Serial.println("LED OFF");
    digitalWrite(LEDpin,LOW);
  }
}

EthernetClient ethClient; // Ethernet object
PubSubClient client( MQTT_SERVER, 1883, callback, ethClient); // MQTT object

void setup() {

  pinMode(LEDpin,OUTPUT);
  
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
    
    String outPayload = "Hello, I'm Arduino.";
    outPayload.toCharArray(buffer_str,40);
    client.publish(outTopic, buffer_str);
  }
  client.loop();
}
