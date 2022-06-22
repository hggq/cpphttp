#include <asio.hpp>
#include <asio/ssl.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <memory>

#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <sys/types.h> 
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/fcntl.h>

#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

#include <array>
#include <iostream>
#include <ctime>
#include <map>
#include <sys/time.h>
#include <map>
#include <thread>
#include <mutex>
#include <filesystem>
#include <future>
#include <functional>
#include <stdexcept>
#include <mysqlx/xdevapi.h>
#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include <zlib.h>
#include "datetime.h"
#include "md5.hpp"
#include "gzip.h"
#include "mime.hpp"
#include "unicode.h"
#include "cookie.hpp"
#include "multicertificate.hpp"
#include "urlcode.h"
#include "request.h"
#include "httpparse.h"
#include "pluginmodule.hpp"
#include "loadconfig.hpp"
#include "Clientpeer.h"

#include "apisendcall.hpp"
#include "WebSocketparse.h"

#include "threadpool.h"
#include "reghttpmethod.hpp"
#include "Websockets.hpp"
#include "regwebsocketmethod.hpp"
#include "httpsocommonapi.h" 

using asio::awaitable;
using asio::co_spawn;
using asio::detached;
using asio::use_awaitable;
using asio::ip::tcp;
namespace this_coro = asio::this_coro;
using namespace http;
namespace fs = std::filesystem;

#if defined(ASIO_ENABLE_HANDLER_TRACKING)
#define use_awaitable                                                          \
  asio::use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif


// std::map<std::string,SSL_CTX*> g_ctxMap;
// std::map<std::string,std::function<std::shared_ptr<websockets_api>(std::weak_ptr<clientpeer>)>> websocketmethodcallback;
// std::map<std::string,std::function<std::string(http::clientpeer &)>>  methodcallback;
 std::string serverconfigpath;
// std::map<std::string,std::map<std::string,std::string>>  _serverconfig;

// bool _siteusehtmlchache;
// unsigned int _siteusehtmlchachetime;


  std::string get_password(){
      return "sslpem123456";
  }
  long serverNameCallback(SSL *ssl, int *ad, void *arg) 
  {
    if (ssl == NULL)
        return SSL_TLSEXT_ERR_NOACK;
   
    const char* servername = SSL_get_servername(ssl, TLSEXT_NAMETYPE_host_name);
    SSL_CTX* ctx = NULL;    

     if (servername && strlen(servername) > 0)
    {       
        ctxmar* ctxptr = ctxmar::instance();
        ctx=ctxptr->getctx(servername);
              
    }else{
        ctxmar* ctxptr = ctxmar::instance();
        ctx=ctxptr->getdefaultctx();
    }

    SSL_set_SSL_CTX(ssl, ctx);

    SSL_set_verify(ssl, SSL_CTX_get_verify_mode(ctx),                             

    SSL_CTX_get_verify_callback(ctx));

    SSL_set_verify_depth(ssl, SSL_CTX_get_verify_depth(ctx));
     SSL_clear_options(ssl, 0xFFFFFFFFL);
    SSL_set_options(ssl, SSL_CTX_get_options(ctx));
 
    return SSL_TLSEXT_ERR_OK; 

}

void loadmysqlconfig(){

        try{
         std::string mysqlconnect="mysqlx://root:123456@127.0.0.1/mysql";   
         std::string mysqlconnectselect="mysqlx://root:123456@127.0.0.1/mysql";   
         std::string rmstag;
         std::hash<std::string> hash_fn;
         size_t dcon;
         rmstag=serverconfigpath;
         if(rmstag.size()>0&&rmstag.back()!='/'){
             rmstag.push_back('/');
         }
         rmstag.append("mysqlorm.conf");
         std::vector<http::mysqlconnect_t> myconfig=http::getmysqlconfig(rmstag);
         std::map<std::string,std::vector<std::string>>  mysqldblinkgroupjion;
         rmstag.clear();
         //转为rmstag分组
         if(myconfig.size()>0){
             for(int li=0;li<myconfig.size();li++){
                rmstag=myconfig[li].port;
                if(rmstag.size()<3){
                        rmstag="33060";
                }
                mysqlconnect="mysqlx://"+myconfig[li].user+":"+myconfig[li].password+"@"+myconfig[li].host+":"+rmstag+"/"+myconfig[li].dbname;
                rmstag=myconfig[li].spname;
                mysqldblinkgroupjion[rmstag].emplace_back(mysqlconnect);
              }
         }
         for(auto iterl=mysqldblinkgroupjion.begin();iterl!=mysqldblinkgroupjion.end();iterl++){
                
                dcon=hash_fn(iterl->first);
                if(iterl->second.size()==1){
                    http::mysqllinkpool db(iterl->second[0],iterl->second[0]);
                    http::mysqldbpoolglobal.insert({dcon,std::move(db)}); 
                }else if(iterl->second.size()>1){
                    http::mysqllinkpool db(iterl->second[0],iterl->second[1]);
                    http::mysqldbpoolglobal.insert({dcon,std::move(db)}); 
                }
         }
                   
     } catch (const mysqlx::Error &err)
    {
         std::cout <<"ERROR: " << err << ::std::endl;
    
    }

}
void loadserverglobalconfig(){
 
    std::string configfile;
    serverconfig&  sysconfigpath=  getserversysconfig();
    configfile=sysconfigpath.configpath;
    if(configfile.size()>0&&configfile.back()!='/'){
        configfile.push_back('/');
    }
    configfile.append("server.conf");
    sysconfigpath.serverconfig=http::loadserversconfig(configfile);
 
   http::siteviewpath=sysconfigpath.serverconfig["default"]["viewsopath"];
   http::sitecontrolpath=sysconfigpath.serverconfig["default"]["controlsopath"];
   if(sysconfigpath.serverconfig["default"]["index"].empty()){
        sysconfigpath.serverconfig["default"]["index"]="index.html";
   }
   if(sysconfigpath.serverconfig["default"]["usehtmlcache"].empty()){
        sysconfigpath.siteusehtmlchache=false;
   }else{
       sysconfigpath.siteusehtmlchache=true;
   }
   if(sysconfigpath.serverconfig["default"]["usehtmlcachetime"].empty()){
        sysconfigpath.siteusehtmlchachetime=0;
   }else{
       sysconfigpath.siteusehtmlchachetime=0;
       for(int i=0;i<sysconfigpath.serverconfig["default"]["usehtmlcachetime"].size();i++){
                     if(sysconfigpath.serverconfig["default"]["usehtmlcachetime"][i]>0x2F&&sysconfigpath.serverconfig["default"]["usehtmlcachetime"][i]<0x3A){
                         sysconfigpath.siteusehtmlchachetime=sysconfigpath.siteusehtmlchachetime*10+(sysconfigpath.serverconfig["default"]["usehtmlcachetime"][i]-'0');
                     }   
       }
       
   }
 
}
//////////////////////////////////////////


class httpserver {
public:
  httpserver() {}
  ~httpserver() {}
  void websocket_loop(int myid) {

        using namespace std::chrono;
        using dsec = duration<double>;
        auto invFpsLimit = duration_cast<system_clock::duration>(dsec{1./0.5});
        auto m_BeginFrame = system_clock::now();
        auto m_EndFrame = m_BeginFrame + invFpsLimit;
        unsigned frame_count_per_second = 0;
        auto prev_time_in_seconds = time_point_cast<seconds>(m_BeginFrame);
        unsigned int fps=0;
        while (true)
        {
           
            auto time_in_seconds = time_point_cast<seconds>(system_clock::now());
            ++frame_count_per_second;
            if (time_in_seconds > prev_time_in_seconds)
            {
                
                frame_count_per_second = 0;
                prev_time_in_seconds = time_in_seconds;

                ++fps;

                 for(auto iter=websockettasks.begin();iter!=websockettasks.end();){
                      std::shared_ptr<clientpeer> peer=iter->lock();
                      try{

                          if(peer){
                              if(peer->websocket->timeloop_num>0&&fps%peer->websocket->timeloop_num==0){
                                  peer->websocket->timeloop();
                              }

                              if(peer->websocket->timeloop_num==0)
                              {   
                                  peer.reset();
                                  websockettasks.erase(iter++);
                              }else{
                                ++iter;
                              }
                          
                          }else{
                                  websockettasks.erase(iter++);   
                          }

                      } catch (std::exception &e) {
                         websockettasks.erase(iter++);   
                      }
                      
                 }
                 if(fps>31536000){
                      fps=1;
                 }
            }
            std::this_thread::sleep_until(m_EndFrame);
            m_BeginFrame = m_EndFrame;
            m_EndFrame = m_BeginFrame + invFpsLimit;
        }
  }

  void http_loop(int myid) {
    for (;;) {
   
      std::unique_lock<std::mutex> lock(this->headqueue_mutex);
      this->headqueue_condition.wait(lock,
                                     [this] { return !this->tasks.empty(); });

      if (this->tasks.empty())
        continue;

      auto task = std::move(this->tasks.front());
      this->tasks.pop();
      lock.unlock();
 
      co_spawn(this->io_context, clientpeerfun(std::move(task)), detached);
    }
  }

  awaitable<void> clientpeerfun(std::shared_ptr<clientpeer> peer) {
    //如果是websocket 保留在这里
    //如果是http移动到线程池
    try {
 
    unsigned int readnum=0;    
    peer->header=std::make_unique<http::httpparse>();
    peer->getremoteip();
    peer->getremoteport();
    peer->getlocalip();
    peer->getlocalport();
    serverconfig&  sysconfigpath=  getserversysconfig();
    for (;;) {
        peer->header->clear();
        for(;;){
            memset(peer->_data, 0x00, 2048);
            if(peer->isssl){
                readnum= co_await peer->https_socket.front().async_read_some(
                asio::buffer(peer->_data), use_awaitable);
            }else{
              readnum= co_await peer->http_socket.front().async_read_some(
                asio::buffer(peer->_data), use_awaitable);
            }          
            peer->header->readoffset=0;
            if(readnum>0){
                peer->header->process(peer->_data,readnum);
            }
          
            if(readnum==0||peer->header->getfinish()){  
                break;
            }else if(peer->header->error>0){
                peer->header->clear();
            } 
        }
        if(peer->header->cookie.check("CPPSESSID")){
            peer->parse_session();
        }
        {
            std::string  temp=http::date("%Y-%m-%d %X");
            temp.push_back(0x09);
            temp.append(peer->remote_ip);
            temp.push_back(0x09);
            temp.append(peer->header->host);
            temp.append(peer->header->urlpath);
            temp.push_back('\n');
            std::unique_lock<std::mutex> lock(log_mutex);
            loglist.emplace_back(temp);
            lock.unlock();
        }
        

        if(peer->header->state.websocket){    
                peer->httptype=1;  
               
                peer->ws=std::make_unique<WebSocketparse>();
                peer->ws->setWebsocketkey(peer->header->websocket.key);
                std::string resp = peer->ws->respondHandshake();

                peer->send(resp);                    
                peer->ws->isopen = true;

                if(peer->header->pathinfo.size()==0){
                      co_return;
                }
                auto wsiter= sysconfigpath.websocketmethodcallback.find(peer->header->pathinfo[0]);   
                if(wsiter==sysconfigpath.websocketmethodcallback.end()){
                    co_return;
                }
                auto myclientwsplugin=sysconfigpath.websocketmethodcallback[peer->header->pathinfo[0]];
                peer->websocket=myclientwsplugin(peer);
                peer->websocket->onopen();
                if(peer->websocket->timeloop_num>0){
                  websockettasks.emplace_back(peer);
                }
                   
                   for(;;) {
                  
                    for(;;) {
 
                       memset(peer->_data, 0x00, 2048);
                     
                      if(peer->isssl){
                          readnum= co_await peer->https_socket.front().async_read_some(
                          asio::buffer(peer->_data,2048), use_awaitable);
                      }else{
                        readnum= co_await peer->http_socket.front().async_read_some(
                          asio::buffer(peer->_data,2048), use_awaitable);
                      }
                      
                      if(peer->ws->contentlength==0){
                            peer->ws->getprocssdata(peer->_data, readnum);
                      }else{
                            peer->ws->parsedata(peer->_data, readnum);
                      }
                      if(peer->ws->isfinish){

                           if(peer->ws->opcode<0x08&&peer->ws->opcode>0x00) {
                              peer->ws->closefile(); 
                              clientrunpool.addclient(peer);
                          }else if (peer->ws->opcode == 0x08) {
                             
                              peer->ws->isopen = false;
                              peer->websocket->onclose();
                              co_return;
                          }else if(peer->ws->opcode== 0x09) {
                              std::string outhello;
                              outhello=peer->ws->makePong();
                              peer->send(outhello);     
                          }
                           
                          break;
                      }

                    }
                    
                  }
                  co_return;

        }else{
           peer->httptype=0;  
           std::promise<int> p;
           std::future<int> f{p.get_future()};
           peer->loopresults.emplace_back(std::move(f));
           peer->looprunpromise=std::move(p);
           clientrunpool.addclient(peer);
           
        }
 
        total_count++;

        try{
         int isget = peer->loopresults.front().get();
         peer->loopresults.pop_front();
        }catch(...) {
          break;
        }
        

        if(peer->keeplivemax==0){
            break;
        }
        if(peer->header->state.keeplive&&peer->keeplive){
          
        }else{
          break;
        }

        peer->cookie.clear();
        peer->headerlists.clear();
      }
    } catch (std::exception &e) {
      std::printf("clientpeer : %s\n", e.what());
 
    }
  }

  awaitable<void> listener() {
    auto executor = co_await this_coro::executor;
    asio::error_code ec;
    serverconfig&  sysconfigpath=  getserversysconfig();

    unsigned short portnum=80;
    std::string filepath=sysconfigpath.serverconfig["default"]["httpport"];

    if(filepath.size()>1){
          portnum=0;
          for(int qi=0;qi<filepath.size();qi++){
                if(filepath[qi]<0x3A&&filepath[qi]>0x2F){
                                portnum= portnum*10+(filepath[qi]-0x30);
                }
          }
          if(portnum==0){
              portnum=80;
          }
    }

    tcp::acceptor acceptor(executor);

    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), portnum);
    acceptor.open(endpoint.protocol());

    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));

#if (defined(unix) || defined(__unix) || defined(__unix__) ||                  \
     defined(__APPLE__)) &&                                                    \
    !defined(__CYGWIN__)

    typedef asio::detail::socket_option::boolean<SOL_SOCKET, SO_REUSEPORT>
        reuse_port;
    acceptor.set_option(reuse_port(true));

#endif

    acceptor.bind(endpoint, ec);
    acceptor.listen(asio::socket_base::max_connections, ec);
    if (ec) {

      perror("acceptor listen http error");
      exit(1);
    }
  
    for (;;) {
      //clientpeer peer;
      std::shared_ptr<clientpeer> clientp= std::make_shared<clientpeer>();
      clientp->globalconfig=&sysconfigpath.serverconfig;
      if(total_count>0xFFFFFF00){
          total_count=0;
      }
      tcp::socket socket = co_await acceptor.async_accept(use_awaitable);
 
      clientp->http_socket.emplace_back(std::move(socket));
      clientp->isssl=false;
      std::unique_lock<std::mutex> lock(headqueue_mutex);
      tasks.emplace(clientp);
      lock.unlock();
      headqueue_condition.notify_one();
    }
  }

  awaitable<void> listeners() {
    auto executor = co_await this_coro::executor;
   // tcp::acceptor acceptor(executor, {tcp::v4(), 443});
    serverconfig&  sysconfigpath=  getserversysconfig();

    unsigned short portnum=443;
    std::string filepath=sysconfigpath.serverconfig["default"]["httpsport"];

    if(filepath.size()>1){
          portnum=0;
          for(int qi=0;qi<filepath.size();qi++){
                if(filepath[qi]<0x3A&&filepath[qi]>0x2F){
                                portnum= portnum*10+(filepath[qi]-0x30);
                }
          }
          if(portnum==0){
              portnum=443;
          }
    }

    asio::error_code ec_error;
    tcp::acceptor acceptor(executor);
    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(),portnum);
    acceptor.open(endpoint.protocol());

    acceptor.set_option(asio::ip::tcp::acceptor::reuse_address(true));

    #if (defined(unix) || defined(__unix) || defined(__unix__) || defined(__APPLE__)) && !defined(__CYGWIN__)

        typedef asio::detail::socket_option::boolean<SOL_SOCKET, SO_REUSEPORT> reuse_port;
        acceptor.set_option(reuse_port(true));

    #endif

    acceptor.bind(endpoint, ec_error);
    acceptor.listen(asio::socket_base::max_connections, ec_error);
    if(ec_error){
        perror("acceptor listen https error");
        exit(1);
    }


    filepath=sysconfigpath.configpath;
    filepath.append("server.pem");

    asio::ssl::context context_(asio::ssl::context::sslv23);
    context_.set_options(
                        asio::ssl::context::default_workarounds
                        | asio::ssl::context::no_sslv2
                        | asio::ssl::context::single_dh_use);
    context_.set_password_callback(std::bind(get_password));
    context_.use_certificate_chain_file(filepath.c_str());
    filepath.erase(filepath.end()-4,filepath.end());

    filepath.append(".key");

    context_.use_private_key_file(filepath.c_str(), asio::ssl::context::pem);
    filepath=serverconfigpath;
    filepath.append("dh4096.pem");
    context_.use_tmp_dh_file(filepath.c_str());
    SSL_CTX_set_tlsext_servername_callback(context_.native_handle(), serverNameCallback);
    
    
    for (;;) {
 
      std::shared_ptr<clientpeer> clientp= std::make_shared<clientpeer>();
      clientp->globalconfig=&sysconfigpath.serverconfig;
      if(total_count>0xFFFFFF00){
          total_count=0;
      }
      tcp::socket socket = co_await acceptor.async_accept(use_awaitable);

       asio::ssl::stream<asio::ip::tcp::socket> sslsocket(std::move(socket), context_);
                
      sslsocket.handshake(asio::ssl::stream_base::server,ec_error);
      if(ec_error){
          continue;
      }

      clientp->https_socket.emplace_back(std::move(sslsocket));
      clientp->isssl=true;
      std::unique_lock<std::mutex> lock(headqueue_mutex);
      tasks.emplace(clientp);
      lock.unlock();
      headqueue_condition.notify_one();
    }
  }

  void http_run() {

    co_spawn(this->io_context, listener(), detached);
    this->io_context.run();
  }
  void https_run() {

    co_spawn(this->io_context, listeners(), detached);
    this->io_context.run();
  }

  void httpwatch(){
      serverconfig&  sysconfigpath=  getserversysconfig();
      
     if(serverconfigpath.empty()){

      std::string currentpath="/etc/chttp";
      fs::path cpath=currentpath; 
      if (fs::is_directory(cpath))
      {
          currentpath=currentpath+"/server.conf";
          cpath=currentpath;
          if(fs::is_regular_file(cpath))
          {
                serverconfigpath="/etc/chttp/";
          }
      }
      if(serverconfigpath.empty()){
          cpath=fs::current_path();
          currentpath=cpath.string();
          currentpath=currentpath+"/config";
          cpath=currentpath; 
          if (fs::is_directory(cpath))
          {
              serverconfigpath=currentpath+"/"; 
              currentpath=currentpath+"/server.conf";
              cpath=currentpath;
              if(fs::is_regular_file(cpath))
              {
                   
              }else{
                serverconfigpath.clear();
              }
          }
      }
     
    }
    
    if(serverconfigpath.size()>0&&serverconfigpath.back()!='/'){
       serverconfigpath.push_back('/');
    }
    sysconfigpath.configpath=serverconfigpath;

    bool reloadmysql=true; 
    bool reloadserverconfig=true; 
    bool alonehttpserver=true; 
    unsigned int  updatetimetemp=0;

    _initwebsocketmethodregto(sysconfigpath.websocketmethodcallback);
    _inithttpmethodregto(sysconfigpath.methodcallback);

    ctxmar* ctxptr = ctxmar::instance();
     ctxptr->setconfigpath(sysconfigpath.configpath);
     clientapi* pn =clientapi::instance();
 
        pn->api_loadview=loadview;
        pn->api_loadviewnotcall=loadviewnotcall;
        pn->api_loadviewfetchnotcall=loadviewfetchnotcall;
        pn->api_loadviewobjcall=loadviewobjcall;

        pn->api_loadcontrol=loadcontrol;
        pn->api_sendjsoncall=sendjsoncall;
        pn->api_modulesenddata=modulesenddata;
        pn->api_echoassignand=echoassignand; 

        pn->api_echoassign=echoassign;
        pn->api_echo_flush=echo_flush; 
        pn->api_send_file=send_file;  

        pn->api_mysqlselect=domysqlexecute;
        pn->api_mysqledit=domysqleditexecute;

        pn->api_mysqlcommit=domysqlcommit;  
        pn->getpeer=getpeer;  
        pn->getoutput=getoutput;  

     std::string currentpath="/tmp/httpexpid.locksocket";
     asio::io_context io_c;
     asio::local::stream_protocol::socket s(io_c);
    try{
      s.connect(asio::local::stream_protocol::endpoint(currentpath.c_str()));
    }catch (std::exception& e){
      alonehttpserver=false;
    }
     unsigned char buf[6];
     unsigned int  temp=0;
     union pidtochar{
        unsigned int i=0;
        unsigned char c[4];    
    }pidex;
    pidex.i=getpid();

    currentpath.clear();
    std::string tempurl;
    struct flock lockstr = {};
    for(;;){
        if(reloadmysql){
             loadmysqlconfig();
             reloadmysql=false;
         }
         if(reloadserverconfig){
             loadserverglobalconfig();
             reloadserverconfig=false;
         }
 
          if(clientrunpool.getlivenum()>(clientrunpool.getmixthreads()-3)){
              clientrunpool.addthread(3);
              updatetimetemp=0;
          }else if(clientrunpool.getpoolthreadnum()>clientrunpool.getmixthreads()){
              
              updatetimetemp+=1;
              if(updatetimetemp==5){
                  clientrunpool.fixthread(); 
                  updatetimetemp=0;
              }
          }
          clientrunpool.printthreads();  

         buf[0]=0x84;
         buf[1]=pidex.c[0];
         buf[2]=pidex.c[1];
         buf[3]=pidex.c[2];
         buf[4]=pidex.c[3];

        std::this_thread::sleep_for(std::chrono::seconds(5));  
        
        if(alonehttpserver){
            try
            {
            asio::write(s, asio::buffer(buf, 5));
              }catch (std::exception& e)
            {
              //std::cout<<" watch http "<<e.what() << std::endl;
              io_context.stop();  
              
              break;
            }
        }
        //save log 


        if(currentpath.empty()){
          currentpath=sysconfigpath.serverconfig["default"]["logpath"];
          if(currentpath.size()>0&&currentpath.back()!='/'){
            currentpath.push_back('/');
          }
          currentpath.append("access.log");
        }

        int fd = open(currentpath.c_str(), O_WRONLY|O_CREAT|O_APPEND,0666);
        if (fd == -1) {
            continue;
        }  
        
        lockstr.l_type = F_WRLCK;
        lockstr.l_whence = SEEK_END;
        lockstr.l_start = 0;
        lockstr.l_len = 0;

        lockstr.l_pid =0;

        if (fcntl(fd, F_SETLK, &lockstr) == -1) {
            continue;
        }
        std::unique_lock<std::mutex> loglock(log_mutex);
        while (!loglist.empty()) {
                int n=write(fd,loglist.front().data(),loglist.front().size());
                loglist.pop_front();
        }
        loglock.unlock();

        lockstr.l_type = F_UNLCK;
        if (fcntl(fd, F_SETLK, &lockstr) == -1) {
          
           continue;
        }
        close(fd);

     }   
  }
  void run() {
    try {
      
      std::thread httpwatch(std::bind(&httpserver::httpwatch, this));
      std::this_thread::sleep_for(std::chrono::seconds(2)); 
      
      total_count = 0;
      {
        serverconfig&  sysconfigpath=  getserversysconfig();
        for(;total_count<10;total_count++){
          if(sysconfigpath.serverconfig.size()>0){
                break;
          }
          std::this_thread::sleep_for(std::chrono::seconds(1)); 
        }

      }

      if(total_count==10){
         return;
      }
      total_count = 0;


      std::thread http(std::bind(&httpserver::http_run, this));
      std::thread https(std::bind(&httpserver::https_run, this));
 

       for (int i = 0; i < 1; ++i) {
        websocketthreads.emplace_back(std::bind(&httpserver::websocket_loop, this, i));
      }

      for (int i = 0; i < 4; ++i) {
 
        runthreads.emplace_back(std::bind(&httpserver::http_loop, this, i));
      }

      if (http.joinable()) {
        http.join();
      }
      if (https.joinable()) {
        https.join();
      }

      for (int i = 0; i < 4; ++i) {
        if (runthreads[i].joinable()) {
          runthreads[i].join();
        }
      }
        for (int i = 0; i < 1; ++i) {
        if (websocketthreads[i].joinable()) {
          websocketthreads[i].join();
        }
      }
      if (httpwatch.joinable()) {
        httpwatch.join();
      }
      io_context.run();
    } catch (std::exception &e) {
      std::printf("Exception: %s\n", e.what());
    }
  }

public:
  // httpheader begin
  asio::io_context io_context{1};
  std::vector<std::thread> runthreads;
  std::vector<std::thread> websocketthreads;
  std::queue<std::shared_ptr<clientpeer>> tasks;
  std::list<std::weak_ptr<clientpeer>> websockettasks;
  std::mutex headqueue_mutex;
  std::condition_variable headqueue_condition;
  bool stop;
  std::atomic_uint total_count = 0;
  // httpheader end
  //log
  std::list<std::string> loglist;
  std::mutex log_mutex;
  //log end

  ThreadPool clientrunpool{32};
  
};
