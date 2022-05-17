#ifndef HTTP_URLDECODE_HTTP
#define HTTP_URLDECODE_HTTP

#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <map>
#include <utility>
#include <string>
#include <string_view>
#include <thread>
#include <chrono>
#include "urlcode.h"
namespace HTTP
{ 
//第一次匹配pos位置
int find_indexOf(const  char * source,int slen,const char * str,int len){
    const char* ps = source;
	  const char* pc = str;

    if(ps==NULL||pc==NULL){
        return -1;
    }
    if(len<1){
        return -1;
    }
    if (*ps == '\0' || *pc == '\0')
	  {
		  return -1;
	  }
    for(int i=0;i<slen;i++){
          if(ps[i]==pc[0]){
              int n=i;
              int j=0;
              for(;j<len;j++){
                  if(ps[n]!=pc[j]){
                      break;
                  }
                  n++;
              }
              //如果相同返回位置
              if(j==len){
                  return i;
              }
          }
    }
    return -1;
}
//第一次匹配pos位置偏移
int find_indexOffset(const  char * source,int begin,int slen,const char * str,int len){
    const char* ps = source;
	  const char* pc = str;

    if(ps==NULL||pc==NULL){
        return -1;
    }
    if(len<1){
        return -1;
    }
    if (*ps == '\0' || *pc == '\0')
	  {
		  return -1;
	  }
      if(begin<0){
          begin=0;
      }
    for(int i=begin;i<slen;i++){
          if(ps[i]==pc[0]){
              int n=i;
              int j=0;
              for(;j<len;j++){
                  if(ps[n]!=pc[j]){
                      break;
                  }
                  n++;
              }
              //如果相同返回位置
              if(j==len){
                  return n;
              }
          }
    }
    return -1;
}
//最后部分或全匹配
int find_lastsubpos(const  char * source,int slen,const char * str,int len){
    const char* ps = source;
	const char* pc = str;

    if(ps==NULL||pc==NULL){
        return -1;
    }
    if(len<1){
        return -1;
    }
    if (*ps == '\0' || *pc == '\0')
	{
		  return -1;
	}
    int n=slen-len;
    int offset=-1;
    if(n<0){
        n=0;
    }
    len=slen-n;
    for(int i=n;i<slen;i++){
          if(ps[i]==pc[0]){
              int n=i;
              int j=0;

              for(;j<len;j++){
                  if(ps[n]!=pc[j]){
                      break;
                  }
                  n++;
              }
              //如果相同返回位置
              if(j==len||n>=slen){
                 offset=i;
                 break;
              }
          }
    }
    return offset;
}


std::vector<std::pair<int,int>>   split_boundary(const char * sstr,int strlen,const char * sp,int len){
        std::vector<std::pair<int,int>>  pdata;
        const char* str = sstr;  
         const char* p = sp;    

    if(strlen==0){
        return pdata;
    }
    if(str==NULL){
        return pdata;
    }
    if(sp==NULL){
        pdata.emplace_back(0,strlen);
        return pdata;
    }
    if(len==0){
        pdata.emplace_back(0,strlen);
        return pdata;
    }

          int lastpos=0;
        for(int i=0;i<strlen;i++){
              if(str[i]==p[0]){
              int n=i;
              int j=0;
              for(;j<len;j++){
                  if(str[n]!=p[j]){
                      break;
                  }
                  n++;
              }
              //如果相同返回位置
              if(j==len){
                  if(n==len){
                     lastpos=n; 
                     i=n-1;
                  }else{ 
                     if(lastpos!=i){
                        pdata.emplace_back(lastpos,i);  
                     } 
                     i=n-1;   
                     lastpos=n; 
                     
                  }
              }
          }
        }

        if(lastpos<strlen){
                 pdata.emplace_back(lastpos,strlen);  
        }
  
        return pdata;
}

std::string url_decode(const char * str,int len){
    std::string url;
    const char* p = str;    
    unsigned char word[2];
    char zifu;   
    for(int i=0;i<len;i++){
        if(p[i]=='%'&&p[i+1]!='%'){
            word[0]=p[i+1];   
            word[1]=p[i+2]; 
            if(word[0] >= 'A' && word[0] <= 'Z'){
               word[0] = word[0] - 'A' + 10;  
            }else if(word[0] >= 'a' && word[0] <= 'z'){
               word[0] = word[0] - 'a' + 10;  
            }else if(word[0] >= '0' && word[0] <= '9'){
               word[0] = word[0] - '0';  
            }else{
               word[0]=0x00;
            } 
           
            if(word[1] >= 'A' && word[1] <= 'Z'){
               word[1] = word[1] - 'A' + 10;  
            }else if(word[1] >= 'a' && word[1] <= 'z'){
               word[1] = word[1] - 'a' + 10;  
            }else if(word[1] >= '0' && word[1] <= '9'){
               word[1] = word[1] - '0';  
            }else{
               word[1]=0x20;
            }
           zifu=word[0]*16+word[1];
            
           url.push_back(zifu); 
           i+=2;
        }else if(p[i]=='+'){
            url.push_back(0x20); 
        }else{
            url.push_back(p[i]); 
            
        }
    }
    
    return url;    
}

std::string url_encode(const char * str,int len){
    std::string url;
    const char* p = str;    
    unsigned char word;
    url.resize(len);
    for(int i=0;i<len;i++){
         if ((p[i] >= 'A' && p[i] <= 'Z')||(p[i] >= 'a' && p[i] <= 'z')||(p[i] >= '0' && p[i] <= '9') || 
            (p[i] == '-') ||
            (p[i] == '_') || 
            (p[i] == '.') || 
            (p[i] == '%') || 
            (p[i] == '~')){
              url.push_back(p[i]); 
 
            }else if (p[i] == ' '){
                url.push_back('+'); 
            }else
            {
    
                url.push_back('%'); 
                 
                word=(unsigned char)p[i] >> 4;
                word= word > 9 ? word + 55 : word+ 48;
                url.push_back(word); 
                 
                word=(unsigned char)p[i] % 16;
                word=  word > 9 ? word + 55 : word+ 48;
                url.push_back(word); 
                 

            }

    }
    
    return url;    
}

std::string url_rawencode(const char * str,int len){
    std::string url;
    const char* p = str;    
    unsigned char word;
    char zifu;   
    int j=0;
    url.resize(len);
    for(int i=0;i<len;i++){
         if ((p[i] >= 'A' && p[i] <= 'Z')||(p[i] >= 'a' && p[i] <= 'z')||(p[i] >= '0' && p[i] <= '9') || 
            (p[i] == '-') ||
            (p[i] == '_') || 
            (p[i] == '/') || 
            (p[i] == '&') || 
            (p[i] == '=') || 
            (p[i] == '?') || 
            (p[i] == '#') || 
            (p[i] == '.') || 
            (p[i] == '~')){
              url.push_back(p[i]); 
 
            }else if (p[i] == ' '){
                url.push_back('+'); 
            }else
            {
    
                url.push_back('%'); 
                 
                word=(unsigned char)p[i] >> 4;
                word= word > 9 ? word + 55 : word+ 48;
                url.push_back(word); 
                 
                word=(unsigned char)p[i] % 16;
                word=  word > 9 ? word + 55 : word+ 48;
                url.push_back(word); 
                 
            }

    }
    
    return url;    
}
}
#endif