from machine import Pin

def callback(p):
	print(p.value())
	
reed = Pin(15,Pin.IN)

reed.irq(trigger = Pin.IRQ_RISING,handle = callback)
