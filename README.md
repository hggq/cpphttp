c++ http server framework

c++ http web 框架

支持多域名网站
支持多域名ssl 服务端

支持http1.1协议
支持websocket服务端
支持同步httpclient get post

框架自带ORM 
框架自带线程池

框架自带websocket推送
框架使用asio自带的协程

框架特色是I/O 使用协程池 运行使用线程池

框架支持普通文件gzip


---------------------


Runtime environment
asio boost openssl 

C++ standard request c++20


Running support Mac OS and Linux

mac os request >=big sur  
---------

asio 1.22.1

boost 1.78

mysql 8.0.26

MySQL Connector/C++ 8.0.26


ubuntu 20.04
-------------------
gcc11

asio 1.22.1

msyql 8.0.26

MySQL Connector/C++ 8.0.26

boost 1.71


ubuntu 20.04 必须安装gcc11
默认是g++-11 
在编译时候要把g++ 换成g++-11


config 目录
---------------
config/gcc.conf 文件

里面内容如果是ubuntu20.04 必须改为g++-11 

conifg/server.conf 服务器文件

里面路径改为你存放当前目录路径，不然看不到内容


config/mysqlorm.conf 文件为数据库配置文件
里面改成你的，config 目录有两个数据库sql文件演示



框架使用了配置文件方式运行，自己的程序放在
controller目录
websockets目录
common 目录上注册方法文件


controller/systest.hpp 测试文件
----------------------


```c++
#include "orm.h"
namespace HTTP {

std::string home(HTTP::OBJ_VALUE& obj){
    echo("hello world! this use systest inline callback");
    echo("<p><a href=\"/weibo/header\">header</a></p>");
    echo("<p><a href=\"/weibo/hello\">content</a></p>");

    orm::sms::News  comnews;

    comnews.where("newsid>",63597).order("newsid  DESC").limit(10).fetch();
     if(comnews.size()>0){
         for(auto &bb:comnews){
         echo("<p>"+std::to_string(bb.newsid)+" "+bb.newtitle+" "+bb.adddate+" "+bb.isview+"</p>");
         
       }

    }
    orm::Moduleauth  mbc;
    mbc.where("mid>",0).fetch();
    echo(mbc.getstrCol("name"));
    echo(mbc.getstrCol("name",true));
    auto ww=mbc.getCol<std::string>("name");
          for(auto &bb:ww){
         echo("<p>"+bb+"</p>");
     }
     obj["name"]="test inline callback";
    viewshow("about/header");
    //send_file("viewmodule.html");
   return "";
}

}
```



websockets/loopwebsockets.hpp websocket测试文件

--------------------------

```c++
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
    loopwebsockets(std::weak_ptr<HTTP::clientpeer> p) : websockets_api(4,0,p){}
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
       std::shared_ptr<HTTP::clientpeer> peer=weakpeer.lock();
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
        std::shared_ptr<HTTP::clientpeer> peer=weakpeer.lock();
        if(peer){
                std::string outhello;
                peer->ws->makeWSText(data, outhello);
                peer->send(outhello);   
        }
    }
    static std::shared_ptr<loopwebsockets> create(std::weak_ptr<HTTP::clientpeer> p) {
        return std::make_shared<loopwebsockets>(p);
    }
};
 
} 
```


LICENSE
-----------------

MIT License
