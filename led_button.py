import RPi.GPIO as GPIO
import time

GPIO.setmode(GPIO.BCM)
LED_4=4
LED_5=5
LED_6=6


GPIO.setup(LED_4, GPIO.OUT)
GPIO.setup(LED_5, GPIO.OUT)
GPIO.setup(LED_6, GPIO.IN)

while True:
    pin6 = GPIO.input(LED_6)
    if pin6 == 1:
        print "Button 6 is release"
        GPIO.output(LED_4, True)
        GPIO.output(LED_5, False)
    else:
        print "Button 6 is push"
        GPIO.output(LED_4, False)
        GPIO.output(LED_5, True)
    
    time.sleep(1)    
    
    #GPIO.output(LED_4, True)
    #GPIO.output(LED_5, False)
    #GPIO.output(LED_6, False)
    #time.sleep(0.5)

    #GPIO.output(LED_4, False)
    #GPIO.output(LED_5, True)
    #GPIO.output(LED_6, False)
    #time.sleep(0.5)
