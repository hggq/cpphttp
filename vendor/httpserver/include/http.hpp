#ifndef HTTP_CONTROL_HPP
#define HTTP_CONTROL_HPP
#include <iostream>
#include <cstdio>
#include <string>
#include <sstream>
#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION
#include <boost/dll/alias.hpp>
#include <boost/function.hpp>
#include <boost/dll/import.hpp>
#include <string_view>
#include <memory>
#include "request.h"
#include "md5.hpp"
#include "http_header.hpp"
#include "Clientpeer.h"
#include <map> 
#include <thread> 
#include <vector>
#include <ctime>
#include <mutex>
#include <array>
#include <condition_variable>
#include <sys/time.h>
#include <sys/stat.h>
#include <mysqlx/xdevapi.h>
#include <unistd.h>
#include <cstdlib>
#include "httpsocommonapi.h" 


namespace http {
   unsigned int get_controlversion(){
       return 0x01000000;
   } 

  inline  std::string stringaddslash(std::string &content){
        std::string temp;
        for(int i=0;i<content.size();i++){
            if(content[i]=='\''){
                temp.append("\\'");
                continue;
            }else if(content[i]=='"'){
                temp.append("\\\"");
                continue;
            }
            temp.push_back(content[i]);
        }
        return std::move(temp);
   }  
  inline  std::string jsonaddslash(std::string &content){
        std::string temp;
        for(int i=0;i<content.size();i++){
            if(content[i]=='"'){
                temp.append("\\\"");
                continue;
            }
            temp.push_back(content[i]);
        }
        return std::move(temp);
   }  
  inline  long long intval(std::string &content){
        long long temp=0;
        for(int i=0;i<content.size();i++){
            if(content[i]==0x20){
                break;
            }
            if(content[i]>='0'&&content[i]<='9'){
                    temp=temp*10+(content[i]-'0');
            }
             
        }
        return temp;
   }  
   void send_file(std::string filename){
     
     try {
       clientapi::get().api_send_file(filename);
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void header(std::string namevalue){

}
void header(std::string name,std::string value){
    name.append(": ");  
    name.append(value);    
}
void setcookie(std::string name,std::string value,std::string path="/",unsigned int timeout=0){
    name.append(": ");  
    name.append(value);    
}
void setcookie(std::string name,std::string &value,std::string path="/",unsigned int timeout=0){
    name.append(": ");  
    name.append(value);    
}
http::OBJ_VALUE getsession(std::string keyname){
    http::OBJ_VALUE b;
    return b;
}
void setsession(std::string keyname,std::string value){
    
}
void setsession(std::string keyname,std::string &value){
    
    
}
void setsession(http::OBJ_VALUE &value){
    
}
void echo_flush(){
    clientapi::get().api_echo_flush("");
}
void loop_send(){
     
}
void echo_json(std::string b){
   clientapi::get().api_sendjsoncall(b);
}
void echo_json(){
       clientapi::get().api_sendjsoncall("application/json");
}
void echo_json(http::OBJ_VALUE &obj){
      clientapi::get().api_sendjsoncall("")(obj);
}

mysqlx::RowResult domysqlexecute(std::string &sql,size_t dbhash){
        return    clientapi::get().api_mysqlselect(sql,dbhash);             
}
mysqlx::SqlResult domysqleditexecute(std::string &sql,size_t dbhash){
 return clientapi::get().api_mysqledit(sql,dbhash);       
}
bool domysqlcommit(std::list<std::string> &sql,size_t dbhash){
   return  clientapi::get().api_mysqlcommit(sql,dbhash);   
 }
#ifndef _CONTROL_DESTROY 
void _destroy(){
     
}
#endif

void echo(std::string &b){
     clientapi::get().api_echoassignand(b);
}
void echo(int b){
    clientapi::get().api_echoassign(std::move(std::to_string(b)));
}
void echo(unsigned int b){
    clientapi::get().api_echoassign(std::move(std::to_string(b)));
}
void echo(long long b){
    clientapi::get().api_echoassign(std::move(std::to_string(b)));
}
void echo(unsigned long long b){
    clientapi::get().api_echoassign(std::move(std::to_string(b)));
}
void echo(std::string &&b){
    clientapi::get().api_echoassign(std::move(b));
}
void echo(http::OBJ_VALUE &b){
     clientapi::get().api_echoassign(b.to_string());       
}
void viewshow(std::string modulemethod){
   clientapi::get().api_loadviewnotcall(modulemethod);
} 
std::string viewfetch(std::string modulemethod){
    
   return clientapi::get().api_loadviewfetchnotcall(modulemethod)(clientapi::get().getpeer()->vobj); 
} 
void viewshow(std::string modulemethod,http::OBJ_VALUE &b){
    clientapi::get().api_loadviewobjcall(modulemethod)(b);
} 
std::string viewfetch(std::string modulemethod,http::OBJ_VALUE &b){
 return  clientapi::get().api_loadview(modulemethod)(b);
} 
std::string loadmodule(std::string modulemethod){
  return  clientapi::get().api_loadcontrol(modulemethod)(clientapi::get().getpeer()->getpeer());
} 
std::string loadmodule(std::string modulemethod,http::clientpeer &b){
   return clientapi::get().api_loadcontrol(modulemethod)(b);
} 
BOOST_DLL_ALIAS(http::clientapi::setclientapi, _setclientapi)
#define _SHOW(A) BOOST_DLL_ALIAS(http::A,A) 
#define _SHOWS(A,B) BOOST_DLL_ALIAS(http::A,B) 
}
#endif