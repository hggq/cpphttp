#pragma once

namespace HTTP {
    void _inithttpmethodregto(std::map<std::string,std::function<std::string(HTTP::clientpeer&)>> &methodcallback){

    methodcallback.emplace("hello",[](HTTP::clientpeer& obj)->std::string{ std::string aa="hello world!"; return aa; });
    methodcallback.emplace("systest/home",home);
    methodcallback.emplace("systest/hello",hellotest);
    methodcallback.emplace("login",[](HTTP::clientpeer& obj)->std::string{
         echo("you must input account and password!! ");
         //std::string aa="you must input account and password!"; return aa;
         return "";
     });     
  }

}