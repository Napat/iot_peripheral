from machine import Pin
import time

_led = Pin(4,Pin.OUT,value=1)
_state = 0
for i in range(10):
	_state = not _state
	_led.value(_state)
	time.sleep(1)
