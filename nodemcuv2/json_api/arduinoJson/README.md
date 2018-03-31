
การใช้งาน ArduinoJson มีเรื่องที่จะต้องทราบก่อนดังนี้
การประกาศตัวแปรสำหรับ json data มีสองชนิดคือ StaticJsonBuffer และ DynamicJsonBuffer  
StaticJsonBuffer ใช้หน่วยความจำบนพื้นที่ stack
DynamicJsonBuffer ใช้หน่วยความจำบนพื้นที่ heap
ในแต่ละ hardware platform จะสามารถใช้ stack size ได้ไม่เท่ากัน และพื้นที่ดังกล่าวมักมีขนาดจำกัดมาก  
จึงอาจมีปัญหาว่าไม่สามารถประกาศ StaticJsonBuffer ที่มีค่าใหญ่ๆได้ 
[ในกรณีแบบนี้จำเป็นจะต้องย้ายไปใช้ DynamicJsonBuffer แทน](https://github.com/bblanchon/ArduinoJson/issues/668#issuecomment-358890048)

## StaticJsonBuffer 
StaticJsonBuffer จะ allocates หน่วยความจำบนพื้นที่ stack  
ในแง่การใช้งานตัวแปรชนิด  StaticJsonBuffer จำเป็นจะต้องคำนวณ capacity ของ buffer ที่จะประกาศเพื่อเก็บข้อมูล json เช่น
```
StaticJsonBuffer<512> jsonBuffer;
```

ตัวเลข 512 คือ Size ของ buffer (ซึ่งจะไม่เท่ากับการนับจำนวนตัวอักษร json แบบตรงๆนะ)  
แต่ไม่ต้องห่วง เราสามารถใช้เว็บช่วยคำนวณหาขนาดของ buffer ที่ต้องใช้ได้ที่   
http://arduinojson.org/assistant/  
เช่น หากข้อมูล json มีลักษณะดังนี้
```
{
  "sensor": "gps",
  "time": 9876543210,
  "data": [
    48.75608,
    2.302038
  ]
}
```

เว็บดังกล่าวก็จะคำนวณขนาดของ StaticJsonBuffer ของแต่ละ platform ต่างๆมาให้
```
Platform		Size
AVR 8-bit		104
ESP8266			138
Visual Studio x86	218
Visual Studio x64	242
```

กรณีนี้เราใช้ ESP8266 ดังนั้นเราก็จะใช้ตัวเลข 138 ใส่ลงในขั้นตอนการประกาศตัวแปร
```
StaticJsonBuffer<138> jsonBuffer;
```

*ระวัง* 
- การป้อนข้อมูลเข้าไปให้เว็บช่วยคำนวณจะต้องใส่ข้อมูล json ที่มีความยาวของ value ที่สูงที่สุดเท่าที่จะเป็นไปได้เข้าไป
เช่น `"time": 9876543210` แปลว่าข้อมูล value สามารถมีความยาวได้สูงสุด 10 หลัก  
หากเผลอป้อนแค่ 6 หลักเช่น 123456 เมื่อนำค่าที่ได้จากการคำนวนจะทำให้ buffer มีขนาดไม่พอใช้และเกิดปัญหาขึ้นได้
- หลังการทำ parseObject(่json) จะต้องเช็ค success() เสมอก่อนนำ root ไปใช้งานต่อ เช่น
```
  char json[] = "{\"sensor\":\"gps\",\"time\":1351824120,\"data\":[48.756080,2.302038]}";
  JsonObject& root = jsonBuffer.parseObject(json);
  if (!root.success()) {
    Serial.println("parseObject() failed");
    return;
  }
  const char* sensor = root["sensor"];
  long time = root["time"];
  double latitude = root["data"][0];
  double longitude = root["data"][1];
```  


#### ตัวอย่างการใช้งาน StaticJsonBuffer 
- [JsonConfigFile](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonConfigFile) Store project binary configuration to json file
- [JsonGeneratorExample](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonGeneratorExample) Generate a JSON document and prettyPrintTo()
- [JsonParseExample](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonParserExample) Deserialize a JSON document to binary 
- [JsonServer](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonServer) HTTP server that sends JSON document in the responses. 
- [JsonUdpBeacon](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonUdpBeacon) Send a JSON document to a UDP socket.


## DynamicJsonBuffer
DynamicJsonBuffer จะ allocates หน่วยความจำบนพื้นที่ heap
การใช้งาน DynamicJsonBuffer สามารถใช้แทน StaticJsonBuffer  
มีข้อดีคือไม่จำเป็นจะต้องคำนวณขนาด buffer ไว้ตั้งแต่แรกก็ได้เช่น
```
// The default initial size for DynamicJsonBuffer is 256.
DynamicJsonBuffer jsonBuffer;	// similar with DynamicJsonBuffer jsonBuffer(256)	
``` 

ในระหว่าง runtime หาก json data ต้องการใช้ขนาดเกินกว่าที่กำหนดไว้ 
ตัว library [จะทำการขยายขนาดของ buffer ให้โดยอัตโนมัติ](https://github.com/bblanchon/ArduinoJson/issues/235#issuecomment-189616569) 
ด้วยการขยายขนาดขึ้นทีละ 2 เท่าของขนาดเดิมจนกว่าขนาดจะพอกับข้อมูลที่ต้องการใช้งาน 
เช่น 256 จะขยายกลายเป็น 512  หรือ 138 ก็จะขยายเป็น 276  

การกำหนด size ไม่จำเป็นจะต้องเริ่มต้นที่ค่า default 256 ก็ได้ เราสามารถกำหนดขนาดเริ่มต้นเองก็ได้
```
DynamicJsonBuffer jsonBuffer(100)
```

#### ตัวอย่างการใช้งาน DynamicJsonBuffer
- [JsonHtpCLient](https://github.com/bblanchon/ArduinoJson/tree/master/examples/JsonHttpClient) Http GET JSON document then parse data.
- [ProgmemExample](https://github.com/bblanchon/ArduinoJson/tree/master/examples/ProgmemExample) use Arduino Flash strings with ArduinoJson.
- [StringExample](https://github.com/bblanchon/ArduinoJson/tree/master/examples/StringExample) ArduinoJson with String 

*Note* 
ควรใช้ตัวแปร String เท่าที่จำเป็นเท่านั้น เนื่องจาก ArduinoJson library จะทำการ duplicate ข้อมูลมาอีกก้อน ซึ่ง String นั้นใช้ทรัพยากรสูงว่า char[] มากทั้งเรื่อง ขนาดของ code(flash rom), ความเร็วการทำงาน รวมไปถึงการใช้หน่วยความจำ (ram) ที่สูงกว่ากันมาก 
หากไปดูสเป็คของ board hardware จาก Arduino ส่วนใหญ่แล้วมี ram ที่จำกัดมากๆ 
หากใครต้องการเป็นนักพัฒนาด้าน embedded system ที่ดีแล้วควรหัดสังเกต ศึกษาและให้ความสำคัญกับเรื่องสป็คของทรัพยากรต่างๆเหล่านี้ให้ดีๆนะ 
