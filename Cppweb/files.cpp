#include"files.h"
files::files()
{

}
void files::setpathfile(std::string & path)
{
    this->path_file =  path;
    if(this->path_file.back()!='/')
    {
        this->path_file.push_back('/');
    }
}
std::shared_ptr<file> files::get(std::string &path)
{
    if(path.empty())
    {
        return std::make_shared<file>();
    }
    if(map_.count(path))
    {
        return  map_[path];
    }
    std::shared_ptr<file> file_ = std::make_shared<file>(absolutepath(path)? path : combinepath(path));
    if(!file_->empty())
    {
        map_[path] = file_;
            
    }
    return  file_;
  
}

std::string  files::combinepath(std::string & path)
{
    std::string str;
    str.reserve(path_file.size()+path.size());
    str.append(path_file);
    if(path.front()=='/')
    {
        str.pop_back();
    }
    str.append(path);
    
    return str;
}


bool files::absolutepath(std::string &str)
{
    return realpath(str.c_str(),nullptr) != NULL;

}
