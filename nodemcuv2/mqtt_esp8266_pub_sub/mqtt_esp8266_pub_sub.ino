/*
 Basic ESP8266 MQTT example

 This sketch demonstrates the capabilities of the pubsub library in combination
 with the ESP8266 board/library.

 It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

 It will reconnect to the server if the connection is lost using a blocking
 reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
 achieve the same result without blocking the main loop.

 To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>

void setup_wifi();
void callback(char* topic, byte* payload, unsigned int length);

// Update these with values suitable for your network.

const char* ssid = "iot-workshop";
const char* password = "password";
const char* mqtt_server = "161.246.38.16";

char inTopic[]   = "napat/esp8266/1";
char outTopic[]   = "napat/esp8266/2";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;

char buffer_str[40];

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

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

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    char clientID[15];
    String("iot-" + String(random(1000000))).toCharArray(clientID, 15); //Random Client ID
    if (client.connect(clientID)) {
      Serial.println("Successfully connected with MQTT");
      Serial.print("Client: ");
      Serial.println(clientID);

      client.subscribe(inTopic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(1000);
    }
  }
}
void loop() {

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    
    String outPayload = "Hello, I'm Arduino.";
    outPayload.toCharArray(buffer_str,40);
    client.publish(outTopic, buffer_str);
  }
}
