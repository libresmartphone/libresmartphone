#!/usr/bin/python

import subprocess
import time
import Adafruit_BBIO.GPIO as GPIO

GPIO.setup("P8_13", GPIO.IN)
while 1:
	
	while GPIO.input("P8_13") == 0:
		time.sleep(0.1)
	print "starting ts_test"	
	subprocess.call("pkill ts_test", shell=True)
	subprocess.Popen("TSLIB_TSDEVICE=/dev/input/event1 /usr/local/bin/ts_test", shell=True)
	print "started ts_test"
