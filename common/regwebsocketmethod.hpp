#pragma once
#include "mywebsockets.hpp"
#include "loopwebsockets.hpp"
namespace http {
    void _initwebsocketmethodregto(std::map<std::string,std::function<std::shared_ptr<websockets_api>(std::weak_ptr<clientpeer>)>> &methodcallback){

    methodcallback.emplace("wstest",[](std::weak_ptr<clientpeer> p)->std::shared_ptr<websockets_api>{
        //     auto ws=std::make_shared<http::mywebsockets>(p);
        //          ws->peer=p;
        //  return ws;
        return http::mywebsockets::create(p);
        //return std::make_shared<http::mywebsockets>(p);
     });   
      methodcallback.emplace("looptest",[](std::weak_ptr<clientpeer> p)->std::shared_ptr<websockets_api>{
        //     auto ws=std::make_shared<http::mywebsockets>(p);
        //          ws->peer=p;
        //  return ws;
        return http::loopwebsockets::create(p);
        //return std::make_shared<http::mywebsockets>(p);
     });     
  }

}