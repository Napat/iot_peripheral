import socket, dht, time
from machine import Pin

#create sensor
_dht22 = dht.DHT22(Pin(12))

#create server
_addr = ('0.0.0.0',50000) #0.0.0.0 means "any IP"
_serv_sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
try:
	_serv_sock.bind(_addr)
except:
	_serv_sock.close()
	_serv_sock.bind(_addr)
	
_serv_sock.listen(3) #accepts only one client at a time

try:
	while True: # loop for accept request
		#get client socket and address
		_cli,_addr = _serv_sock.accept() 
		
		#convert client socket to file object
		_cli_file = _cli.makefile('rwb',0) # 
		while True :
			#traverse to end of file
			_line = _cli_file.readline()
			if not _line or _line == b'\r\n':
				break
		#get sensor value		
		_dht22.measure()
		_t = _dht22.temperature()
		_h = _dht22.humidity()
		# HTML Response
		_html	= 'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'
		_html += """<!DOCTYPE html>
<html>
<body>
<h3>Web Report</h3>
<table>
<tr><th>Temperature :</th><td>{:.2f} C</td></tr>
<tr><th>Humidity :</th><td>{:.2f} %</td></tr>
</table>
</body>
</html>\n""".format(_t,_h)
		#write data to client
		_cli_file.write(_html)
		_cli.close()
		
		#to avoid CPU 100% usage
		time.sleep_ms(1000)	
except :
	print("Error")
	
finally :
	_serv_sock.close()
