#include"pages.h"
pages::pages() = default;
void  pages::setpathhtmldir(std::string & path)
{
    this->path_html = path;
    if(this->path_html.back()!='/')
    {
        this->path_html.push_back('/');
    }
}
std::shared_ptr<page> pages::getpage(std::string &path)
{ 
    
    if(map_.count(path))
    {
         return map_[path];
    }
    
    std::string str;
    str.reserve(path.size()+path_html.size()); 
    str.append(path_html);
    if(path.front()=='/')
    {
        str.pop_back();
    }
    str.append(path);
    
    std::shared_ptr<page> page_=std::make_shared<page>(str);  
    if(!page_->empty())
    {
        map_[path] = page_;
    }
    return page_;
    
   
}