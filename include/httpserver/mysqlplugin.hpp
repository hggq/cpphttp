#ifndef HTTP_MYSQLPLUGIN_HPP
#define HTTP_MYSQLPLUGIN_HPP

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
 
 
#include <condition_variable>

namespace HTTP {

      std::mutex sessedit_mutex,sessselect_mutex;

      struct mysqllinkpool;
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
        // for(int i=0;i<myconfig.size();i++){
        //     std::cout<<"i"<<std::to_string(i)<<" pretable"<<myconfig[i].pretable<<std::endl;
        // }
        return myconfig;
    }
 
      //每对配置读写分离  
      struct mysqllinkpool{

                 mysqllinkpool(std::string ms,std::string sl):connectedit(ms),connectselect(sl){

                 }   
                 void addselectsession(unsigned int num){
                          for(unsigned int i=0;i<num;i++){
                               sessselecttpool.push(std::move(std::make_unique<mysqlx::Session>(connectselect)));
                           }
                  }
                   void addeditsession(unsigned int num){
                          for(unsigned int i=0;i<num;i++){
                               sesseditpool.push(std::move(std::make_unique<mysqlx::Session>(connectedit)));
                           }
                  }

                 mysqlx::RowResult sqlselectfetch(std::string &sql){
                       
                        std::unique_lock<std::mutex> lock(sessselect_mutex);
                        if(sessselecttpool.empty()){
                              
                              sessselecttpool.push(std::move(std::make_unique<mysqlx::Session>(connectselect)));
                        }
                        std::unique_ptr<mysqlx::Session> sess(std::move(sessselecttpool.front()));
                        sessselecttpool.pop();
                        selectbusynum++;
                        lock.unlock();
                        
                        mysqlx::RowResult temp=sess->sql(sql).execute();
                        std::unique_lock<std::mutex> lck(sessselect_mutex);
                        sessselecttpool.push(std::move(sess));
                        selectbusynum--;
                        lck.unlock();
                        return std::move(temp);
                  }

                 mysqlx::SqlResult sqleditfetch(std::string &sql){
                        //dbreadpool[0].sql()
                        std::unique_lock<std::mutex> lock(sessedit_mutex);
                        if(sesseditpool.empty()){
                                 sesseditpool.push(std::move(std::make_unique<mysqlx::Session>(connectedit)));
                          }
                        std::unique_ptr<mysqlx::Session> sess(std::move(sesseditpool.front()));
                                 sesseditpool.pop();
                                 editbusynum++;
                                 lock.unlock();

                        mysqlx::SqlResult temp=sess->sql(sql).execute();
                           
                        std::unique_lock<std::mutex> lck(sessedit_mutex);
                        sesseditpool.push(std::move(sess));
                        editbusynum--;
                        lck.unlock();
                        return std::move(temp);
                  }
                  bool sqleditcommit(std::list<std::string> &sql){
                        //dbreadpool[0].sql()
                        std::unique_lock<std::mutex> lock(sessedit_mutex);
                        if(sesseditpool.empty()){
                                 sesseditpool.push(std::move(std::make_unique<mysqlx::Session>(connectedit)));
                          }
                        std::unique_ptr<mysqlx::Session> sess(std::move(sesseditpool.front()));
                                 sesseditpool.pop();
                                 editbusynum++;
                                 lock.unlock();
                        sess->startTransaction();
                        try {
                            
                           for(;!sql.empty();){
                               sess->sql(sql.front()).execute();
                               sql.pop_front();
                           }

                           sess->commit();
                                std::unique_lock<std::mutex> lck(sessedit_mutex);
                                sesseditpool.push(std::move(sess));
                                editbusynum--;
                                lck.unlock();
                                return true;
                        }
                        catch (const  mysqlx::Error &err) {
                       
                                sess->rollback();

                                std::unique_lock<std::mutex> lck(sessedit_mutex);
                                sesseditpool.push(std::move(sess));
                                editbusynum--;
                                lck.unlock();

                                 return false;   
                        }    
                       
                        
                  }
                  mysqlx::SqlResult sqleditfetch(std::string &sql,long long &effectrow,std::function<std::unique_ptr<mysqlx::Session>(std::string &,mysqlx::SqlResult&,std::unique_ptr<mysqlx::Session>)> func){
 
                             std::unique_lock<std::mutex> lock(sessedit_mutex);
                             if(sesseditpool.empty()){
                                 sesseditpool.push(std::move(std::make_unique<mysqlx::Session>(connectedit)));
                             }
                             std::unique_ptr<mysqlx::Session> sess(std::move(sesseditpool.front()));
                                 sesseditpool.pop(); 
                                 editbusynum++;
                                 lock.unlock();
                             mysqlx::SqlResult temp;
                             sess=func(sql,temp,std::move(sess));

                            std::unique_lock<std::mutex> lck(sessedit_mutex);
                            sesseditpool.push(std::move(sess));
                            editbusynum--;
                            lck.unlock();

                      return  std::move(temp);
                  }
                   mysqlx::SqlResult sqleditfetch(std::string &sql,long long &effectrow,std::function<std::unique_ptr<mysqlx::Session>(std::string &,std::unique_ptr<mysqlx::Session>)> funcbeg,std::function<std::unique_ptr<mysqlx::Session>(std::string &,std::unique_ptr<mysqlx::Session>)> funcend){
                            std::unique_lock<std::mutex> lock(sessedit_mutex);
                            if(sesseditpool.empty()){
                                    sesseditpool.push(std::move(std::make_unique<mysqlx::Session>(connectedit)));
                            }
                            std::unique_ptr<mysqlx::Session> sess(std::move(sesseditpool.front()));
                            sesseditpool.pop(); 
                            editbusynum++;
                            lock.unlock();

                        sess=funcbeg(sql,std::move(sess));
                        mysqlx::SqlResult temp=sess->sql(sql).execute();;
                        sess=funcend(sql,std::move(sess));

                            std::unique_lock<std::mutex> lck(sessedit_mutex);
                            sesseditpool.push(std::move(sess));
                            editbusynum--;
                            lck.unlock();

                      return  std::move(temp);
                  }

                 unsigned int getselectpoolnum(){
                      std::unique_lock<std::mutex> lock(sessselect_mutex);
                      return sessselecttpool.size();
                  }
                   unsigned int geteditpoolnum(){
                      std::unique_lock<std::mutex> lock(sessedit_mutex);
                      return sesseditpool.size();
                  }

                unsigned int clearpool(){
                         int i=0;
                         if(selectbusynum==0){
                           
                               std::unique_lock<std::mutex> lock(sessselect_mutex);
                               for(;!sessselecttpool.empty();){
                                    std::unique_ptr<mysqlx::Session> sess(std::move(sessselecttpool.front()));
                                    sessselecttpool.pop();
                                    sess->close();
                                    sess.reset(nullptr);
                                  
                                    i++;
                               }
                         }
                          if(editbusynum==0){
                              
                               std::unique_lock<std::mutex> lock(sessedit_mutex);
                               for(;!sesseditpool.empty();){
                                    std::unique_ptr<mysqlx::Session> sess(std::move(sesseditpool.front()));
                                    sesseditpool.pop();
                                    sess->close();
                                    sess.reset(nullptr);
                                     
                                    i++;
                               }
                         }
                         return i;
                  }
              
                 void initpool(){
                         addselectsession(2);
                         addeditsession(1);
                  }
           size_t dbhash; 
           unsigned editmax=2,editmin=1,selectmax=2,selectmin=1; 
           unsigned int selectbusynum=0,editbusynum=0;
           std::queue<std::unique_ptr<mysqlx::Session>>  sesseditpool;
           std::queue<std::unique_ptr<mysqlx::Session>>  sessselecttpool; 
           std::string connectedit;
           std::string connectselect;
      };
       

       


}
#endif