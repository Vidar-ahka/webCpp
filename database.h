#ifndef  DATABASE_H 
#define DATABASE_H
#include"pqxx/pqxx"
#include"string"
#include"iostream"
#include"vector"


using namespace pqxx;

class DataBase
{

public:

    DataBase(const std::string dboption);
    ~DataBase();
    
    bool is_open();
    bool adduser(std::string name , std::string email , std::string password);
    bool deleteuser(int id);
    bool setname    (int id, std::string new_name);
    bool setemail   (int id, std::string current_email,    std::string new_email);
    bool setpassword(int id, std::string current_password, std::string new_password);
    std::shared_ptr<result> getquery(std::string query );

private:
    bool is_valid_data(work &tnx,std::stringstream &request);
    
    connection * connect;
    std::string dboption;
    std::string tablename = "test";
};
#endif