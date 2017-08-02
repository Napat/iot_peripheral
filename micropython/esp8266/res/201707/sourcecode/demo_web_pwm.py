import usocket
from machine import Pin, PWM

def map_val(self,x,in_min,in_max,out_min,out_max):
	if x < in_min:
		return out_min
	out =  int((x - in_min) * (out_max - out_min) / (in_max - in_min) ) 
	return out + out_min	
			
def write(angle):
	if 0 <= angle <= 180 :
		duty = map_val(angle,0,180,33,122)
	_servo.duty(duty)

_servo = PWM(Pin(5)) #D1
_servo.freq(50)

#create server
_addr = ('0.0.0.0',8080)
_serv_sock = socket.socket(socket.AF_INET,	socket.SOCK_STREAM)
_serv_sock.bind(_addr)
_serv_sock.listen(1) #accepts only one client at a time
