#ifndef PROJECT_CLIENTPEER_H
#define PROJECT_CLIENTPEER_H

#include <asio.hpp>
#include <asio/ssl.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <list>
#include <map>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <memory>
#include <iostream>
#include <zlib.h>
#include <string_view>
#include <future>

#include "datetime.h"
#include "md5.hpp"
#include "gzip.h"
#include "mime.hpp"
#include "unicode.h"
#include "cookie.hpp"
#include "urlcode.h"
#include "request.h"
#include "WebSocketparse.h"
#include "Websockets.hpp"
#include "httpparse.h"


namespace http { 
 namespace fs = std::filesystem; 
class clientpeer {
public:
  clientpeer(){}
  ~clientpeer() { std::cout<<"~clientpeer"<<std::endl; }
  void sendfile(std::string);
  void send(std::string &data);
  void send(const char *data,int sendsize);
  void send(unsigned int statecode,std::string &str);
  void send( int statecode,std::string &&);
  void send( int statecode);
  void sendheader(unsigned int ,unsigned long long );
  void addheader(std::string_view);
  void addheader(const char *);
  void addheader(std::string,std::string);
  std::string makeetag();
  std::string writetime_tostring(fs::file_time_type const& ftime);
  void getfileinfo();
  void getsitepath();
   void sendfileto();
    void displaydirectory(std::string configpath);
    std::string getremoteip();
    unsigned short getremoteport();

    std::string getlocalip();
    unsigned short getlocalport();

       clientpeer& operator<<(http::OBJ_VALUE &a);
             clientpeer& operator<<(std::string &&a);
                 clientpeer& operator<<(std::string &a);
                 clientpeer& operator<<(std::string_view a);
                clientpeer& operator<<(char const *a);
                clientpeer& operator<<(float a);
                clientpeer& operator<<(long long a);
                 clientpeer& operator<<(int a);
                 clientpeer& operator<<(short a);
                  clientpeer& operator<<(unsigned short a);
                clientpeer& operator<<(unsigned long long a);
                 clientpeer& operator<<(unsigned int a);
                clientpeer& operator<<(double a);
                template<typename T>
                clientpeer& operator<<(T &a);

  void parse_session();
  void save_session();
  void clear_session();
  void addcookie(std::string,std::string,unsigned long,std::string,std::string,bool,bool);
  void addcookie(std::string,std::string,unsigned long,std::string,std::string);
  void addcookie(std::string,std::string,unsigned long);
  void addcookie(std::string,std::string,int,std::string,std::string);
  void addcookie(std::string,std::string,int);
  void cookietoheader();
  clientpeer& getpeer();
public:
  std::list<asio::ssl::stream<asio::ip::tcp::socket>> https_socket;
  std::list<asio::ip::tcp::socket> http_socket;
  std::list<std::string> headerlists;
  std::mutex writemutex;
  unsigned char httptype=0;
  bool isssl = false;
  bool issendheader=false;
  int  readnum=0;
  unsigned char _data[2051]={0x00};
  std::unique_ptr<WebSocketparse> ws;
  std::shared_ptr<websockets_api> websocket;
  //HTTP::httpparse *header;
  std::unique_ptr<http::httpparse> header;

  std::map<std::string,std::map<std::string,std::string>> *globalconfig;

  bool keeplive=true;
  bool isusehtmlcache=false;
  unsigned long long chachefiletime=10;
  std::string _output;
  http::OBJ_VALUE vobj;
  http::OBJ_VALUE session;
  unsigned long long  sessionfile_time=0;
  Cookie cookie;
  std::list<std::future<int>> loopresults;
  std::promise<int> looprunpromise;
  
  std::string sitepath;
  std::string senddatastring;
             std::string sendfilename;
             std::string filenamebase;
             std::string fileexttype;

             unsigned char pathtype;//file path index
             struct stat fileinfo;
             std::string pathinfo;
             std::string etag;
             std::string mimetype;
             time_t systimeid;
             tm* lsystemTime;
             std::ostringstream tempchache;
             unsigned char keeplivemax=100;
             unsigned long long modifytime=0;
             unsigned long long filesize=0;

  std::string remote_ip;
  unsigned short remote_port;   

  std::string local_ip;
  unsigned short local_port;        
};
}
#endif 