#include"files.h"
files::files()
{

}

std::shared_ptr<file> files::get(std::string & path_html,std::string &path,std::string &type)
{
    if(path.empty())
    {
        return std::make_shared<file>();
    }
   
    std::string str;

    if(!absolutepath(path))
    {
        str.reserve(path_html.size()+path.size());
        str.append(path_html);
    }
    if(path[0]=='/')
    {
        str.pop_back();
    }
    str.append(path);
    
    if(!map_.count(str))
    {
        std::shared_ptr<file> file_ = std::make_shared<file>(str,type);
        if(!file_->empty())
        {
            map_[str] = file_;
            return file_;
        }
        return  file_;
    }
    return  map_[str];
}
bool files::absolutepath(std::string &str)
{
    return realpath(str.c_str(),nullptr) != NULL;

}
