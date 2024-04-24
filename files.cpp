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
        std::string & ref = type == "css" ? path_css : path_file;
        str.reserve(ref.size()+path.size());
        str.append(ref);
    }
    if(path[0]=='/'&&str.back()!='/')
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

void files::setpathcss(std::string  & path)
{
    this->path_css = path;
}
void files::setpathfile(std::string  & path)
{
    this->path_file = path;
}
    
bool files::absolutepath(std::string &str)
{
    return realpath(str.c_str(),nullptr) != NULL;

}
