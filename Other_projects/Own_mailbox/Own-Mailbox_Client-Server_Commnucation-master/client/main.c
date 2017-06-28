#include "request.h"
#include <unistd.h>
#include <getopt.h>
#include <stdlib.h>
#include <linux/ioctl.h>
#include <string.h>

static struct option long_options[] =
        {
          {"request_domain",  required_argument, 0, 'd'},
          {"inform_tor_hidden_service",    required_argument, 0, 't'},
          {"cookie_path",    required_argument, 0, 'c'},	  	  
          {0, 0, 0, 0}
        };
	
	
void print_usage();

main(int argc , char *argv[])
{
  char cookie[10000];
  char cookie_path[256]="cookie";
  char request_domain_name[256]="";
  char inform_tor_hidden_service[256]="";
  

  
     int option_index = 0;
     int opt;
    while ((opt = getopt_long (argc, argv, "d:t:c:",long_options, &option_index)) != -1) {
        switch (opt) {
             case 'd' : strcpy(request_domain_name,optarg);
                 break;
             case 't' : strcpy(inform_tor_hidden_service,optarg);
                 break;
	     case 'c' : strcpy(cookie_path,optarg);   
	       break;
     		 
             default: print_usage(); 
                 //exit(EXIT_FAILURE);
        }
    }

  omb_read_cookie(cookie_path,cookie);
  
    omb_request_init();
    
  if (strlen(request_domain_name)!=0)
    omb_request_domain_name(request_domain_name,cookie);
  
  if (strlen(inform_tor_hidden_service)!=0)
    omb_inform_tor_hidden_service(inform_tor_hidden_service,cookie);
  

  omb_request_end();
}

void print_usage()
{
  
}