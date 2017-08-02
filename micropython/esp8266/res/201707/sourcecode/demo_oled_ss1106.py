from machine import  Pin,I2C
from sh1106 import SH1106_I2C
import time

_i2c = I2C(scl=Pin(5),sda=Pin(4),freq=1000000)
_addr = _i2c.scan()
_display = SH1106_I2C(128,64,i2c=_i2c,addr=0x3c,res=None)
_display.reset()
_display.poweron()
_display.fill(0)
_display.text('Hello',5,5,1)
_display.show()
time.sleep(5)
_display.poweroff()





