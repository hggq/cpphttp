/**
 *  @copyright copyright 2022, huang ziquan  All rights reserved.
 *  @author huang ziquan
 *  @author 黄自权 
 *  @file http_parse.hpp
 *  @date 2022-04-17
 *  
 *  html protocol parse file 
 *  
 *
 */

#include <iostream>
#include <cstdio>
#include <stdexcept>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <list>
#include <filesystem>
 
#include <string_view>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <thread>
#include <chrono>
#include <strings.h>
#include <cstring>
#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

#include "datetime.h"
// #include "md5.hpp"
// #include "mime.hpp"
#include "unicode.h"
// #include "cookie.hpp"
 #include "urlcode.h"
 #include "request.h"
// #include "WebSocket.h"
#include "httpparse.h"
namespace HTTP { 

            httpparse::httpparse(){
                    error=0;     
            }
            unsigned int httpparse::header_valuetoint(){
                    unsigned int temp=0;
                    for(int qi=0;qi<header_value.size();qi++){
                            if(header_value[qi]<0x3A&&header_value[qi]>0x2F){
                                            temp= temp*10+(header_value[qi]-0x30);
                            }
                      }
                      return temp;
            }
            unsigned int httpparse::checkheadend(const unsigned char * buffer,unsigned int buffersize){
                     unsigned int i=readoffset;
                     if(headendhitnum==2){
                                if(buffer[i]==0x0D&&i<buffersize){
                                    i++;
                                    headendhitnum++;
                                    if(buffer[i]==0x0A&&i<buffersize){
                                            i++;
                                            headendhitnum++;
                                    
                                    }     
                                }      
                        }else{
                            if(buffer[i]==0x0A&&i<buffersize){
                                            i++;
                                            headendhitnum++;
                                            if(buffer[i]==0x0D&&i<buffersize){
                                                i++;
                                                headendhitnum++;
                                                if(buffer[i]==0x0A&&i<buffersize){
                                                        i++;
                                                        headendhitnum++;
                                                
                                                }     
                                            }     
                                    }        
                        }
                        return headendhitnum;
            }
            void httpparse::procssparamter(){
                   std::string objname;
                              bool isgroup=true;
                              for(int j=0;j<header_temp.length();j++){
                                    if(header_temp[j]=='['){
                                          std::string key1name;
                                          int n=j;
                                          n++;
                                          bool ishaskey=false;
                                          bool ishaskey2=false;
                                          for(;n<header_temp.length();n++){
                                                if(header_temp[n]==']'){
                                                      ishaskey=true;
                                                      n++;
                                                      break;
                                                }else if(header_temp[n]=='['){
                                                     
                                                      break;
                                                }  
                                                if(header_temp[n]!=0x22){ 
                                                      key1name.push_back(header_temp[n]);
                                                }
                                          }
                                          
                                          std::string key2name;
                                          if(ishaskey){
                                                
                                                int m=n;
                                                if(n<header_temp.length()){
                                                      if(header_temp[m]=='['){
                                                            m+=1;
                                                            for(;m<header_temp.length();m++){
                                                                  if(header_temp[m]==']'){
                                                                        ishaskey2=true;
                                                                        m++;
                                                                        break;
                                                                  }else if(header_temp[m]=='['){
                                                      
                                                                        break;
                                                                  }
                                                                  if(header_temp[m]!=0x22){
                                                                        key2name.push_back(header_temp[m]);
                                                                  }   
                                                                  

                                                            }
                                                            
                                                            if(ishaskey2&&m==header_temp.length()){
                                                            }else{
                                                                ishaskey2=false;  
                                                            }
                                                      }        
                                                }      
                                                
                                               if(ishaskey2){
                                                      //双数组
                                                      if(key1name.empty()){
                                                          if(key2name.empty()){
                                                                 HTTP::OBJ_ARRAY objtemp;
                                                                 objtemp.push(header_input); 
                                                                 HTTP::OBJ_ARRAY objtemp1;
                                                                 objtemp1.push(std::move(objtemp)); 
                                                                 get[objname].push(std::move(objtemp1));   
                                                          }else{
                                                                 HTTP::OBJ_VALUE objtemp;
                                                                 objtemp[key2name]=header_input;
                                                                 HTTP::OBJ_ARRAY objtemp1;
                                                                 objtemp1.push(std::move(objtemp)); 
                                                                 get[objname].push(std::move(objtemp1));   
                                                          }  
                                                          
                                                      }else{
                                                          if(key2name.empty()){
                                                                 get[objname][key1name].set_array();   
                                                                 get[objname][key1name]=header_input;   
                                                          }else{
                                        
                                                                get[objname][key1name][key2name]=header_input;     
                                                          }  
                                                           
                                                      } 
                                                      j=m;
                                                      isgroup=false;
                                               }else if(n==header_temp.length()){
                                                      //只有一个
                                                      if(key1name.empty()){
                                                          get[objname].set_array();  
                                                          get[objname].push(header_input);        
                                                      }else{
                                                          get[objname].push(key1name,header_input);
                                                      } 
                                                      j=n;  
                                                      isgroup=false;
                                               }else{
                                                     
                                                      //没有数组

                                               } 
     
                                          }
                                          if(isgroup){
                                              objname.push_back(header_temp[j]);   
                                          }
                                    }else{
                                          objname.push_back(header_temp[j]);
                                    }
                                    
                              }
                              if(isgroup){
                                    get[header_temp]=header_input;
                              }

            }
            void httpparse::procssxformurlencoded(){
                   std::string objname;
                              bool isgroup=true;
                              for(int j=0;j<header_temp.length();j++){
                                    if(header_temp[j]=='['){
                                          std::string key1name;
                                          int n=j;
                                          n++;
                                          bool ishaskey=false;
                                          bool ishaskey2=false;
                                          for(;n<header_temp.length();n++){
                                                if(header_temp[n]==']'){
                                                      ishaskey=true;
                                                      n++;
                                                      break;
                                                }else if(header_temp[n]=='['){
                                                     
                                                      break;
                                                }  
                                                if(header_temp[n]!=0x22){ 
                                                      key1name.push_back(header_temp[n]);
                                                }
                                          }
                                          
                                          std::string key2name;
                                          if(ishaskey){
                                                
                                                int m=n;
                                                if(n<header_temp.length()){
                                                      if(header_temp[m]=='['){
                                                            m+=1;
                                                            for(;m<header_temp.length();m++){
                                                                  if(header_temp[m]==']'){
                                                                        ishaskey2=true;
                                                                        m++;
                                                                        break;
                                                                  }else if(header_temp[m]=='['){
                                                      
                                                                        break;
                                                                  }
                                                                  if(header_temp[m]!=0x22){
                                                                        key2name.push_back(header_temp[m]);
                                                                  }   
                                                                  

                                                            }
                                                            
                                                            if(ishaskey2&&m==header_temp.length()){
                                                            }else{
                                                                ishaskey2=false;  
                                                            }
                                                      }        
                                                }      
                                                
                                               if(ishaskey2){
                                                      //双数组
                                                      if(key1name.empty()){
                                                          if(key2name.empty()){
                                                                 HTTP::OBJ_ARRAY objtemp;
                                                                 objtemp.push(header_input); 
                                                                 HTTP::OBJ_ARRAY objtemp1;
                                                                 objtemp1.push(std::move(objtemp)); 
                                                                 post[objname].push(std::move(objtemp1));   
                                                          }else{
                                                                 HTTP::OBJ_VALUE objtemp;
                                                                 objtemp[key2name]=header_input;
                                                                 HTTP::OBJ_ARRAY objtemp1;
                                                                 objtemp1.push(std::move(objtemp)); 
                                                                 post[objname].push(std::move(objtemp1));   
                                                          }  
                                                          
                                                      }else{
                                                          if(key2name.empty()){
                                                                 post[objname][key1name].set_array();   
                                                                 post[objname][key1name]=header_input;   
                                                          }else{
                                        
                                                                post[objname][key1name][key2name]=header_input;     
                                                          }  
                                                           
                                                      } 
                                                      j=m;
                                                      isgroup=false;
                                               }else if(n==header_temp.length()){
                                                      //只有一个
                                                      if(key1name.empty()){
                                                          post[objname].set_array();  
                                                          post[objname].push(header_input);        
                                                      }else{
                                                          post[objname].push(key1name,header_input);
                                                      } 
                                                      j=n;  
                                                      isgroup=false;
                                               }else{
                                                     
                                                      //没有数组

                                               } 
     
                                          }
                                          if(isgroup){
                                              objname.push_back(header_temp[j]);   
                                          }
                                    }else{
                                          objname.push_back(header_temp[j]);
                                    }
                                    
                              }
                              if(isgroup){
                                    post[header_temp]=header_input;
                              }

            } 
            void httpparse::methodprocess(){
                  unsigned int ioffset=0,linesize;
                  unsigned int j=0;   
                  linesize=contentline.size();
                  header_key.clear();
                  header_value.clear();
                   
                  for(;ioffset<linesize;ioffset++){
                        if(contentline[ioffset]==0x20){
                              break;
                        }
                        header_key.push_back(contentline[ioffset]);
                        j++;
                        if(j>9){
                              error=6;
                              break;
                        }
                  }
                  if(header_key.size()>8){
                        error=6;
                        return;;
                  }    
                  method=HEAD_METHOD::UNKNOW;  
                  switch(header_key[0]){
                      case 'c':
                      case 'C':
                             if(strcasecmp(header_key.c_str(),"CONNECT")==0){
                                method=HEAD_METHOD::CONNECT;
                             }else{
                                error=6;   
                             }
                            break;    
                      case 'h':
                      case 'H':
                            if(strcasecmp(header_key.c_str(),"HEAD")==0){
                                method=HEAD_METHOD::HEAD;
                             }else{
                                error=6;   
                             }
                            break;  
                      case 'g':
                      case 'G':
                            if(strcasecmp(header_key.c_str(),"GET")==0){
                                method=HEAD_METHOD::GET;
                             }else{
                                error=6;   
                             }
                            break;
                      case 'p':
                      case 'P':
                              
                              if(strcasecmp(header_key.c_str(),"POST")==0){
                                method=HEAD_METHOD::POST;  
                              }else if(strcasecmp(header_key.c_str(),"PUT")==0){
                                method=HEAD_METHOD::PUT; 
                              }else{
                                error=6;   
                              }
                             
                              break;
                      case 'o':
                      case 'O':
                             if(strcasecmp(header_key.c_str(),"OPTIONS")==0){
                                method=HEAD_METHOD::OPTIONS;
                             }else{
                                error=6;   
                             }
                            break;   
                      case 't':
                      case 'T':
                             if(strcasecmp(header_key.c_str(),"TRACE")==0){
                                method=HEAD_METHOD::TRACE;
                             }else{
                                error=6;   
                             }
                            break;                      
                      default:
                            method=HEAD_METHOD::UNKNOW;
                             error=6;            
                  }
                  if(error>0){
                        return;
                  }
                  headerstep=1;
                  for(;ioffset<linesize;ioffset++){
                        if(contentline[ioffset]==0x20){
                              continue;
                        }
                        break;
                  }
                  header_key.clear();  
                  buffer_key.clear();
                  pathinfo.clear();
                  for(;ioffset<linesize;ioffset++){
                        if(contentline[ioffset]==0x20){
                              headerstep=2;    
                              break;
                        }
                        if(contentline[ioffset]==0x3F){
                              headerstep=6; 
                              break; 
                        }
                        if(contentline[ioffset]==0x2F){
                               if(buffer_key.size()>0){
                                    if(buffer_key.size()==2&&buffer_key[0]=='.'&&buffer_key[1]=='.'){
                                        if(pathinfo.size()>0){
                                          pathinfo.pop_back(); 
                                         }         
                                    }else if(buffer_key.size()==1&&buffer_key[0]=='.'){
                                       
                                        
                                    }else{
                                        pathinfo.emplace_back(buffer_key.substr());        
                                    } 
                                    buffer_key.clear();  
                              }
                        }else{
                              buffer_key.push_back(contentline[ioffset]);
                        }
                        header_key.push_back(contentline[ioffset]);
                        
                  } 
                  if(buffer_key.size()>0){
                        if(buffer_key.size()==2&&buffer_key[0]=='.'&&buffer_key[1]=='.'){
                                    if(pathinfo.size()>0){
                                          pathinfo.pop_back(); 
                                    }      
                                            
                              }else if(buffer_key.size()==1&&buffer_key[0]=='.'){
                                       
                                    
                              }else{
                                    pathinfo.emplace_back(buffer_key.substr());        
                              } 
                              
                  }
                  
 
                 if(headerstep==2||headerstep==6){
                       urlpath=HTTP::url_decode(header_key.data(), header_key.length());
                 }  
                 if(headerstep==6){
                     
                      querystring.clear();
                      if(contentline[ioffset]==0x3F){
                              ioffset++;
                      }
                      for(;ioffset<linesize;ioffset++){
                        if(contentline[ioffset]==0x20){
                              headerstep=7;    
                              break;
                        }
                        querystring.push_back(contentline[ioffset]);
                     }
                    
                 }
                 if(headerstep==7){
                   //parameter  
                    header_key.clear();  
                    header_value.clear();  
                    header_temp.clear();  
                    header_input.clear();
                    int qsize=querystring.size();
                    unsigned char partype=0;
                    for(j=0;j<qsize;j++){
                        if(querystring[j]==0x3D){
                            header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                            header_value.clear(); 
                            partype=1;
                            continue;    
                        }else if(querystring[j]==0x26){
                            header_input=HTTP::url_decode(header_value.data(),header_value.length());
                            procssparamter();
                            header_value.clear();  
                            partype=2;   
                            continue;     
                        }  
                        header_value.push_back(querystring[j]);
                    }
                     if(partype==1){
                        header_input=HTTP::url_decode(header_value.data(),header_value.length());
                        procssparamter();
                     }else if(partype==2){
                        header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                        header_input.clear();
                        procssparamter();    
                     }else if(header_value.size()>0){
                        header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                        header_input.clear();
                        procssparamter();  
                     }
                        

                 }
                 for(;ioffset<linesize;ioffset++){
                        if(contentline[ioffset]==0x20){
                              continue;
                        }
                        break;
                 }
                   httpversion=0; 
                   version.clear();
                   for(;ioffset<linesize;ioffset++){
                         if(contentline[ioffset]>='0'&&contentline[ioffset]<='9'){
                            if(httpversion<25)
                            httpversion=httpversion*10+(contentline[ioffset]-'0');
                        }                           
                        version.push_back(contentline[ioffset]);
                     }
                 headerstep=8;    
                  
 
            }
            void httpparse::callposttype(){
                 switch (buffer_value.size()){
                    case 33:
                        if(strcasecmp(buffer_value.c_str(),"application/x-www-form-urlencoded")==0){
                                poststate.type="application/x-www-form-urlencoded";
                                poststate.posttype=1;
                                return;
                        }
                        break;
                    case 24:
                        if(strcasecmp(buffer_value.c_str(),"application/octet-stream")==0){
                                poststate.type="application/octet-stream";
                                poststate.posttype=5;
                                return;
                        }
                        break;    
                    case 19:
                        if(strcasecmp(buffer_value.c_str(),"multipart/form-data")==0){
                                poststate.type="multipart/form-data";
                                poststate.posttype=2;
                                return;
                        }
                        break;
                    case 16:
                        if(strcasecmp(buffer_value.c_str(),"application/json")==0){
                                poststate.type="application/json";
                                poststate.posttype=3;
                                return;
                        }
                        break;    
                    case 15:
                        if(strcasecmp(buffer_value.c_str(),"application/xml")==0){
                                poststate.type="application/xml";
                                poststate.posttype=4;
                                return;
                        }
                    case 6:
                        if(strcasecmp(buffer_value.c_str(),"binary")==0){
                                poststate.type="binary";
                                poststate.posttype=6;
                                return;
                        }    
                        break;
                    default:
                          poststate.type="raw";
                                poststate.posttype=7;
                                return;      
                 }

                 
            }
            void httpparse::getcontenttype(){
                    unsigned int i=0,linesize;
                    linesize=header_value.size();
                    buffer_value.clear();
                    unsigned char statetemp=0;
                    poststate.posttype=0;
                   for(;i<linesize;i++){
                                                             
                              if(header_value[i]==0x3B){
                                     
                                    if(statetemp==0){
                                        callposttype();   
                                    }else if(statetemp==1){
                                          poststate.chartset=buffer_value; 
                                          statetemp=0;
                                    }else if(statetemp==2){
                                          poststate.boundary=buffer_value; 
                                          statetemp=0;  
                                    }
                                    /////////////////////      
                                    buffer_value.clear();
                                    continue;

                              }
                              if(header_value[i]==0x3D){
                                    if(strcasecmp(buffer_value.c_str(),"charset")==0){    
                                          buffer_value.clear();
                                          statetemp=1;
                                          continue;
                                    }else if(strcasecmp(buffer_value.c_str(),"boundary")==0){    
                                          buffer_value.clear();
                                          statetemp=2;
                                          continue;
                                    }
                              }
                              if(header_value[i]==0x20){
                                    continue;
                              }
                              buffer_value.push_back(header_value[i]);
                        }
                        if(buffer_value.size()>0){
                            if(statetemp==1){
                                poststate.chartset=buffer_value; 
                            }else if(statetemp==2){
                                poststate.boundary=buffer_value; 
                            }else{
                                callposttype();
                            }
                        }     
 
            }
             void httpparse::getrange(){
                   unsigned int j=0,linesize;
                   linesize=header_value.size();
                   buffer_value.clear();
                   for(;j<linesize;j++){
                        if(header_value[j]==0x3D){
                              j++;
                              break;
                        }
                        buffer_value.push_back(header_value[j]);  
                  }
                  
                  if(strcasecmp(buffer_value.c_str(),"bytes")==0){          
                        state.rangebytes=true;
                  }
                  buffer_value.clear();
                  bool ismuilt=false;
                        for(;j<linesize;j++){
                        if(header_value[j]==0x2C){
                              j++;
                              ismuilt=true;
                              break;
                        }
                        if(header_value[j]==0x2D){
                              
                              long long tm=0;
                              for(int qi=0;qi<buffer_value.size();qi++){
                                    if(buffer_value[qi]<0x3A&&buffer_value[qi]>0x2F){
                                                      tm= tm*10+(buffer_value[qi]-0x30);
                                    }
                              }
                              state.rangebegin=tm;
                              buffer_value.clear();
                              continue;
                        }
                        buffer_value.push_back(header_value[j]);  
                  }

                  if(j==header_value.length()||ismuilt){
                        long long tm=0;
                        for(int qi=0;qi<buffer_value.size();qi++){
                                    if(buffer_value[qi]<0x3A&&buffer_value[qi]>0x2F){
                                         tm= tm*10+(buffer_value[qi]-0x30);
                                    }
                              }
                        state.rangeend=tm;
                  }
                
            } 
            void httpparse::readheaderline(const unsigned char * buffer,unsigned int buffersize){
                    unsigned int i=readoffset;
                    if(headendhitnum>0){
                       headendhitnum=checkheadend(buffer,buffersize);
                    }
                    if(headendhitnum>3){
                        headerfinish=1;
                        readoffset=i;
                        buffer_value.clear();
                        header_key.clear();
                        header_value.clear();
                        header_temp.clear();
                        header_input.clear();
                        buffer_key.clear();
                        headendhitnum=0;
                        return;
                    }
                    headendhitnum=0;

                    int lineend=0;
                    for(;i<buffersize;i++){
                        if(buffer[i]==0x0D){
                                lineend=1;
                                break;
                        }
                        contentline.push_back(buffer[i]);
                   }
                   if(lineend==1){
                      
                        if(contentline.size()>0){

                            headerrawcontent.emplace_back(contentline);
                                if(headerstep==0){
                                    methodprocess();    
                                }else{

                                    header_key.clear();
                                    header_value.clear();
                                    bool isfirst;
                                    isfirst=true;
                                    for(int j=0;j<contentline.size();j++){
                                            if(isfirst&&contentline[j]==':'){
                                                header_key=header_value;
                                                j++;
                                                for(;j<contentline.size();j++){
                                                        if(contentline[j]!=0x20){
                                                            j-=1;
                                                            break;
                                                        }
                                                }
                                                header_value.clear();
                                                isfirst=false;
                                                continue;
                                            }
                                            if(isfirst&&contentline[j]==0x20){
                                                 continue;   
                                            }
                                            header_value.push_back(contentline[j]);
                                    }
                                    if(header_key.size()>0){
                                            header[header_key]=header_value;
                                            switch (header_key.size()) {
                                                 case 24:
                                                    if(strcasecmp(header_key.c_str(),"Sec-WebSocket-Extensions")==0){
                                                        
                                                        getwebsocketextensions();  
                                                    }      
                                                    break; 
                                                case 21:
                                                    if(strcasecmp(header_key.c_str(),"Sec-WebSocket-Version")==0){
                                                         
                                                           websocket.version= (unsigned char)header_valuetoint();
                                                    }      
                                                    break;  
                                                 case 19:
                                                       if(strcasecmp(header_key.c_str(),"If-Unmodified-Since")==0){
                                                             getifunmodifiedsince();
                                                       } 
                                                       break;     
                                                 case 17:
                                                         
                                                     switch (header_key[0]) {
                                                            case 's':
                                                            case 'S':
                                                                   if(strcasecmp(header_key.c_str(),"Sec-WebSocket-Key")==0){
                                                                        
                                                                        websocket.key= header_value;  
                                                                  } 
                                                                  break;
                                                            case 'i':      
                                                            case 'I':
                                                                  if(strcasecmp(header_key.c_str(),"If-Modified-Since")==0){
                                                                         
                                                                        getifmodifiedsince();      
                                                                  }  
                                                                  break;
                                                            default:
                                                                  ;            
                                                      }
                                                    break;    
                                                case 15:
                                                         if(header_key[7]=='E'){   
                                                                  if(strcasecmp(header_key.c_str(),"Accept-Encoding")==0){
                                                                         
                                                                        getacceptencoding();
                                                                        break;
                                                                  } 
                                                          }else if(header_key[7]=='L'){
                                                                if(strcasecmp(header_key.c_str(),"Accept-Language")==0){
                                                                        
                                                                        getacceptlanguage();   
                                                                        break;   
                                                                  } 
                                                          }       
                                                                   
                                                              if(strcasecmp(header_key.c_str(),"Accept-Encoding")==0){
                                                                         
                                                                        getacceptencoding();
                                                                         
                                                                  } 
                                                                     if(strcasecmp(header_key.c_str(),"Accept-Language")==0){
                                                                        
                                                                        getacceptlanguage();   
                                                                          
                                                                  }      
                                                      //Accept-Language
                                                      
                                                       break;  
                                                case 14:
                                                       if(strcasecmp(header_key.c_str(),"Content-Length")==0){
                                                             poststate.length=header_valuetoint();
                                                       } 
                                                       break;  
                                                case 13: 
                                                      if(strcasecmp(header_key.c_str(),"If-None-Match")==0){
                                                            getifnonematch();
                                                       }     
                                                      break;             
                                                case 12:
                                                        if(strcasecmp(header_key.c_str(),"Content-Type")==0){
                                                            
                                                            getcontenttype();  
                                                        }
                                                        break;       
                                                case 10:
                                                       switch (header_key[0]) {
                                                            case 'c':
                                                            case 'C':
                                                                    if(strcasecmp(header_key.c_str(),"Connection")==0){
                                                                            getconnection();
                                                                    } 
                                                                    break;
                                                            case 'u':
                                                            case 'U':
                                                                    if(strcasecmp(header_key.c_str(),"User-Agent")==0){
                                                                            useragent=header_value;
                                                                            
                                                                    }  
                                                                    break;
                                                       }
                                                       break;
                                                case 8:
                                                       if(strcasecmp(header_key.c_str(),"If-Match")==0){
                                                            
                                                            getifnonematch();
                                                       }
                                                       break;        
                                                case 7:
                                                       if(strcasecmp(header_key.c_str(),"Upgrade")==0){
                                                             
                                                            getupgrade();
                                                       }
                                                       break;         
                                                case 6:
                                                      
                                                       switch(header_key[0]){
                                                                  case 'c':
                                                                  case 'C':
                                                                        if(strcasecmp(header_key.c_str(),"Cookie")==0){
                                                                               
                                                                              getcookie();
                                                                        }
                                                                        break;
                                                                  case 'a':      
                                                                  case 'A':
                                                                        if(strcasecmp(header_key.c_str(),"Accept")==0){
                                                                               
                                                                              getaccept();
                                                                        }
                                                                        break;            
                                                            }
                                                       break;        
                                                case 5:
                                                       if(strcasecmp(header_key.c_str(),"Range")==0){
                                                            getrange();
                                                       } 
                                                       break;         
                                                case 4:
                                                       if(strcasecmp(header_key.c_str(),"Host")==0){
                                                            getheaderhost();
                                                       } 
                                                       break;        
                                            }
                                    }
                             }
                        }
                        contentline.clear();
                        headendhitnum++;
                        i++;
                        if(buffer[i]==0x0A&&i<buffersize){
                            i++;
                            headendhitnum++;
                            if(buffer[i]==0x0D&&i<buffersize){
                                i++;
                                headendhitnum++;
                                if(buffer[i]==0x0A&&i<buffersize){
                                        i++;
                                        headendhitnum++;
                                }     
                            }     
                        }    
                         
                        if(headendhitnum>3){
                            headerfinish=1;
                            readoffset=i;
                              buffer_value.clear();
                              header_key.clear();
                              header_value.clear();
                              header_temp.clear();
                              header_input.clear();
                              buffer_key.clear();
                              headendhitnum=0;
                            return;
                        }
                    }
                    readoffset=i;

            }
            void httpparse::getaccept(){
                    unsigned int i=0,linesize;
                    linesize=header_value.size();
                    
                    buffer_value.clear();
 
                   for(;i<linesize;i++){
                              if(header_value[i]==0x2C||header_value[i]==0x3B){
                                    switch (buffer_value.length()) {
                                          case 10:
                                                if(buffer_value[6]=='a'&&buffer_value[7]=='v'&&buffer_value[8]=='i'&&buffer_value[9]=='f'){
                                                    state.avif=true;        
                                                }else if(buffer_value[6]=='w'&&buffer_value[7]=='e'&&buffer_value[8]=='b'&&buffer_value[9]=='p'){
                                                    state.webp=true;  
                                                }
                                                break;
                                          default:
                                                ;      
                                    }
                                    buffer_value.clear();
                                    continue;
                              }
                              if(header_value[i]==0x20){
                                 continue;
                              }
                              buffer_value.push_back(header_value[i]);
                }
                if(buffer_value.size()>0){
                        switch (buffer_value.length()) {                  
                              case 10:
                                    if(buffer_value[6]=='a'&&buffer_value[7]=='v'&&buffer_value[8]=='i'&&buffer_value[9]=='f'){
                                          state.avif=true;        
                                    }else if(buffer_value[6]=='w'&&buffer_value[7]=='e'&&buffer_value[8]=='b'&&buffer_value[9]=='p'){
                                          state.webp=true;  
                                    }
                                    break;
                              default:
                                    ;      
                       }
                } 
                 
            }
            void httpparse::getacceptlanguage(){
                  int i=0;
                  for(;i<header_value.size();i++){
                        if(header_value[i]==0x2C){
                            break;   
                        }
                        state.language[i]=header_value[i];
                        if(i>4){
                            break;  
                        }
                   }   
                   state.language[5]=0x00;
                   
            }
            void httpparse::getifunmodifiedsince(){
                  state.ifmodifiedsince=strgmttotime(header_value);
            }
            void httpparse::getifmodifiedsince(){
                  state.ifmodifiedsince=strgmttotime(header_value);
            }
            void httpparse::getifnonematch(){
                    unsigned int i=0;
                    etag.clear();    
                    if(header_value[i]=='W'||header_value[i]=='w'){
                          if(header_value[i+1]==0x2F){
                                i+=2;
                          }
                    }     
                    for(;i<header_value.size();i++){
                        if(header_value[i]!=0x22){
                            etag.push_back(header_value[i]);      
                        }
                   }   
                   
            }
            void httpparse::getwebsocketextensions(){
                    switch (header_value.length()) {
                        case 22:
                              if(strcasecmp(header_value.c_str(),"x-webkit-deflate-frame")==0){
                                    websocket.deflateframe=true;
                                    websocket.deflate=true;
                              }
                              break;
                        case 18:
                                    
                              if(strcasecmp(header_value.c_str(),"permessage-deflate")==0){    
                                    websocket.permessagedeflate=true;
                                    websocket.deflate=true;
                                    
                              }
                              break;     
                        case 16: 
                              if(strcasecmp(header_value.c_str(),"perframe-deflate")==0){       
                                    websocket.perframedeflate=true;
                                    websocket.deflate=true;
                              }
                              break;
                        default:
                              ;              
                  }
                  if(websocket.deflate){
                      return;
                  } 
                  if(header_value.find("permessage-deflate")!=std::string::npos){
                         websocket.permessagedeflate=true;
                         websocket.deflate=true;
                         return;
                  }     
                 if(header_value.find("perframe-deflate")!=std::string::npos){
                         websocket.perframedeflate=true;
                         websocket.deflate=true;
                         return;
                  }    
                  if(header_value.find("x-webkit-deflate-frame")!=std::string::npos){
                          websocket.deflateframe=true;
                          websocket.deflate=true;
                         return;
                  }        
            }
            void httpparse::getupgrade(){
                    
                    if(header_value.size()>9){
                        if(header_value.back()==0x20){
                            header_value.pop_back();
                        }
                    }
                
                    if(strcasecmp(header_value.c_str(),"websocket")==0){
                        state.websocket=true;
                    }
            }
            void httpparse::getconnection(){
                    if(strcasecmp(header_value.c_str(),"keep-alive")==0){     
                                    state.keeplive=true;
                    }
                    if(strcasecmp(header_value.c_str(),"Upgrade")==0){       
                                    state.upgradeconnection=true;
                    }
                    if(header_value[0]=='c'||header_value[0]=='C'){
                                    state.keeplive=false;
                    }
            }
            void httpparse::getacceptencoding(){
                    unsigned int i=0,linesize;
                    linesize=header_value.size();
                    buffer_key.clear();
                    buffer_value.clear();
 
                   for(;i<linesize;i++){
                        if(header_value[i]==0x2C){
                               
                              switch(buffer_value.size()){
                                    case 2:
                                          if(buffer_value[0]=='b'){
                                              state.br=true;        
                                          }
                                          break;
                                    case 4:
                                          if(buffer_value[0]=='g'){
                                              state.gzip=true;      
                                          }
                                          break;
                                    case 7:
                                          if(buffer_value[0]=='d'){
                                              state.deflate=true;   
                                          }
                                          break;
                                    default:
                                          ;                  
                              }
                              buffer_value.clear();
                              continue;
                        }
                        if(header_value[i]==0x20){
                              continue;
                        }
                        buffer_value.push_back(header_value[i]);    

                     }
                    if(buffer_value.size()>0){
                         
                         switch(buffer_value.size()){
                                    case 2:
                                          if(buffer_value[0]=='b'){
                                              state.br=true;        
                                          }
                                          break;
                                    case 4:
                                          if(buffer_value[0]=='g'){
                                              state.gzip=true;      
                                          }
                                          break;
                                    case 7:
                                          if(buffer_value[0]=='d'){
                                              state.deflate=true;   
                                          }
                                          break;
                                    default:
                                          ;                  
                              }
                              buffer_value.clear();
                    }
            }
            void httpparse::getcookie(){
                        unsigned int i=0,linesize;
                        linesize=header_value.size();
                        buffer_key.clear();
                        buffer_value.clear();
                        for(;i<linesize;i++){
                                if(header_value[i]==0x3D){
                                    buffer_key=HTTP::url_decode(buffer_value.data(), buffer_value.length());
                                    buffer_value.clear();
                                    continue;
                                }
                                if(header_value[i]==0x3B){
                                    buffer_value=HTTP::url_decode(buffer_value.data(), buffer_value.length());
                                    cookie[buffer_key]=buffer_value;
                                    buffer_key.clear();
                                    buffer_value.clear();
                                    continue;
                                }
                                if(header_value[i]==0x20){
                                        continue;
                                }
                            buffer_value.push_back(header_value[i]);
                        }
                        if(buffer_value.size()>0){
                              buffer_value=HTTP::url_decode(buffer_value.data(), buffer_value.length());
                              cookie[buffer_key]=buffer_value;
                        }  
                       
                         
            }
            void httpparse::getheaderhost(){
                   unsigned int ioffset=0,linesize;
                  linesize=header_value.size();
                  unsigned char ishasport=0;
                  port=0;
                  //check hostport 检查有没有定制端口
                  for(;ioffset<linesize;ioffset++){
                        if(header_value[ioffset]==0x3A){
                              ishasport=1;
                              ioffset++;
                              break;
                        }
                        host.push_back(header_value[ioffset]);
                  }
                  std::transform(host.begin(),host.end(),host.begin(),::tolower);
                  if(ishasport==1){
                        for(;ioffset<linesize;ioffset++){
                              if(header_value[ioffset]<0x3A&&header_value[ioffset]>0x2F){
                                    port=port*10+(header_value[ioffset]-0x30);
                              }
                        }
                  }
                  state.port=port;
                   
            }
            void httpparse::readboundaryline(const unsigned char * buffer,unsigned int buffersize){
                  unsigned int i=readoffset;
                  unsigned int isbound=0;
                        for(;i<buffersize;i++){
                             if(buffer[i]==0x0D){
                                   isbound=1;
                                   break;
                             } 
                             buffer_key.push_back(buffer[i]);   
                        }
                        if(isbound==1){
                           std::string bi;
 
                           bi=buffer_key.substr(2);
                           if(bi==poststate.boundary){
                                  
                                 postfieldtype=2;
                           }        
                              i++;
                              if(buffer[i]==0x0A&&i<buffersize){
                                   i++;
                              }    
                         
                        }
                        readoffset=i;
            }
             void httpparse::readformfilename(const unsigned char * buffer,unsigned int buffersize){
                  unsigned int i=readoffset;
                  unsigned int isbound=0;
                        // if(buffer[i]==0x0A&&i<buffersize){
                        //             i++;
                        // } 
                        for(;i<buffersize;i++){
                             if(buffer[i]==0x0D){
                                   isbound=1;
                                   headendhitnum=1; 
                                   break;
                             } 
                             buffer_key.push_back(buffer[i]);   
                        }
                        if(isbound==1){
                           std::string fieldname;
                                 
                                    header_temp.clear();
                                    unsigned int jj=0;
                                    for(;jj<buffer_key.size();jj++){
                                          if(buffer_key[jj]==';'){
                                                header_temp.clear();
                                                continue;
                                          }
                                          if(buffer_key[jj]==0x20){
                                                header_temp.clear();
                                                continue;
                                          }
                                          if(buffer_key[jj]==0x3D){
                                                if(header_temp=="name"){
                                                      int mm=jj;
                                                      mm+=1;
                                                      if(buffer_key[mm]=='"'){
                                                            mm+=1;
                                                      }
                                                      header_key.clear();
                                                      for(;mm<buffer_key.size();mm++){
                                                                  if(buffer_key[mm]=='"'){
                                                                        break;
                                                                  }
                                                          header_key.push_back(buffer_key[mm]);
                                                      }
                                                      if(header_key.size()>0){
                                                            if(postfieldtype<3){
                                                                  postfieldtype=4;
                                                            }
                                                      }
                                                       
                                                      if(buffer_key[mm]=='"'){
                                                            mm+=1;
                                                      }
                                                      jj=mm;


                                                }else if(header_temp=="filename"){

                                                      int mm=jj;
                                                      mm+=1;
                                                      if(buffer_key[mm]=='"'){
                                                            mm+=1;
                                                      }
                                                      header_value.clear();
                                                      for(;mm<buffer_key.size();mm++){
                                                                  if(buffer_key[mm]=='"'){
                                                                        break;
                                                                  }
                                                          header_value.push_back(buffer_key[mm]);
                                                      }
                                                      if(header_value.size()>0){
                                                            if(postfieldtype<5){
                                                                  postfieldtype=6;
                                                            }
                                                      }
                                                       
                                                      if(buffer_key[mm]=='"'){
                                                            mm+=1;
                                                      }
                                                      jj=mm;

                                                }
                                                continue;
                                          }
                                          header_temp.push_back(buffer_key[jj]);
                                    }
                                   header_temp.clear();       

                                   if(postfieldtype==6){
                                         upfile.filename=header_value;
                                         upfile.name=header_key;


                                         
                                          header_temp=upfile.filename+std::to_string(timeid())+header_key; 
                                      
                                          upfile.tempfile="./tmp/";
                                          upfile.tempfile.append(std::to_string(std::hash<std::string>{}(header_temp)));
                                   
                                          uprawfile=fopen(upfile.tempfile.c_str(),"wb"); 
                                          if(!uprawfile){
                                                upfile.tempfile.append("_t");
                                                uprawfile=fopen(upfile.tempfile.c_str(),"wb"); 
                                                if(!uprawfile){
                                                      error=3;
                                                      postfieldtype=12;
                                                }
                                          }
                                          upfile.size=0;
                                          header_temp.clear();

                                   } 
                                    changetype=0;
                                           
                              header_input.clear();
                              i++;
                              
                               if(buffer[i]==0x0A&&i<buffersize){
                                    i++;
                                    headendhitnum++;
                                    if(buffer[i]==0x0D&&i<buffersize){
                                          i++;
                                          headendhitnum++;
                                          if(buffer[i]==0x0A&&i<buffersize){
                                                      i++;
                                                      headendhitnum++;
                                          
                                          }     
                                    }     
                              }       
                           buffer_key.clear();
                            
                        }
                        readoffset=i;
            }
            void httpparse::checkformfilecontentbegin(const unsigned char * buffer,unsigned int buffersize){
                      unsigned int i=readoffset;
                  
                    if(headendhitnum>0){
                        if(headendhitnum==2){
                                if(buffer[i]==0x0D&&i<buffersize&&headendhitnum<4){
                                    i++;
                                    headendhitnum++;
                                    if(buffer[i]==0x0A&&i<buffersize&&headendhitnum<4){
                                            i++;
                                            headendhitnum++;
                                    
                                    }     
                                }      
                        }else{
                            if(buffer[i]==0x0A&&i<buffersize&&headendhitnum<4){
                                            i++;
                                            headendhitnum++;
                                            if(buffer[i]==0x0D&&i<buffersize&&headendhitnum<4){
                                                i++;
                                                headendhitnum++;
                                                if(buffer[i]==0x0A&&i<buffersize&&headendhitnum<4){
                                                        i++;
                                                        headendhitnum++;
                                                
                                                }     
                                            }     
                                    }        
                        }
                    }
                    readoffset=i;
                    if(headendhitnum>3){
                        headendhitnum=0;
                        postfieldtype+=3;
                        buffer_key.clear();
                        header_temp.clear();
                        header_input.clear();
                        changetype=0;
                        return;
                    }
                    headendhitnum=0;
                    for(;i<buffersize;i++){
                          if(buffer[i]==0x0D){
                                headendhitnum=1;
                                i++;
                                break;
                          }
                          if(buffer[i]==':'){
                                if(strcasecmp(header_temp.c_str(),"Content-Type")==0){
                                      changetype=2;
                                }
                                header_temp.clear();
                                continue;
                                
                          }
                          if(buffer[i]==0x20){
                                continue;
                          }
                          if(buffer[i]==';'){
                                if(changetype==2){
                                       
                                       upfile.type=header_temp;
                                       changetype=1;
                                }
                                header_temp.clear();
                                continue;
                          }
                          header_temp.push_back(buffer[i]);
                    }
                    if(headendhitnum==1){
                           if(changetype==2){
                                       upfile.type=header_temp;
                           }
                           header_temp.clear();
                           buffer_key.clear();
                           changetype=0;
                    }
                    readoffset=i;    
            }
            void httpparse::readformfielditem(const unsigned char * buffer,unsigned int buffersize){
                   unsigned int i=readoffset;
                  unsigned int isbound=0;

                    for(;i<buffersize;i++){
                             if(buffer[i]==0x0D){
                                   //test bounday
                                   //both 0D between 
                                   if(buffer[i+1]!=0x0A){
                                         
                                        if(headerstep==100){
                                                headerstep=0;
                                                header_input.push_back(0x0D);
                                                for(int j=0;j<header_temp.size();j++){
                                                      header_input.push_back(header_temp[j]);  
                                                }
                                                header_temp.clear(); 
                                        }else{
                                           headerstep=0;     
                                        }  

                                         header_input.push_back(buffer[i]);
                                         continue;
                                   }else{
                                         if(headerstep==100){
                                                 
                                                header_input.push_back(0x0D);
                                                for(int j=0;j<header_temp.size();j++){
                                                      header_input.push_back(header_temp[j]);  
                                                }
                                                header_temp.clear(); 
                                        }
                                   }
 
                                   headerstep=100;
                                   header_temp.clear(); 
                                   
                                   continue;
                             } 
                             if(headerstep==100){
  
                                header_temp.push_back(buffer[i]);  
                                if(header_temp.size()==(poststate.boundary.size()+3)){
                                      if(header_temp[0]==0x0A&&header_temp[1]==0x2D&&header_temp[2]==0x2D){
                                            int jjj=3;
                                            for(int nnn=0;nnn<poststate.boundary.size();nnn++){
                                                      if(header_temp[jjj]!=poststate.boundary[nnn]){
                                                            break;
                                                      }
                                                      jjj+=1;
                                            }
                                            if(jjj==header_temp.size()){
                                                postfieldtype=2;
                                                 
                                                header_temp=header_key;
                                                procssxformurlencoded();
                                                //post[header_key]=header_input;
                                                header_key.clear();  
                                                header_value.clear();  
                                                header_temp.clear();  
                                                header_input.clear();
                                                buffer_key.clear(); 
                                                 headendhitnum=1;
                                                 headerstep=0;
                                                 i++;     
                                                 if(buffer[i]==0x2D&&buffer[i+1]==0x2D){
                                                      headerfinish=2;
                                                      i+=2;
                                                      readoffset=i;
                                                      headendhitnum=0;
                                                      return;
                                                 }

                                                 if(buffer[i]==0x0A&&i<buffersize){
                                                      i++;
                                                      headendhitnum++;
 
                                                }      

                                                readoffset=i;
                                                return;

                                            }
                                      }
                                      headerstep=0;
                                      header_input.push_back(0x0D);
                                      for(int j=0;j<header_temp.size();j++){
                                                      header_input.push_back(header_temp[j]);  
                                      }
                                      header_temp.clear(); 
                                }    
                             }else{
                               header_input.push_back(buffer[i]);   
                             }
                             
                   }
                   readoffset=i;

            }
             void httpparse::procssformfile(){
                        std::string objname;
                              bool isgroup=true;
                              for(int j=0;j<upfile.name.length();j++){
                                    if(upfile.name[j]=='['){
                                          std::string key1name;

                                          int n=j;
                                          n++;
                                          bool ishaskey=false;
                                          bool ishaskey2=false;
                                          for(;n<upfile.name.length();n++){
                                                if(upfile.name[n]==']'){
                                                      ishaskey=true;
                                                      n++;
                                                      break;
                                                }else if(upfile.name[n]=='['){
                                                     
                                                      break;
                                                }  
                                                if(upfile.name[n]!=0x22){ 
                                                      key1name.push_back(upfile.name[n]);
                                                }
                                          }
                                          
                                          std::string key2name;
                                          if(ishaskey){
                                                
                                                int m=n;
                                                if(n<upfile.name.length()){
                                                      if(upfile.name[m]=='['){
                                                            m+=1;
                                                            for(;m<upfile.name.length();m++){
                                                                  if(upfile.name[m]==']'){
                                                                        ishaskey2=true;
                                                                        m++;
                                                                        break;
                                                                  }else if(upfile.name[m]=='['){
                                                      
                                                                        break;
                                                                  }
                                                                  if(upfile.name[m]!=0x22){
                                                                        key2name.push_back(upfile.name[m]);
                                                                  }   
                                                                  

                                                            }
                                                            
                                                            if(ishaskey2&&m==upfile.name.length()){
                                                            }else{
                                                                ishaskey2=false;  
                                                            }
                                                      }        
                                                }      
                                                
                                               if(ishaskey2){
                                                      //双数组
                                                      if(key1name.empty()){
                                                          if(key2name.empty()){
                                                                 

                                                                  HTTP::OBJ_VALUE objtemp;
                                                                  objtemp.set_array();
                                                                  objtemp["filename"]=upfile.filename;
                                                                        objtemp["tempfile"]=upfile.tempfile;
                                                                        objtemp["type"]=upfile.type;
                                                                        objtemp["size"]=upfile.size;
                                                                        objtemp["error"]=upfile.error;

                                                                   HTTP::OBJ_ARRAY objtemp1;
                                                                 objtemp1.push(std::move(objtemp));      
                                                                  files[objname].push(std::move(objtemp1));       

                                                          }else{
                                                                 

                                                                  HTTP::OBJ_VALUE objtemp;
                                                                  objtemp[key2name].set_array();
                                                                  objtemp[key2name]["filename"]=upfile.filename;
                                                                        objtemp[key2name]["tempfile"]=upfile.tempfile;
                                                                        objtemp[key2name]["type"]=upfile.type;
                                                                        objtemp[key2name]["size"]=upfile.size;
                                                                        objtemp[key2name]["error"]=upfile.error;
                                                                  files[objname].set_array();
                                                                  files[objname].push(std::move(objtemp));      


                                                          }  
                                                          
                                                      }else{
                                                          if(key2name.empty()){
                                                                 

                                                                 files[objname][key1name].set_array();
                                                                  HTTP::OBJ_VALUE objtemp;
                                                                  objtemp.set_array();
                                                                  objtemp["filename"]=upfile.filename;
                                                                        objtemp["tempfile"]=upfile.tempfile;
                                                                        objtemp["type"]=upfile.type;
                                                                        objtemp["size"]=upfile.size;
                                                                        objtemp["error"]=upfile.error;

                                                                  files[objname][key1name]=objtemp;
                                                                  

                                                          }else{
                                                                
                                                                  files[objname][key1name][key2name].set_array();
                                                                  files[objname][key1name][key2name]["filename"]=upfile.filename;
                                                                  files[objname][key1name][key2name]["tempfile"]=upfile.tempfile;
                                                                  files[objname][key1name][key2name]["type"]=upfile.type;
                                                                  files[objname][key1name][key2name]["size"]=upfile.size;
                                                                  files[objname][key1name][key2name]["error"]=upfile.error;    

                                                          }  
                                                           
                                                      } 
                                                      j=m;
                                                      isgroup=false;
                                               }else if(n==upfile.name.length()){
                                                      //只有一个
                                                      if(key1name.empty()){
                                                          files[objname].set_array();  
                                                          HTTP::OBJ_VALUE objtemp;
                                                          objtemp.set_array();
                                                          objtemp["filename"]=upfile.filename;
                                                            objtemp["tempfile"]=upfile.tempfile;
                                                            objtemp["type"]=upfile.type;
                                                            objtemp["size"]=upfile.size;
                                                            objtemp["error"]=upfile.error;
                                                          files[objname]=objtemp;        
                                                      }else{
                                                          //files[objname].push(key1name,"");
                                                            files[objname][key1name].set_array();  
                                                            files[objname][key1name]["filename"]=upfile.filename;
                                                            files[objname][key1name]["tempfile"]=upfile.tempfile;
                                                            files[objname][key1name]["type"]=upfile.type;
                                                            files[objname][key1name]["size"]=upfile.size;
                                                            files[objname][key1name]["error"]=upfile.error;
                                                      } 
                                                      j=n;  
                                                      isgroup=false;
                                               }else{
                                                     
                                                      //not array

                                               } 
     
                                          }
                                          if(isgroup){
                                              objname.push_back(upfile.name[j]);   
                                          }
                                    }else{
                                          objname.push_back(upfile.name[j]);
                                    }
                                    
                              }
                              if(isgroup){
                                   // files[upfile.name]=buffer_value;
                                    files[upfile.name].set_array(); 
                                    files[upfile.name]["filename"]=upfile.filename;
                                    files[upfile.name]["tempfile"]=upfile.tempfile;
                                    files[upfile.name]["type"]=upfile.type;
                                    files[upfile.name]["size"]=upfile.size;
                                    files[upfile.name]["error"]=upfile.error;
                                 
                              }
                             upfile.filename.clear();
                             upfile.tempfile.clear();
                             upfile.type.clear();
                             upfile.size=0;
                             upfile.error=0;
            }
            void httpparse::readformfilecotent(const unsigned char * buffer,unsigned int buffersize){
                   unsigned int i=readoffset;
                  unsigned int isbound=0;

                    for(;i<buffersize;i++){
                             if(buffer[i]==0x0D){
                                   //test bounday
                                   //both 0D between 
                                   if(buffer[i+1]!=0x0A){
                                        if(headerstep==100){
                                                headerstep=0;
                                        }else{
                                           headerstep=0;     
                                        }  
                                         header_input.clear(); 
                                         continue;
                                   }
                                   headerstep=100;
                                   header_input.clear(); 
                                   continue;
                             } 
                             if(headerstep==100){  
                                header_input.push_back(buffer[i]);  
                                if(header_input.size()==(poststate.boundary.size()+3)){
                                      if(header_input[0]==0x0A&&header_input[1]==0x2D&&header_input[2]==0x2D){
                                            int jjj=3;
                                            for(int nnn=0;nnn<poststate.boundary.size();nnn++){
                                                      if(header_input[jjj]!=poststate.boundary[nnn]){
                                                            break;
                                                      }
                                                      jjj+=1;
                                            }
                                            if(jjj==header_input.size()){
                                                postfieldtype=2;
                                                //buffer_key.pop_back();
                                                upfile.size+=(i-readoffset-header_input.size());
                                                fwrite(&buffer[readoffset],(i-readoffset-header_input.size()),1,uprawfile); 
 
                                                //post[header_key]=buffer_key;
                                                //upfile.size=0;
                                                if(uprawfile){
                                                      fclose(uprawfile);
                                                      uprawfile=NULL;
                                                }
                                                procssformfile();
                                                header_key.clear();  
                                                header_value.clear();  
                                                header_temp.clear();  
                                                header_input.clear();
                                                buffer_key.clear(); 
                                                 headendhitnum=1;
                                                  headerstep=0;
                                                 i++;     
                                                 if(buffer[i]==0x2D&&buffer[i+1]==0x2D){
                                                      headerfinish=2;
                                                      i+=2;
                                                      readoffset=i;
                                                      headendhitnum=0;
                                                      return;
                                                 }

                                                 if(buffer[i]==0x0A&&i<buffersize){
                                                      i++;
                                                      headendhitnum++;
                                                }      

                                                readoffset=i;
                                                return;

                                            }
                                      }
                                      headerstep=0;
                                      header_input.clear(); 
                                }    
                             }
                             
                   }
                   fwrite(&buffer[readoffset],(i-readoffset),1,uprawfile); 
                   upfile.size+=(i-readoffset);
                   readoffset=i;

            }
            void httpparse::readmultipartformdata(const unsigned char * buffer,unsigned int buffersize){

                   for(;readoffset<buffersize;){
                          switch (postfieldtype) {
                                    case 0:
                                          //开头
                                          readboundaryline(buffer,buffersize);
                                          header_key.clear();  
                                          header_value.clear();  
                                          header_temp.clear();  
                                          header_input.clear();
                                          buffer_key.clear();
                                          break;
                                    case 2:
                                          readformfilename(buffer,buffersize);
                                          break;   
                                    case 4:
                                          checkformfilecontentbegin(buffer,buffersize);
                                          break;
                                    case 6:
                                          checkformfilecontentbegin(buffer,buffersize);
                                          break;               
                                    case 7:
                                          readformfielditem(buffer,buffersize);
                                          break;  
                                    case 9:
                                          readformfilecotent(buffer,buffersize);
                                          break;               
                              default:
                                   readoffset++; 
                          }     
                   }
                  

            }
            void httpparse::readformjson(const unsigned char * buffer,unsigned int buffersize){
                        unsigned int i=readoffset;
                        for(;i<buffersize;i++){
                                    buffer_value.push_back(buffer[i]);   
                        }
                        readoffset=i;
                        if((buffer_value.size()+2)>=poststate.length){
                              headerfinish=2;
                              json.fromjson(buffer_value);
                              

                        }
                    
            }
             void httpparse::readformurlencoded(const unsigned char * buffer,unsigned int buffersize){
                        unsigned int i=readoffset;
                        for(;i<buffersize;i++){
                                    buffer_value.push_back(buffer[i]);   
                        }
                        readoffset=i;
                        if((buffer_value.size()+2)>=poststate.length){
                              headerfinish=2;
 
                              header_key.clear();  
                              header_value.clear();  
                              header_temp.clear();  
                              header_input.clear();
                              int qsize=buffer_value.size();
                              unsigned char partype=0;
                              unsigned int j=0;
                              for(j=0;j<qsize;j++){
                                    if(buffer_value[j]==0x3D){
                                          header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                                          header_value.clear(); 
                                          partype=1;
                                          continue;    
                                    }else if(buffer_value[j]==0x26){
                                          header_input=HTTP::url_decode(header_value.data(),header_value.length());
                                          procssxformurlencoded();
                                          header_value.clear();  
                                          partype=2;   
                                          continue;     
                                    }  
                                    header_value.push_back(buffer_value[j]);
                              }
                              if(partype==1){
                                    header_input=HTTP::url_decode(header_value.data(),header_value.length());
                                    procssxformurlencoded();
                              }else if(partype==2){
                                    header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                                    header_input.clear();
                                    procssxformurlencoded();    
                              }else if(header_value.size()>0){
                                    header_temp=HTTP::url_decode(header_value.data(),header_value.length());
                                    header_input.clear();
                                    procssxformurlencoded();  
                              }

                              

                        }
                    
            }
          
            void httpparse::readformxml(const unsigned char * buffer,unsigned int buffersize){
                        unsigned int i=readoffset;

                        if(!uprawfile){
                              header_temp="application/octet-stream"+std::to_string(timeid())+std::to_string(rand()); 
                              upfile.tempfile="./tmp/";
                              upfile.tempfile.append(std::to_string(std::hash<std::string>{}(header_temp)));

                              uprawfile=fopen(upfile.tempfile.c_str(),"wb"); 
                              if(!uprawfile){
                                    upfile.tempfile.append("_t");
                                    uprawfile=fopen(upfile.tempfile.c_str(),"wb"); 
                                    if(!uprawfile){
                                          error=3;
                                           
                                    }
                              }
                              upfile.size=0;
                        }     
                        if(i<buffersize&&uprawfile){
                             unsigned int tempnum=buffersize-i;
                             auto n=fwrite(&buffer[i],tempnum,1,uprawfile); 
                             upfile.size=tempnum;
                        }
                         
                        if((upfile.size+2)>=poststate.length){

                                    fclose(uprawfile);
                                    uprawfile=NULL;
                                    headerfinish=2;
                        }
                      
            }
 
            void httpparse::process(const unsigned char * buffer,unsigned int buffersize){

                   if(error>0){
                               return;
                   }
                  if(headerfinish==0){
                         for(;readoffset<buffersize;){
                               
                              readheaderline(buffer,buffersize);  
                              if(error>0){
                                    break;
                              }
                              if(headerfinish==1){
                                    break;
                              }
                         }
                         
                  }
                  if(method==HEAD_METHOD::POST&&headerfinish==1&&error==0){
                        switch (poststate.posttype) {
                              case 1:
                                    //x-www-form-urlencoded
                                    readformurlencoded(buffer,buffersize);      
                                    break;
                              case 2:
                                    //multipart/form-data-
                                    readmultipartformdata(buffer,buffersize);      
                                    break;         
                              case 3:
                                    //json
                                    readformjson(buffer,buffersize);      
                                    break; 
                              case 4:
                                    //xml
                                    readformxml(buffer,buffersize);      
                                    break;   
                              case 5:
                                    //octet-stream
                                    readformxml(buffer,buffersize);      
                                    break;                 
                        }
                        for(;readoffset<buffersize;){
                                    readoffset++;
                        }
                       
                  }

         }
          bool httpparse::getfinish(){   
               if(method==HEAD_METHOD::POST){
                      if(headerfinish==2){
                          return true;
                        }else{
                           return false;
                        }
               }
               if(headerfinish==1){
                     return true;
               }else{
                     return false;
               }

         }
         void httpparse::finishdata(){
              if(headerfinish==0){
                  //headfinish
                  if(contentline.size()>0){
                      headerrawcontent.emplace_back(contentline);
                  }
              }
         }
        void httpparse::display(){
            for(int i=0;i<headerrawcontent.size();i++){
                std::cout<<i<<":"<<headerrawcontent[i]<<std::endl;
            }
        }
        void httpparse::clear(){
                 state.gzip=false;
                 state.deflate=false;
                 state.br=false; 
                 state.avif=false;
                 state.webp=false; 
                 state.keeplive=false;
                 state.websocket=false;
                 state.upgradeconnection=false;
                 state.rangebytes=false;
                 state.language[0]={0};
                 state.version=0;
                 state.port=0;
                 state.ifmodifiedsince=0;
                 state.rangebegin=0;
                 state.rangeend=0; 
                 headerrawcontent.clear();
                 header.clear();
                 pathinfo.clear();
                 readoffset=0;
                 headendhitnum=0;
                 host.clear();
                 etag.clear();
                 error=0;      
                 cookie.clear(); 
                  method=HEAD_METHOD::UNKNOW;
                  headerfinish=0;
                   
                  websocket.deflate=false;
                  websocket.permessagedeflate=false;
                  websocket.perframedeflate=false;
                  websocket.deflateframe=false;
                  websocket.isopen=false;
                  websocket.version=0x00;
                  websocket.key.clear();
                  websocket.ext.clear();
                         
        }
      
}
