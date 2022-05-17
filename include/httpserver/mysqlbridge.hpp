#ifndef HTTP_MYSQLBRIDGE_HPP
#define HTTP_MYSQLBRIDGE_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"
#include <iostream>
#include  <functional> 
#include <mysqlx/xdevapi.h>
#include  <map> 
#include <typeinfo>
 
#include <memory>
 
#include <list>
#include <queue>
#include "mysqlpool.h" 
 
#include <condition_variable>

namespace HTTP {


     class mysqlapiproxy
    {
    public:
        ~mysqlapiproxy(){
          
        }
        mysqlapiproxy(const mysqlapiproxy&)=delete;
        mysqlapiproxy& operator=(const mysqlapiproxy&)=delete;
        static mysqlapiproxy& getInstance(){
           static mysqlapiproxy instance;
            return instance;

        }
       std::map<size_t,mysqllinkpool> &mysqldbpoolglobal;
    private:
        mysqlapiproxy(){}
    };

}
#endif


