#pragma once
#ifndef __SERVERCONFIG_H
#define __SERVERCONFIG_H
#include <string> 
#include <map>

namespace HTTP 
{
      
      std::map<std::string,std::map<std::string,std::string>> loadserversconfig(std::string filename)
      {
            std::map<std::string,std::map<std::string,std::string>> serverconfig;
            std::map<std::string,std::string> itemconfig;
            FILE* f = fopen(filename.c_str(), "rb"); 
            if(f==NULL){
                return serverconfig;
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
            keyname="";
            std::string typeone;
            for(int i=0;i<s.size();i++){
                    if(s[i]==';'){
                        i++;
                        if(linestr.size()>0){
                            itemconfig[linestr]=strval;
                        }
                        
                        linestr.clear();
                        strval.clear();
                        isvalue=false;
                        readkey=false;
                        for(;i<s.size();i++){
                                if(s[i]==0x0A){
                                    break;
                                }
                        }
                        
                    }
                    if(s[i]==0x0A){
                        readkey=false;
           
                        if(linestr.size()>0){
                            itemconfig[linestr]=strval;
                        }
                        linestr.clear();
                        strval.clear();
                        isvalue=false;
                        continue;
                    }
                    if(s[i]=='['){
                        if(keyname.size()>0){

                               serverconfig[keyname]= itemconfig;
                               itemconfig.clear(); 
                        }
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
                   
            }
            if(linestr.size()>0){
                            itemconfig[linestr]=strval;
            }
            if(itemconfig.size()>0){
 
                serverconfig[keyname]= itemconfig;
            }
            return serverconfig;
      }



}
#endif 