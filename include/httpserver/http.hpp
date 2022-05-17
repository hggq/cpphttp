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
// #include "httpclient.h"
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


namespace HTTP {

    typedef boost::function<std::string(std::string)> http_callback_t;//header("");getheader setcookie() cookie
    typedef boost::function<void(std::string)> echo_callback_t;//header("");getheader setcookie() cookie
    typedef boost::function<void(std::string&)> echo_callbackand_t;
    typedef boost::function<int(const char *,int)> webscoket_callback_t;//websocket send
   // typedef boost::function<void(const char *,int)> webscoket_readcall_t;//websocket read
   typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
    typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;

    typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
    typedef boost::function<bool(std::list<std::string>&,size_t)> mysql_callbacksql_rollback;
    std::map<std::string,modulemethod_callback_t> _render;
    std::map<std::string,webscoket_callback_t> _senddata;
    std::map<std::string,http_callback_t> _httpsever;
    std::map<std::string,echo_callback_t> _echocallback;
    std::map<std::string,echo_callbackand_t> _echocallbackand;
     std::map<std::string,mysql_callbackand_t> _mysqlpluginselect;
     std::map<std::string,mysql_callbacksql_t> _mysqlpluginedit;
     std::map<std::string,mysql_callbacksql_rollback> _mysqlplugincommit;
    HTTP::OBJ_VALUE vobj;
    std::mutex controlinitmtx;

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
       _echocallback["sendfile"](filename);
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void header(std::string namevalue){
   // _header.emplace_back(namevalue);
}
void header(std::string name,std::string value){
    name.append(": ");  
    name.append(value);    
    //_header.emplace_back(name);
}
void setcookie(std::string name,std::string value,std::string path="/",unsigned int timeout=0){
    name.append(": ");  
    name.append(value);    
    //_header.emplace_back(name);
}
void setcookie(std::string name,std::string &value,std::string path="/",unsigned int timeout=0){
    name.append(": ");  
    name.append(value);    
    //_header.emplace_back(name);
}
HTTP::OBJ_VALUE getsession(std::string keyname){
    HTTP::OBJ_VALUE b;
    return b;
}
void setsession(std::string keyname,std::string value){
    
}
void setsession(std::string keyname,std::string &value){
    
    
}
void setsession(HTTP::OBJ_VALUE &value){
    
}
void echo_flush(){
    try {
       _echocallback["echoflush"]("");
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
}
void loop_send(){
     
}
void echo_json(std::string b){
   if(b.size()>0){
       _render["jsonsend"](b);
   }  
}
void echo_json(){
       _render["jsonsend"]("application/json");
}
void echo_json(HTTP::OBJ_VALUE &obj){
 
      _render["jsonsend"]("")(obj);
}

mysqlx::RowResult domysqlexecute(std::string &sql,size_t dbhash){

   try {
                return  _mysqlpluginselect["mysql"](sql,dbhash);   
    }catch (std::exception& e)  
    {  
       std::cout<<"http error:" << e.what() << std::endl; 
       mysqlx::RowResult temp;
       return temp; 
    }  
                
}
mysqlx::SqlResult domysqleditexecute(std::string &sql,size_t dbhash){

   try {
                return  _mysqlpluginedit["mysql"](sql,dbhash);   
    }catch (std::exception& e)  
    {  
       std::cout<<"http error:" << e.what() << std::endl; 
       mysqlx::SqlResult temp;
       return temp; 
    }  
                
}
bool domysqlcommit(std::list<std::string> &sql,size_t dbhash){
            try {
                return  _mysqlplugincommit["mysql"](sql,dbhash);   
    }catch (std::exception& e)  
    {  
       std::cout<<"http error:" << e.what() << std::endl; 
       return false;
    }  
                        

 }
 unsigned int _initmysqlcommitplugin(std::map<std::string,mysql_callbacksql_rollback>& function){
 

      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_mysqlplugincommit.size()==0){
          _mysqlplugincommit=function;
      }
      lock.unlock();
      return get_controlversion();
}
unsigned int _initmysqleditplugin(std::map<std::string,mysql_callbacksql_t>& function){
 

      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_mysqlpluginedit.size()==0){
          _mysqlpluginedit=function;
      }
      lock.unlock();
      return get_controlversion();
}
unsigned int _initmysqlplugin(std::map<std::string,mysql_callbackand_t>& function){
 
      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_mysqlpluginselect.size()==0){
        
          _mysqlpluginselect=function;
      }
      lock.unlock();
      return get_controlversion();
}
unsigned int _initserver(std::map<std::string,http_callback_t>& function){
 

      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_httpsever.size()==0){
          _httpsever=function;
      }
      lock.unlock();
      return get_controlversion();
}
unsigned int _initvoidstringcallback(std::map<std::string,echo_callback_t>& function){
    //std::map<std::string,echo_callback_t> _echocallback;

      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_echocallback.size()==0){
          _echocallback=function;
      }
      lock.unlock();
      return get_controlversion();
}
unsigned int _initvoidstringandcallback(std::map<std::string,echo_callbackand_t>& function){
    //std::map<std::string,echo_callback_t> _echocallback;

      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_echocallbackand.size()==0){
          _echocallbackand=function;
      }
      lock.unlock();
      return get_controlversion();
}

unsigned int _initcallback(std::map<std::string,modulemethod_callback_t>& function){
      std::unique_lock<std::mutex> lock(controlinitmtx); 
      if(_render.size()==0){
          _render=function;
      }
      lock.unlock();
      return get_controlversion();
}

#ifndef _CONTROL_DESTROY 
void _destroy(){
     
}
#endif

void echo(std::string &b){
     try {
       _echocallbackand["echo"](b);
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(int b){
     try {
       _echocallback["echo"](std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(unsigned int b){
     try {
       _echocallback["echo"](std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(long long b){
     try {
       _echocallback["echo"](std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(unsigned long long b){
     try {
       _echocallback["echo"](std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(std::string &&b){
     
    try {
           _echocallback["echo"](std::move(b));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
}
void echo(HTTP::OBJ_VALUE &b){
     
    try {
           _echocallback["echo"](b.to_string());
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
}
void viewshow(std::string modulemethod){
    try {
       _render["viewnotobj"](modulemethod);
    }catch (std::exception& e)  
    {  
        std::cout << e.what() << std::endl;  
    }  
   
} 
std::string viewfetch(std::string modulemethod){
 
  try {
      return _render["viewfetchnotobj"](modulemethod)(vobj);

    }catch (std::exception& e)  
    {  
        //std::cout << e.what() << std::endl; 
        //echo.append(e.what());
        return "not found:"+modulemethod; 
    }   
} 
void viewshow(std::string modulemethod,HTTP::OBJ_VALUE &b){
    try {
       _render["viewobj"](modulemethod)(b);
    }catch (std::exception& e)  
    {  
        //echo.append(e.what());
        std::cout << e.what() << std::endl;  
    }  
   
} 
std::string viewfetch(std::string modulemethod,HTTP::OBJ_VALUE &b){
 
  try {
      return _render["view"](modulemethod)(b);
    }catch (std::exception& e)  
    {  
        return "not found:"+modulemethod; 
    }  
} 
std::string loadmodule(std::string modulemethod){
    try {
        return _render["router"](modulemethod)(vobj);
    }catch (std::exception& e)  
    {  
        return e.what();
        //std::cout << e.what() << std::endl;  
    }  
   
} 
std::string loadmodule(std::string modulemethod,HTTP::OBJ_VALUE &b){
    try {
        return _render["router"](modulemethod)(b);
    }catch (std::exception& e)  
    {  
        return e.what();
        //std::cout << e.what() << std::endl;  
    }  
   
} 
BOOST_DLL_ALIAS(HTTP::_initcallback, _initcallback)
BOOST_DLL_ALIAS(HTTP::_initvoidstringandcallback, _initandcall)
BOOST_DLL_ALIAS(HTTP::_initvoidstringcallback, _initvoidcall)
BOOST_DLL_ALIAS(HTTP::_initserver, _initserver)
BOOST_DLL_ALIAS(HTTP::_initmysqlplugin, _initmysqlplugin) 
BOOST_DLL_ALIAS(HTTP::_initmysqleditplugin, _initmysqleditplugin) 
BOOST_DLL_ALIAS(HTTP::_initmysqlcommitplugin, _initmysqlcommitplugin) 

BOOST_DLL_ALIAS(HTTP::_destroy, _destroy)

#define _SHOW(A) BOOST_DLL_ALIAS(HTTP::A,A) 
#define _SHOWS(A,B) BOOST_DLL_ALIAS(HTTP::A,B) 
}
#endif