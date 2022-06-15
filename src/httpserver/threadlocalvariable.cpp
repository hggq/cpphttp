#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"

#include "threadlocalconfig.h"
#include "serverconfig.h"
#include "threadlocalvariable.h"
namespace http {

    threadlocalconfig& getthreadlocalobj(){
               thread_local static threadlocalconfig instance;
    return instance;
    }
    serverconfig& getserversysconfig(){
          
       static  serverconfig instance;
         return instance;
 
    }
}