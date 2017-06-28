#include "request.h"
#include <string.h>

int omb_remaing_credit(char cookie[10000])
{

}

void omb_request_domain_name(char domain[256], char cookie[10000])
{

  CURLcode res;
  char URL[1024]="";
  strcat(URL,OMB_SERVER_ADRR);    
  strcat(URL,OMB_PAGE_REQUEST_DOMAIN);
  strcat(URL,"?domain="); 
  strcat(URL,domain);      
  
  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_COOKIE, cookie); 
  curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
  curl_easy_setopt(curl, CURLOPT_PROXY, "localhost:9050"); 
  
/* Perform the request, res will get the return code */ 
  res = curl_easy_perform(curl);

  /* Check for errors */ 
  if(res != CURLE_OK)
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
	    curl_easy_strerror(res));


  
}

void omb_inform_tor_hidden_service(char service[256], char cookie[10000])
{
  CURLcode res;
  char URL[1024]="";
  strcat(URL,OMB_SERVER_ADRR);    
  strcat(URL,OMB_PAGE_INFORM_TOR_SERVICE);
  strcat(URL,"?service="); 
  strcat(URL,service);      
  
  curl_easy_setopt(curl, CURLOPT_URL, URL);
  curl_easy_setopt(curl, CURLOPT_COOKIE, cookie); 
  curl_easy_setopt(curl, CURLOPT_PROXYTYPE, CURLPROXY_SOCKS5);
  curl_easy_setopt(curl, CURLOPT_PROXY, "localhost:9050"); 
  
/* Perform the request, res will get the return code */ 
  res = curl_easy_perform(curl);

  /* Check for errors */ 
  if(res != CURLE_OK)
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
	    curl_easy_strerror(res));

}

void omb_read_cookie(char cookie_path[1024], char result[10000])
{
FILE *fp;
char ch; int i;
i=0;
char tmp[100];
 fp = fopen(cookie_path,"r"); // read mode

 if (fp == NULL)
 {return;
 fprintf(stderr,"Error: Impossible to read cookie: file does not exist\n");
 
 }
 
while( ( ch = fgetc(fp) ) != EOF )
    {
      result[i]=ch;
      i++;
    }
}

void omb_request_init()
{ 
  curl_global_init(CURL_GLOBAL_DEFAULT);
  curl = curl_easy_init();
}

void omb_request_end()
{
  /* always cleanup */ 
  curl_easy_cleanup(curl);
}
