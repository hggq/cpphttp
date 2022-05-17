
 
#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <list>
#include <filesystem>
#include <vector>
 
namespace fs = std::filesystem;
//g++ cli/modelsmar.cpp -o climodel -std=c++20 -Iinclude -lmysqlcppconn8


int main(){
     
 
    class ReadINI{
          
          public:
          ReadINI():isstring(true){ }
          ReadINI(std::string a):s_val(std::move(a)),isstring(true){ }
          ReadINI(std::map<std::string,std::string> a):v_val(std::move(a)),isstring(false){ }
          explicit operator std::string () const { 
              return s_val;
          }
          bool is_string(){
               return isstring;
          }
          private:
            std::map<std::string,std::string> v_val;
            std::string s_val;
            bool isstring=true;
    };

    std::string filename="mysql.conf";
       FILE* f = fopen(filename.c_str(), "rb"); 
       if(f==NULL){
           return 0;
       }
       fseek(f, 0, SEEK_END);
        auto const size = ftell(f);
        fseek(f, 0, SEEK_SET);
        
        std::string s,linestr,keyname,strval;
        s.resize(size);
        
        auto  nread =fread(&s[0], 1, size, f);
         s.resize(nread);
        fclose(f);
        bool readkey=false;
        bool isvalue=false;
        std::map<std::string,std::map<std::string,std::string>> mysqldbconfig;
        std::map<std::string,std::string> myconfig;
        keyname="default";
        std::cout<<s;
        for(int i=0;i<nread;i++){
                if(s[i]==';'||s[i]=='#'){
                    i++;
                    if(linestr.size()>0){
                            mysqldbconfig[keyname][linestr]=strval;
                    }
                    linestr.clear();
                     strval.clear();
                     isvalue=false;
                    for(;i<nread;i++){
                               if(s[i]==0x0A){
                                   break;
                               }
                    }
                    
                }
                 if(s[i]==0x0A){
                     readkey=false;
                     //myconfig[linestr]=strval;
                     if(linestr.size()>0){
                         mysqldbconfig[keyname][linestr]=strval;
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
                std::cout<<s[i];
        }
        for(auto iter=mysqldbconfig.begin();iter!=mysqldbconfig.end();iter++){
              std::cout<<iter->first<<std::endl;
        }
    return 0;
}