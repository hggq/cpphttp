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

namespace http {

class loopwebsockets : public websockets_api {
    public:
    unsigned int outcount=0;    
    loopwebsockets(std::weak_ptr<http::clientpeer> p) : websockets_api(4,0,p){}
    ~loopwebsockets() {
        std::cout<<"~loopwebsockets"<<std::endl;
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
            std::string aa="looptests";
            std::string outhello;
            peer->ws->makeWSText(aa, outhello);
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
        std::shared_ptr<http::clientpeer> peer=weakpeer.lock();
        if(peer){
                std::string outhello;
                peer->ws->makeWSText(data, outhello);
                peer->send(outhello);   
        }
    }
    static std::shared_ptr<loopwebsockets> create(std::weak_ptr<http::clientpeer> p) {
        return std::make_shared<loopwebsockets>(p);
    }
};
 
} 
 


