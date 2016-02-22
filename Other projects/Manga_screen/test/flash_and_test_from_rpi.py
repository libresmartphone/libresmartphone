import RPi.GPIO as GPIO
import time
import subprocess
import signal

leds = [4,17,22,10,9,11]

def setup(): 
    leds = [4,17,22,10,9,11]
    GPIO.setmode(GPIO.BCM)
    GPIO.setup(7, GPIO.IN)
    for x in range(6):
        GPIO.setup(leds[x], GPIO.OUT)
        GPIO.output(leds[x], False)

def exit():
    led_off([0, 1, 2, 3, 4, 5])
    GPIO.cleanup()

def test():
    subprocess.call("pkill ts_test", shell=True)
    subprocess.Popen("TSLIB_TSDEVICE=/dev/input/event0 /usr/bin/ts_test", shell=True)    

def edid():
    return subprocess.call("make -C /home/pi/manga-screen/edid write_edid", shell=True)

def flash():
    return subprocess.call("make -C /home/pi/manga-screen/touch/Atmel/Atmega32U4/LUFA-130303/Projects/MangaScreenRevA4/ upload", shell=True)    

def led_on(nr):
    if isinstance(nr, list):
        for x in nr:
            GPIO.output(leds[x], True)
    else:
        GPIO.output(leds[nr], True)

def led_off(nr):
    if isinstance(nr, list):
        for x in nr:
            GPIO.output(leds[x], False)
    else:
        GPIO.output(leds[nr], False)



signal.signal(signal.SIGTERM, exit)
setup()

try:
    led_on(2)
    # Loop until users quits with CTRL-C
    while True :
        while GPIO.input(7)==0:
            time.sleep(0.1)
        led_off([0, 1, 3, 4, 5])
	led_on(3)
        if edid() == 0:
	    led_on(1)
	else:
	    led_on(4)
        if flash() == 0:
	    led_on(0)
	else:
	    led_on(5)
	test()

except KeyboardInterrupt:
    exit()
