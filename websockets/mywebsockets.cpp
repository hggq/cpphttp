#include "http.hpp"
#include "orm.h"
 
#include "Clientpeer.h"
#include "Websockets.hpp"
/*
--compiler--begin--
--compiler--end--
*/
//g++ -shared -fPIC mywebsockets.cpp -o mywebsockets.so
//g++   mywebsockets.cpp -o ../module/websockets/mywebsockets.so -shared -fPIC -std=c++20 -I../include ../src/request.cpp ../src/httpclient.cpp    -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem -lz -lmysqlcppconn8  -I../models/include ../models/Modblocks.cpp ../models/User.cpp ../models/Company.cpp ../models/Applyproduct.cpp ../models/Email.cpp -I../models ../models/sms/News.cpp ../src/Clientpeer.cpp ../src/WebSocket.cpp
namespace http {

class mywebsockets : public websockets_api {
    public:
//    unsigned int timeloop_num;
//    unsigned char state;
    unsigned int outcount=0;    
    mywebsockets(std::weak_ptr<clientpeer> p) : websockets_api(4,0,p){}
    ~mywebsockets() {

        std::cout<<"~mywebsockets"<<std::endl;
    }
public:
    void onopen(){
        std::cout<<"onopen"<<std::endl;
    }
     void onclose(){
        std::cout<<"onopen"<<std::endl;
    }
     void timeloop() {
       std::shared_ptr<clientpeer> peer=weakpeer.lock();
         if(peer){
                std::cout<<"timeloop:"<<std::endl;
                std::string aa="777888asdafasfasfasdaadfasdfasfasfasfasfasfaslja;lkj;lkj asdfasdfasfasfafa asdadfasflk asdafasf asafa";
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
    static std::shared_ptr<mywebsockets> create(std::weak_ptr<clientpeer> p) {
        return std::make_shared<mywebsockets>(p);
    }
};


BOOST_DLL_ALIAS(
    http::mywebsockets::create, // <-- this function is exported with...
    create_websocket                               // <-- ...this alias name
)

} // namespace my_namespace
//]



