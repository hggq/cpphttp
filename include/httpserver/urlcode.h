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

namespace HTTP
{ 
//第一次匹配pos位置
int find_indexOf(const  char * source,int slen,const char * str,int len);
//最后部分或全匹配
int find_lastsubpos(const  char * source,int slen,const char * str,int len);

std::vector<std::pair<int,int>>   split_boundary(const char * sstr,int strlen,const char * sp,int len);
std::string url_decode(const char * str,int len);

std::string url_encode(const char * str,int len);
std::string url_rawencode(const char * str,int len);
}
#endif