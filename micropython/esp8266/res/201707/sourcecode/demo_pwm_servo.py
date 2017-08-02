from machine import Pin, PWM
import time

_servo = Pin(4) # D2
_pwm = PWM(_servo)

_fq = 50
_dc  = 120
_pwm.freq(_fq)
_pwm.duty(_dc)

for _dc in range(30,122,1):
	_pwm.duty(_dc)
	time.sleep_ms(10)





