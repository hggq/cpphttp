// Copyright 2014 Renato Tegon Forti, Antony Polukhin.
// Copyright Antony Polukhin, 2015-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <iostream>
#include <boost/make_shared.hpp>
#include <memory>
// MinGW related workaround
#define BOOST_DLL_FORCE_ALIAS_INSTANTIATION

//[plugcpp_my_plugin_aggregator
#include <boost/dll/alias.hpp> // for BOOST_DLL_ALIAS   
#include <string_view>

#include "Clientpeer.h"
#include "Websockets.hpp"

//g++ -shared -fPIC mywebsockets.cpp -o mywebsockets.so
namespace http {

class mywebsockets : public websockets_api {
    public:
//    unsigned int timeloop_num;
//    unsigned char state;
    unsigned int outcount=0;    
    mywebsockets(std::weak_ptr<http::clientpeer> p) : websockets_api(4,0,p){}
    ~mywebsockets() {
        std::cout<<"~mywebsockets"<<std::endl;
    }
public:
    void onopen(){
        std::cout<<"onopen"<<std::endl;
    }
     void onclose(){
        std::cout<<"onclose"<<std::endl;
    }
     void timeloop() {
       std::shared_ptr<http::clientpeer> peer=weakpeer.lock();
        if(peer){
                std::cout<<"timeloop:"<<std::endl;
                std::string aa="77788sdadfa";
                 std::string outhello;
                            peer->ws->makeWSData(aa.data(), aa.length(), outhello);
                           peer->send(outhello);    

             //   peer->send(aa);
             if(outcount==4){
                 timeloop_num=0;
                 outcount=0;
                 return;
             }
             outcount++;
         }else{
            std::cout<<"peer is die!"<<std::endl;
         }
    }
    void onfiles(std::string_view filename) {
        std::cout<<"--------onfiles:--------"<<filename<<std::endl;
    }
    void onmessage(std::string_view data) {
        std::cout<<"onmessage:"<<data<<std::endl;
    }
    static std::shared_ptr<mywebsockets> create(std::weak_ptr<http::clientpeer> p) {
        return std::make_shared<mywebsockets>(p);
    }
};


BOOST_DLL_ALIAS(
    http::mywebsockets::create, // <-- this function is exported with...
    create_plugin                               // <-- ...this alias name
)

} // namespace my_namespace
//]



