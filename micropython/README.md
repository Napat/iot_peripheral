
# MicroPython
[MicroPython](https://micropython.org/) is a full Python compiler and runtime that runs on the bare-metal.   
After flashing micropython to microcontroller board, e.g. esp8266, you may get an *python interactive prompt* via serial port.  
By using [amphy](https://github.com/adafruit/ampy), you can put python source code to your board and execute program.   

# ESP8266 get start
## MicroPython firmware(binary at official website) 
Newbie step  
1. Go to https://micropython.org/download, select board [ESP8266](https://micropython.org/download#esp8266).
Then download .bin file.
2. Erase ESP8266 flash memory  
Before flashing microPython firmware *YOU SHOULD* [erase ESP8266 flash memory](http://www.pratikpanda.com/completely-format-erase-esp8266-flash-memory/).
To clean esp8266 flash memory(4MB) by using `blank_1MB.bin` you have to flash for 4 times,
to the address offset 0x000000, 0x100000, 0x200000 and 0x300000.  
3. Flashing binary to your board
3.1 For linux user, I prefer to use esptool.py as described in [the tutorial](http://docs.micropython.org/en/latest/esp8266/esp8266/tutorial/intro.html#deploying-the-firmware).  
3.2 For Windows user, there are many software to flashing your board.  
3.2.1 [ESP8266Flasher](https://github.com/nodemcu/nodemcu-flasher/tree/master/Win64/Release)   
3.2.2 [ESPFlashDownloadTool](https://espressif.com/en/support/download/other-tools)  
4. Access python interactive prompt via serial port(baud rate: 115200)
Additionally, you can check the firmware integrity from a MicroPython prompt (assuming you were able to flash it and --verify option doesn’t report errors):
```
import esp
esp.check_fw()
print("Hello World!")
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
- ใครๆก็สามารถดูด source code .py ออกจากบอดไปได้เลยสิ จะแปลงเป็น binary ได้มั้ยละเนี่ยะ??  
--:> python obfuscation น่าจะพอช่วยได้นิดนึงนะ  
- มี wathdog api รึเปล่า เหมือนบาง hardware เช่น esp8266 จะยังมีปัญหาเรื่องนี้อยู่นะ  
- เขียน c เพื่อสร้างเป็น libs ให้ใช้ได้มั้ยหนอ?   
