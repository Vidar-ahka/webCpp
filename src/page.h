#ifndef PAGE_H
#define PAGE_H

#include"string"
#include"unordered_map"
#include"fstream"
#include"iostream"
#include"list"
#include"memory"

class para;
class page
{
    
public:
    page();
    page(std::string &path);
    size_t size();
    std::list<std::shared_ptr<para>> &  getlist();
    bool empty();
private:   
    size_t size_;
    std::string path;
    std::list<std::shared_ptr<para>> txt_;
    std::list<std::string> paths;
    bool open_file;
};


class para
{
public:
    std::string begin;
    std::string key;
};

#endif