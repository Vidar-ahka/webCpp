#include"httprespone.h"
httprespone::httprespone()
{
}

httprespone::httprespone(const  int status, const  std::string type, const std::string extension )
{
    
    this->status = status;
    this->type = type;
    this->extension = extension; 
}

    
httprespone::~httprespone()
{

}

void httprespone::settype(const std::string type)
{
    this->type =  type;
}

void httprespone::setextension(const std::string extension)
{
    this->extension = extension;
}


std::string  httprespone::gettype()
{

    return type;
}

std::string  httprespone::getextension()
{
    return extension;
}

int httprespone::getstatus()
{
    return status;
}

bool httprespone::empty()
{
    return status == 0 && type.empty()&&extension.empty();
}
/*============================================*/

httpresponehtlm :: httpresponehtlm()
{

}

httpresponehtlm::httpresponehtlm( const int status, const std::string type,
const std::string extension)
{
    this->status = status;
    this->type = type;
    this->extension = extension; 
}    

 
httpresponehtlm::~httpresponehtlm()
{

}

bool httpresponehtlm :: empty()
{
    return httprespone::empty()&&html.empty();
}

void httpresponehtlm :: add_html_code(const std::string &html_code)
{
    html.append(html_code);
}

void httpresponehtlm ::clear()
{
    html.clear();
}

void httpresponehtlm ::reserve(size_t size_)
{
    html.reserve(size_);
}

size_t httpresponehtlm ::size()
{
    return  html.size();
}

char * httpresponehtlm ::data()
{
   return  html.data();
} 



/*=====================================================*/

httpresponefile::httpresponefile()
{

}

httpresponefile ::httpresponefile(const  int status, 
const std::string type,const std::string extension)
{
    this->status = status;
    this->type = type;
    this->extension = extension; 
}

httpresponefile::httpresponefile(const int status, const std::string type,
const std::string extension,  std::shared_ptr<file> file_)
{
    this->status = status;
    this->type = type;
    this->extension = extension; 
    this->file_ = file_;  
}

httpresponefile::~httpresponefile()
{
    
}

bool httpresponefile::empty()
{
   
    return  file_==NULL || httprespone::empty() || file_->empty();
}

void httpresponefile :: clear()
{
    file_ = NULL;
}

size_t  httpresponefile::size()
{
    if(file_==NULL)
    {
        return 0;
    }
    return file_->size();
}

char * httpresponefile::data()
{
    if(file_==NULL)
    {
        return NULL; 
    }
    return file_->byte();
}

void httpresponefile::addfile(const  std::shared_ptr<file> file_)
{
    this->file_ = file_;
}
