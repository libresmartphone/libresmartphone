#include <curl/curl.h>

#define OMB_SERVER_ADRR "https://www.own-mailbox.com/proxy/"
#define OMB_PAGE_REQUEST_DOMAIN "request_domain.php"
#define OMB_PAGE_INFORM_TOR_SERVICE "inform_tor_service.php"

CURL *curl;
  
void omb_request_init();
void omb_request_end();
void omb_request_domain_name(char domain[256], char cookie[10000]);
void omb_inform_tor_hidden_service(char service[256], char cookie[10000]);
int  omb_remaing_credit(char cookie[10000]);
void omb_read_cookie(char cookie_path[1024], char result[10000]);