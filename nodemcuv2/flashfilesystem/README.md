
Flash layout
-----------------
```
    |--------------|-------|---------------|--|--|--|--|--|
    ^              ^       ^               ^     ^
    Sketch    OTA update   File system   EEPROM  WiFi config (SDK)
```    


SPI Flash File System for esp8266 
-----------------
พื้นที่ส่วน file system ของโมดูล esp8266 นั้นจะไม่ถูกแก้ไขใดๆในขั้นตอนการแฟลชไฟล์ Sketch ใหม่ทำให้เราสามารถนำพื้นที่ดังกล่าวมาใช้งานเพื่อเก็บค่า config ต่างๆได้   
SPIFF(SPI Flash File System) นั้นถูกออกแบบมาเพื่อใช้งานกับอุปกรณ์แบบ SPI NOR flash devices สำหรับ embedded devices ซึ่งจะกินทรัพยากร(ram) ต่ำ
โดย default แล้ว SPIFF ไม่ได้ซับพอทการทำ directories แต่เนื่องจากสามารถใส่เครื่องหมาย `/` เข้าไปที่ชื่อได้ทำให้สามารถใช้การเขียน function api ที่ช่วยให้สามารถพิจารณาแยกชื่อไฟล์กับ path ออกจากกันได้แบบ api มาตรฐาน ทั้งนี้มีข้อควรระวังดังต่อไปนี้ 

*[ระวัง](https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst#file-system-limitations)*  
1. ชื่อ path จะต้องขึ้นต้นด้วย `/` เสมอ  
2. ชื่อ path + filename ห้ามยาวเกิน 31 ตัวอักษร เช่น 
- `/res/imgs/bird.jpg` นับเป็น 18ต ัวอักษร สามารถใช้งานได้ปกติ
- `/website/images/bird_thumbnail.jpg`นับเป็น 34 ตัวอักษร ซึ่งยาวเกินไป ใช้งานแล้วจะมีปัญหา  

ตัวอย่างโปรแกรม  
-----------------
- [open_rw](opem_rw): โปรแกรมอ่านเขียนและวนลูปข้อมูลจากไฟล์มาแสดงผล begin() , exists(), open(), close() , available(), readStringUntil(), remove(), seek()     

การเขียนพื้นที่ SPIFF ด้วยโปรแกรม arduino
------------------
เราสามารถออกแบบโครงสร้างและข้อมูลต่างๆให้เสร็จจากภายในเครื่อง pc/notebook แล้วค่อย upload ข้อมูลไปยัง Flash file system ได้โดยใช้โปรแกรม arduino แต่จะต้องติดตั้ง tool [ESP8266 filesystem uploader](https://github.com/esp8266/arduino-esp8266fs-plugin) เพิ่มเติม ขั้นตอนติดตั้งสามารถอ่านได้จากใน git repo ขั้นตอนโดยคร่าวๆคือ download ไฟล์มาจาก releases page จากนั้นสร้าง directory สำหรับ arduino tool เพิ่มเติม เช่น `C:\Users\Napat\Documents\Arduino\tools\ESP8266FS\tool` เป็นต้น แล้วค่อย copy ไฟล์ `esp8266fs.jar` ใส่ลงไป จากนั้น restart โปรแกรม arduino ใหม่  
  
ให้ทำการสร้าง project ใหม่ และเพิ่ม directory ชื่อ `<Sketch .ino dir>/data/` ไว้ที่เดียวกับโปรเจคนั้น แล้วจึงโยนไฟล์ต่างๆเข้าไปไว้ภายในนั้น(กรณีต้องการล้าง flash file system ให้ปล่อยให้เป็น directory เปล่าๆ) แล้วจึงสั่งอัปโหลดโดยการกดปุ่ม flash ให้เหมือนการอัปโหลดโปรแกรม Sketch ปกติแต่เปลี่ยนเมนูที่ใช้เป็น `Tools > ESP8266 Sketch Data Upload` ก็จะอัปโหลดได้  
Note: *อย่าลืมปิดหน้าต่าง serial port monitor ให้หมดก่อน*  

References
-----------
- [esp8266 FS doc: git]( https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst)
- [esp8266 FS doc: web](http://esp8266.github.io/Arduino/versions/2.0.0/doc/filesystem.html)
- [SPIFF FS arduino header](https://github.com/esp8266/Arduino/blob/master/cores/esp8266/FS.h#L125)
- [SPIFF official](https://github.com/pellepl/spiffs)
- [FTP access FS](https://diyprojects.io/esp8266-ftp-server-spiffs-file-exchange-rapid-development-web-server/#.WoE3dqiWaUk)
- [Arduino IDE direct access SPIFF](http://www.instructables.com/id/Using-ESP8266-SPIFFS/)  
