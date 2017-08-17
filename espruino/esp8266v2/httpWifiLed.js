/*
  A simple example to control the built-in LED
  over a HTML web page
  http://aaa.bbb.ccc.ddd:8080
*/

var ledpin      = NodeMCU.D4; 

var wifi        = require('Wifi');
var ssid        = "JASUS";
var password    = "1b1e1aac68d3";

var http = require('http');

function initWifi(){
    //wifi.stopAP();
    wifi.connect(ssid, {password: password}, function(err) {
        if (err){
            console.log("Wifi connection error: " + err);
            return;
        }
        console.log("Wifi is connected!");
        console.log(wifi.getStatus());
        console.log(wifi.getIP() );
        // Set host name 
        wifi.setHostname("espruino_mcu01");
        
        // Save the Wi-Fi settings to automatically at power-up
        wifi.save();
    });
}

function restoreWifiCfg(){
  // connect to the Wi-Fi AP with the informations
  // provided in config by previous config with wifi.save()
  wifi.restore();

  // Set host name, the hostname is sent with every DHCP request and is broadcast via mDNS. 
  // The DHCP hostname may be(or may be NOT) visible in the access point
  //wifi.setHostname("espruino_mcu01");
}

function initHttp(){
  http.createServer(function(req, res) {
    switch(req.method) {
      case 'GET':
        switch(req.url) {
          case '':
          case '/':
            res.writeHead(200);
            res.write('<html>');
            res.write('  <head>');
            res.write('    <title>LED Control</title>');
            res.write('  </head>');
            res.write('  <body>');
            res.write('    <h1>Control the built-in LED</h1>');
            res.write('    <form action="/led/on" method="POST">');
            res.write('      <button type="submit">Turn on</button>');
            res.write('    </form>');
            res.write('    <form action="/led/off" method="POST">');
            res.write('      <button type="submit">Turn off</button>');
            res.write('    </form>');
            res.write('  </body>');
            res.write('</html>');
            break;
          default:
            console.log('INFO: URL not handled, ' + req.url);
            res.writeHead(404);
            break;
        }
        break;
      case 'POST':
        switch(req.url) {
          case '/led/on':
            console.log('INFO: Turn on the LED');
            digitalWrite(ledpin, LOW);
            res.writeHead(200);
            res.write('<html>');
            res.write('  <head>');
            res.write('    <title>LED Control</title>');
            res.write('    <meta http-equiv="refresh" content="2;url=/" />');
            res.write('  </head>');
            res.write('  <body>');
            res.write('    <a href="/">Back</a>');
            res.write('  </body>');
            res.write('</html>');
            break;
          case '/led/off':
            console.log('INFO: Turn off the LED');
            digitalWrite(ledpin, HIGH);
            res.writeHead(200);
            res.write('<html>');
            res.write('  <head>');
            res.write('    <title>LED Control</title>');
            res.write('  </head>');
            res.write('  <body>');
            res.write('    <a href="/">Back</a>');
            res.write('  </body>');
            res.write('</html>');
            break;
          default:
            console.log('INFO: URL not handled, ' + req.url);
            res.writeHead(404);
            break;
        }
        break;
      default:
        console.log('INFO: Method not handled, ' + req.method);
        res.writeHead(405);
        break;
    }
    res.end();
  }).listen(8080);
}

initWifi();
initHttp();
// Save app from memory to flash to automatically at power-up
save();
