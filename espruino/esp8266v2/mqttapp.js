var ssid="JASUS";
var password="1b1e1aac68d3";
var clientID = "board/"+getSerial();
//var topic = clientID+"/status";
var topic = clientID + "/2txt";
var wifi = require("Wifi");
//var server = "iot.eclipse.org"; // the address of your MQTT broker
var server = "mqtt.espert.io";

var options = { // all optional - the defaults are below
    client_id : clientID,
    keep_alive: 60, // keep alive time in seconds
    port: 1883, // port number
    clean_session: true,
   /* username: "username", // default is undefined
    password: "password",  // default is undefined*/
    protocol_name: "MQTT", // or MQIsdp, etc..
    protocol_level: 4, // protocol level
  };

var mqtt = require("MQTT").create(server);

mqtt.on('connected', function() {
    console.log("mqtt connected!");
    mqtt.publish(topic, "test");
    mqtt.subscribe(clientID+"/command");
});

mqtt.on('disconnected', function() {
  console.log("MQTT disconnected... reconnecting.");
  setTimeout(function() {
    mqtt.connect();
  }, 1000);
});

/*when message arrive fire this function*/
mqtt.on('publish', function (pub) { 
  console.log("topic: " + pub.topic);
  console.log("message: " + pub.message);
});

function main(){

}

function onInit(){
  wifi.connect(ssid, {password: password},
  function(err){
     if(err)console.log(err);
     else{ 
        mqtt.connect();
        console.log("connected! : "+clientID);
        console.log(wifi.getIP());
      }
   });   
  main();
}

E.on("init",  onInit() );
save();

 


