#include"file.h"
file::file()
{
    size_ = 0;   
}
file ::file (file  & file_)
{
   this->byte_ = file_.byte_;
   this->size_ = file_.size_;
}

file::file(const std::string &path)
{
    load_t(path);
}

/*file ::file (const std::string path)
{
    load_t(path);
}*/
size_t file ::size()
{
    return size_;
}
char * file ::byte()
{
    return byte_.data();
}
void file ::load(const std::string &path)
{
    load_t(path);
}
void file ::load_t(const std::string &path )
{
   
    try
    {

    std::ifstream file;
    
    file.open(path.c_str(),std::ifstream::binary);
    
    if(!file.is_open())
    {
        std::cout<<"file dont opne : path "<<path<<'\n';
        return;
    }
    file.seekg(0,std::ifstream::end);
    size_= file.tellg();
    if(size_ == 0)
    {
        file.close();
  
        return;
    }
   
    file.seekg(0,std::ifstream::beg);
  
    byte_.reserver(size_);
    file.read(byte_.data(),size_);
    this->path = path;
    file.close();
    
    }
    catch(const std::exception& e)
    {
        std::cerr <<"\n what \n____________________\n "<< e.what() << '\n';
    }
}
 bool file ::empty()
 {
    return byte_.empty() || this->size_ == 0;
 } 