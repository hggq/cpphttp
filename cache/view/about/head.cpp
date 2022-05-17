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

//g++ cache/view/about/head.cpp -o module/view/about/head.so -shared -fPIC -std=c++20 -I../../include ../../src/request.cpp   -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem

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

        
 echo<<"<table width=\"111\" border=\"11\">\n    <tbody>\n      <tr>\n        <td>&nbsp;myname:";
 echo<<(std::string)obj["name"]; 
 echo<<"</td>\n        <td>&nbsp;</td>\n        <td>&nbsp;myname:";
 echo<<(std::string)obj["name"]; 
 echo<<"</td>\n      </tr>\n      <tr>\n        <td>&nbsp;aa</td>\n        <td>&nbsp;bb</td>\n        <td>&nbsp;cc</td>\n      </tr>\n      <tr>\n        <td>&nbsp;a</td>\n        <td>&nbsp;b</td>\n        <td>&nbsp;c</td>\n      </tr>\n    </tbody>\n  </table>";

            return echo.str();
        }

            BOOST_DLL_ALIAS(HTTP::view, view)
            BOOST_DLL_ALIAS(HTTP::_initview, _initview)
            BOOST_DLL_ALIAS(HTTP::_initserver, _initserver)
        }
    