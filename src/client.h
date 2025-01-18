#ifndef  CLIENT_H
#define  CLIENT_H
#include"openssl/ssl.h"
#include"openssl/bio.h"
#include"openssl/err.h"
#include<arpa/inet.h>
#include"unistd.h"
#include"page.h"
#include"unordered_map"
#include"request.h"
#include"httprespone.h"
class  client
{
public:
    client(const int  &socket_s, SSL_CTX * ctx);
    ~client();
    
    int   getsocket();
    bool  is_connect();
    bool  write(std::shared_ptr<httprespone> respone);
    std::shared_ptr<request>  readrequest(); 
private:
   sockaddr_in s_addr;
   socklen_t len;
   SSL * ssl ;
   int  socket_;
   bool val;
};
#endif