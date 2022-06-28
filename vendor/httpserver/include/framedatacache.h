#ifndef HTTP_FRAMEDATACACHE_H
#define HTTP_FRAMEDATACACHE_H
#include <string>
#include <string_view>
#include <memory>
#include <list>


namespace http {

struct cache_data_t{
    unsigned int length;
    unsigned int livetime;
    unsigned char *data;
};



cache_data_t* getcachedata(unsigned long long);

void setcachedata(unsigned long long,unsigned int,std::string_view);
void setcachedata(unsigned long long,unsigned int,std::string &&);

}
#endif