 
#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"
//#include "common_functions.h"
#include "modulemar.hpp"
#include "http_header.hpp"
#include "mysqlmodule.h"
#include "Clientpeer.h"


namespace http {
std::mutex loadcontrolmtx,loadviewmtx,moudulecachemethod;  

std::string httpempty(http::OBJ_VALUE& a){
    return "<p>--.so image not found--</p>";
}
std::string echoempty(http::OBJ_VALUE& a){
    return "";
}

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


void echo_flush(std::string name){
   // std::cout<<"mb:"<<name<<std::endl;
    _output.append(std::move(name));
    //now send data
}
void echoassignand(std::string& name){
   // std::cout<<"mb:"<<name<<std::endl;
    _output.append(name);
     
}
// void send_file(std::string name);
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
std::string renderjsonfetchtosend(http::OBJ_VALUE& b){
        
        _output.append(b.tojson());
        return "";
}
std::string renderjsonlocaltosend(http::OBJ_VALUE& b){
        
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
            std::cout<<"---local plugin msyql find"<<std::endl;
                auto iter=mysqldbpoolglobal.find(dbhash);

                        mysqlx::RowResult res = iter->second.sqlselectfetch(sql);

                        return std::move(res);

        }
void initcallbackmap(){
    if(rendercallback.size()==0){
            rendercallback["view"]=loadview;
            rendercallback["viewnotobj"]=loadviewnotcall;
            rendercallback["viewfetchnotobj"]=loadviewfetchnotcall;
            rendercallback["viewobj"]=loadviewobjcall;
      
            rendercallback["router"]=loadcontrol;
            rendercallback["jsonsend"]=sendjsoncall;
            rendercallback["send"]=modulesenddata;
        }
    if(_renderechocallback.size()==0)
    {
          _renderechocallback["echo"]=echoassign;
          _renderechocallback["echoflush"]=echo_flush;  
          _renderechocallback["sendfile"]=send_file;  
    } 
    if(_renderechocallbackand.size()==0)
    {
          _renderechocallbackand["echo"]=echoassignand;
    }     

    if(_mysqlselectcallback.size()==0){
        _mysqlselectcallback["mysql"]=domysqlexecute;
    }
    if(_mysqlplugineditcallback.size()==0){
        _mysqlplugineditcallback["mysql"]=domysqleditexecute;
    }
}
method_callback_t viewmodulecreate(std::string module,std::string name){
        boost::dll::fs::path shared_library_path =module;

         std::cout<<shared_library_path.string()<<" method:"<<name<<std::endl;
         try {
                    if(boost::dll::fs::exists(shared_library_path)){

                             boost::dll::shared_library lib(shared_library_path); 
                            if(lib.has("_initview"))  
                            {

                                boost::function<void(modulemethod_callback_t)> _initview= boost::dll::import_alias<void(modulemethod_callback_t)>(shared_library_path, "_initview");
                                _initview(&loadview);
                            }
                            if(lib.has(name))  
                            {
                                return std::move(boost::dll::import_alias<std::string(http::OBJ_VALUE&)>(shared_library_path, name ));
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
                    std::call_once(rendercallback_flag,initcallbackmap);
                     
                    if(boost::dll::fs::exists(shared_library_path)){
                            boost::dll::shared_library lib(shared_library_path); 
                             boost::function<unsigned int (std::map<std::string,modulemethod_callback_t>&)> _initcallback;
                             boost::function<unsigned int (std::map<std::string,echo_callbackand_t>&)> _initcallandback;
                             boost::function<unsigned int (std::map<std::string,echo_callback_t>&)> _initcallvoidback;
                             boost::function<unsigned int (std::map<std::string,mysql_callbackand_t>&)> _initmysqlcallback;
                             boost::function<unsigned int (std::map<std::string,mysql_callbacksql_t>&)> _initmysqleditcallback;
                            if(lib.has("_initcallback"))  
                            {
                              //boost::function<unsigned int (std::map<std::string,modulemethod_callback_t>&)> _initcallback= boost::dll::import_alias<unsigned int (std::map<std::string,modulemethod_callback_t>&)>(shared_library_path, "_initcallback");                    
                              _initcallback= boost::dll::import_alias<unsigned int (std::map<std::string,modulemethod_callback_t>&)>(shared_library_path, "_initcallback");                    

                             unsigned int  controlversion=_initcallback(rendercallback);
                             //_initcallback.clear();
                            }
                            if(lib.has("_initandcall"))  
                            {
                             // boost::function<unsigned int (std::map<std::string,echo_callbackand_t>&)> _initcallandback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callbackand_t>&)>(shared_library_path, "_initandcall");                    
                              _initcallandback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callbackand_t>&)>(shared_library_path, "_initandcall");                    

                             unsigned int  controlversion=_initcallandback(_renderechocallbackand);
                             //_initcallandback.clear();
                            }
                             if(lib.has("_initvoidcall"))  
                            {
                             // boost::function<unsigned int (std::map<std::string,echo_callbackand_t>&)> _initcallandback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callbackand_t>&)>(shared_library_path, "_initandcall");                    
                              _initcallvoidback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callback_t>&)>(shared_library_path, "_initvoidcall");                    

                             unsigned int  controlversion=_initcallvoidback(_renderechocallback);
                             //_initcallvoidback.clear();
                            }
                             if(lib.has("_initmysqlplugin"))  
                            {
                               std::cout<<"++++++++_initmysqlplugin_initmysqlplugin++++++"<<std::endl; 
                             // boost::function<unsigned int (std::map<std::string,echo_callbackand_t>&)> _initcallandback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callbackand_t>&)>(shared_library_path, "_initandcall");                    
                              _initmysqlcallback= boost::dll::import_alias<unsigned int (std::map<std::string,mysql_callbackand_t>&)>(shared_library_path, "_initmysqlplugin");                    

                             unsigned int  controlversion=_initmysqlcallback(_mysqlselectcallback);
                             //_initcallvoidback.clear();
                            }

                               if(lib.has("_initmysqleditplugin"))  
                            {
                               std::cout<<"++++++++_initmysqlplugin_initmysqlplugin++++++"<<std::endl; 
                             // boost::function<unsigned int (std::map<std::string,echo_callbackand_t>&)> _initcallandback= boost::dll::import_alias<unsigned int (std::map<std::string,echo_callbackand_t>&)>(shared_library_path, "_initandcall");                    
                              _initmysqleditcallback= boost::dll::import_alias<unsigned int (std::map<std::string,mysql_callbacksql_t>&)>(shared_library_path, "_initmysqleditplugin");                    

                             unsigned int  controlversion=_initmysqleditcallback(_mysqlplugineditcallback);
                             //_initcallvoidback.clear();
                            }

                             if(lib.has(name))  
                            {
                               controlpathchache[tt]=std::move(boost::dll::import_alias<std::string(http::OBJ_VALUE&)>(shared_library_path, name ));
                               if(_initcallback){
                                   _initcallback.clear();
                               } 
                                if(_initcallandback){
                                   _initcallandback.clear();
                               } 
                                if(_initcallvoidback){
                                   _initcallvoidback.clear();
                               } 
                                if(_initmysqlcallback){
                                   _initmysqlcallback.clear();
                               }    
                               if(_initmysqleditcallback){
                                   _initmysqleditcallback.clear();
                               }    
                               return controlpathchache[tt]; 
                            }else if(lib.has("_init404")){
                                controlpathchache[tt]=std::move(boost::dll::import_alias<std::string(http::OBJ_VALUE&)>(shared_library_path, "_init404" ));
                               if(_initcallback){
                                   _initcallback.clear();
                               } 
                                if(_initcallandback){
                                   _initcallandback.clear();
                               } 
                                if(_initcallvoidback){
                                   _initcallvoidback.clear();
                               } 
                                if(_initmysqlcallback){
                                   _initmysqlcallback.clear();
                               }    
                               if(_initmysqleditcallback){
                                   _initmysqleditcallback.clear();
                               }    
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
                //std::cout<<" t:"<<t<<std::endl;
                std::unique_lock<std::mutex> lock(loadcontrolmtx);
                if(controlpathchache.find(t)==controlpathchache.end()){
                std::cout<<"-----------unique_lock unique_lock:-------------------------"<<std::endl;
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
               // std::cout<<"createcreatecreatecreate method:"<<path<<std::endl;
                std::unique_lock<std::mutex> lock(loadviewmtx);
                if(sharedpathchache.find(t)==sharedpathchache.end()){
                    std::cout<<"++++++++++++++++++++++++++++"<<std::endl;
                    sharedpathchache[t]=viewmodulecreate(path,"view");
                }
                
        }

        return sharedpathchache[t];

}
method_callback_t loadviewnotcall(std::string modulemethod){
  
        _output.append(loadview(std::move(modulemethod))(vobj));
        return httpempty;

}
std::string renderviewobjfetch(http::OBJ_VALUE& b){
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

std::string renderviewfetch(http::OBJ_VALUE& a){
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
                std::cout<<" view module:"<<path<<std::endl; 
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
                            std::cout<< "path "<<path;
                            std::cout<<iter->second[i]<<std::endl;
                            size_t t=std::hash<std::string>{}(hash);
                            std::cout<< " t "<<t<<path;
                            auto citer=controlpathchache.find(t);
                             if(citer!=controlpathchache.end()){
                                 citer->second.clear();
                                 std::unique_lock<std::mutex> lock(loadcontrolmtx);
                                 controlpathchache.erase(citer);
                                 std::cout<<"----------erase method:"<<std::endl;
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
std::string loadmodule(std::string modulemethod,http::OBJ_VALUE &b){
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
void viewshow(std::string modulemethod,http::OBJ_VALUE &b){
    try {
       loadviewobjcall(modulemethod)(b);
    }catch (std::exception& e)  
    {  
        //echo.append(e.what());
        std::cout << e.what() << std::endl;  
    }  
   
} 
std::string viewfetch(std::string modulemethod,http::OBJ_VALUE &b){
 
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
void echo_json(http::OBJ_VALUE &obj){
 
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
     try {
       echoassignand(b);
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(int b){
     try {
      echoassign(std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(unsigned int b){
     try {
       echoassign(std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(long long b){
     try {
       echoassign(std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(unsigned long long b){
     try {
       echoassign(std::move(std::to_string(b)));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
     
}
void echo(std::string &&b){
     
    try {
           echoassign(std::move(b));
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
}
void echo(http::OBJ_VALUE &b){
     
    try {
           echoassign(b.to_string());
    }catch (std::exception& e)  
    {  
       // std::cout << e.what() << std::endl;  
    }  
}
 

}
