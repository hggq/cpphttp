#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <functional>
#include <list>
#include <utility>
#include <string>
#include <string_view>
#include <thread>
#include <chrono>

#include "visitlog.h"

VISIT_LOG::VISIT_LOG(){}
void VISIT_LOG::save_log(){
    
}
VISIT_LOG& VISIT_LOG::operator<<(std::string &&a){
    logcontent.append(a);
    return *this;
} 
VISIT_LOG& VISIT_LOG::operator<<(std::string &a){
    logcontent.append(a);
    return *this;
}
VISIT_LOG& VISIT_LOG::operator<<(std::string_view a){
    logcontent.append(a);
    return *this;
}
VISIT_LOG& VISIT_LOG::operator<<(char const *a){
    logcontent.append(a);
    return *this;
}
VISIT_LOG& VISIT_LOG::operator<<(unsigned char a){
    if(a=='\n'){
       logcontent.push_back('\n'); 
       save_log(); 
    }
    logcontent.append(std::to_string(a));
    return *this;
}