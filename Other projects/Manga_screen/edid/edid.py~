#!/usr/bin/python
'''
edid.py File for making EDID information. 

Author: Elias Bakken
email: elias.bakken@gmail.com
Website: http://www.hipstercircuits.com
License: BSD

You can use and change this, but keep this heading :)
'''

# Extended display identification data
# All of this has been taken from wikipedia. 


import struct
import array

# 0-19
man_id      = "IAG" # Manufacturer ID, three letters, upper case
prod_code   = 1     # Manufacturer product code. 16-bit number, little-endian.
serial_nr   = 1     # Serial number. 32 bits, little endian.
week_of_man = 25    # Week of manufacture, 8 bits. 
year_of_man = 2013  # Year of manufacture
edid_ver    = 1     # Version
edid_rev    = 3     # Revision

# 20-24
dig_input   = 1     # Digital input, if set the following apply
vesa_compat = 1     # VESA DFP 1.x compatible 
# dig_input = 0     # Analog input. If clear, the following bit definitions apply:
video_white = 0     # Video white and sync levels, relative to blank:
blank_black = 0     # Blank-to-black setup (pedestal) expected
sep_sync    = 0     # Separate sync supported
comp_sync   = 0     # Composite sync (on HSync) supported
sync_on_grn = 0     # Sync on green supported
vsync_serr  = 0     # VSync pulse must be serrated when composite or sync-on-green is used.

max_hor_img = 10    # Maximum horizontal image size, in centimetres (max 292 cm/115 in at 16:9 aspect ratio)
max_vert_img= 6     # Maximum vertical image size, in centimetres. If either byte is 0, undefined (e.g. projector)
disp_gamma  = 120   # Display gamma, datavalue  
DPMS_stnd   = 1     # DPMS standby supported
DPMS_susp   = 1     # DPMS suspend supported
DPMS_off    = 1     # DPMS active-off supported
disp_type   = 0     # Display type (digital): 00 = RGB 4:4:4; 01 = RGB 4:4:4 + YCrCb 4:4:4; 
                    # 10 = RGB 4:4:4 + YCrCb 4:2:2; 11 = RGB 4:4:4 + YCrCb 4:4:4 + YCrCb 4:2:2
disp_typ_an = 0     # Display type (analog): 00 = Monochrome or Grayscale; 01 = RGB color; 10 = Non-RGB color; 11 = Undefined
std_RGB     = 1     # Standard sRGB colour space.
pref_timing = 1     # Preferred timing mode specified in descriptor block 1.
GTF_sup     = 1     # GTF supported with default parameter values.

# 25-34 - Chromaticity coordinates.
red_x   = 0.633
red_y   = 0.340
green_x = 0.295
green_y = 0.591
blue_x  = 0.141
blue_y  = 0.096
white_x = 0.312
white_y = 0.328

red_x_lsb   = 0     # Red x value least-significant 2 bits
red_y_lsb   = 0     # Red y value least-significant 2 bits
grn_x_lsb   = 0     # Green x value least-significant 2 bits
grn_y_lsb   = 0     # Green y value least-significant 2 bits
blu_x_lsb   = 0     # Blue and white least-significant 2 bits
blu_y_lsb   = 0
wht_x_lsb   = 0
wht_y_lsb   = 0
red_x_msb   = red_x*(2**8)     # Red x value most significant 8 bits.
red_y_msb   = red_y*(2**8)     # Red y value most significant 8 bits
grn_x_msb   = green_x*(2**8)     # Green x value most significant 8 bits
grn_y_msb   = green_y*(2**8)     # Green x value most significant 8 bits
blu_x_msb   = blue_x*(2**8)     # Blue x value most significant 8 bits
blu_y_msb   = blue_y*(2**8)     # Blue y value most significant 8 bits
wht_x_msb   = white_x*(2**8)     # Default white point x value most significant 8 bits
wht_y_msb   = white_y*(2**8)     # Default white point y value most significant 8 bits

# 35-37 - Established timing bitmap. Supported bitmap for very common timing modes.
byte_35     = 0
byte_36     = 0
byte_37     = 0
# 38-53
x_res       = 0 # (100-31)
pix_rat     = 0
v_freq      = 0

# Descriptor 1, 54-71
pix_clk         = 2459      # Pixel clock in 10 kHz units
hor_act         = 480       # Horizontal active pixels 8 lsbits 
hor_blank       = 32        # Horizontal blanking pixels 8 lsbits End of act to start of next act.  (HBLK)
vert_act        = 800       # Vertical active lines 8 lsbits (0-4095)                               
vert_blank      = 12        # Vertical blanking lines 4 msbits                                      (VBL)
h_sync_off      = 5         # Horizontal sync offset pixels 8 lsbits (0-1023) From blacking start   (HFP)
h_sync_pw       = 6         # Horizontal sync pulse width pixels 8 lsbits (0-1023)                  (HS)
v_sync_off      = 3         # Vertical sync offset lines (0-63)                                     (VFP)
v_sync_pw       = 3         # Vertical sync pulse width lines (0-63)                                (VS)
h_disp_size     = 56        # Horizontal display size, mm, 8 lsbits
v_disp_size     = 93        # Vertical display size, mm, 8 lsbits
h_bord_px       = 0         # Horizontal border pixels (each side; total is twice this)
v_bord_ln       = 0         # Vertical border lines (each side; total is twice this)
interlaced      = 0         # \ Interlaced
stereo_mode     = 0         # | Stereo mode
sync_type       = 3         # | Sync type
v_sync_pol      = 0         # | Vertical sync polarity (1=positive)
h_sync_pol      = 0         # | HSync polarity (1=positive)
int_stereo      = 0         # / 2-way line-interleaved stereo, if bits 3-4 are not 00

# Descriptor 2
monitor_name    = "Manga Screen"

# Descriptor 3
min_v_field     = 55       # Minimum vertical field rate (1-255 Hz)
max_v_field     = 65       # Maximum vertical field rate (1-255 Hz)
min_h_field     = 42       # Minimum horizontal line rate (1-255 kHz)
max_h_field     = 67       # Maximum horizontal line rate (1-255 kHz)
max_px_clk      = 3        # Maximum pixel clock rate, rounded up to 10 MHz multiple (10-255 MHz)

def make_edid():
    edid = array.array('c', '\0' * 128)    
    # Bytes 0-19
    struct.pack_into("BBBBBBBB", edid, 0, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00) # Header
    idm = "0b0"+"".join([bin(ord(l)-ord('A')+1)[2:].rjust(5, '0') for l in man_id])
    struct.pack_into(">H", edid, 8, int(idm, 2))
    struct.pack_into("<H", edid, 10, prod_code) 
    struct.pack_into("<I", edid, 12, serial_nr) 
    struct.pack_into("B", edid, 16, week_of_man) 
    struct.pack_into("B", edid, 17, year_of_man-1990) 
    struct.pack_into("B", edid, 18, edid_ver) 
    struct.pack_into("B", edid, 19, edid_rev) 
    #Bytes 20-24 
    if dig_input == 1:
        struct.pack_into("B", edid, 20, vesa_compat+0x80)
    else:
        s = "0b"+bin(video_white)[2:].rjust(3, '0')+str(blank_black)+str(sep_sync)+str(comp_sync)+str(sync_on_grn)+str(vsync_serr)
        struct.pack_into("B", edid, 20, int(s, 2))
    struct.pack_into("B", edid, 21, max_hor_img) 
    struct.pack_into("B", edid, 22, max_vert_img) 
    struct.pack_into("B", edid, 23, disp_gamma) 
    s = "0b"+str(DPMS_stnd)+str(DPMS_susp)+str(DPMS_off)+bin(disp_type)[2:].rjust(2, "0")
    s+= str(std_RGB)+str(pref_timing)+str(GTF_sup)
    struct.pack_into("B", edid, 24, int(s, 2))
    # Bytes 25-34
    s = "0b"+bin(red_x_lsb)[2:].rjust(2, "0")+bin(red_y_lsb)[2:].rjust(2, "0")
    s+= bin(grn_x_lsb)[2:].rjust(2, "0")+bin(grn_y_lsb)[2:].rjust(2, "0")
    struct.pack_into("B", edid, 25, int(s, 2))
    s = "0b"+bin(blu_x_lsb)[2:].rjust(2, "0")+bin(blu_y_lsb)[2:].rjust(2, "0")
    s+= bin(wht_x_lsb)[2:].rjust(2, "0")+bin(wht_y_lsb)[2:].rjust(2, "0")
    struct.pack_into("B", edid, 26, int(s, 2))
    struct.pack_into("B", edid, 27, red_x_msb)    
    struct.pack_into("B", edid, 28, red_y_msb)    
    struct.pack_into("B", edid, 29, grn_x_msb)    
    struct.pack_into("B", edid, 30, grn_y_msb)    
    struct.pack_into("B", edid, 31, blu_x_msb)    
    struct.pack_into("B", edid, 32, blu_y_msb)    
    struct.pack_into("B", edid, 33, wht_x_msb)    
    struct.pack_into("B", edid, 34, wht_y_msb)    
    # Bytes 35-37 Established timing maps 
    struct.pack_into("B", edid, 35, byte_35)    
    struct.pack_into("B", edid, 36, byte_36)    
    struct.pack_into("B", edid, 37, byte_37)    

    # Bytes 38-39 Standard timing
    #struct.pack_into("B", edid, 38, x_res)
    #s = "0b"+bin(pix_rat)[2:].rjust(2, "0")+bin(v_freq)[2:].rjust(6, "0")
    #struct.pack_into("B", edid, 39, int(s, 2))
    for i in range(38, 54):
        struct.pack_into("B", edid, i, 0x01)    

    # Descriptor 1 (54-71)
    struct.pack_into("H", edid, 54+0, pix_clk)              # Byte 0-1
    struct.pack_into("B", edid, 54+2, hor_act%256)          # Byte 2
    struct.pack_into("B", edid, 54+3, hor_blank%256)        # Byte 3
    s  = "0b"+bin((hor_act&0xF00)>>8)[2:].rjust(4, "0")
    s += bin((hor_blank&0xF00)>>8)[2:].rjust(4, "0")
    struct.pack_into("B", edid, 54+4, int(s, 2))            # Byte 4
    struct.pack_into("B", edid, 54+5, vert_act & 0xFF)      # Byte 5 
    struct.pack_into("B", edid, 54+6, vert_blank & 0xFF)    # Byte 6
    s  = "0b"+bin((vert_act & 0xF00)>>8)[2:].rjust(4, "0")
    s += bin((vert_blank & 0xF00)>>8)[2:].rjust(4, "0")
    struct.pack_into("B", edid, 54+7, int(s, 2))            # Byte 7
    struct.pack_into("B", edid, 54+8, h_sync_off & 0xFF)    # Byte 8
    struct.pack_into("B", edid, 54+9, h_sync_pw & 0xFF)     # Byte 9
    s  = "0b"+bin(v_sync_off & 0xF)[2:].rjust(4, "0")
    s += bin(v_sync_pw & 0xF)[2:].rjust(4, "0")
    struct.pack_into("B", edid, 54+10, int(s, 2))           # Byte 10
    s  = "0b"+bin( (h_sync_off&0x800)>>8 )[2:].rjust(2, "0")
    s +=      bin( (h_sync_pw &0x800)>>8 )[2:].rjust(2, "0")
    s +=      bin( (v_sync_off&0x80 )>>4 )[2:].rjust(2, "0")
    s +=      bin( (v_sync_pw &0x80 )>>4 )[2:].rjust(2, "0")
    struct.pack_into("B", edid, 54+11, int(s, 2))           # Byte 11
    struct.pack_into("B", edid, 54+12, h_disp_size&0xFF)    # Byte 12
    struct.pack_into("B", edid, 54+13, v_disp_size&0xFF)    # Byte 13
    s  = "0b"+bin( (h_disp_size&0xF00)>>8 )[2:].rjust(4, "0")
    s +=      bin( (v_disp_size&0xF00)>>8 )[2:].rjust(4, "0")
    struct.pack_into("B", edid, 54+14, int(s, 2))           # Byte 14
    struct.pack_into("B", edid, 54+15, h_bord_px)           # Byte 15
    struct.pack_into("B", edid, 54+16, v_bord_ln)           # Byte 16
    s = "0b"+str(interlaced)+bin(stereo_mode)[2:].rjust(2, "0")
    s += bin(sync_type)[2:].rjust(2, "0")+str(v_sync_pol)+str(h_sync_pol)+str(int_stereo)
    struct.pack_into("B", edid, 54+17, int(s, 2))           # Byte 17

    # Descriptor 2: Other monitor descriptors (72-89)
    struct.pack_into("H", edid, 72+0, 0)                    # 0 indicates not timing info
    struct.pack_into("B", edid, 72+2, 0)                    
    struct.pack_into("B", edid, 72+3, 0xFC)                 # 0xFF indicates monitor serial number
    struct.pack_into("B", edid, 72+4, 0)                    
    # Monitor name   
    for i, c in enumerate(monitor_name):
        struct.pack_into("B", edid, 72+5+i, ord(c))
    struct.pack_into("B", edid, 72+5+len(monitor_name), 0x0A)
    
    
    # Descriptor 3: Monitor range limits (90-107)
    struct.pack_into("H", edid, 90+0, 0)                    # 0 indicates not timing info
    struct.pack_into("B", edid, 90+2, 0)                    
    struct.pack_into("B", edid, 90+3, 0xFD)                 # 0xFF indicates monitor serial number
    struct.pack_into("B", edid, 90+4, 0)                    
    struct.pack_into("B", edid, 90+5, min_v_field)
    struct.pack_into("B", edid, 90+6, max_v_field)
    struct.pack_into("B", edid, 90+7, min_h_field)
    struct.pack_into("B", edid, 90+8, max_h_field)
    struct.pack_into("B", edid, 90+9, max_px_clk)
    struct.pack_into("B", edid, 90+10, 0x00)
    struct.pack_into("B", edid, 90+11, 0x0A)                    
    struct.pack_into("B", edid, 90+12, 0x20)                    
    struct.pack_into("B", edid, 90+13, 0x20)                    
    struct.pack_into("B", edid, 90+14, 0x20)                    
    struct.pack_into("B", edid, 90+15, 0x20)                    
    struct.pack_into("B", edid, 90+16, 0x20)                    
    struct.pack_into("B", edid, 90+17, 0x20)                    

	# Descriptor 4: Unspecified text 0xFE
    struct.pack_into("H", edid, 108+0, 0)                    # 0 indicates not timing info
    struct.pack_into("B", edid, 108+2, 0)                    
    struct.pack_into("B", edid, 108+3, 0xFE)                 # 0xFF indicates monitor serial number
    struct.pack_into("B", edid, 108+4, 0)                    
    struct.pack_into("B", edid, 108+5, 0x0A)                    
    for i in range(17-6):
        struct.pack_into("B", edid, 108+5+i, 0x20)    

    struct.pack_into("B", edid, 126, 0)                     # Byte 126
    

    checksum = 0
    for i in range(127):
        checksum += struct.unpack("B", edid[i])[0]
    checksum %= 256
    checksum = (256-checksum)
    struct.pack_into("B", edid, 127, checksum)

    return edid
    
print "EDID maker V0.1"
edid = make_edid()

print len(edid)

f = open("edid.dat", "w+b")
f.write(edid)
f.close()

f = open("edid.c", "w+")
f.write("char edid[] = {")
for i in range(128):
    f.write(hex(struct.unpack("B", edid[i])[0])+", ")
f.write("};")
f.close()

print "EDID information written to edid.dat and edid.c"
