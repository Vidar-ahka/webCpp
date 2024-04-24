  #include"client.h"
client  :: client (const int  &socket_s , SSL_CTX * ctx)
{
    ssl = nullptr;
    len  = sizeof(s_addr);
    socket_ = accept(socket_s,(sockaddr*)&s_addr,&len);    
    val = false;
    if(socket_ == -1)
    {
        std::cout <<" disconncet socket"<< socket_ <<"\n";
        
        return;
    }
  
    ssl = SSL_new(ctx);
 
    SSL_set_fd(ssl,socket_);
   
    if(SSL_accept(ssl)==-1)
    {
        if(ssl==nullptr)
        {
            std::cout<<"ssl = nullptr \n";   
        }
        std::cout <<" drop \n";
        return;
    }

    
    val = true;
}
client::~client()
{
    
    close(socket_);    
    SSL_free(ssl);
        
}
bool client :: is_connect()
{

    return  val;
}

 
std::shared_ptr<request>  client :: readrequest()
{
    std::string str;
    str.resize(1000); 
    int count  = SSL_read(ssl,str.data(),500); 
    return std::make_shared<request>(str);
}



int   client::getsocket()
{
    return socket_;
}

bool  client::write(std::shared_ptr<httprespone> respone)
{
   
    
    if(respone->empty())
    {
        return false;
    }
 
    std::string req = "HTTP/1.1 "+ std::to_string(respone->getstatus())+  " OK\r\nConnection: keep-alive\r\nContent-Type:" +respone->gettype()+'/'+respone->getextension()+"\r\nContent-Length:"
    +std::to_string(respone->size())
    +"\r\n\r\n";
 
    int count = SSL_write(ssl,req.c_str(),req.size());
    if(!count) 
    {
        return false;
    }
    count =  SSL_write(ssl,respone->data(),respone->size());
  
    return count;
}


   