#ifndef IMAGE_H
#define IMAGE_H
#include"string"
#include"fstream"
#include"bytearray.h"
#include"iostream"
#include"experimental/filesystem"
namespace fs = std::experimental::filesystem;
class file
{
public:
    file();
    file(file  & file_);
    file(const std::string &path,const std::string & type);
    void load(const std::string &path,const std::string & type );
   
    size_t size();
    char * byte();
    bool   empty();
private:
    void load_t(const std::string &path,const std::string & type );
    bytearray byte_;
    size_t size_;
    std::string path;
};
#endif