#ifndef SERVER_H
#define SERVER_H

#include"iostream"
#include"pages.h"
#include"client.h"
#include"functional"
#include"httprespone.h"
#include"experimental/filesystem"
#include"files.h"
#include"atomic"
#include"csignal"
#include"sys/select.h"
#include"future"
namespace fs = std::experimental::filesystem;

class server{

public:
    server(int port);
    ~server();
    bool start();
    void setpathhtml(std::string path);
    void setpathcss (std::string path);
    void setpathfile(std::string path);
    void setcertificate(std::string url);
    void setprivatekey(std::string new_private_key_path);
    void setCAcertificate(std::string new_ca_certificate_path);
    void setPort(int port);
    void add(std::string form, std::function<std::shared_ptr<httprespone>(std::shared_ptr<request>)> fun);

    std::shared_ptr<httprespone> render(std::string path, std::unordered_map<std::string,std::string> & key);
    std::shared_ptr<httprespone> render(std::string path);
    static std::unordered_map<std::string, std::shared_ptr<pages>> pages_save;
    
    static void end(int num);    
    static bool work;
 private:   

    
    void clientprocessing(client &cl);  
    bool init();
    bool socketinit();
    void delete_slesh(std::string  & path);
  
    int socket_m {-1};
    int port = 3232;
    sockaddr_in sa_serv;
    SSL_CTX    *ctx;
    
    std::string certificate_path ;
    std::string private_key_path ;
    std::string CA_path;
    std::string path_html;    
    std::string path_css;     
    std::string path_file; 
    std::unordered_map<std::string ,std::function<std::shared_ptr<httprespone>(std::shared_ptr<request>)>> forms;
    std::shared_ptr<files>  files_;
    std::shared_ptr<pages>  pages_;

};



#endif