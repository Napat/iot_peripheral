from machine import Pin, PWM
import time

_led = Pin(4) # D2
_pwm = PWM(_led)

_fq = 0
_dc  = 100
_pwm.duty(_dc)

#change freq
for i in range(0,100,5):
	_pwm.freq(i)	
	time.sleep(0.5)

_pwm.duty(0)

for i in range(10,500,10) :
	_pwm.duty(i)
	time.sleep(0.2)
for i in range(500,0,-10) :
	_pwm.duty(i)
	time.sleep(0.2)	
_pwm.duty(0)
