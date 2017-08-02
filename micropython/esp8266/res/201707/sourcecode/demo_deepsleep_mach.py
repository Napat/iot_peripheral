import machine

#create real time clock
_rtc = machine.RTC()

_rtc = irq(trigger = _rtc.ALARM0, wake = machine.DEEPSLEEP)
_rtc.alarm(_rtc.ALARM0,10*1000) #wake up after 10 seconds

#put machine to deepsleep mode
machine.deepsleep()

