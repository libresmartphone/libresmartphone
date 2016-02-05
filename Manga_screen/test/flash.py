#!/usr/bin/python

import subprocess
import time
import Adafruit_BBIO.GPIO as GPIO

GPIO.setup("P8_14", GPIO.IN)
while 1:
	while GPIO.input("P8_14") == 0:
		time.sleep(0.1)
	
	subprocess.call("make -C /usr/src/manga-screen/edid write_edid", shell=True)
	subprocess.call("make -C /usr/src/manga-screen/touch/Atmel/Atmega32U4/LUFA-130303/Projects/MangaScreenRevA4/ upload", shell=True)

	subprocess.call("echo default-on >  /sys/class/leds/beaglebone\:green\:usr0/trigger", shell=True)
	subprocess.call("echo default-on >  /sys/class/leds/beaglebone\:green\:usr1/trigger", shell=True)
	subprocess.call("echo default-on >  /sys/class/leds/beaglebone\:green\:usr2/trigger", shell=True)
	subprocess.call("echo default-on >  /sys/class/leds/beaglebone\:green\:usr3/trigger", shell=True)

	time.sleep(1)

	subprocess.call("echo heartbeat >  /sys/class/leds/beaglebone\:green\:usr0/trigger", shell=True)
        subprocess.call("echo mmc0      >  /sys/class/leds/beaglebone\:green\:usr1/trigger", shell=True)
        subprocess.call("echo cpu0      >  /sys/class/leds/beaglebone\:green\:usr2/trigger", shell=True)
        subprocess.call("echo mmc1      >  /sys/class/leds/beaglebone\:green\:usr3/trigger", shell=True)
