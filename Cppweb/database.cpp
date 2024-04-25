#include"database.h"
DataBase::DataBase(const std::string dboption)
{  
    
    this->dboption = dboption;
    connect = new connection(dboption);
    if(!is_open())
    {
        std::cout<<"data base dont open \n";
        return;
    }
    std::cout<<"data base open \n";

    work tnx(*connect);
    std::stringstream str;
    str<<"SELECT * FROM pg_tables WHERE tablename = '"<<tablename<<"';";
    

    if(!is_valid_data(tnx,str))
    {
        str.clear();
        str<<"CREATE TABLE "<<tablename<<"(id_user  BIGSERIAL,name TEXT ,email TEXT,password TEXT);";
        tnx.exec(str); 
    }
    tnx.commit();

}
DataBase::~DataBase()
{
    connect->disconnect();
    delete connect;
}
bool DataBase::is_open()    
{
    return connect->is_open();
}


bool DataBase::adduser(std::string Name , std::string email , std::string password)
{
    
    work tnx(*connect);
    std::stringstream str;
    str<<"INSERT INTO "<<tablename<<"(name,email,password) VALUES('"<<Name<<"','"
    <<email<<"','"
    <<password<<"');";  
    tnx.exec(str);
    tnx.commit();
    return false;
}
bool DataBase::deleteuser(int id)
{

   work tnx(*connect);
   std::stringstream str;
   str<<"DELETE FROM  "<<tablename<<" WHERE id_user = "<<id<<';';
   tnx.exec(str);
   tnx.commit();
   return true; 

}
bool DataBase::setname (int id,std::string new_name)
{

    work  tnx(*connect);
    std::stringstream str;
    str<<"UPDATE "<<tablename<< " SET name  = '"<<new_name<<"' WHERE id_user ="<<id<<';';
    tnx.exec(str);
    tnx.commit();
    return true;
}

bool DataBase::setemail   (int id, std::string current_email,std::string new_email)
{
     work tnx(*connect);
     std::stringstream str;
     str<<"SELECT email FROM "<<tablename<< " WHERE id_user = "<< id <<" AND email = '"<<current_email<<"';";  

     if(!is_valid_data(tnx,str))
     {
        tnx.commit();
        return false;
     }
     
     str.clear();
     str<<"UPDATE "<<tablename<<" SET email  = '"<<new_email<<"' WHERE id_user ="<<id<<';';
     
     tnx.exec(str);
     tnx.commit();
     return true;
}
bool DataBase::setpassword(int id, std::string current_password,std::string new_password)
{    
    
     work tnx(*connect);

     std::stringstream str;     
     str<<"SELECT password FROM  "<<tablename<<" WHERE id_user = "<<id<<" AND password  = '"<<current_password<<"';";
     
     if(!is_valid_data(tnx,str))
     {
        tnx.commit();
        return false;
     } 
    
     str.clear();
     str<<"UPDATE "<<tablename<< " SET password = '"<<new_password<<"' WHERE id_user ="<<id<<';';
     
     tnx.exec(str);
     tnx.commit();
     return true;
}

  bool DataBase::is_valid_data(work &tnx,std::stringstream &request)
  {     
        return tnx.exec(request).affected_rows()>0;
  }

std::shared_ptr<result> DataBase::getquery(std::string query )
{
    work tnx(*connect);
    return  std::make_shared<result>(tnx.exec(query));
}
