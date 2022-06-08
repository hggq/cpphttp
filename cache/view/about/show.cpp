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

//g++ cache/view/about/show.cpp -o module/view/about/show.so -shared -fPIC -std=c++20 -I../../include ../../src/request.cpp   -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem

  namespace http {
       
        std::string view(http::OBJ_VALUE &obj){
            std::ostringstream echo;

        
 echo<<"<html>\n<head>\n    <meta charset=\"utf-8\">\n<title>hello world 标题111</title>\n</head>\n<body>\n";
  try{ echo<<clientapi::get().api_loadviewobjcall("about/head")(obj); }catch (std::exception& e)   {          std::cout << e.what() << std::endl;  }
 echo<<"myname:";
 echo<<obj["name"]; 
 echo<<"<ul>\n";

for(auto &a:obj["list"].as_array()){

 echo<<"<li>";
 echo<<a.second.as_string(); 
 echo<<"</li>\n";

}

 echo<<"</ul>\n";

if(obj["my"].is_array()){

 echo<<"    ";

    for(auto &b:obj["my"].as_array()){
    
 echo<<"    <div>";
 echo<<b.second.as_string(); 
 echo<<"</div>\n    ";

    }
    
 echo<<"      \n";

}

 echo<<"\n</body>\n</html>\n\n\n";

            return echo.str();
        }

            BOOST_DLL_ALIAS(http::view, view)
            BOOST_DLL_ALIAS(http::clientapi::setclientapi, _setclientapi)
        }
    