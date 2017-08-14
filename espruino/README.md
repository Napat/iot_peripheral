
# เกริ่นนำ  
เดิมทีแล้ว Javascript นั้นมักใช้เพื่อพัฒนางานในฝั่งของ Front-end แต่ในยุคปัจจุบันได้มีการทำเครื่องมือเพื่อพัฒนาให้นักพัฒนาโปรแกรมสามารถข้าม 
platform กันได้ออกมาหลากหลายชนิดเพื่อลดเวลาในการเรียนรู้ของนักพัฒนาทั้งหน้าเก่าและหน้าใหม่ลง ไม่เว้นแต่ฝั่งของ Embedded system หรือ Internet of Things 
ได้มีคนพัฒนาเครื่องมือเพื่อนำเอา Javascript มาใช้งานในอุปกรณ์ Microcontroller เครื่องมือหนึ่งในนั้นมีชื่อว่า [Espruino](http://www.espruino.com)   

# Espruino firmware  
เดิมทีแล้ว Espruino(software) ถูกพัฒนาให้ใช้งานบนบอร์ดฮาร์แวร์(hardware)ของตัวเอง สามารถสั่งซื้อได้จาก [link](http://www.espruino.com/Order) 
แต่ hardware ดังกล่าวไม่ได้จะได้รับความนิยมมากนักจึงได้มีการพอท software ให้สามารถทำงานได้บน hardware ที่หลากหลายมากขึ้น 
สามารถดูรายการของอุปกรณ์ที่ซัพพอตได้ที่ [link](http://www.espruino.com/Other+Boards)  
  
จะเห็นว่า ESP8266 เป็นฮาร์แวร์หนึ่งที่ได้รับความนิยมอย่างสูงและได้รับการพอท Espruino โดยมี firmware ให้ดาว์โหลดมาใช้งานได้จากเว็บได้เลย 
ในบทความนี้จะใช้งาน ESP8266v2 ซึ่งมี Flash 4MB เป็นหลักเนื่องจากหาง่ายและราคาคุ้มค่าที่สุด(ณ วันที่เขียน)นะครับ   
  
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
หากท่านใช้ tools อื่นๆสามารถดูตัวอย่างการตั้งค่าได้จากในรูปด้านล่างซึ่งใช้ ESP8266 Download Tool เลย 
หลังจากตั้งค่าให้เหมือนตามรูปเสร็จก็กดปุ่ม START ด้านล่างซ้ายเลยครับ  
  
![alt tag](res/img/flashdownloadertool.jpg)  
  
เมื่อแฟรช firmware เสร็จแล้ว(Download Panel 1 ขึ้นสีเขียวพร้อมคำว่า Finish) ให้ทำการกดปุ่ม reset ที่อยู่บนบอด ESP8266v2 ครั้งนึง
(Flash tool อื่นบางตัวอาจจะต้องตัดไฟบอร์ดด้วย) ก็จะสามารถติดต่อ Javascript console ผ่าน Serial port terminal ต่างๆเช่น putty ได้เลยครับ
ให้ตั้งค่า `Baud rate=115200` แล้วทดสอบด้วย javascript syntax ได้เลยเช่น
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
เปิด Google Chrome browser ขึ้นมาและเค้นหาด้วยคำว่า `Espruino Web IDE chrome.google.com` หรือ [click แรงๆ](https://chrome.google.com/webstore/detail/espruino-web-ide/bleoifhkdalbjfbobjackfdifdneehpo) จากนั้นให้ทำการติดตั้งให้เรียบร้อย  
  
![alt tag](res/img/EspruinoWebIDEInstall.jpg)  
  
เปิดโปรแกรม Espruino Web IDE ขึ้นมาและคลิ๊กเข้าไปที่ Settings(รูปเฟื้องบริขวามือบน) และตั้งค่า Baud rate ให้เท่ากับ 115200 ตามรูปก็เสร็จสิ้นการตั้งค่าเรียบร้อย  

![alt tag](res/img/espruinowebide_setup.jpg)  
  
ปิดโปรแกรม Serial port terminal อื่นๆให้หมด และทำการ connect โดยการกดปุ่มรูปปั๊กส้มๆด้านบนซ้ายและเลือก COM PORT ที่ใช้งาน   

![alt tag](res/img/espruinowebide_interface.jpg)  
  
หลังจากขั้นตอนนี้เราก็จะสามารถใช้งาน Espruino javascript console ผ่านโปรแกรม Espruino Web IDE ได้แล้ว ซึ่งเราสามารถเขียนโปรแกรมฝั่งและสั่งลงไปรันบนบอร์ดได้ด้วยปุ่ม Send to Espruino  
  

