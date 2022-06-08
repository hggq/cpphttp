#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <boost/dll/alias.hpp>
#include <boost/function.hpp>
#include <boost/dll/import.hpp>

#include "request.h"
#include <map> 
#include <vector>
#include <ctime>
#include <array>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>
#include "httpsocommonapi.h" 

//g++ cache/view/about/test.cpp -o module/view/about/test.so -shared -fPIC -std=c++20 -I../../include ../../src/request.cpp   -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem

  namespace http {
       
        std::string view(http::OBJ_VALUE &obj){
            std::ostringstream echo;

        
 echo<<"<html>\n<head>\n    <meta charset=\"utf-8\">\n<title>hello world 标题</title>\n</head>\n<body>\n\nmyname:null\n<ul>\n\n</ul>\n";

            return echo.str();
        }

            BOOST_DLL_ALIAS(http::view, view)
            BOOST_DLL_ALIAS(http::clientapi::setclientapi, _setclientapi)
        }
    