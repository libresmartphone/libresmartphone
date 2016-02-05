# Own-Mailbox_Client-Server_Commnucation
Allows usual client/server communication between an Own-mailbox and the proxy server, it performs necessery
operations during normal usage:

*For the own-mailbox to specify the proxy its .onion address
*For the own-mailbox to request a domain name to the proxy server.
*For the own-mailbox to request various informations about its acount.
*For other communications in the future.

All requests form the own-mailbox are made through tor in order to preserve anonymity.
In order to work the client must run a tor proxy on port 9050.
