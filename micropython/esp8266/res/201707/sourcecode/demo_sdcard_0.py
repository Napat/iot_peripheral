import os,sdcard
from machine import Pin, SPI

card = sdcard.SDCard(SPI(1),Pin(15))
os.umount("/")
vfs = os.VfsFat(card)
os.listdir()
