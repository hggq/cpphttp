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

//g++ cache/view/about/show.cpp -o module/view/about/show.so -shared -fPIC -std=c++20 -I../../include ../../src/request.cpp   -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem

  namespace HTTP {

        typedef boost::function<std::string(std::string)> http_callback_t;
        typedef boost::function<std::string(HTTP::OBJ_VALUE&)> method_callback_t;
        typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
        std::map<std::string,modulemethod_callback_t> _render;
        std::map<std::string,http_callback_t> _httpsever;
        void _initview(modulemethod_callback_t& function){
            if(_render.size()==0){
                _render["view"]=function;
                std::cout<<"_render view view view -----------"<<std::endl;
            }
            
        }
         void _initserver(std::map<std::string,http_callback_t>& function){
            if(_httpsever.size()==0){
                _httpsever=function;
                std::cout<<"_render server server server -----------"<<std::endl;
            }
            
        }
       
        std::string view(HTTP::OBJ_VALUE &obj){
            std::ostringstream echo;

        
 echo<<"<html>\n<head>\n    <meta charset=\"utf-8\">\n<title>hello world 标题</title>\n</head>\n<body>\n";
  try{ echo<<_render["view"]("about/head")(obj); }catch (std::exception& e)   {          std::cout << e.what() << std::endl;  }
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

            BOOST_DLL_ALIAS(HTTP::view, view)
            BOOST_DLL_ALIAS(HTTP::_initview, _initview)
            BOOST_DLL_ALIAS(HTTP::_initserver, _initserver)
        }
    