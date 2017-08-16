var ledpin      = 2;               // built-in LED, may replace by "var ledPin = NodeMCU.D4"
var status      = true;            // default LED 
var blinkdelay  = 1000;            // blink LED every 1 sec

function initBlink(){
    pinMode(ledpin, "output");
    setInterval(function(){
        status =! status;
        digitalWrite(ledpin, status);
        console.log(status);
    }, blinkdelay);
}

E.on("init",  initBlink() );    // call initBlink() at initial event
