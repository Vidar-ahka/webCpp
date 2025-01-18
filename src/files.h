#ifndef IMAGES_H
#define IMAGES_H
#include"iostream"
#include"memory"
#include"unordered_map"
#include"file.h"
#include"page.h"

class files_base
{
public:
    files_base();
    virtual  ~files_base();
    void setpathfile(std::string & path);
protected:
    std::string path_file;
    bool  absolutepath(std::string &str);
    std::string  combinepath(std::string & path);
    
};


class files : public files_base
{
public:
    files();
    ~files();
    std::shared_ptr<file>  get(std::string &path);
private:
    std::unordered_map<std::string,std::shared_ptr<file>> map_;
};

class pages : public files_base
{
    
public:
    pages();
    ~pages();
    std::shared_ptr<page> getpage(std::string &path);
private:
    std::unordered_map<std::string , std::shared_ptr<page>> map_;
};


#endif  