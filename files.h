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
    void setpathcss(std::string  & path);
    void setpathfile(std::string  & path);
    
    std::shared_ptr<file>  get(std::string& path_html,std::string &path,std::string &extesion);
private:
    std::unordered_map<std::string,std::shared_ptr<file>> map_;
    bool absolutepath(std::string &str);
    std::string path_css;
    std::string path_file;
    
};
#endif  