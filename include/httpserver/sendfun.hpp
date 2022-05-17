#ifndef FRAME_APISENDCALL_HPP
#define FRAME_APISENDCALL_HPP

#include "common_functions.h"
#include "Clientpeer.h"
#include <iostream>
#include <map>
#include <string>

namespace HTTP{
    void send_data(std::string name){
   
   _threadclientpeer->send(name);
     
}
void send_data(std::string &name){
   
    _threadclientpeer->send(name);
     
}
void send_data(unsigned int statecode,std::string name){
   
   _threadclientpeer->send(statecode,name);
     
}
void send_data(unsigned int statecode,std::string &name){
   
    _threadclientpeer->send(statecode,name);
     
}

void send_file(std::string sendfilename){

      _threadclientpeer->sendfile(sendfilename);
 
}

}

#endif     