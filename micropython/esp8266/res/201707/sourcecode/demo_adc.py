from machine import  ADC
import time

_adc = ADC(0)

for  i in range(50):
	print(_adc.read())
	time.sleep_ms(250)
