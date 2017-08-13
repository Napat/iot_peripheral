
# Python  
เป็นภาษาที่ได้รับความนิยมอย่างสูงเนื่องจากตัวภาษานั้นเข้าใจได้ง่าย Learning curve ต่ำและมีไลบรารี่ให้มากมายในหลากหลายสาขา ในปัจจุบันจึงมีการดึงเอา Python มาตรฐานมาตัดแต่งบางส่วนออกไปให้เหมาะสมกับทรัพยากรที่ microcontroller มีอยู่ซึ่งรู้จักกันในชื่อ [MicroPython](https://micropython.org/)  

# MicroPython
ซัพพอตบอดมาตรฐานที่ได้รับความนิยมอย่างมากเช่น ESP8266 และ[อื่นๆ](https://micropython.org/download#other)  
หลังจากติดตั้ง MicroPython ลงใน microcontroller board เช่น ESP8266 แล้ว เราจะสามารถติดต่อกับ *python interactive prompt* ผ่าน serial port เพื่อรันคำสั่งทีละบรรทัดแบบ python shell ได้ทันที  
นอกจากนั้นเรายังสามารถนำเอา python script ที่เป็นไฟล์ลงไปรันในบอดได้แต่จะต้องติดตั้ง tools เพิ่มเติมเช่น WebREPL, 
[amphy](https://github.com/adafruit/ampy) , [mpfshell](https://github.com/wendlers/mpfshell), [uPyCraft](https://github.com/DFRobot/uPyCraft)   

# ESP8266 get start
## MicroPython firmware(binary at official website) 
Newbie step  
1. เข้าไปที่ https://micropython.org/download, select board [ESP8266](https://micropython.org/download#esp8266).
กด download .bin file ที่ต้องการมาเก็บไว้  
  
2. การแฟลช binary ของ micropython ลงบน ESP8266 สามารถใช้งานได้หลากหลายโปรแกรม  
ผู้ใช้งาน Windows ส่วนใหญ่มักจะชื่นชอบ gui tools มากกว่าการใช้งาน tools ประเภท command line  
ซึ่งก็มีโปรแกรมสำหรับแฟลช firmware ให้ใช้งานอยู่หลายโปรแกรม ตัวที่มีคนใช้เยอะๆ เช่น  
 - [ESP8266Flasher](https://github.com/nodemcu/nodemcu-flasher/tree/master/Win64/Release) 
 - [ESPFlashDownloadTool](https://espressif.com/en/support/download/other-tools)  
  
เท่าที่ลองใช้ firmware ของ micropython แล้วส่วนตัวจะเจอปัญหากับบอดที่เคยใช้งานมาก่อนหน้าแล้วซึ่งถูกแฟลชโปรแกรมใหญ่ๆลงไปก่อนหน้า เมื่อแฟลช firmware micropython ลงไปแล้ว
มักจะมี error แปลกๆโผล่ออกมาในตอนใช้งานด้วย ดังนั้นควรจะเคลีย flash memory ซะก่อน [erase ESP8266 flash memory](http://www.pratikpanda.com/completely-format-erase-esp8266-flash-memory/) โดยการใช้ blank binary `blank_1MB.bin` 
ลงไปยังตำแหน่ง address offset 0x000000, 0x100000, 0x200000 และ 0x300000 เพื่อล้างโปรแกมเก่าออกจาก flash ของ ESP8266   
  
ใครชอบใช้ ESP8266Flasher ก็ลองดูตัวอย่างการตั้งค่าได้ตามรูปเลยครับ (ส่วนตัวพอใช้โปรแกรมนี้หากทำ blank binary มักเจอปัญหาเลยชอบใช้ ESPFlashDownloadTool มากกว่าครับ)  
  
![alt tag](esp8266/res/img/ESP8266Flasher8266.jpg)  
** issue: หลังจากใช้ ESP8266Flasher แฟลชเสร็จให้ดึงสาย usb ออกแล้วเสียบใหม่ทีนึงถึงจะใช้งานได้ครับ **
  
สำหรับโปรแกรมแฟลชเฟริมแวร์วิธีที่ผมชอบใช้มากกว่าคือ [ESPFlashDownloadTool](https://espressif.com/en/support/download/other-tools) 
ซึ่งสามารถเขียนทับค่าเก่าด้วย blank binary `blank_1MB.bin` เพื่อล้างโปรแกมเก่าออกจาก ESP8266 ได้อย่างไม่มีปัญหา  
อีกทั้งไม่ต้องดึงสาย usb ออกทีนึงหลังจากแฟลช firmware แบบโปรแกรม ESP8266Flasher ครับ(กดปุ่ม reset ได้เลย)  
ความรู้สึกส่วนตัว: ผมว่าจะแฟลชได้เร็วกว่า ESP8266Flasher ด้วย การตั้งค่าสามารถดูได้จากรูปเลยครับ  
  
![alt tag](esp8266/res/img/eps8266DownloadTool.jpg)  
  
สำหรับผู้ใช้งาน Linux หรือชื่นชอบการใช้ผ่าน command line และพอมีความรู้เกี่ยวกับ python ผมแนะนำใช้ไปใช้โปรแกรม
`esptool.py` ซึ่งเป็น python module สามารถลงผ่าน pip ตามขั้นตอนในลิงค์ [official the tutorial](http://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html#deploying-the-firmware) ได้เลยครับ  
ผู้ใช้กลุ่มนี้น่าจะมีความรู้พอเอาตัวรอดอยู่แล้วแหละเนอะ (๕๕)  
  
3. ทดสอบใช้งาน MicroPython ผ่าน serial port กัน  
หลังจากแฟลชโปรแกรมเสร็จเรียบร้อย อาจจะปิดโปรแกรมที่ใช้แฟลชให้หมดก่อนก็ได้ครับเพื่อการันตีว่าไม่มีใครใช้ serial port อยู่แล้ว(จริงๆแล้วในกรณีที่แฟลชเสร็จสมบูรณ์มันจะเลิกใช้ให้เองอยู่แล้วแหละ)  
จากนั้นใช้โปรแกรม serial port terminal ต่างๆเช่น putty/Xshell/...  
ตั้งค่า baud rate: 115200 และเปิด serial port เพื่อเข้าสู่ MicroPython prompt  
เราจะเรียกโหมดนี้ว่า REPL(Read Evaluate Print Loop) เราสามารถตรวจสอบความสมบูรณ์ของ MicroPython firmware ได้ดังนี้  
```
>>> import esp
>>> esp.check_fw()
size: 612028
md5: 7653de1969a66ed01e27fd3b18b71aa6
True
>>> print("Hello World!")
Hello World!
>>> import sys
>>> print (sys.version)
3.4.0
>>> 
```

# ทำความเข้าใจ MicroPython boot sequence แบบรวดเร็ว  
1. โปรแกรม boot.py(ไฟล์นี้จะมีอยู่แล้วใน default firmware) จะถูกรันเป็นไฟล์แรกเมื่อ power on  
2. โปรแกรม main.py จะถูก execute โดยอัตโนมัติหลังจากจบการทำงานของ boot.py  
เราสามารถใส่ไฟล์ main.py เข้าไปในบอดได้ด้วยโปรแกรมต่างๆเช่นใช้ ampy ซึ่งจะกล่าวถึงในขั้นตอนถัดไป  
  
# [Ampy](https://github.com/adafruit/ampy)  
คือเครื่องมืออย่างง่ายสำหรับติดต่อกับ MicroPython board เช่น put/get/run sourcecode.py ผ่าน serial connection  
Note: Advance tool/Advance user อาจจะไปใช้ [mpfshell](https://github.com/wendlers/mpfshell) ซึ่งมีความสามารถสูงกว่าเช่น   
ซับพอตการสื่อสารผ่าน serial line/Websockets(ESP8266) และ Telnet(สำหรับ WiPy borad)  
  
1. ติดตั้ง python to your host(PC/Notebook)  
2. ติดตั้ง ampy module ด้วย pip  
**Windows user ควรรัน cmd ด้วยสิทธิของ administrator**  
**ใครใช้ virtualenv เป็นก็แนะนำให้ใช้ไปเลยนะครับ แต่คงไม่อธิบายตรงนี้เดี๋ยวจะยาวเกินไป**  
```  
# Windows with python2
> pip install adafruit-ampy
  
# Windows with python3
> pip3 install adafruit-ampy

# Other platform see: https://github.com/adafruit/ampy
```
```
> pip list
adafruit-ampy (1.0.1)
click (6.7)
ecdsa (0.13)
esptool (2.0.1)
pip (9.0.1)
pyaes (1.6.0)
pyserial (3.4)
setuptools (36.2.7)
wheel (0.29.0)
```
3. ตรวจสอบการติดต่อสื่อสารกับ board ด้วยการแสดง python script ที่อยู่บน board   
สำหรับผู้ใช้งาน Windows ให้ทำการตั้งค่า env ก่อนเพื่อการใช้งานที่ง่าย  
**อย่าลืมปิดโปรแกรมอื่นๆที่ใช้ Serial port** ก่อนรัน ampy  
```
# Windows user please set env to select comport
> set AMPY_PORT=COM6

# list all files in your board
> ampy ls
boot.py

```
4. ทดสอบคำสั่ง ampy put / run / get
ทำการเขียนโปรแกรมไฟกระพริบ (demo_led.py) ให้เสร็จ จากนั้นทำการทดสอบเอาโปรแกรมไปรันบนบอดดังนี้ 
ตัวอย่างโปรแกรม demo_led.py
```
$ cat demo_led.py  # หรือ type demo_led.py สำหรับ Windows user
#
# micropython use gpio port number to input to function parameter 
# from esp8266 link: https://github.com/nodemcu/nodemcu-devkit
# you will found that led on board is plug with GPIO16
#

from machine import Pin
import time

_led = Pin(16,Pin.OUT,value=1)
_state = 0
for i in range(10):
	_state = not _state
	_led.value(_state)
	time.sleep(1)

```
ทดสอบส่งโปรแกรมเข้าไปในบอดและรันโปรแกรมด้วยคำสั่งดังนี้  
```
$ ampy ls
boot.py
$ ampy put demo_led.py
$ ampy ls
boot.py
demo_led.py
$ ampy run demo_led.py
```

สำหรับการดึงไฟล์จาก board มาไว้ในเครื่องเราจะใช้ทริกนิดหน่อยดังนี้  
```
ampy get boot.py > boot.py
```
  
# การเปิดใช้งาน WebREPL และตั้งค่า password [Reference](https://learn.adafruit.com/micropython-basics-esp8266-webrepl/access-webrepl)
WebREPL คือการใช้งาน REPL ผ่าน network ซึ่งโดยค่า default แล้วฟีเจอร์นี้จะถูกปิดอยู่ เราจะต้องใช้ REPL ในการตั้งค่าเพื่อเปิดใช้งานซะก่อนดังนี้  
```
>>> import webrepl_setup
WebREPL daemon auto-start status: disabled

Would you like to (E)nable or (D)isable it running on boot?
(Empty line to quit)
> E
To enable WebREPL, you must set password for it
New password: password
Confirm password: password
Changes will be activated after reboot
Would you like to reboot now? (y/n) y

```
หลังจาก reboot เสร็จจะมี wifi radio ขึ้นมาชื่อ `MicroPython-xxxxxx` ให้ใช้ password: **micropythoN** เพื่อ connect wifi ดังกล่าว  
  
![alt tag](esp8266/res/img/WebREPL_wifi.jpg)  
  
สำหรับการติดต่อเข้าไปยัง Webrepl ของ esp8266 นั้นจะวิ่งผ่าน websocket ดังนั้นเราจำเป็นจะต้องมีโปรแกรม client เพื่อติดต่อเข้าไป
1. ในกรณีที่ host(PC/Notebook) ของเรายังวิ่งออก internet ได้ (เช่นออก internet ผ่านสาย lan & wifi ต่อเข้า MicroPython-xxxxxx)  
สามารถใช้ online client [click](http://micropython.org/webrepl/) ได้เลย  
  
![alt tag](esp8266/res/img/webrepl_client_online.JPG)   
  
2. ในกรณีที่ไม่สามารถเข้าถึง Internet พร้อมกับ connect wifi MicroPython-xxxxxx ให้ไปดาว์โหลด client มาไว้ในเครื่องก่อน [micropython/webrepl](https://github.com/micropython/webrepl)  
ตัวอย่างขั้นตอนการใช้ webrepl แบบรวดเร็วใน 3 ขั้นตอน  
1. Download https://github.com/micropython/webrepl/archive/master.zip  
2. Connect wifi MicroPython-xxxxxx  
3. Extract .zip และ เปิดไฟล์ webrepl.html ด้วย Chrome หรือ Firefox browser  
จบ เปิดมาก็ต้องใช้เป็นแล้วแหละ...    
  
# การตั้งค่า  WIFI Access Point (AP) name และ password ใหม่  
ชื่อ Default AP จะอยู่ในรูปแบบ `MicroPython-xxxxxx` และ password คือ  `micropythoN`  
เราสามารถตั้งค่าใหม่ได้ดังนี้  
```
>>> import network;
>>> ap = network.WLAN(network.AP_IF);
>>> print(ap.config('essid'));
MicroPython-0b4246
>>> ap.active(True);
>>> ap.config(essid='MyNewESP8266', authmode=network.AUTH_WPA_WPA2_PSK, password='mynewpassword');
>>> print(ap.config('essid'));
MyESP8266
>>> 
```

สำหรับผู้ใช้งาน Linux นั้นมา tools ที่มีความสามารถสูงกว่า ampy เช่นสามารถรับส่งไฟล์ผ่าน network ได้, ใช้งานโหมดหรือคำสั่งต่างๆได้หลากหลาย ให้ใช้งานอยู่ด้วย   
- [rshell](https://github.com/dhylands/rshell) **ณ.เวลาที่เขียนโปรแกรมนี้ยังไม่ support Windows 100%**  
- [mpfshell](https://github.com/wendlers/mpfshell) ตัวนี้ใช้กับ Windows ได้แต่พบปัญหาค่อนข้างมากมาย  

# IDE  
ทั้งนี้ทั้งนั้น Windows ก็มี GUI IDE ที่น่าจะถูกใจชาว Windows อยู่ตัวนึงชื่อว่า [uPyCraft](https://github.com/DFRobot/uPyCraft)  
สามารถกดโหลด uPyCraft.exe มาลองใช้ได้เลยครับ   
  
![alt tag](esp8266/res/img/uPyCraftGuiIDE.jpg)  
  
# Trick การเขียนโปรแกรม
## การ porting libs
- สามารถไปดู sourcecode จากใน python ตัวปกติว่าเขียนยังไงแล้วนำมาพอตใช้ได้นะ
- จะอัปเดท application(เช่น main.py) ผ่าน internet ทำได้ผ่าน WebREPL      
- โปรแกรม a.py สามารถเขียนโปรแกรม write b.py ไปตรงๆได้เลยเช่น 

```
fo = open("foo.txt", "w")
fo.write( "Python is a great language.\nYeah its great!!\n")
fo.close()
```

เนื่องจากมันเป็น interpreter ซึ่งดูแล้วเป็นอะไรที่ดูเปิดกว้างให้ทำอะไรได้หลายอย่างมากทั้งดีและไม่ดีเช่น    
สามารถเขียน code ไปอัปเกรด firmware ได้ง่ายๆเลยแต่ก็กลายเป็นความเสี่ยงที่จะถูก hack เช่นกัน  

ต้องระวังการถ้าโดนเข้าถึง WebREPL ให้ดีๆด้วย **จะต้องตั้งค่า password ให้แข็งแรงเลย**  
การตั้งค่า password WebREPL ใหม่ได้ดังนี้

```
import webrepl
webrepl._webrepl.password("yourNewPassword")
```

# คำถาม ?  
- ทำเป็น bootloader ช่วยอัปเกรด partition MicroPython ทั้งก้อนได้มั้ย?  
--:> คงต้อง compile micropython เองใหม่เลยแหละมั้งเนี่ยะ     
  
- source code .py สามารถแปลงเป็น binary ให้อ่านไม่ออกได้มั้ย?  
--:> python obfuscation ไปก่อนละกัน     

- มี wathdog api รึเปล่า  
--:> เหมือนบาง hardware เช่น esp8266 จะยังมีปัญหาเรื่องนี้นะ เป็นปัญหาใหญ่เลยนะ  

- เขียน c เพื่อสร้างเป็น libs ให้ใช้ได้มั้ยหนอ?   
--:> ไม่รู้ ยังไม่ได้หา  
  