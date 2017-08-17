var wifi = require("Wifi");
var ssid="JASUS";
var password="1b1e1aac68d3";

var buttonPin=12;
pinMode(buttonPin, 'input_pullup');

function fireButton(){
  require("http").get("https://maker.ifttt.com/trigger/hooker/with/key/xxxxxxxxxxxxxxxxx", function(res) {
      res.on('data', function(data) {
        console.log("HTTP> "+data);
      });
      res.on('close', function(data) {
        console.log("Connection closed");
      });
  });
}

// function fireButtonPost(){
//   require("http").post("https://maker.ifttt.com/trigger/hooker/with/key/xxxxxxxxxxxxxxxxx", {
//     value1: "101",
//     value2: "102",
//     value3: "103"
//   });
// }

function checkButton(){
 setWatch(function() {
    console.log("pressed!");
    fireButton();
  }, buttonPin, { repeat: true, debounce : 50, edge: "rising"   });
}

function inittxline(){
  setInterval(function(){
    console.log("tx msg to line!");
    fireButton();
    //fireButtonPost();
  }, 10000);   
}

function main(){
  wifi.connect(ssid, {password: password},
   function(err){
     if(err)console.log(err);
     else{
       inittxline();
       //checkButton();
      }
   });
}

E.on("init",main());
save();
