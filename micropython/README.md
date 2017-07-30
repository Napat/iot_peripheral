
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
