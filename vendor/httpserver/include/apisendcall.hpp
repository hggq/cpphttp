#ifndef FRAME_APISENDCALL_HPP
#define FRAME_APISENDCALL_HPP

#include "pluginmodule.hpp"
#include <iostream>
#include <map>
#include <string>

namespace http{
   // thread_local clientpeer* _threadclientpeer;
    void send_data(std::string name){
   
   getthreadlocalobj().peer->send(name);
     
}
void send_data(std::string &name){
   
    getthreadlocalobj().peer->send(name);
     
}
void send_data(unsigned int statecode,std::string name){
   
   getthreadlocalobj().peer->send(statecode,name);
     
}
void send_data(unsigned int statecode,std::string &name){
   
    getthreadlocalobj().peer->send(statecode,name);
     
}

void send_file(std::string sendfilename){
     getthreadlocalobj().peer->sendfile(sendfilename);
     // _threadclientpeer->sendfile(sendfilename);
 
}

}

#endif     