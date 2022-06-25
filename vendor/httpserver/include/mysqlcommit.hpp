#ifndef HTTP_MYSQLCOMMIT_HPP
#define HTTP_MYSQLCOMMIT_HPP

#include <list>
#include <string>
#include <iostream>
//using namespace HTTP;
namespace orm {

    class mysqlcommit
    {
    public:
        ~mysqlcommit(){
            std::cout<<"destructor called!"<<std::endl;
                               std::cout<<"~mysqlcommit"<<std::endl;
                    for(;!sql.empty();){
                          std::cout<<sql.front()<<std::endl;
                          sql.pop_front();
                    }
        }
        mysqlcommit(const mysqlcommit&)=delete;
        mysqlcommit& operator=(const mysqlcommit&)=delete;
        static mysqlcommit& getInstance(){
           thread_local static mysqlcommit instance;
            return instance;

        }
       std::list<std::string> sql; 
    private:
        mysqlcommit(){}
    };

}
#endif