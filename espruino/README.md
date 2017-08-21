
# เกริ่นนำ  
แต่เดิมนั้นตัวภาษา Javascript ได้ถูกพัฒนาขึ้นเพื่อใช้งานในฝั่ง Front-end แต่ในยุคปัจจุบันได้มีการทำเครื่องมือเพื่อพัฒนาให้นักพัฒนาโปรแกรมสามารถข้าม 
platform กันได้ออกมาหลากหลายชนิดเพื่อลดเวลาในการเรียนรู้ของนักพัฒนาทั้งหน้าเก่าและหน้าใหม่ลง ไม่เว้นแม้แต่ฝั่งของ Embedded system หรือ Internet of Things ก็มีคนพัฒนาโปรเจคเพื่อนำเอา Javascript มาใช้งานในอุปกรณ์ Microcontroller อยู่หลากหลายแพลทฟอมด้วยกัน ตัวอย่างเช่น [Espruino](http://www.espruino.com), [Tessel](https://tessel.io/)
, [johnny-five](http://johnny-five.io/), [nodebots](http://nodebots.io/) เป็นต้น ในที่นี้เราจะมาเรียนรู้การใช้งาน [Espruino](http://www.espruino.com) กันดูซักหน่อย    
  
# Espruino firmware  
ในช่วงเริ่มต้นของโปรเจค Espruino(software) ถูกพัฒนาขึ้นเพื่อให้ใช้งานบนบอร์ดฮาร์แวร์(hardware)ของตัวเอง สามารถสั่งซื้อได้จาก [link](http://www.espruino.com/Order) 
แต่ hardware ดังกล่าวไม่ได้จะได้รับความนิยมมากนัก หลังจากนั้นได้มีการพอร์ท software ดังกล่าวให้สามารถทำงานกับ hardware ที่หลากหลายมากขึ้น 
สามารถตรวจสอบรายการของอุปกรณ์ที่ซัพพอตได้ที่ [link](http://www.espruino.com/Other+Boards)  
  
จะเห็นว่า ESP8266 เป็นฮาร์แวร์หนึ่งที่ได้รับความนิยมอย่างสูงและได้รับการซับพอทจาก Espruino โดยตรง ซึ่งภายในเว็บไซท์จะมี firmware สำหรับ ESP8266 ให้ดาว์โหลดมาใช้งานได้จากเว็บได้เลย 
ในบทความนี้เราจะใช้งาน ESP8266v2 ซึ่งมี Flash 4MB เป็นหลักนะครับ สำหรับ hardware รุ่นอื่นๆอาจจะต้องมีการปรับเปลี่ยนหารตั้งค่าบางอย่างบ้าง  
  
![alt tag](res/img/esp8266v2.jpg)   
  
# Requirements list
1.Python3  
2.Espruino firmware for esp8266  
3.Flash firmware tools เช่น ESP8266 Download Tool, esptool.py  
4.Espruino Web IDE (Chrome browser extensions)  
5.ความอยากรู้อยากลองและความสามารถในการแก้ปัญหาเฉพาะตัว  
  
## Espruino firmware for esp8266  
ขั้นแรกให้เข้าไป Download Espruino firmware มาจาก [official](http://www.espruino.com/Download) ก่อนครับ 
เลือก version ตามที่ชอบเลย(ตัว stable ที่ใหม่สุดนั่นแหละ) ของผมจะเลือกเป็น [1v93](http://www.espruino.com/files/espruino_1v93.zip) 
มาใช้งานครับ  

เมื่อดาว์โหลดลงแล้วให้ทำการแตกไฟล์ .zip ออกมาก็จะพบว่ามี firmware หลายตัวให้เลือกใช้ซึ่งก็จะต้องเลือกให้ตรงกับฮาดแวร์ที่ใช้ครับ  
```
.
├── changelog.txt
├── espruino_1v93_esp32
│   ├── bootloader.bin
│   ├── espruino_esp32.bin
│   ├── partitions_espruino.bin
│   └── README_flash.txt
├── espruino_1v93_esp32.bin
├── espruino_1v93_esp8266
│   ├── blank.bin
│   ├── boot_v1.6.bin
│   ├── esp_init_data_default.bin
│   ├── espruino_esp8266_user1.bin
│   ├── espruino_esp8266_user2.bin
│   ├── README_flash.txt
│   └── wiflash.sh
├── espruino_1v93_esp8266_4mb
│   ├── blank.bin
│   ├── boot_v1.6.bin
│   ├── esp_init_data_default.bin
│   ├── espruino_esp8266_user1.bin
│   ├── espruino_esp8266_user2.bin
│   ├── README_flash.txt
│   ├── _temp_by_dltool
│   │   └── downloadPanel1
│   │       ├── boot_v1.6.bin_rep
│   │       ├── esp_init_data_default.bin_rep
│   │       └── espruino_esp8266_user1.bin_rep
│   └── wiflash.sh
├── espruino_1v93_esp8266_4mb_combined_4096.bin
├── espruino_1v93_esp8266_combined_512.bin
├── espruino_1v93_espruino_1r3.bin
├── espruino_1v93_espruino_1r3_wiznet.bin
├── espruino_1v93_hystm32_24_ve.bin
├── espruino_1v93_hystm32_28_rb.bin
├── espruino_1v93_hystm32_32_vc.bin
├── espruino_1v93_microbit.hex
├── espruino_1v93_nucleof401re.bin
├── espruino_1v93_nucleof411re.bin
├── espruino_1v93_olimexino_stm32.bin
├── espruino_1v93_pico_1r3_cc3000.bin
├── espruino_1v93_pico_1r3_wiznet.bin
├── espruino_1v93_puckjs.zip
├── espruino_1v93_raspberrypi
├── espruino_1v93_ruuvitag.zip
├── espruino_1v93_stm32f3discovery.bin
├── espruino_1v93_stm32f4discovery.bin
├── espruino_1v93_stm32vldiscovery.bin
├── espruino_1v93_wifi.bin
├── functions.html
├── licences.txt
└── readme.txt
```
ในที่นี้ผมจะใช้ไฟล์ที่อยู่ใน folder espruino_1v93_esp8266_4mb นะครับ  

## การ Flash Espruino firmware ลงบนบอร์ด  
หากท่านใช้งาน `esptool.py` สามารถอ่านขั้นตอนได้จากไฟล์ `espruino_1v93_esp8266_4mb/README_flash.txt` ได้เลยครับ  
หากท่านใช้ tools อื่นๆสามารถดูตัวอย่างการตั้งค่าได้จากในรูปด้านล่างซึ่งใช้ ESP8266 Download Tool 
หลังจากตั้งค่าให้เหมือนตามรูปเสร็จก็กดปุ่ม START ด้านล่างซ้ายเลยครับ  
  
![alt tag](res/img/flashdownloadertool.jpg)  
  
เมื่อแฟรช firmware เสร็จแล้ว(Download Panel 1 ขึ้นสีเขียวพร้อมคำว่า Finish) ให้ทำการกดปุ่ม reset ที่อยู่บนบอด ESP8266v2 ครั้งนึง
(Flash tool อื่นบางตัวอาจจะต้องตัดไฟบอร์ดด้วย) ก็จะสามารถติดต่อ Javascript console ผ่าน Serial port terminal ต่างๆเช่น putty ได้เลยครับ
ให้ตั้งค่า `Baud rate=115200` แล้วทดสอบด้วย javascript syntax ได้เลย เช่น
```
>1+1
=2
>a = "Hello Expruino"          
="Hello Expruino"
>console.log(a)
Hello Expruino
=undefined
>(new Uint8Array([1,2,3])).forEach(function(value) { console.log(value);});
1
2
3
=undefined
>
```
  
เราสามารถตรวจสอบ memory ของระบบได้โดยการใช้คำสั่งดังนี้  
```
>process.memory()
={ "free": 1547, "usage": 53, "total": 1600, "history": 39 }
```

## ติดตั้ง Espruino Web IDE (Chrome browser extensions)  
เปิด Google Chrome browser ขึ้นมาและค้นหาด้วยคำว่า `Espruino Web IDE chrome.google.com` หรือ [click แรงๆ](https://chrome.google.com/webstore/detail/espruino-web-ide/bleoifhkdalbjfbobjackfdifdneehpo) จากนั้นให้ทำการติดตั้งให้เรียบร้อย  
  
![alt tag](res/img/EspruinoWebIDEInstall.jpg)  
  
เปิดโปรแกรม Espruino Web IDE ขึ้นมาและคลิ๊กเข้าไปที่ Settings(รูปเฟื้องแถวๆมุมขวาบน) และตั้งค่า Baud rate ให้เท่ากับ 115200 ตามรูปก็เสร็จสิ้นการตั้งค่าเรียบร้อย  

![alt tag](res/img/espruinowebide_setup.jpg)  
  
ปิดโปรแกรม Serial port terminal อื่นๆให้หมด และทำการ connect โดยการกดปุ่มรูปปลั๊กสีเหลืองส้มด้านบนซ้ายและเลือก COM PORT ที่ใช้งาน   

![alt tag](res/img/espruinowebide_interface.jpg)  
  
หลังจากขั้นตอนนี้เราก็จะสามารถใช้งาน Espruino javascript console ผ่านโปรแกรม Espruino Web IDE ได้แล้ว ซึ่งเราสามารถเขียนโปรแกรมฝั่งและสั่งลงไปรันบนบอร์ดได้ด้วยปุ่ม Send to Espruino  
  
นอกจากนี้ยังมีโหมดการออกแบบโรปรแกรมด้วย Graphical Designer ซึ่งจะคล้ายๆกับ [SCRATCH](https://scratch.mit.edu/) ของ MIT ที่ออกแบบไว้สำหรับสอนเด็กๆอายุ 8-16 ขวบเขียนโปรแกรมด้วยครับ  
  
![alt tag](res/img/GraphicalDesigner.jpg)  
  
สามารถแสดงสถานะ memory ปัจจุบันได้ด้วยการใช้คำสั่ง `process.memory()` เช่นเดียวกับตอนใช้ serial port terminal เช่น putty  
  
  
## Examples
| Title     							              	      | Description        											                              |
|-----------------------------------------------|-----------------------------------------------------------------------|
| [Blink](esp8266v2/blinkled.js)     				                                 | A simple example to blink LED in **memory**(not save flash)                	|
| [WiFi client](esp8266v2/wificlientWithBlink.js)     				                 | Connect to wifi APand make the NodeMCU board. [Wifi api Reference](http://www.espruino.com/Reference#Wifi)                  	|
| [DHTxx: Humidity & Temperature](esp8266v2/humidityTemperatureDHTxxModule.js)     	 | Humidity&Temperature sensor module to be json string           |
| [Led controller over http webserver](esp8266v2/httpWifiLed.js)     	                         | Webserver to on/off led or devices           |
| [IFTTT Webhook](esp8266v2/ifttt_app.js)     	                                     | Webhook to IFTTT to do something like line notify           |
  
  
ตัวอย่างการใช้งานสามารถหาอ่านเพิ่มเติมได้ที่ [Official Link](https://www.espruino.com/Tutorials)
  
#### ระวัง  
โดย default แล้วหลังจากเชื่อมต่อเข้ากับ wifi แล้วเราสามารถ telnet เข้าไปที่ ip address ของบอร์ดเพื่อเข้าสู่ javascript console ในโหมด telnet ได้ทันทีโดยไม่มี password ใดๆเลย หากไม่ได้ใช้ฟีเจอร์นี้ควรทำการปิดด้วยนะครับ  
  
# สรุป  
เราสามารถใช้งาน javascript เพื่อทดสอบต่างๆได้อย่างรวดเร็วและง่ายมากๆ  
จากตัวภาษาซึ่งสามารถเรียนรู้ได้ง่ายอยู่แล้วเมื่อมารวมเข้ากับ library  
ซึ่งมีคนทำเอาไว้ให้ใช้งานอีกจำนวนหนึ่งทำให้เมื่อเปรียบเทียบความยาวของโค๊ดกับภาษาอื่นๆดูแล้วจะเห็นว่าสั้นมากๆเลย  
เราสามารถสร้าง application ที่ติดต่อกับ web หรือ internet technology ต่างๆได้อย่างรวดเร็วและง่ายมากสมชื่อ javascript จริงๆ 
  
**แต่** จากที่ลองใช้งานดูรู้สึกขัดใจชัดเจนในเรื่องความไม่เสถียรหลายๆเรื่อง  
มักจะมี error แปลกๆหรือปัญหาประหลาดๆโผล่มาแล้วก็หายไปเยอะมากทั้งๆที่ลองกับ ESP8266 ซึ่งน่าจะเป็นที่นิยมที่สุดในเวลานี้แล้ว  
(ถ้าจะเสถียรกว่านี้คงต้องใช้ hardware ของทาง ESPRUINO ที่เกริ่นไว้ในตอนต้นแล้วแหละ)  
รวมไปถึงเรื่องที่ ESP8266 [ไม่สามารถใช้งาน watchdog](http://forum.espruino.com/conversations/782/) ได้  
  
มันเป็นปัญหาใหญ่มากๆเลยนะสำหรับการออกแบบโปรดักซ์ในระดับมืออาชีพ  
เท่าที่คุยกับคนที่อาจจะเข้ามาเพราะจากกระแส IoT ฟีเวอร์ดูแล้วค่อนข้างเป็นห่วงมากที่ไม่ค่อยให้ความสำคัญในเรื่องนี้เท่าที่ควรเลย  
ทั้งๆที่มันเป็นเรื่องสำคัญมากที่สุดเรื่องหนึ่งในการออกแบบ embedded system ที่มักจะทำงานอยู่เงียบๆ  
หลายๆคนบอกว่าใช้งานรันเป็นปีๆแล้วไม่เห็นเป็นอะไร  
หลายคนบอกว่าไม่ได้ใช้ในโรงงานหรือที่ๆมีคลื่นหรือกระแสรบกวนแรงๆเลยไม่กังวล  
ซึ่งมันเป็นการปลูกฝัง mindset ที่อันตรายมากนะ ที่คุณรันเป็นปีๆรู้ได้ไงว่ามันทำงานได้อยู่จริงๆอยู่กี่ชั่วโมง?  
ลองนึกถึงเวลา internet จาก ISP ใช้งานไม่ได้ซักชั่วโมงนึงคนบ่นกันขนาดไหน?  
ลองนึกถึงเวลาที่คุณรีโมทมาดูกล้องที่บ้านแล้วเข้าดูไม่ได้มาซักสองชั่วโมงแล้วละ?  
ลองนึกถึงตู้เติมเงินที่สามวันดีสี่วันไข้ดูสิ  
ลองนึกถึงโปรดักซ์ที่เกี่ยวกับชีวิตคนดู...   
  
บ่นยาวไปหน่อย สรุปของสรุปก็คือ ณ เวลาที่เขียนผมมองว่า ESPRUINO ยังคงเป็นแพลตฟอร์มที่ฉาบฉวยไร้ตวามน่าเชื่อถือเลยแหละ  
อย่างมากก็ใช้ได้กับแค่งาน prototype ทำแบบเร็วๆเท่านั้น  
ถ้ายังแก้ปัญหาจุกจิกหรือทำให้มันรันแบบมีเสถียรภาพมากกว่านี้ไม่ได้คงไม่แนะนำศึกษาจริงจังหรือเอามาใช้ทำงานครับ  
เอาเวลาที่มีค่าและมีไม่เคยพอของเราไปใส่ในอะไรที่รับประกันคุณภาพได้จะคุ้มค่ากว่านะ  
    
