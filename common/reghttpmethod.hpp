#pragma once
#include "systest.hpp"
namespace http {
    void _inithttpmethodregto(std::map<std::string,std::function<std::string(http::clientpeer&)>> &methodcallback){

    methodcallback.emplace("hello",[](http::clientpeer& obj)->std::string{ std::string aa="hello world!"; return aa; });
    methodcallback.emplace("systest/home",home);
    methodcallback.emplace("systest/test",test);
    methodcallback.emplace("systest/hello",hellotest);
    methodcallback.emplace("login",[](http::clientpeer& obj)->std::string{
         echo("you must input account and password!! ");
         //std::string aa="you must input account and password!"; return aa;
         return "";
     });     
  }

}