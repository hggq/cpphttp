#pragma once

namespace HTTP {
    void _inithttpmethodregto(std::map<std::string,std::function<std::string(HTTP::OBJ_VALUE&)>> &methodcallback){

    methodcallback.emplace("hello",[](HTTP::OBJ_VALUE& obj)->std::string{ std::string aa="hello world!"; return aa; });
    methodcallback.emplace("systest/home",home);
    methodcallback.emplace("login",[](HTTP::OBJ_VALUE& obj)->std::string{
         echo("you must input account and password!! ");
         //std::string aa="you must input account and password!"; return aa;
         return "";
     });     
  }

}