
#include <string>
#include <string_view>
#include <memory>
#include "request.h"
#include <mysqlx/xdevapi.h>
#include "Clientpeer.h"
#include "httpsocommonapi.h" 
 namespace HTTP { 
  // thread_local HTTP::OBJ_VALUE clientapi::vobj=NULL;    
   //  thread_local std::string clientapi::_output{};    
 //thread_local std::string clientapi::output={}; 
//  thread_local  std::string __output;
 clientapi* clientapi::singleton =clientapi::instance();


 //thread_local std::weak_ptr<clientpeer> clientapi::peer =std::nullptr_t;
        
 }