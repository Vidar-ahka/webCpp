#include"page.h"

page::page(std::string path)
{
    std::fstream file;
    file.open(path.c_str());
    
    if(!file.is_open())
    {
        return;
    }    
    open_file = true;
    file.seekg(0,std::ios::beg);       
    size_ = 0;
    char var;
    int  count  = 0;
    bool work = false;
    int  open;
    int  close;

    std::shared_ptr<para> para_ = std::make_shared<para>();
    
    while(file.get(var))
    {

        if(var =='{')
        {
            ++count;
        }
        else if(var=='"' &&count == 2)
        {
        
            if(work)
            {
                close = para_.get()->begin.size() - open;
            }
            else 
            {
                open = para_.get()->begin.size()+1;
                work = true;
            }
        }
        else if(work)
        {
            
            if(count>2 &&count<0)
            {
                work = false;
                open  = -1;
                close = -1;
            }
            else if(var =='}')
            {         
                --count;   
            }          
            else if(count == 0)
            {
                work  = false;
                para_.get()->key = para_.get()->begin.substr(open,close);
                para_.get()->begin.resize(open-3);
                txt_.push_back(para_);
                para_ = std::make_shared<para>();
            } 
        }
        else if(count!=2) count  = 0;     
        para_.get()->begin.push_back(var);
    }

    file.close();

    if(para_ !=  (*txt_.rbegin()))
    {
        txt_.push_back(para_);
    }
    for(auto &i:txt_)
    {
        size_+=i.get()->begin.size();
    }
}
bool page::empty()
{
    return open_file ;
}
size_t page::size()
{
    return   size_ ; 
}

std::list<std::shared_ptr<para>> &  page :: getlist()
{
    return  txt_;
}