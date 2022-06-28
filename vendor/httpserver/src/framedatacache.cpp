#include <string>
#include <string_view>
#include <memory>
#include <list>

#include "framedatacache.h"


namespace http {

std::list<cache_data_t> _cachedata_list;

cache_data_t* getcachedata(unsigned long long cacheid){
  return  &_cachedata_list.front();
}

void setcachedata(unsigned long long cacheid,unsigned int livetime,std::string_view data){

}
void setcachedata(unsigned long long cacheid,unsigned int livetime,std::string && data){

}


}