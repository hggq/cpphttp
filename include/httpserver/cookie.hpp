#ifndef HTTP_COOKIE_HPP
#define HTTP_COOKIE_HPP

#include <string>
#include <vector>
#include <map>
#include "datetime.h"
#include "urlcode.h"

namespace http {
class Cookie{

      public:
      Cookie(){

      }
      Cookie * set(std::string key,std::string val,unsigned long exptime=0,std::string domain="",std::string path="",bool secure=false,bool httponly=false){
                _val[key]=val;
                if(exptime!=0){
                    _expires[key]=exptime;
                }
                if(!domain.empty()){
                    _domain[key]=domain;
                }
                if(!path.empty()){
                    _path[key]=path;
                }
                if(secure){
                    _secure[key]=1;
                }
                if(httponly){
                    _httponly[key]=1;
                }
                curkey=key;
                _set[key]=true;
               return this; 
      }
       Cookie * opt(std::string key){
              curkey=key;
              return this; 
      }  
      Cookie * domain(std::string d){
              if(curkey.empty()){
                  return this;
              }
              _domain[curkey]=d;
              return this; 
      }   
      Cookie * expires(unsigned long e){
              if(curkey.empty()){
                  return this;
              }
              _expires[curkey]=e;
              _set[curkey]=true;
              return this; 
      }   
      Cookie * path(std::string p){
              if(curkey.empty()){
                  return this;
              }  
              _path[curkey]=p;
              return this; 
      }
       Cookie * secure(unsigned char p){
              if(curkey.empty()){
                  return this;
              }  
              _set[curkey]=true;
              _secure[curkey]=p;
              return this; 
      }
        Cookie * httponly(unsigned char p){
              if(curkey.empty()){
                  return this;
              }
              _set[curkey]=true;  
              _httponly[curkey]=p;
              return this; 
      }
       std::string get(std::string key){
              return _val[key];
      } 
      std::string& operator[](std::string key){
                
              return _val[key];
      } 
       
    std::map<std::string,std::string>::const_iterator begin() const {
        return _val.begin();
    }


    std::map<std::string,std::string>::const_iterator end() const{
        return _val.end();
    }

    std::map<std::string,std::string>::iterator begin(){
        return _val.begin();
    }

    std::map<std::string,std::string>::iterator end(){
        return _val.end();
    }

      std::map<std::string,std::string> getAll(){
          return _val;
      }
      std::string makeheader(std::string key){
            std::string tempc;
         if(_val.find(key)!=_val.end()){
                tempc.append("Set-Cookie: ");
                tempc.append(http::url_encode(key.data(),key.size()));
                tempc.push_back('=');
                tempc.append(http::url_encode( _val[key].data(), _val[key].size()));

                unsigned long long timeexp=0;
                   if(_expires.find(key)!=_expires.end()){
                       timeexp=_expires[key];

                             if(timeexp>0&&timeexp<63072000){
                                    timeexp=http::timeid()+timeexp;
                                }
                                if(timeexp>0){
                                    
                                    tempc.append("; Expires=");
                                    tempc.append(http::getGmtTime(timeexp));
                                }

                    } 



              return tempc;
          }else{
              return tempc;
          }
      }
      void clear(){
           _val.clear();
           _domain.clear();
           _path.clear();
           _expires.clear();
           _secure.clear();
           _httponly.clear();
           _set.clear();
      }
      bool check(std::string key){
          if(_val.find(key)!=_val.end()){
              return true;
          }else{
              return false;
          }
      }

      std::string getDomain(std::string key){
           if(_domain.find(key)!=_domain.end()){
              return _domain[key];
          }else{
              return "";
          }   
      }  
       std::string getPath(std::string key){
           if(_path.find(key)!=_path.end()){
              return _path[key];
          }else{
              return "";
          }   
      }  
      unsigned long getExpires(std::string key){
           if(_expires.find(key)!=_expires.end()){
              return _expires[key];
          }else{
              return 0;
          }   
      }  
      unsigned char getSecure(std::string key){
           if(_secure.find(key)!=_secure.end()){
              return _secure[key];
          }else{
              return 0;
          }   
      }  
       unsigned char getHttponly(std::string key){
           if(_httponly.find(key)!=_httponly.end()){
              return _httponly[key];
          }else{
              return 0;
          }   
      } 
      public:
      
      std::map<std::string,std::string> _val;
      std::map<std::string,std::string> _domain;
      std::map<std::string,std::string> _path;
      std::map<std::string,unsigned long> _expires;
      std::map<std::string,unsigned char> _secure;
      std::map<std::string,unsigned char> _httponly; 
      std::string curkey; 
      std::map<std::string,bool> _set;

};
}
#endif