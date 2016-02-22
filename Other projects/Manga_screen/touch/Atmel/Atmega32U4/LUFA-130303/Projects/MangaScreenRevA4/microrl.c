#include "microrl/src/config.h"
#include <string.h>
#include <stdlib.h>
#include <avr/io.h>
#include <stdio.h>
#include "MangaScreen.h"
#include "Digitizer.h"
#include "eeprom.h"
    
// definition commands word
#define _CMD_HELP       "help"
#define _CMD_CLEAR      "clear"
#define _CMD_BACKLIGHT  "set_backlight"
#define _CMD_DISPLAY    "set_display"
#define _CMD_DIGITIZER  "init_digitizer"
#define _CMD_COORDINATE "config_xy"
#define _CMD_DEBUG      "set_debug"

#define _NUM_OF_CMD 7

//available  commands
char * keyworld [] = {_CMD_HELP, _CMD_CLEAR, _CMD_BACKLIGHT, _CMD_DISPLAY, _CMD_DIGITIZER, _CMD_COORDINATE, _CMD_DEBUG};

// array for comletion
char * compl_world [_NUM_OF_CMD + 1];


//*****************************************************************************
void print (const char * str){
    printf(str);
}

//*****************************************************************************
// execute callback for microrl library
// do what you want here, but don't write to argv!!! read only!!
int execute (int argc, const char * const * argv){
	int i = 0;
	// just iterate through argv word and compare it with your commands
	while (i < argc) {
		if (strcmp (argv[i], _CMD_HELP) == 0) {
			printf ("Manga Screen CLI\n");
	        printf ("Use TAB key for completion\nCommand:\n");
	        printf ("\tclear               - clear screen\n");
            printf ("\tset_backlight       - Set the backlight level, <0..255> \n");
            printf ("\tset_display         - Turn display on or off <on/off>\n");
            printf ("\tinit_digitizer      - Run init code for digitizer\n");
            printf ("\tconfig_xy           - Set the config of the digitizer\n");
            printf ("\tset_debug           - Set the debug level, 0..60\n");
		} 
        else if (strcmp (argv[i], _CMD_CLEAR) == 0) {
			print ("\033[2J");    // ESC seq for clear entire screen
			print ("\033[H");     // ESC seq for move cursor at left-top corner
        }
        else if(strcmp (argv[i], "set_display") == 0){
            if (++i < argc) {
                if (strcmp (argv[i], "on") == 0) {
					LCD_Init();
                    print ("LCD initialized\n");
				} else if (strcmp (argv[i], "off") == 0) {
					LCD_UnInit();
                    print ("LCD uninitialized\n");
				} else {
					print ("only 'on' and 'off' supported\n");
					return 1;
				}		        		        				
			} else {
					print ("specify state, on or off\n");
				return 1;
			}    
	    }
	    else if(strcmp(argv[i], _CMD_BACKLIGHT) == 0){
            if (++i < argc) {
                int val = atoi (argv[i]);
		        if(val >= 0 && val <= 255){
			        BL_on(val);
                    write_brightness(val); // Update EEPROM
                    printf ("Brightness updated to %i\n", val);
                }
                else {
					printf("Wrong value '%s'. Value must be between 0 and 255\n", argv[i]);
				    return 1;
                }
            }
            else {
			    printf ("specify value, <0..255>\n");
				return 1;
			}
	    }
	    else if(strcmp(argv[i], _CMD_DIGITIZER) == 0){
            int ret = digitizer_init();
		    if(ret)
			    dev_err("Digitizer error: %x\n", ret);
            else
			    dev_info("Digitizer OK: %x\n", ret);
        }
        else if(strcmp(argv[i], _CMD_COORDINATE) == 0){
            if (++i < argc) {
                int val = atoi (argv[i]);
		        if(val >= 0 && val <= 6){
                    digitizer_set_config(val);
                    write_digitizer_config(val); // Update EEPROM
                    printf ("Digitizer config updated to %i\n", val);
                }
                else {
					printf("Wrong value '%s'. Value must be between 0 and 6\n", argv[i]);
				    return 1;
                }
            }
            else {
			    printf ("specify value, <0..6>\n");
				return 1;
			}
        }
        else if(strcmp(argv[i], _CMD_DEBUG) == 0){
            if (++i < argc) {
                int val = atoi (argv[i]);
		        if(val >= 0 && val <= 60){
                    debug_level = val;
                    write_debug_level(val); // Update EEPROM
                    printf ("Debug level updated to %i\n", val);
                }
                else {
					printf("Wrong value '%s'. Value must be between 0 and 60\n", argv[i]);
				    return 1;
                }
            }
            else {
			    printf ("specify value, <0..60>\n");
				return 1;
			}

        }
		else {
			print ("command: '");
			print ((char*)argv[i]);
			print ("' Not found.\n");
		}
		i++;
	}
	return 0;
}

#ifdef _USE_COMPLETE
//*****************************************************************************
// completion callback for microrl library
char ** complet (int argc, const char * const * argv){
	int j = 0;

	compl_world [0] = NULL;

	// if there is token in cmdline
	if (argc == 1) {
		// get last entered token
		char * bit = (char*)argv [argc-1];
		// iterate through our available token and match it
		for (int i = 0; i < _NUM_OF_CMD; i++) {
			// if token is matched (text is part of our token starting from 0 char)
			if (strstr(keyworld [i], bit) == keyworld [i]) {
				// add it to completion set
				compl_world [j++] = keyworld [i];
			}
		}
	} else { // if there is no token in cmdline, just print all available token
		for (; j < _NUM_OF_CMD; j++) {
			compl_world[j] = keyworld [j];
		}
	}

	// note! last ptr in array always must be NULL!!!
	compl_world [j] = NULL;
	// return set of variants
	return compl_world;
}
#endif

//*****************************************************************************
void sigint (void){
	print ("^C catched!\n");
}
