#ifndef HTTP_VISITLOG_H
#define HTTP_VISITLOG_H

#include <atomic>
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

namespace HTTP
{ 

    class VISIT_LOG{
        public:
            VISIT_LOG();
            save_log();
        public:
               VISIT_LOG& operator<<(std::string &&a);
                 VISIT_LOG& operator<<(std::string &a);
                 VISIT_LOG& operator<<(std::string_view a);
                VISIT_LOG& operator<<(char const *a); 
                VISIT_LOG& operator<<(unsigned char a);     
       std::string logcontent;         
       std::string logpath;
       bool  isfull=false;
        std::atomic_flag lock_edit = ATOMIC_FLAG_INIT;
    };

}
#endif