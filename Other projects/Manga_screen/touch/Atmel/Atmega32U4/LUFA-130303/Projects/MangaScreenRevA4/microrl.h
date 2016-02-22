#ifndef _MICRORL_MISC_H_
#define _MICRORL_MISC_H_

/*
Platform independent interface for implementing some specific function
for AVR, linux PC or ARM
*/

void print (const char * str);

// execute callback
int execute (int argc, const char * const * argv);

// completion callback
char ** complet (int argc, const char * const * argv);

// ctrl+c callback
void sigint (void);

#endif
