#ifndef IMAGES_H
#define IMAGES_H
#include"iostream"
#include"memory"
#include"unordered_map"
#include"file.h"
class files
{
public:
    files();
    std::shared_ptr<file>  get(std::string &path);
    void setpathfile(std::string & path);
private:
    std::string path_file;
    std::unordered_map<std::string,std::shared_ptr<file>> map_;
    bool absolutepath(std::string &str);
    std::string  combinepath(std::string & path);
};
#endif  