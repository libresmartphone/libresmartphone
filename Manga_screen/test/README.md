Use this script to flash the EEPROM of the Manga Screen and upload the latest firmware. 
You need these packages: 

This script is meant to start automatically as a part of a testing/flashing jig. 

sudo apt-get install dfu-programmer make python-smbus i2c-tools read-edid gcc-avr avr-libc autoconf pkg-config libtool build-essential python-dev python-pip

cd /usr/src
git clone https://bitbucket.org/intelligentagent/manga-screen/
cd manga-screen/edid
git clone https://github.com/bulletmark/edid-rw

cd /usr/src
git clone https://github.com/kergoth/tslib
cd tslib 
./autogen.sh
./configure --prefix=/usr
make
make install
nano /usr/local/etc/ts.conf
remove # on raw input 



cp manga-screen-flash.service /lib/systemd/system
cp manga-screen-test.service  /lib/systemd/system
systemctl enable manga-screen-flash
systemctl enable manga-screen-test

