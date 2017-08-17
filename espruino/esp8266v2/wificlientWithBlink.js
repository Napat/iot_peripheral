/*
More api about wifi api
 - https://www.espruino.com/ESP8266_WifiUsage
 - http://www.espruino.com/Reference#Wifi
*/
var ledpin      = NodeMCU.D4; 
var status      = true;             
var blinkdelay  = 1000; 

var wifi        = require("Wifi");
var ssid        = "JASUS";
var password    = "1b1e1aac68d3";

function initWifi(){
    //wifi.disconnect();
    wifi.connect(ssid, {password: password}, function(err) {
        if (err){
            console.log("Wifi connection error: " + err);
            return;
        }
        console.log("Wifi is connected!");
        console.log(wifi.getStatus());
        console.log(wifi.getIP() );
        
        // Set host name, the hostname is sent with every DHCP request and is broadcast via mDNS. 
        // The DHCP hostname may be(or may be NOT) visible in the access point
        //wifi.setHostname("espruino_mcu01");
        
        // Save the Wi-Fi settings to automatically at power-up
        wifi.save();
    });
}

function initBlink(){
    pinMode(ledpin, "output");
    setInterval(function(){
        status =! status;
        digitalWrite(ledpin, status);
        console.log(status);
    }, blinkdelay);
}

function initall(){
  initBlink();
  initWifi();
}

E.on("init",initall());

// Save app from memory to flash to automatically at power-up
save();
