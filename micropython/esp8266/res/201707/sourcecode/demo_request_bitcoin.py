import urequests 
import ujson
from machine import Pin, SPI
import time
import sh1106

class Nokia5110():
	def __init__(self,cs=2,dc=15,rst=0,backlight=12):
		_spi = SPI(1, baudrate=80000000, polarity=0, phase=0)
		_cs = Pin(cs)
		_dc = Pin(dc)
		_rst = Pin(rst)

		self._backlight = Pin(backlight, Pin.OUT, value=1)
		self._lcd = pcd8544.PCD8544(_spi, _cs, _dc, _rst)

		self._buf = bytearray((self._lcd.height // 8) * self._lcd.width)
		self._framebuf = framebuf.FrameBuffer1(self._buf, self._lcd.width, self._lcd.height)

	@property
	def dimension(self):
		return (self._lcd.width,self._lcd.height)
	
	def backlight(self,state=0): # 0:off, 1:on
		self._backlight.value(state)
		
	def text(self,text,x=0,y=0,color=1):
		self._framebuf.text(text, x, y, color)
		self._lcd.data(self._buf)
		
	def hline(self,x,y,w,c):
		self._framebuf.hline(x, y,w,c )
		self._lcd.data(self._buf)
		
	def scroll(self,xstep=0,ystep=0):
		self._framebuf.scroll(xstep,ystep)
		self._lcd.data(self._buf)	
	
	def lightup(self):
		self._framebuf.fill(1)
		self._lcd.data(self._buf)	
		
	def clear(self):
		self._framebuf.fill(0)
		self._lcd.data(self._buf)
		
	def write_buf(self):
		self._lcd.data(self._buf)




def show_date(date,dur):
	nk5110.clear()	
	sp = date.split(" ")
	#sp = M D Y T UTC
	nk5110.text("BTC Price",1,0,1)	
	nk5110.hline(1,8,nk5110.dimension[0],1)
	nk5110.text(sp[0]+" "+sp[1],1,25,1)	
	nk5110.text(sp[2],1,35,1)
	nk5110.text(utc2local(sp[3]),1,15,1)
	time.sleep_ms(dur)		
		
def show_price(data,dur):
	nk5110.clear()	
	nk5110.text("1BTC (USD)",1,0,1)	
	nk5110.hline(1,8,nk5110.dimension[0],1)
	#nk5110.text("USD ",1,25,1)
	nk5110.text(precision(data['usd'],2),5,25,1)	
	time.sleep_ms(dur)		
	nk5110.clear()
	
	nk5110.text("1BTC (EUR)",1,0,1)	
	nk5110.hline(1,8,nk5110.dimension[0],1)
	#nk5110.text("EUR ",1,25,1)		
	nk5110.text(precision(data['eur'],2),5,25,1)	
	time.sleep_ms(dur)		
	nk5110.clear()

	nk5110.text("1BTC (GBP)",1,0,1)	
	nk5110.hline(1,8,nk5110.dimension[0],1)
	#nk5110.text("GBP ",1,25,1)
	nk5110.text(precision(data['gbp'],2),5,25,1)	
	time.sleep_ms(dur)		
	nk5110.clear()

def precision(num,prec=2):
	sp = num.split(".")
	return sp[0] +"."+ sp[1][:prec]

def utc2local(utc):
	sp = utc.split(':')
	h = int(sp[0])+7
	return str(h)+":"+sp[1]+":"+sp[2]


nk5110 = Nokia5110()

for i in range(3):
	_bct_json = urequests.get('http://api.coindesk.com/v1/bpi/currentprice.json').json()
	_time = _bct_json['time']['updated']
	_price = {"usd":_bct_json['bpi']['USD']['rate'],"eur":_bct_json['bpi']['EUR']['rate'],"gbp":_bct_json['bpi']['GBP']['rate']}
	nk5110.clear()
	nk5110.backlight(1)
	show_date(_time,5000)
	show_price(_price,5000)
	nk5110.clear()		
	nk5110.backlight(0)
	time.sleep_ms(10000)





