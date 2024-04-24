#ifndef REQUEST_H
#define REQUEST_H
#include"sstream"
#include"string"
#include"unordered_map"
#include"algorithm"
enum Em
{
    Empty = 0,
    GET
};
class request
{
 public:
    request();   
    request(std::string & buff);
    ~request();
    void  parsing(std::string  & buff);
    Em method();
    std::string url;  
    std::unordered_map<std::string , std::string > GET;
    std::string  headers(std::string name);
    std::string& gettype();
    std::string& getextension();


private:
    void parsing_1(std::string& buff);
    void parsing_2(std::string& buff);
   
    Em status;
    std::string buff;
    std::unordered_map<std::string ,std::pair<size_t ,size_t>>  headers_;
    size_t size_first_line;
    std::string type;
    std::string extension;
};
#endif