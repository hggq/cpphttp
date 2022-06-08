
 
#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <list>
#include <filesystem>
#include <mysqlx/xdevapi.h>

namespace fs = std::filesystem;
//g++ cli/modelsmar.cpp -o climodel -std=c++20 -Iinclude -lmysqlcppconn8


int main(){
     
     http::controllerparse ctp;
    fs::path current_path=fs::current_path();

    std::cout<<"\033[36m 🍄 current path:\033[0m \033[1m\033[35m"<<current_path.string()<<"\033[0m"<<std::endl;
    std::string controlpath="controller/";
    std::string controlrunpath="module/controller/";
    fs::path vpath=controlpath;

    if(!fs::exists(vpath)){
        std::cout<<" controller directory not in current path "<<std::endl;
    }
    std::string mysqlconnect="mysqlx://root:123456@127.0.0.1/aaa";
    std::shared_ptr<mysqlx::Session> sess=std::make_shared<mysqlx::Session>(mysqlconnect);   

    mysqlx::RowResult res= sess->sql("SHOW FULL COLUMNS FROM user").execute();
 const mysqlx::Columns &columns = res.getColumns();
   
         for (unsigned char index=0; index < res.getColumnCount(); index++)
        {       
             std::count<<"\t"<<columns[index].getColumnName();              
        }

    
                mysqlx::Row row;
                int j=0;
                while ((row = res.fetchOne()))
                {
                    for(int i=0;i<res.getColumnCount();i++){
                            std::count<<"\t"<<row[i];   
                    }
                    
                    j++;
                     
                }
    return 0;
}