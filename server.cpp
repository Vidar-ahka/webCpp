#include"server.h"

bool server::work = true;
std::unordered_map<std::string , std::shared_ptr<pages>> server::pages_save;
server::server(int port):port(port) 
{
 
}
server::~server()
{
    std::cout <<"destruct \n";
    close(socket_m);
}

static void *get_in_addr(sockaddr *sa)
{
    if(sa->sa_family=AF_INET)
    {
        return &(((sockaddr_in*)sa)->sin_addr);
    }
    
    return &(((sockaddr_in6*)sa)->sin6_addr);

}

static std::string get_ip(const sockaddr_in & data)
{
    char buff[INET6_ADDRSTRLEN];
    inet_ntop(data.sin_family,(sockaddr*)&data.sin_addr,buff,sizeof(buff));
    return std::string(buff);
}

bool server::start()
{
    if(!init())
    {
        std::cout<<"\n dont create  init  \n";
        return false;
    }
    if(!socketinit())
    {
        std::cout<<"\n dont create socekt \n";
        return false;
    }
    std::cout<<"start server port - "<<port<<'\n';
   
   
   
    files_ = std::make_shared<files>();  
    if(pages_save.count(this->path_html))
    {
        pages_ = pages_save[this->path_html];
    } 
    else 
    {
        pages_ = std::make_shared<pages>();
        pages_->setpathhtmldir(path_html);

        pages_save[path_html] = pages_;  
    }

    signal(SIGHUP,server::end);
    fd_set readfds; 
    FD_ZERO(&readfds);
    FD_SET(socket_m, &readfds);
    struct timeval timeout;

    
    while (work)
    {
        
        timeout.tv_sec = 45; // Установка времени ожидания в 1 секунду
        timeout.tv_usec = 0;
    
         
         std::cout<<"long poll \n";
         int ready = select(socket_m+1,&readfds,nullptr,nullptr,&timeout);  
         if(ready>0){

            client cl(socket_m,ctx);
            if(!cl.is_connect())
            {
               std::cout<<"disconnect "<<cl.getsocket()<<'\n';
               continue;
            }
            try
            {
                std::future<void> ft = std::async(std::launch::async,&server::clientprocessing,this,std::ref(cl));
               
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
            
            
        }
        else if(ready==-1)
        {
            break;
        }
    
    }
    return true;
    
}

void  server::clientprocessing(client &cl)
{
    
    
    
    std::shared_ptr<request> request_  =  cl.readrequest();
    if(request_->getextension() == "html"&&forms.count(request_->url))
    {
        cl.write(forms[request_->url](request_));
    }
    else
    { 
        std::shared_ptr<file> file_ = files_->get(path_html,request_->url,request_->gettype());             
        cl.write(std::make_shared<httpresponefile>(200,request_->gettype(),request_->getextension(),file_));          
    }
}

bool server::init()
{
    SSL_library_init(); /* load encryption & hash algorithms for SSL */                
    SSL_load_error_strings(); /* load the error strings for good error reporting */


    ctx = SSL_CTX_new(const_cast<SSL_METHOD*>(TLS_server_method()));

    if(SSL_CTX_use_certificate_file(ctx, this->certificate_path.c_str(),SSL_FILETYPE_PEM)<=0)
    {
        std::cout<<"\n"<<" cert " << this->certificate_path <<'\n';
        ERR_print_errors_fp(stderr);
        SSL_CTX_free(ctx);
        return false;
    }
    if(!SSL_CTX_use_PrivateKey_file(ctx,private_key_path.c_str(),SSL_FILETYPE_PEM))
    {
        std::cout<<"\n! priveteeky \n" ;
        ERR_print_errors_fp(stderr);
 
        return false;
    }
    if(!SSL_CTX_load_verify_locations(ctx, this->CA_path.c_str(),NULL))
    {
        std::cout<< "\n! load verify location \n"  ;
    }
    return true;
}

void  server::setcertificate(std::string url)
{  
    this->certificate_path = url;   
}

void server::setprivatekey(std::string new_private_key_path)
{
    this->private_key_path = new_private_key_path;
}

void server::setCAcertificate(std::string new_ca_certificate_path)
{
    this->CA_path = new_ca_certificate_path;
}
void server::setpathhtml(std::string path)
{
    if(path.empty())
    {
        return;
    }
    if(path[path.size()-1]!='/')
    {
        path.push_back('/');
    }
    this->path_html = path;
}
void server::setpathcss (std::string path)
{
    
}
void server::setpathfile(std::string path)
{

}

bool server::socketinit()
 {

     socket_m  = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
     if(socket_m == -1) 
     {
        std::cout<<" socket_m == -1 \n";
        std::cout<<'\n';
        return  false;
     }
     memset(&sa_serv,0,sizeof(sa_serv));
     sa_serv.sin_family = AF_INET;
     sa_serv.sin_addr.s_addr  = INADDR_ANY;
     sa_serv.sin_port = htons(port);
     if(bind(socket_m,(sockaddr*)&sa_serv,sizeof(sa_serv))==-1)
     {
        std::cout<<"!bind \n";
        close(socket_m);
        return false;
     }
     if(listen(socket_m,100)==-1)
     {
        close(socket_m);
        std::cout<<"!listen \n";
        return false;
     }

     return true;
}

void server::setPort(int port)
{
    this->port = port;   
}
void server::add(std::string form, std::function<std::shared_ptr<httprespone>(std::shared_ptr<request>)> fun) 
{
    forms[form]  = fun;
}



std::shared_ptr<httprespone> server::render(std::string path, std::unordered_map<std::string,std::string> & key)
{
    std::shared_ptr<page> page_  = server::pages_->getpage(path);
    if(page_->empty())
    {
        return std::make_shared<httpresponehtlm>();
    }
    
    size_t size  = page_->size();

    std::shared_ptr<httpresponehtlm> http  = std::make_shared<httpresponehtlm>(200,"text","html");
    
    for(auto  & it :key)
    {
        size += it.second.size();
    }
    http->reserve(size);
    for( auto &it :page_->getlist())
    {
        http->add_html_code(it->begin);
        if(key.count(it->key))
        {
            http->add_html_code(key[it->key]);
        }
    }
    return http;
}

std::shared_ptr<httprespone> server::render(std::string path)
{
    std::shared_ptr<page> page_ = server::pages_->getpage(path);
    if(!page_->empty())
    {
        return  std::make_shared<httpresponehtlm>();
    }
    std::shared_ptr<httpresponehtlm> http = std::make_shared<httpresponehtlm>(200,"text","html");

    http->reserve(page_->size());
    for(auto &it: page_->getlist())
    {
        http->add_html_code(it->begin);
    }
    return http;
}


void server:: end(int num)
{
    server::work == num!=SIGHUP;
}