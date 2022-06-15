#pragma once
#ifndef FRAME_THREADLOCALCONFIG_H
#define FRAME_THREADLOCALCONFIG_H
#include <string>
#include <map>
#include "request.h"
#include "Clientpeer.h"
#include "Websockets_api.h"

namespace http 
{
   
    class threadlocalconfig{

        public:
            std::string output;
            http::OBJ_VALUE vobj;
            std::string _outputtemp;

            std::string hostcontrolsopath;
            std::string hostviewsopath;

            http::clientpeer* peer;
            

    };

}
#endif 