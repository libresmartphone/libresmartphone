This page contains the software used in the open hardware smartphone (libresmartphone) and other projects files and documentation that can be useful to develop it. In the future it will have the mechanical (Freecad) and Electronical (Kicad) designs to make it. Visit http://libresmartphone.com and https://hackaday.io/project/6310-libresmartphone for more information.

# Description

Libresmartphone is a smartphone that can be connected to a bigger screen and be used as a desktop computer to edit documents, watch videos, listen to music, edit images and videos and much more.

When it is finished it will have a 6 inch screen, hdmi output, camera, bluetooth, wifi, GPS, 3G or 4G, GSM (to receive and send/make SMS/calls). It will also have a microusb that will allow you to connect your printer and other gadgets/ peripherials.

It will be open software and open hardware to let other users study, change and improve the software and the hardware.

If you want a longer battery life, easy repairs, make it more durable or modify it according to your needs this is the smartphone you need.

If you are concerned by the mass surveillance the goverment makes you will be able to modify the smartphone to put hardware kill switches to the camera, GPS, 3G, GSM... easily. 

# Details

For years I had been following the openmoko project and the neo900 smartphone. I wanted to have a smartphone capable of running open software.

I thought that the NeoFreerunner had a very small screen, but I liked (and like) the neo900 a lot.

The libresmartphone project began when Adafruit released their first Fona the 7 of July of 2014. It was the first time I thought that I could achieve to make a smartphone.

In the following months I started searching for information on how to make what I desired. And I finally bought the Fona.

I connected the arduino UNO with the Fona... and it was like magic! I couldn't believe that adafruit could make things so easy.

Then I started searching for all the other components I needed to make a smartphone: Touchscreen, battery, etc.

When I had all the components I needed to make a prototype I started looking for a software to make it work. I found software that only could run the call and SMS software without being able to use all the other applications that I needed, like text editor, browser, etc.

I looked several programming languanges and decided that I would be using python and PyQt to make the software. The libresmartphone software has 3 tabs: Call, SMS and configuration.

At the present time I am working on the gps, the camera, the 3G module and making libresmartphone smaller and more open.

For the GPS I am using the Navit open source navigation system with the openstreet maps, I have to make the gpsd work with the Fona and it will work as a normal navigation system.

For the camera I am making a python/PyQt software.

To make the libresmartphone smaller and more open I purchased the Udoo Neo. When I receive it I will verify if it works as desired. Udoo Neo is open hardware and as the creators describe it is a Raspberry Pi + Arduino + Wi-Fi + BT 4.0 + Sensors.

To make it more open I also purchased the capacitive manga screen. It is both open hardware and firmware.

For the 3G module I am using the Fona 3G, I only have to solder it and see if it works well.

The more I work in this project, the more I fall in love with it and more time each day I spend improving it. It is a vicious circle!

When all the software and hardware available works as desired I am planning on making my own board using Freescale and ATMEL chips to reduce the size and fit all libresmartphone in a smaller case.

