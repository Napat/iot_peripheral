// netpie 
const APPID = "......yourappid.......";
const APPKEY = "......yourappkey........";
const APPSECRET = ".........yourappsecret.......";
const ALIAS = "webapp";

var microgear = Microgear.create({
    gearkey: APPKEY,
    gearsecret: APPSECRET
});

// JustGage
var gageTemp01;
var gageHumi01;
window.onload = function () {
    gageTemp01 = new JustGage({
        id: "gageTemp01",
        value: 0,
        min: 0,
        max: 50,
        title: "Temperature gage",
        label: "oC",
        levelColors: ["#00fff6", "#ff00fc", "#1200ff"]
    });
    gageHumi01 = new JustGage({
        id: "gageHumi01",
        value: 0,
        min: 0,
        max: 100,
        title: "Humidity gage",
        label: "%",
        levelColors: ["#00fff6", "#ff00fc", "#1200ff"]
    });
};


var timestamp = 0;
microgear.on('message', function (topic, msg) {
    var timestampNow = new Date().toUTCString();
    
    console.log(timestampNow + ": " + msg);
  
//    var msgArr = msg.split(",");
//
//    switch (msgArr[0]) {
//        case "temp01":
//            console.log("case temp01");
//            gageTemp01.refresh(msgArr[1]);
//            break;
//        case "humi01":
//            console.log("case temp01");
//            break;
//        default:
//            console.log("Receive unknown message: " + msgArr[0]);
//    }

    var msgJson = JSON.parse(msg);

    if(typeof msgJson.temp01 !== "undefined") {
        console.log("temp01: " + msgJson.temp01);
        gageTemp01.refresh(msgJson.temp01);
    }

    if(typeof msgJson.humi01 !== "undefined") {
        console.log("humi01" + msgJson.humi01);
        gageHumi01.refresh(msgJson.humi01);
    }    

});

microgear.on('connected', function () {
    console.log('microgear on connected');
    microgear.setAlias(ALIAS);
    document.getElementById("mylogo").innerHTML =
        '<p><img src="https://static1.squarespace.com/static/529c0603e4b0a6ba0e3871f1/t/54318b3fe4b0ff6362e9e226/1412532765861/?format=1000w" id="tesr" onclick="location.reload()" height="130"></p>';

    //document.getElementById("dashboardsensor").style.display = "float";
    gageTemp01.refresh(10);
});

microgear.resettoken(function (err) {
    microgear.connect(APPID);
});


function toggle() {
    if(document.getElementById("lamp01").innerText=="Lamp is off"){
        microgear.chat('freeboard-01/webapp/lamp','ON');   
        document.getElementById("lamp01").innerText="Lamp is on"; 
    }
    else{
        microgear.chat('freeboard-01/webapp/lamp','OFF');
        document.getElementById("lamp01").innerText="Lamp is off";
    }
}