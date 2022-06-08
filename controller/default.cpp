
#include "http.hpp"
#include "orm.h"
#include "httpclient.h"
 
/*
--compiler--begin--
--compiler--end--
*/

 
namespace http {
 
std::string menubar(http::clientpeer& client){
     client.vobj["home"]="/";
     client.vobj["news"]="/news";
     client.vobj["about"]="/about";
 
   client<<"<p align=\"center\">newqefqqqq!</p>";
   client<<"<p><a href=\"/weibo/home\">home</p>";
   client<<"<p><a href=\"/weibo/hello\">content</p>";
    viewshow("about/head");
     return "";
} 

std::string home(http::clientpeer& client){
    client<<"hello world!";
    return "";
} 

std::string _init404(http::clientpeer& client){
   client<<"<p><a href=\"/weibo/home\">home</p>";
   client<<client.vobj["get"]["aa"];
   return "";
}
_SHOWS(menubar,header)
_SHOW(home)
_SHOW(_init404)


// BOOST_DLL_ALIAS(http::hello, hello)
// BOOST_DLL_ALIAS(http::menubar, header)


}