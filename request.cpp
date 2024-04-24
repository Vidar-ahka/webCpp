#include"request.h"
#include"iostream"

request::request()=default;
request::request(std::string &buff )
{
    parsing(buff);
}
request::~request()
{

}
void request::parsing(std::string &buff  )
{
  
    parsing_1(buff);
    parsing_2(buff);
    this->buff = std::move(buff);
}
std::string request::headers(std::string name)
{
    if(headers_.count(name))
    {
        auto &it = headers_[name];
        return this->buff.substr(it.first,it.second);
    }
    name+=':';

    size_t size_ = this->buff.find(name,0);
    
    if(size_ != std::string::npos)
    {
        size_t beg_pos = size_   + name.size()+2;
        size_t end_pos = beg_pos + this->buff.find("\n",beg_pos); 
        headers_[name] =  std::pair<size_t,size_t>(beg_pos,end_pos);
        return  this->buff.substr(beg_pos,end_pos);
    }
    return "";
}


void request::parsing_1(std::string& buff)
{
    size_t i = 0;
    std::string str;    
    while(buff[i]!=' ')
    { 
        str.push_back(buff[i]);
        ++i;
    }
    if(str == "GET")
    {
        status = Em::GET;
    }     
    str.clear();
    while(buff[i]==' ')++i;

    while(buff[i]!=' '&&buff[i]!='?')
    {
        url.push_back(buff[i++]);
    }
    ++i;
    while(buff[i]!=' ')
    {
        if(buff[i]=='=')
        {
            auto  & it = GET[str];
            str.clear();
            
            size_t j = 1;
            while(buff[i+j]!=' '&& buff[i+j]!='&')
            {
                it.push_back(buff[i+j++]);
            }
            if(it[it.size()-1]=='+')
            {
                it.pop_back();    
            }
            i+=j;
        }
        else 
        {
            str.push_back(buff[i]);
        }
        ++i;
    }
}
void request::parsing_2(std::string& buff)
{

    std::string  accept = "Accept:";
    size_t beg_pos  = buff.find(accept);
    
    if(beg_pos!= std::string::npos)
    {
        beg_pos = beg_pos + accept.size()+1;
        while (buff[beg_pos]!='/')
        {
            type.push_back(buff[beg_pos++]);
        }
        while(buff[++beg_pos]!=','&&buff[beg_pos]!='\n')
        {
            
            extension.push_back(buff[beg_pos]);
        }      
      
        
    }
}
std::string& request::gettype()
{
    return type;
}
std::string& request::getextension()
{
   
    return extension;
}
Em request::method()
{
    return status;
}




