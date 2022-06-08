#ifndef HTTP_MYSQLMODULES_H
#define HTTP_MYSQLMODULES_H

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <vector>
#include <queue>
#include <mysqlx/xdevapi.h>

namespace http {
    //   std::mutex sessedit_mutex,sessselect_mutex;
      class mysqllinkpool{
            public:
                 mysqllinkpool(std::string ms,std::string sl);
                 void addselectsession(unsigned int num);
                   void addeditsession(unsigned int num);
                 mysqlx::RowResult sqlselectfetch(std::string &sql);
                 mysqlx::SqlResult sqleditfetch(std::string &sql);
                  mysqlx::SqlResult sqleditfetch(std::string &sql,long long &effectrow,std::function<std::unique_ptr<mysqlx::Session>(std::string &,mysqlx::SqlResult&,std::unique_ptr<mysqlx::Session>)> func);
                   mysqlx::SqlResult sqleditfetch(std::string &sql,long long &effectrow,std::function<std::unique_ptr<mysqlx::Session>(std::string &,std::unique_ptr<mysqlx::Session>)> funcbeg,std::function<std::unique_ptr<mysqlx::Session>(std::string &,std::unique_ptr<mysqlx::Session>)> funcend);

                 unsigned int getselectpoolnum();
                   unsigned int geteditpoolnum();

                unsigned int clearpool();
              
                 void initpool();
           public:       
           size_t dbhash; 
           unsigned editmax=2,editmin=1,selectmax=2,selectmin=1; 
           unsigned int selectbusynum=0,editbusynum=0;
           std::queue<std::unique_ptr<mysqlx::Session>>  sesseditpool;
           std::queue<std::unique_ptr<mysqlx::Session>>  sessselecttpool; 
           std::string connectedit;
           std::string connectselect;
      };
      
      
      struct mysqlconnect_t{
          std::string type;  
          std::string host;  
          std::string port;  
          std::string dbname;  
          std::string user;
          std::string password;
          std::string pretable;
          std::string maxpool;
          std::string spname;
     };
      std::vector<mysqlconnect_t> getmysqlconfig(std::string filename);
         
}
#endif