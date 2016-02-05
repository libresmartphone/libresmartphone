
get_edid: get_edid_rev_a3

write_edid: write_edid_rev_a3

# Make sure your display is connected from a normal (Ubuntu) PC. 
# Fist run "python edid.py" to make edid.dat
# You might have to change the port from 0 to something else
get_edid_rev_a3:
	sudo ./edid-rw/edid-rw 2 | parse-edid

write_edid_rev_a3:
	sudo ./edid-rw/edid-rw 2 -w -s 0.01 < edid.dat

write_empty: 
	for number in $(shell seq 0x00 0xFF); do \
		echo $$number ; \
		sudo i2cset -y 2 0x50 $$number 0xFF ; \
	done

