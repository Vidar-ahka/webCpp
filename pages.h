#ifndef PAGES_H
#define PAGES_H

#include"memory"
#include"string"
#include"unordered_map"
#include"page.h"
#include"vector"
class pages
{
    
public:
    pages();

    pages(std::vector<std::string> &paths);

    void  append_doc_html(std::string  path);
    void  append_doc_html(std::string &path);
    void  append_doc_html(std::vector<std::string> &paths);
    void  setpathhtmldir(std::string & path);
    std::shared_ptr<page> getpage(std::string &path);
private:
    std::string path_html;
    std::unordered_map<std::string , std::shared_ptr<page>> map_;
};
#endif