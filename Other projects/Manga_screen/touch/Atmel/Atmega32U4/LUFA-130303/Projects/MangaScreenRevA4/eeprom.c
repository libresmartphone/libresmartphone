

#include "eeprom.h"

/**
EEPROM related functions and default values
 */

uint8_t EEMEM ee_brightness = 100; // First time booting, 50% brighness
uint8_t EEMEM ee_debug = 40;       // First time booting, Only errors
uint8_t EEMEM ee_config = 0;       // First time booting

// Read the brightness level from EEPROM
int read_brightness(void){
    return eeprom_read_byte (&ee_brightness);
}

// Write brighness level to EEPROM
void write_brightness(int brightness){
    eeprom_update_byte (&ee_brightness, brightness);
}

// Read debug level from EEPROM
int read_debug_level(void){
    return eeprom_read_byte (&ee_debug);
}

// Write debug level to EEPROM
void write_debug_level(int level){
    eeprom_update_byte (&ee_debug, level);
}

// Write the digitizer config value
void write_digitizer_config(int config){
    eeprom_update_byte (&ee_config, config);
}

// Read the digitizer config coorditate system value. 
int read_digitizer_config(void){
    return eeprom_read_byte (&ee_config);
}
