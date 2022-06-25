#pragma once
#ifndef FRAME_SERVERCONFIG_H
#define FRAME_SERVERCONFIG_H
#include <string>
#include <map>
#include "request.h"
#include "Clientpeer.h"
#include "Websockets_api.h"

namespace http 
{
   
    class serverconfig{

        public:
            std::string serverpath;
            std::string wwwpath;
            std::map<std::string,std::function<std::shared_ptr<websockets_api>(std::weak_ptr<clientpeer>)>> websocketmethodcallback;
            std::map<std::string,std::function<std::string(http::clientpeer &)>>  methodcallback;
            std::string configpath;
            std::map<std::string,std::map<std::string,std::string>>  serverconfig; 
            bool reloadmysql=true;
            bool reloadserverconfig=true;
            unsigned int siteusehtmlchachetime=0;
            bool siteusehtmlchache=false;

    };

}
#endif 