#ifndef HHTPRESPONE_H
#define HHTPRESPONE_H
#include"string"
#include"unordered_map"
#include"memory"
#include"forward_list"
#include"file.h"
#include"page.h"
#include"iostream"
class client;


class httprespone
{
public:
    httprespone();

    httprespone(const int status, const std::string type,const std::string extension);

    
    virtual ~httprespone();
    virtual void   clear()= 0;
    virtual char * data() = 0;
    virtual size_t size() = 0;
    virtual std::string gettype();
    virtual std::string getextension();
    virtual int getstatus();   
    void settype(const std::string type);
    void setextension(const std::string extension);
    virtual bool empty();
    friend class client;
protected:

    std::string  type;
    std::string  extension;
    int status;
    
};

class httpresponehtlm : public httprespone
{
public:
    httpresponehtlm();
    httpresponehtlm  (const int status, const std::string type,  const std::string extension );
    virtual ~httpresponehtlm();
    void clear()  override;
    size_t size() override;
    char * data() override;
    bool empty()  override ;
    void add_html_code(const std::string &html_code);
    void reserve(size_t size_);
    
private:
    std::shared_ptr<page> page_;
    std::string html;

};

class httpresponefile :public httprespone
{
public:
    httpresponefile();
    httpresponefile(const  int status, const   std::string type,const   std::string extension_);
    httpresponefile(const int status, const std::string type, const std::string extension, std::shared_ptr<file> file_);
    
    virtual ~httpresponefile();
    void   clear()  override;
    size_t size()   override;
    char * data()   override;
    bool   empty()  override;
    void   addfile(const std::shared_ptr<file> file_);
private:
    std::shared_ptr<file> file_;
};
#endif