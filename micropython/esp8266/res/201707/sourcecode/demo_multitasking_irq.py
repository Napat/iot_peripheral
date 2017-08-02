from machine import Pin
import time

def callback(p):
	if p.value() == 0 :
		_led.value(1)	
		time.sleep(1)
		_led.value(0)

_sw = Pin(5,Pin.IN,Pin.PULL_UP) #D1
_led = Pin(4,Pin.OUT,value=0) #D2
_led2 = Pin(0,Pin.OUT,value=0) #D3
_sw.irq(trigger = Pin.IRQ_FALLING, handler=callback)
for i in range(10):
	_led2.value(1)
	time.sleep_ms(1000)
	_led2.value(0)
	time.sleep_ms(1000)

