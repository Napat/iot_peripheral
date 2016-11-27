#include <PubSubClient.h>

#include <SPI.h>
#include <Ethernet.h>
#include <PubSubClient.h>

float value = 5.67;
char buff[20];

//char MQTT_SERVER[] = "broker.mqttdashboard.com";
//char MQTT_SERVER[] = "neutron.it.kmitl.ac.th";
char MQTT_SERVER[] = "161.246.38.16";

char outTopic[] = "iot/napat/1";
//char outTopic[] = "304";
char payload[] = "test from arduino...";

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0x30 }; // แต่ละ device ต้องไม่ซ้ำกัน
EthernetClient ethClient; // Ethernet object
PubSubClient client( MQTT_SERVER, 1883, 0, ethClient); // MQTT object

void setup() {
  Serial.begin(9600);
  Serial.println("Net begin");
  if (Ethernet.begin(mac) == 0) // Get connected!
  {
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
      break;
    }
    else {
      Serial.println("cant connected with MQTT");
      delay(200);
    }
  }
}

void loop() {
  // put your main code here, to run repeatedly:

/*
 * There is function dtostrf() to convert float to string value 
 * but don't like it because it's available only in arduino platform.
 *  char temp_str[10];
 *  float f_val = 25.50;
 *  dtostrf( f_val, 3, 2, temp_str);
 *  client.publish(outTopic, temp_str);
 */

/* 
 * sprintf() in arduino doesn't support float 
 * sprintf(buff, "%s %f", payload, value); will print ? at %f
*/
  //client.publish(outTopic, payload);
  // retain flag to keep message to new connection(last message only)
  client.publish(outTopic, payload, true);  //publish(const char* topic, const char* payload, boolean retained);
  
  delay(5000);
}
