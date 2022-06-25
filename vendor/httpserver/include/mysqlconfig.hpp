#ifndef HTTP_MYSQLCONFIG_HPP
#define HTTP_MYSQLCONFIG_HPP

#include <boost/dll/import.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"
#include <iostream>
#include  <functional> 
#include <mysqlx/xdevapi.h>
#include  <map> 
#include <typeinfo>
 
#include <memory>
 
#include <list>
#include <queue>
#include "mysqlpool.h"
 
#include <condition_variable>

namespace http {

   //   std::mutex sessedit_mutex,sessselect_mutex;

    //  struct mysqllinkpool;
      std::map<size_t,mysqllinkpool> mysqldbpoolglobal;

       struct mysqlconnect_t{
          std::string type;  
          std::string host;  
          std::string port;  
          std::string dbname;  
          std::string user;
          std::string password;
          std::string pretable;
          std::string maxpool;
          std::string spname;
     };

  
std::vector<mysqlconnect_t> getmysqlconfig(std::string filename){
     std::vector<mysqlconnect_t> myconfig;
    FILE* f = fopen(filename.c_str(), "rb"); 
       if(f==NULL){
           return myconfig;
       }
       fseek(f, 0, SEEK_END);
        auto const size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        std::string s,linestr,keyname,strval;
        s.resize(size);
        
        auto  nread =fread(&s[0], 1, size, f);
         s.resize(nread);
        fclose(f);
        struct mysqlconnect_t mysqlconf;
        bool readkey=false;
        bool isvalue=false;
       
       
        keyname="default";
        std::string typeone;
        for(int i=0;i<s.size();i++){
                if(s[i]==';'||s[i]=='#'){
                    i++;
                    if(linestr.size()>0){
                          //  mysqldbconfig[keyname][linestr]=strval;
                          if(linestr=="type"){
                                if(typeone.empty()){
                                    typeone=strval;
                                    mysqlconf.spname=keyname;
                                }else{
                                    
                                    myconfig.push_back(mysqlconf);
                                    typeone=strval;
                                    mysqlconf.type=strval;
                                    mysqlconf.host.clear();
                                    mysqlconf.port.clear();
                                    mysqlconf.dbname.clear();
                                    mysqlconf.user.clear();
                                    mysqlconf.password.clear();
                                    mysqlconf.pretable.clear();
                                    mysqlconf.maxpool.clear();
                                    mysqlconf.spname=keyname;
                                }
                          }
                    }
                    linestr.clear();
                     strval.clear();
                     isvalue=false;
                    for(;i<s.size();i++){
                               if(s[i]==0x0A){
                                   break;
                               }
                    }
                    
                }
                 if(s[i]==0x0A){
                     readkey=false;
                     //myconfig[linestr]=strval;
                     if(linestr.size()>0){
                         //mysqldbconfig[keyname][linestr]=strval;
                         if(strcasecmp(linestr.c_str(),"type")==0){
                               if(typeone.empty()){
                                    typeone=strval;
                                    mysqlconf.spname=keyname;
                                }else{
                                    
                                    myconfig.push_back(mysqlconf);
                                    typeone=strval;
                                    mysqlconf.type=strval;
                                    mysqlconf.host.clear();
                                    mysqlconf.port.clear();
                                    mysqlconf.dbname.clear();
                                    mysqlconf.user.clear();
                                    mysqlconf.password.clear();
                                    mysqlconf.pretable.clear();
                                    mysqlconf.maxpool.clear();
                                    mysqlconf.spname=keyname;
                                }
                         }
                          if(strcasecmp(linestr.c_str(),"host")==0){
                                mysqlconf.host=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"port")==0){
                                mysqlconf.port=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"dbname")==0){
                                mysqlconf.dbname=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"user")==0){
                             
                                mysqlconf.user=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"password")==0){
                                mysqlconf.password=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"pretable")==0){
                                mysqlconf.pretable=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"maxpool")==0){
                                mysqlconf.maxpool=strval;
                          }
                     }
                     
                     linestr.clear();
                     strval.clear();
                     isvalue=false;
                     continue;
                }
                if(s[i]=='['){
                    keyname.clear();
                    readkey=true;
                    continue;
                } 
                 if(s[i]==']'){
                    readkey=false;
                    continue;
                } 
                if(s[i]==0x20){
                    
                    continue;
                }  
                 if(s[i]=='\t'){
                    
                    continue;
                } 
                 if(s[i]=='"'){
                    
                    continue;
                } 
                 if(s[i]=='='){
                    isvalue=true;
                    continue;
                } 
                if(readkey){
                    keyname.push_back(s[i]);
                }else{
                    if(isvalue){
                        strval.push_back(s[i]);
                    }else{
                        linestr.push_back(s[i]);
                    }
                    
                }
                // std::cout<<s[i];
        }
        if(mysqlconf.host.size()>0){
             if(strcasecmp(linestr.c_str(),"host")==0){
                                mysqlconf.host=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"port")==0){
                                mysqlconf.port=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"dbname")==0){
                                mysqlconf.dbname=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"user")==0){
                                mysqlconf.user=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"password")==0){
                                mysqlconf.password=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"pretable")==0){
                                mysqlconf.pretable=strval;
                          }
                          if(strcasecmp(linestr.c_str(),"maxpool")==0){
                                mysqlconf.maxpool=strval;
                          }
                          mysqlconf.spname=keyname;
             myconfig.push_back(mysqlconf);
        }
 
        return myconfig;
    }
 
    
       


}
#endif