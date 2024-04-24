#include"pages.h"
pages::pages() = default;

pages::pages(std::vector<std::string> &paths)
{
    append_doc_html(paths);
}

void pages::append_doc_html(std::string path)
{
    map_[path] = std::make_shared<page>(path);
}

void   pages::append_doc_html(std::string &path)
{
    map_[path] = std::make_shared<page>(path);

}
void   pages::append_doc_html(std::vector<std::string> &paths)
{
    for(auto &i: paths)
    {
        map_[i] = std::make_shared<page>(i);
    }
}
void  pages::setpathhtmldir(std::string & path)
{
    this->path_html = path;
}
std::shared_ptr<page> pages::getpage(std::string &path)
{ 
     
    if(!map_.count(path))
    {
        std::shared_ptr<page> page_=std::make_shared<page>(path_html+path);
        if(!page_->empty())
        {
            map_[path] = page_;
        }
        return page_;
    }
    return map_[path];
}