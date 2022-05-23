
#include "httpserver.hpp"

/*
mac os
 g++ testserver.cpp src/httpserver/request.cpp src/httpserver/unicode.cpp  -std=c++20 -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Iinclude/httpserver -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp src/httpserver/Clientpeer.cpp src/httpserver/WebSocketparse.cpp -Iwebsockets src/httpserver/gzip.cpp src/httpserver/datetime.cpp src/httpserver/urlcode.cpp -Icontroller -Icommon src/httpserver/mysqlpool.cpp src/httpserver/httpparse.cpp src/httpserver/httpsocommonapi.cpp
*/
/*
ubuntu20.04
g++-11 -std=c++20 testserver.cpp src/httpserver/request.cpp src/httpserver/unicode.cpp   -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Iinclude/httpserver -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp src/httpserver/Clientpeer.cpp src/httpserver/WebSocketparse.cpp -Iwebsockets src/httpserver/gzip.cpp src/httpserver/datetime.cpp src/httpserver/urlcode.cpp -Icontroller -Icommon src/httpserver/mysqlpool.cpp src/httpserver/httpparse.cpp src/httpserver/httpsocommonapi.cpp -lpthread -I/usr/include/mysql-cppconn-8
*/
int main() {
  try {
    
    httpserver httpmy;
    httpmy.run();

  } catch (std::exception &e) {
    std::printf("Exception: %s\n", e.what());
  }
}
