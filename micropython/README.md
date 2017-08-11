
# MicroPython
[MicroPython](https://micropython.org/) is a full Python compiler and runtime that runs on the bare-metal.   
After flashing micropython to microcontroller board, e.g. esp8266, you may get an *python interactive prompt* via serial port.  
By using [amphy](https://github.com/adafruit/ampy), you can put python source code to your board and execute program.   

# ESP8266 get start
## MicroPython firmware(binary at official website) 
Newbie step  
1. เข้าไปที่ https://micropython.org/download, select board [ESP8266](https://micropython.org/download#esp8266).
กด download .bin file ที่ต้องการมาเก็บไว้  
  
2. ก่อนจะติดตั้ง micropython ลงบน ESP8266 ควรจะต้องลบ flash memory ซะก่อน [erase ESP8266 flash memory](http://www.pratikpanda.com/completely-format-erase-esp8266-flash-memory/)    
โดยเฉพาะบอดที่เคยถูกแฟลชโปรแกรมใหญ่ๆลงไปมักจะพบปัญหาหลังจากโปรแกรม micropython เข้าไป     
ซึ่งในที่นี้จะใช้โปรแกรม `flash_download_tools` และ binary `blank_1MB.bin` เพื่อล้างโปรแกมเก่าออกจาก ESP8266  
เนื่องจาก ESP8266 ในที่นี้มี flash memory ขนาด 4MB ดังนั้นจะต้องทำการแฟลช `blank_1MB.bin` ลงไปยังตำแหน่ง address offset 0x000000, 0x100000, 0x200000 และ 0x300000 ดังรูป  
  
![alt tag](esp8266/res/howto_blank_1MB.jpg)  
  
3. ขั้นตอนการแฟลช binary ของ micropython ลงบน ESP8266 สามารถทำให้หลายวิธี   
3.1 สำหรับผู้ใช้ Linux แนะนำให้ใช้วิธีโปรแกรมด้วย esptool.py ซึ่งเป็น python module 
สามารถลงผ่าน pip ด้วยขั้นตอนในลิงค์ official [the tutorial](http://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html#deploying-the-firmware) ได้เลย    
3.2 สำหรับผู้ใช้ Windows มีโปรแกรมให้เลือกใช้หลากหลาย เช่น   
3.2.1 ใช้ esptool.py เหมือนของ linux ซึ่งจะต้องลง python ในเครื่องด้วย  
ซึ่งอาจจะลำบากนิดนึงสำหรับผู้ไม่ชอบ command line หรือไม่เคยใช้ python มาก่อน  
(แต่นี่เรากำลังจะใช้ micropython กันนะ!!)   
3.2.2 ใช้โปรแกรม [ESP8266Flasher](https://github.com/nodemcu/nodemcu-flasher/tree/master/Win64/Release) ส่วนตัวแนะนำให้ใช้โปรแกรมนี้เนื่องจากง่ายสำหรับผู้ใช้ทุกระดับ   
   
![alt tag](esp8266/res/flash8266.jpg)  
   
3.2.4 ใช้โปรแกรม [ESPFlashDownloadTool](https://espressif.com/en/support/download/other-tools) ที่ใช้ในขั้นตอนลบ flash นั่นแหละ **แต่ผมลองใช้โปรแกรมนี้ flash micropython ลง ESP8266 แล้วไม่มันเวิกแฮะ??? จริงๆก็ควรจะใช้ได้นะ อาจจะตั้งค่าอะไรผิดไป ช่างมันเถอะ**  
  
4. หลังจากโปรแกรมเสร็จเรียบร้อยให้ทำการปิดโปรแกรมที่ใช้แฟลชให้หมด(เพื่อการันตีว่าไม่มีใครใช้ serial port แล้ว)  
จากนั้นใช้โปรแกรม serial port terminal ต่างๆเช่น putty/Xshell/...  
ตั้งค่า baud rate: 115200 และเิร่มการคุย serial port เพื่อเข้าสู่ MicroPython prompt  
เราจะเรียกโหมดนี้ว่า REPL(Read Evaluate Print Loop) ซึ่งเราสามารถตรวจสอบความสมบูรณ์ของ MicroPython firmware ได้ดังนี้  
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

# MicroPython boot sequence
1. run boot.py(auto add by default firmware)
2. run main.py(can manual put to board by ampy)  

# ampy: put/get/run sourcecode.py to/from board
Ref: https://github.com/adafruit/ampy
1. Install ampy to your host(PC/Notebook) by user pip
```
# windows with python2
pip install adafruit-ampy

# windows with python3
pip3 install adafruit-ampy

# other platform see ref link 
```
2. Windows set env and list all files in your board
```
# set env: select comport
set AMPY_PORT=COM4
# list all files in your board
ampy ls
```
3. ampy put / run / get

To put app source code(demo_led.py) to board and run demo_led.py 
```
$ cat demo_led.py
#
# micropython use gpio port number in sourcecode 
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
```
$ ampy ls
boot.py
$ ampy put demo_led.py
$ ampy ls
boot.py
demo_led.py
$ ampy run demo_led.py
```

To get source file from board 
```
ampy get boot.py > boot.py
```

# Trick
## การ porting libs
สามารถไปดู sourcecode จากใน python ตัวปกติว่าเขียนยังไงแล้วนำมาใช้ได้นะ

# ข้อเสีย / ข้อสงสัยที่ยังสงสัย :P
- จะอัปเดท application(เช่น main.py) ผ่าน internet ได้มั้ยหว่า??  
--:> ทำเป็น bootloader ช่วยอัปเกรด partition MicroPython ทั้งก้อนไปเลยดีมั้ย?   
--:> สามารถเขียนโปรแกรม write .py ไปตรงๆได้เลยมั้ยหว่า ใช้ path ยังไงดี?  
--:> อาจจะต้องลองใช้ไอ้นี่ดูนะ https://learn.adafruit.com/micropython-basics-esp8266-webrepl/access-webrepl
- ใครๆก็สามารถดูด source code .py ออกจากบอดไปได้เลยสิ จะแปลงเป็น binary ได้มั้ยละเนี่ยะ??  
--:> python obfuscation น่าจะพอช่วยได้นิดนึงนะ  
- มี wathdog api รึเปล่า เหมือนบาง hardware เช่น esp8266 จะยังมีปัญหาเรื่องนี้อยู่นะ  
- เขียน c เพื่อสร้างเป็น libs ให้ใช้ได้มั้ยหนอ?   
