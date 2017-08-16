var ledpin      = NodeMCU.D4; 
var status      = true;             
var blinkdelay  = 1000; 

function initBlink(){
    pinMode(ledpin, "output");
    setInterval(function(){
        status =! status;
        digitalWrite(ledpin, status);
        console.log(status);
    }, blinkdelay);
}

function initdht(){
  // Change DHT11,DHT22 depend on your module.(For DHT12 please using DHT11 config)
  // Connect at pin 5 = NodeMCU.D1
  var dht = require("DHT22").connect(NodeMCU.D1);  

  setInterval(function() {
      dht.read(function (a) {
        console.log("Temp is "+a.temp.toString()+" and RH is "+a.rh.toString());
        var dhtData={"t":a.temp.toString(),"h":a.rh.toString()};
        dhtData=JSON.stringify(dhtData);
        console.log(dhtData);
      });
   }, 2000); 
}

function initall(){
  initBlink();
  initdht();
}

E.on("init",  initall() );
save();
