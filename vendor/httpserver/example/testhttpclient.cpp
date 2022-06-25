
#include <string.h>
#include <sstream>
#include "request.h"
#include "httpclient.h"
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <asio/write.hpp>
#include <asio/version.hpp>
#include <asio/ssl.hpp>
#include <cstdio>
#include <string_view>
#include "zlib.h"
#include "gzip.h"
#include "urlcode.h"

using asio::ip::tcp;
using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;
namespace this_coro = asio::this_coro;

#if defined(ASIO_ENABLE_HANDLER_TRACKING)
# define use_awaitable \
  asio::use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif

//g++ testhttpclient.cpp -std=c++20  -Iinclude/httpserver src/httpserver/request.cpp src/httpserver/httpclient.cpp -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lz src/httpserver/gzip.cpp src/httpserver/urlcode.cpp

int main()
{

  http::client a;
  http::OBJ_VALUE parameter;
  parameter["name"]="老师短发";
  std::cout<<"asio version:"<<ASIO_VERSION<<std::endl;
  std::cout<<"name:"<<parameter["name"].size()<<std::endl;
  // // parameter["name"]=parameter["name"]+0x11;
  // {
  //   std::string *p=parameter["name"].ptr_string();
  //   p->append("aaa");
  //   std::cout<<"pp:"<<*p<<std::endl;
  //   std::string &ptr=parameter["name"].ref();

  //   ptr.append("bbb");
  // }


    parameter["num"]=345;

    //a.getjson("http://www.vhost1.com/mm.zip",parameter);
    a.getjson("http://www.869869.com:4444/assets/brand/bootstrap-logo.svg",parameter);
    //a.getjson("http://www.vhost1.com/info.php",parameter);
    //a.get("https://www.vhost1.com/6660543.jpg",parameter);
    //a.data=parameter;
    //a.addfile("test","sendjson.json");//
    // a.addfile("test2","sharetool.svg");
    //a.posttype("multipart/form-data");
    //a.addheader("Content-Type","application/json");
    //a.header["Content-Type"]="application/json";
    //a.header["Accept-Encoding"]="gzip";
    //a.header["Content-Type"]="application/octet-stream";
    //a.get("http://www.vhost2.com/info.php?aa=33&bb=44",parameter);
    //a.postjson("http://www.vhosT2.com/info.php?wwwqqq=33&bss=4444");
    //a.addfile("test2","/Users/hzq/cpp/NotoColorEmoji.ttf");
    //a.header["Content-Type"]="application/json";
    //a.datatype("json");
    //a.post("http://www.vhost1.com/info.php");
    //a.posttype("multipart/form-data");
    a.timeout(30);
    a.send();
    if(a.state.code==200){
      std::cout<<"get ok"<<std::endl;
    }
    a.save("./upload/");
    std::cout<<"========"<<a.state.code<<" "<<a.state.codemessage<<std::endl;
    std::cout<<"==============content==============\r\n"<<a.state.content<<std::endl;
    std::cout<<(std::string)a.state.json["liminghui"]<<std::endl;

    for(auto &bb:a.state.cookie){
      std::cout<<bb.first<<":"<<bb.second<<std::endl;
    }



}