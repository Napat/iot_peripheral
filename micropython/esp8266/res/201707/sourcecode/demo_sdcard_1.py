from machine import  Pin,SPI
import sdcard
import time
import os

#sd card must be Fat16 
hw_spi = SPI(1)
_cs = Pin(15) #D8

_card = sdcard.SDCard(hw_spi,_cs)

os.mount(_card,'/sdcard')
os.chdir('/sdcard')
with open("test.txt","rw") as f :
	f.write('Hello')
	
os.chdir('/')
os.umount('/sdcard')





