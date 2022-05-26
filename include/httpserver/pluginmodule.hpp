#ifndef HTTP_LOADMODULE_HPP
#define HTTP_LOADMODULE_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"
#include "modulemar.hpp"
#include "http_header.hpp"
// #include "mysqlplugin.hpp"
 #include "mysqlconfig.hpp"
// #include "mysqlpool.h"
#include "Clientpeer.h"
#include "mysqlproxyfun.h"
#include "httpsocommonapi.h" 

namespace HTTP {
 
typedef boost::function<void()> callback_t;
typedef boost::function<void(std::string)> echo_callback_t;
typedef boost::function<void(std::string&)> echo_callbackand_t;
typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
typedef boost::function<bool(std::list<std::string>&,size_t)> mysql_callbacksql_rollback;
typedef boost::function<std::string(HTTP::OBJ_VALUE&)> method_callback_t;
typedef boost::function<std::string(HTTP::clientpeer*)> www_method_call;
typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
typedef boost::function<boost::function<std::string(HTTP::clientpeer*)>(std::string)> module_method_call;

std::string siteviewpath="module/view/";
std::string sitecontrolpath="module/controller/";
std::map<std::size_t,std::vector<std::string>>  sharedmethodchache;
std::map<std::size_t,method_callback_t>  sharedpathchache,controlpathchache;
std::mutex loadcontrolmtx,loadviewmtx,moudulecachemethod;
std::string httpempty(HTTP::OBJ_VALUE& a){
    return "<p>--.so image not found--</p>";
}
std::string echoempty(HTTP::OBJ_VALUE& a){
    return "";
}
template<typename T>
T& get_local_global(){
   thread_local static T instance;
    return instance;
}
template<typename T>
T& get_global(){
    static T instance;
    return instance;
}

//class clientpeer;
/////test/////
thread_local modulemar bbb;
thread_local http_header _http_header;

thread_local std::string _output;
thread_local std::string _outputtemp;
thread_local unsigned int _output_type;
thread_local bool loadmoduleinitcall=false;
thread_local HTTP::OBJ_VALUE vobj;
//thread_local wwwserver *_wwwhttpserver;
thread_local HTTP::clientpeer* _threadclientpeer;
thread_local std::map<std::string,std::map<std::string,std::string>> *_thishostsiteconfig;
thread_local std::string _thishostcontrolsopath;
thread_local std::string _thishostviewsopath;
thread_local std::vector<std::string> _header;


method_callback_t loadview(std::string);
method_callback_t loadviewnotcall(std::string);
method_callback_t loadviewfetchnotcall(std::string);
method_callback_t loadviewobjcall(std::string);

method_callback_t loadcontrol(std::string);
method_callback_t modulesendfile(std::string);
method_callback_t modulesenddata(std::string);//websocket使用
std::map<std::string,modulemethod_callback_t> rendercallback;
std::map<std::string,echo_callback_t> _renderechocallback;
std::map<std::string,echo_callbackand_t> _renderechocallbackand;
std::map<std::string,mysql_callbackand_t> _mysqlselectcallback;
std::map<std::string,mysql_callbacksql_t> _mysqlplugineditcallback;
std::map<std::string,mysql_callbacksql_rollback> _mysqlplugicommitcall;
std::once_flag rendercallback_flag;

method_callback_t modulesendfile(std::string name){
    return httpempty;
}
method_callback_t modulesenddata(std::string name){
    return httpempty;
}
void echoassign(std::string name){
   // std::cout<<"mb:"<<name<<std::endl;
    _output.append(std::move(name));
    
}
void send_data(std::string name);
void send_data(std::string &name);
void send_data(unsigned int statecode,std::string name);
void send_data(unsigned int statecode,std::string &name);

void echo_flush(std::string name){
   // std::cout<<"mb:"<<name<<std::endl;
    _output.append(std::move(name));
    //now send data
}
HTTP::clientpeer* getpeer(){
    return _threadclientpeer;
}
void echoassignand(std::string& name){
   // std::cout<<"mb:"<<name<<std::endl;
    _output.append(name);
     
}
void send_file(std::string name);
// void send_file(std::string name){
//     std::cout<<"mb:"<<name<<std::endl;
//     //_output.append(std::move(name));
//     //now send data
// }
void header(std::string namevalue){
    _header.emplace_back(namevalue);
}
void header(std::string name,std::string value){
    name.append(": ");  
    name.append(value);    
    _header.emplace_back(name);
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
std::string renderjsonfetchtosend(HTTP::OBJ_VALUE& b){
        
        _output.append(b.tojson());
        return "";
}
std::string renderjsonlocaltosend(HTTP::OBJ_VALUE& b){
        
        _output.append(vobj.tojson());
        return "";
}
method_callback_t sendjsoncall(std::string modulemethod){

        _outputtemp.clear();
        _outputtemp=modulemethod;
        
        if(modulemethod.size()==0){
            return renderjsonfetchtosend;

        }else  if(modulemethod.size()>0){
            if(modulemethod=="application/json"){
                return renderjsonlocaltosend;
            }else{
                _output.append(modulemethod);    
                return echoempty;
            }  
        } 
        return echoempty;
}
 mysqlx::SqlResult domysqleditexecute(std::string &sql,size_t dbhash){
                auto iter=mysqldbpoolglobal.find(dbhash);

                        mysqlx::SqlResult res = iter->second.sqleditfetch(sql);

                        return std::move(res);

        }   
        mysqlx::RowResult domysqlexecute(std::string &sql,size_t dbhash){
            
                auto iter=mysqldbpoolglobal.find(dbhash);

                        mysqlx::RowResult res = iter->second.sqlselectfetch(sql);

                        return std::move(res);

        }
         bool domysqlcommit(std::list<std::string> &sql,size_t dbhash){
            
                auto iter=mysqldbpoolglobal.find(dbhash);

                       return iter->second.sqleditcommit(sql);

                        

        }
void initcallbackmap(){
    // if(rendercallback.size()==0){
    //         rendercallback["view"]=loadview;
    //         rendercallback["viewnotobj"]=loadviewnotcall;
    //         rendercallback["viewfetchnotobj"]=loadviewfetchnotcall;
    //         rendercallback["viewobj"]=loadviewobjcall;
      
    //         rendercallback["router"]=loadcontrol;
    //         rendercallback["jsonsend"]=sendjsoncall;
    //         rendercallback["send"]=modulesenddata;
    //     }
    // if(_renderechocallback.size()==0)
    // {
    //       _renderechocallback["echo"]=echoassign;
    //       _renderechocallback["echoflush"]=echo_flush;  
    //       _renderechocallback["sendfile"]=send_file;  
    // } 
    // if(_renderechocallbackand.size()==0)
    // {
    //       _renderechocallbackand["echo"]=echoassignand;
    // }     

    // if(_mysqlselectcallback.size()==0){
    //     _mysqlselectcallback["mysql"]=domysqlexecute;
    // }
    // if(_mysqlplugineditcallback.size()==0){
    //     _mysqlplugineditcallback["mysql"]=domysqleditexecute;
    // }
    // if(_mysqlplugicommitcall.size()==0){
    //     _mysqlplugicommitcall["mysql"]=domysqlcommit;
    // }
}
method_callback_t viewmodulecreate(std::string module,std::string name){
        boost::dll::fs::path shared_library_path =module;

         try {
                    if(boost::dll::fs::exists(shared_library_path)){       
                             boost::dll::shared_library lib(shared_library_path); 
                             if(lib.has("_setclientapi"))  
                            {
                              boost::function<HTTP::clientapi*(HTTP::clientapi*)> setclientapicall= boost::dll::import_alias<HTTP::clientapi*(HTTP::clientapi*)>(shared_library_path, "_setclientapi"); 
                                    HTTP::clientapi* pn =HTTP::clientapi::instance();
                                    setclientapicall(pn);
                            }
                            if(lib.has(name))  
                            {
                                return std::move(boost::dll::import_alias<std::string(HTTP::OBJ_VALUE&)>(shared_library_path, name ));
                            }
                    }
            }catch (std::exception& e)  
            {  
                //error log 捕获
                std::cout << e.what() << std::endl; 
                std::cout<<" create fail:"<<name<<std::endl; 
            }  
        return httpempty;
}


method_callback_t controlmodulecreate(std::string module,std::string name,size_t tt){
        boost::dll::fs::path shared_library_path =module;
        size_t t=std::hash<std::string>{}(module);
         auto iter=sharedmethodchache.find(t);
         bool hasmethod=true;
            if(iter!=sharedmethodchache.end()){
                   for(int i=0;i<iter->second.size();i++){
                         if(iter->second[i]==name){
                             hasmethod=false;
                             break;
                         }
                   }
            }
            if(hasmethod){
                sharedmethodchache[t].emplace_back(name);
            }
         try {
                   // std::call_once(rendercallback_flag,initcallbackmap);
                    
                    if(boost::dll::fs::exists(shared_library_path)){  
                            boost::dll::shared_library lib(shared_library_path); 
                            if(lib.has("_setclientapi"))  
                            {
                              boost::function<HTTP::clientapi*(HTTP::clientapi*)> setclientapicall= boost::dll::import_alias<HTTP::clientapi*(HTTP::clientapi*)>(shared_library_path, "_setclientapi"); 
                                    HTTP::clientapi* pn =HTTP::clientapi::instance();
                                    setclientapicall(pn);
                            }

                             if(lib.has(name))  
                            {
                               controlpathchache[tt]=std::move(boost::dll::import_alias<std::string(HTTP::OBJ_VALUE&)>(shared_library_path, name ));
                               return controlpathchache[tt]; 
                            }else if(lib.has("_init404")){
                                controlpathchache[tt]=std::move(boost::dll::import_alias<std::string(HTTP::OBJ_VALUE&)>(shared_library_path, "_init404" ));
                               return controlpathchache[tt]; 
                            }
                                   
                            
                    }

                    
            }catch (std::exception& e)  
            {  
                //error log 捕获
                std::cout << e.what() << std::endl; 
                std::cout<<" create fail:"<<name<<std::endl; 
            }  

       
        return httpempty;
}

method_callback_t loadcontrol(std::string modulemethod){
        std::string hash;
 
        std::string path;
        int i=0;
        if(_thishostcontrolsopath.empty()){
             path.append(sitecontrolpath);
        }else{
            path.append(_thishostcontrolsopath);
            hash.append(path);
            if(hash.back()!='/'){
                hash.push_back('/');
            }
        
            if(modulemethod[0]=='/'){
                i++;
            } 
            for(;i<modulemethod.size();i++){
                    if(modulemethod[i]=='/'){
                        i++;
                        break;
                    }
                    hash.push_back(modulemethod[i]);
            }
            hash.append(".so");
            struct stat modso;
            if(stat(hash.c_str(),&modso)==0){
                if(modso.st_mode & S_IFREG){

                }else{
                    hash.clear();
                }
            }else{
                hash.clear();
            }
        }
       
        if(hash.size()>0){
            path=hash;
        }else{
             if(path.back()!='/'){
                path.push_back('/');
            }
    
            if(modulemethod[0]=='/'){
                i++;
                
            } 
            for(;i<modulemethod.size();i++){
                    if(modulemethod[i]=='/'){
                        i++;
                        break;
                    }
                    path.push_back(modulemethod[i]);
            }
            path.append(".so");
        }
           
      
         
        hash.clear();  
        hash.append(modulemethod);
        hash.append(path);
        size_t t=std::hash<std::string>{}(hash);
        
        hash.clear();  
        for(;i<modulemethod.size();i++){
                if(modulemethod[i]=='/'){
                    i++;
                    break;
                }
                hash.push_back(modulemethod[i]);
        }        
        
        if(controlpathchache.find(t)==controlpathchache.end()){
                std::unique_lock<std::mutex> lock(loadcontrolmtx);
                if(controlpathchache.find(t)==controlpathchache.end()){
                controlpathchache[t]=controlmodulecreate(path,hash,t);  
                }
        }

        return controlpathchache[t];

}

method_callback_t loadview(std::string modulemethod){
        std::string hash;
          std::string path;
         if(_thishostviewsopath.empty()){
             path.append(siteviewpath);
        }else{
            path.append(_thishostviewsopath);
            hash.append(path);
             if(hash.back()!='/'){
                hash.push_back('/');
            }
            
            if(modulemethod[0]=='/'){
                    
                hash.append(modulemethod.substr(1,modulemethod.size()-1));
            }else{
                hash.append(modulemethod);
            }
            hash.append(".so");

            struct stat modso;
            if(stat(hash.c_str(),&modso)==0){
                if(modso.st_mode & S_IFREG){

                }else{
                    hash.clear();
                }
            }else{
                hash.clear();
            }
        }
        
        if(hash.size()>0){
            path=hash;
        }else{
            if(path.back()!='/'){
                path.push_back('/');
            }
            
            if(modulemethod[0]=='/'){
                    
                path.append(modulemethod.substr(1,modulemethod.size()-1));
            }else{
                path.append(modulemethod);
            }
            path.append(".so");
        }    
        // }
      
        // if(path.back()!='/'){
        //     path.push_back('/');
        // }
        
        // if(modulemethod[0]=='/'){
                
        //     path.append(modulemethod.substr(1,modulemethod.size()-1));
        // }else{
        //     path.append(modulemethod);
        // }
        // path.append(".so");
 
        hash.clear();  
        hash.append(modulemethod);
        hash.append(path);
        size_t t=std::hash<std::string>{}(hash);
        if(sharedpathchache.find(t)==sharedpathchache.end()){
                std::unique_lock<std::mutex> lock(loadviewmtx);
                if(sharedpathchache.find(t)==sharedpathchache.end()){
                    
                    sharedpathchache[t]=viewmodulecreate(path,"view");
                }
                
        }

        return sharedpathchache[t];

}
method_callback_t loadviewnotcall(std::string modulemethod){
        _output.append(loadview(modulemethod)(vobj));
        return httpempty;

}
std::string renderviewobjfetch(HTTP::OBJ_VALUE& b){
        if(!_outputtemp.empty()){
            if(_outputtemp.size()<30){
                _output.append(loadview(_outputtemp)(b));  
            }    
        }
        
        return "";
}

method_callback_t loadviewobjcall(std::string modulemethod){

        _outputtemp.clear();
        _outputtemp=modulemethod;
        return renderviewobjfetch;

}

std::string renderviewfetch(HTTP::OBJ_VALUE& a){
        std::string temp(_outputtemp);
        _outputtemp.clear();
        return std::move(temp);
}
method_callback_t loadviewfetchnotcall(std::string modulemethod){
  
        _outputtemp.clear();
        _outputtemp.append(loadview(std::move(modulemethod))(vobj));
        return renderviewfetch;

}
void viewmoduleclear(std::string module,std::string method){
     std::string path;
   
    path.append(module);
    path.append("/");
    path.append(method);
    path.append(siteviewpath);
     if(siteviewpath.back()!='/'){
        path.push_back('/');
    }
    path.append(module);
    path.append("/");
    path.append(method);
 
    path.append(".so");
    size_t t=std::hash<std::string>{}(path);
 
    auto citer=sharedpathchache.find(t);
    if(citer!=sharedpathchache.end()){
            try{
                citer->second.clear();
               
                std::unique_lock<std::mutex> lock(loadviewmtx);
                sharedpathchache.erase(citer);
            }catch (std::exception& e)  
            {  
                //error log 捕获
                std::cout << e.what() << std::endl; 
                std::cout<<" release fail:"<<std::endl; 
            }  
            
     }
}    

void controlmoduleclear(std::string module,std::string method){
     std::string path(sitecontrolpath);
    if(path.back()!='/'){
        path.push_back('/');
    }
    path.append(module);
 
    if(!path.ends_with(".so")){
        path.append(".so");
    }
    size_t t=std::hash<std::string>{}(path);
     
     auto iter=sharedmethodchache.find(t);
      try{
            if(iter!=sharedmethodchache.end()){
                //清除所有方法
                std::string hash;
                for(int i=0;i<iter->second.size();i++)
                {
                            hash.clear();  
                            hash.append(module);
                            hash.push_back('/');
                            hash.append(iter->second[i]);

                            hash.append(path);
                         
                            size_t t=std::hash<std::string>{}(hash);
                         
                            auto citer=controlpathchache.find(t);
                             if(citer!=controlpathchache.end()){
                                 citer->second.clear();
                                 std::unique_lock<std::mutex> lock(loadcontrolmtx);
                                 controlpathchache.erase(citer);
                                 
                            }

                }
                std::unique_lock<std::mutex> lock(moudulecachemethod);
                sharedmethodchache.erase(iter);
            }
     }catch (std::exception& e)  
            {  
                //error log 捕获
                std::cout << e.what() << std::endl; 
                std::cout<<" release fail:"<<std::endl; 
            }  
    path.clear();  
    path.append(module);
    path.append("/");
    path.append(method);
    path.append(sitecontrolpath);
     if(path.back()!='/'){
        path.push_back('/');
    }
    path.append(module);
    if(!path.ends_with(".so")){
        path.append(".so");
    }
    t=std::hash<std::string>{}(path);

    auto citer=controlpathchache.find(t);
    if(citer!=controlpathchache.end()){
            try{
                citer->second.clear();
                std::unique_lock<std::mutex> lock(loadcontrolmtx);
                controlpathchache.erase(citer);
            }catch (std::exception& e)  
            {  
                //error log 捕获
                std::cout << e.what() << std::endl; 
                std::cout<<" release fail:"<<std::endl; 
            }  
            
     }
}           


std::string loadmodule(std::string modulemethod){
    try {
        return loadcontrol(modulemethod)(vobj);
    }catch (std::exception& e)  
    {  
        return e.what();
        //std::cout << e.what() << std::endl;  
    }  
   
} 
std::string loadmodule(std::string modulemethod,HTTP::OBJ_VALUE &b){
    try {
        return loadcontrol(modulemethod)(b);
    }catch (std::exception& e)  
    {  
        return e.what();
        //std::cout << e.what() << std::endl;  
    }  
   
} 


void viewshow(std::string modulemethod){
    try {
       loadviewnotcall(modulemethod);
    }catch (std::exception& e)  
    {  
        std::cout << e.what() << std::endl;  
    }  
   
} 
std::string viewfetch(std::string modulemethod){
 
  try {
      return loadviewfetchnotcall(modulemethod)(vobj);

    }catch (std::exception& e)  
    {  
        //std::cout << e.what() << std::endl; 
        //echo.append(e.what());
        return "not found:"+modulemethod; 
    }   
} 
void viewshow(std::string modulemethod,HTTP::OBJ_VALUE &b){
    try {
       loadviewobjcall(modulemethod)(b);
    }catch (std::exception& e)  
    {  
        //echo.append(e.what());
        std::cout << e.what() << std::endl;  
    }  
   
} 
std::string viewfetch(std::string modulemethod,HTTP::OBJ_VALUE &b){
 
  try {
      return loadview(modulemethod)(b);
    }catch (std::exception& e)  
    {  
        return "not found:"+modulemethod; 
    }  
} 


void echo_json(std::string b){
   if(b.size()>0){
       sendjsoncall(b);
   }  
}
void echo_json(){
       sendjsoncall("application/json");
}
void echo_json(HTTP::OBJ_VALUE &obj){
 
      sendjsoncall("")(obj);
}


   unsigned int get_controlversion(){
       return 0x01000000;
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

void echo(std::string &b){
_output.append(b);  
     
}
void echo(int b){
_output.append(std::to_string(b));  
     
}
void echo(unsigned int b){
_output.append(std::to_string(b));  
}
void echo(long long b){
_output.append(std::to_string(b));  
     
}
void echo(unsigned long long b){
     _output.append(std::to_string(b));     
}
void echo(std::string &&b){
      _output.append(b);
}
void echo(HTTP::OBJ_VALUE &b){
     _output.append(b.to_string());
}
std::string& getoutput(){
     return _output;
} 

}
#endif