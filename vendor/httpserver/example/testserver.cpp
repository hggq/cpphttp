
#include "httpserver.hpp"

/*
mac os
g++ testserver.cpp vendor/httpserver/src/request.cpp vendor/httpserver/src/unicode.cpp  -std=c++20 -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Ivendor/httpserver/include -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp vendor/httpserver/src/Clientpeer.cpp vendor/httpserver/src/WebSocketparse.cpp -Iwebsockets vendor/httpserver/src/gzip.cpp vendor/httpserver/src/datetime.cpp vendor/httpserver/src/urlcode.cpp -Icontroller -Icommon vendor/httpserver/src/mysqlpool.cpp vendor/httpserver/src/httpparse.cpp vendor/httpserver/src/httpsocommonapi.cpp vendor/httpserver/src/threadlocalvariable.cpp vendor/httpserver/src/threadpool.cpp
*/
/*
ubuntu20.04
g++-11 -std=c++20 testserver.cpp vendor/httpserver/src/request.cpp vendor/httpserver/src/unicode.cpp  -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Ivendor/httpserver/include -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp vendor/httpserver/src/Clientpeer.cpp vendor/httpserver/src/WebSocketparse.cpp -Iwebsockets vendor/httpserver/src/gzip.cpp vendor/httpserver/src/datetime.cpp vendor/httpserver/src/urlcode.cpp -Icontroller -Icommon vendor/httpserver/src/mysqlpool.cpp vendor/httpserver/src/httpparse.cpp vendor/httpserver/src/httpsocommonapi.cpp vendor/httpserver/src/threadlocalvariable.cpp vendor/httpserver/src/threadpool.cpp -lpthread -I/usr/include/mysql-cppconn-8

*/
int main(int argc,char *argv[]) {
  try {
    if(argc>1){
            serverconfigpath=argv[1];
    }
    httpserver httpmy;
    httpmy.run();

  } catch (std::exception &e) {
    std::printf("Exception: %s\n", e.what());
  }
}
