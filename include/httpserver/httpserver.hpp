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
#include <cstdlib>
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
#include <cstdio>
#include <iostream>
#include <memory>
#include <cstdio> 
#include <iostream>
#include <ctime>
#include <map>
#include <string>
#include <sys/time.h>
#include <atomic>
#include <queue>
#include <memory>
#include <map>
#include <thread>
#include <mutex>
#include <filesystem>
#include <condition_variable>
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
//#include "httpparse.hpp"
#include "pluginmodule.hpp"
//#include "wwwserver.hpp"
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


#if defined(ASIO_ENABLE_HANDLER_TRACKING)
#define use_awaitable                                                          \
  asio::use_awaitable_t(__FILE__, __LINE__, __PRETTY_FUNCTION__)
#endif


// std::map<std::string,SSL_CTX*> g_ctxMap;
std::map<std::string,std::function<std::shared_ptr<websockets_api>(std::weak_ptr<clientpeer>)>> websocketmethodcallback;
std::map<std::string,std::function<std::string(http::clientpeer &)>>  methodcallback;
std::string serverconfigpath;
std::map<std::string,std::map<std::string,std::string>>  _serverconfig;



bool _siteusehtmlchache;
unsigned int _siteusehtmlchachetime;



  std::string get_password(){
      return "sslpem123456";
  }
  long   serverNameCallback(SSL *ssl, int *ad, void *arg) 
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
    configfile=serverconfigpath;
    if(configfile.size()>0&&configfile.back()!='/'){
        configfile.push_back('/');
    }
    configfile.append("server.conf");
    _serverconfig=http::loadserversconfig(configfile);
 
   http::siteviewpath=_serverconfig["default"]["viewsopath"];
   http::sitecontrolpath=_serverconfig["default"]["controlsopath"];
   if(_serverconfig["default"]["index"].empty()){
        _serverconfig["default"]["index"]="index.html";
   }
   if(_serverconfig["default"]["usehtmlcache"].empty()){
        _siteusehtmlchache=false;
   }else{
       _siteusehtmlchache=true;
   }
    if(_serverconfig["default"]["usehtmlcachetime"].empty()){
        _siteusehtmlchachetime=0;
   }else{
       _siteusehtmlchachetime=0;
       for(int i=0;i<_serverconfig["default"]["usehtmlcachetime"].size();i++){
                     if(_serverconfig["default"]["usehtmlcachetime"][i]>0x2F&&_serverconfig["default"]["usehtmlcachetime"][i]<0x3A){
                         _siteusehtmlchachetime=_siteusehtmlchachetime*10+(_serverconfig["default"]["usehtmlcachetime"][i]-'0');
                     }   
       }
       
   }
 
}
//////////////////////////////////////////
  void ThreadPool::printthreads(){
               std::unique_lock<std::mutex> lck(livemtx);           
              for(auto iter=threadlist.begin();iter!=threadlist.end();iter++){
                        std::cout<<iter->first<<" isbusy:"<<iter->second.busy<<" ip:"<<(iter->second.ip)<<" url:"<<iter->second.url<<std::endl;
              }
        }

unsigned int ThreadPool::getpoolthreadnum() { return threadlist.size(); }

bool ThreadPool::live_end(std::thread::id id) {

  auto iter = threadlist.find(id);
  if (iter != threadlist.end()) {
    std::unique_lock<std::mutex> lck(livemtx);
    unsigned long long temp = time((time_t *)NULL);
    threadlist[id].end = temp;
    return true;
  } else {
    return false;
  }
}
bool ThreadPool::live_add(std::thread::id id) {
  unsigned long long temp = time((time_t *)NULL);
  std::unique_lock<std::mutex> lck(livemtx);
  threadlist[id].begin = temp;
  return true;
}

inline void ThreadPool::threadloop(int index) {
  std::thread::id thread_id = std::this_thread::get_id();
  while (!this->stop) {

 
    std::unique_lock<std::mutex> lock(this->queue_mutex);
    this->condition.wait(lock, [this, thread_id] {
      return this->stop || !this->clienttasks.empty() ||
             this->threadlist[thread_id].stop;
    });
    if (this->stop && this->clienttasks.empty())
      break;

    if (this->threadlist[thread_id].stop) {
      break;
    }

    if (this->clienttasks.empty())
      continue;

    auto task = std::move(this->clienttasks.front());
    this->clienttasks.pop();
    lock.unlock();

    live_add(thread_id);
    livethreadcount += 1;
    this->threadlist[thread_id].busy = true;

    if(task->httptype==0){
      this->http_clientrun(task);
    }else{
       this->http_websocketsrun(task);
    }
    
    livethreadcount -= 1;
    this->threadlist[thread_id].busy = false;
    live_end(thread_id);
     
  }

  this->threadlist[thread_id].close = true;
}
bool ThreadPool::fixthread() {

  unsigned int tempcount = threadlist.size();
  if(tempcount<128){
    return false;
  }
  if (tempcount < (mixthreads.load() + 10)) {
    return false;
  }

   
  {

    std::unique_lock<std::mutex> lock(queue_mutex);
    for (auto &iter : threadlist) {
      if (iter.second.busy == false) {
        iter.second.stop = true;
        tempcount--;
      }
      if (tempcount <= mixthreads.load()) {
        break;
      }
    }
    lock.unlock();
  }

  condition.notify_all();

  std::unique_lock<std::mutex> lock(queue_mutex);
  for (auto iter = threadlist.begin(); iter != threadlist.end();) {
    if (iter->second.close) {
      if (iter->second.thread.joinable()) {
        iter->second.thread.join();
        threadlist.erase(iter++);
        pooltotalnum -= 1;
 
      } else {
        iter++;
      }
    } else {
      iter++;
    }
  }
  lock.unlock();

  return true;
}

bool ThreadPool::addthread(size_t threads) {

  if (threadlist.size() > 2048) {
    return false;
  }
 
  for (size_t i = 0; i < threads; ++i) {
    struct threadinfo_t tinfo;
    tinfo.thread = std::thread(
        std::bind(&ThreadPool::threadloop, this, pooltotalnum.load()));
    // tinfo.thread=std::thread(&ThreadPool::threadloop,this,pooltotalnum.load());
    std::thread::id temp = tinfo.thread.get_id();
    tinfo.id = temp;
    threadlist[tinfo.id] = std::move(tinfo);
    pooltotalnum++;
  }
  return true;
}

// the constructor just launches some amount of workers
inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
  pooltotalnum.store(0);
  livethreadcount.store(0);
  mixthreads.store(32);
  for (size_t i = 0; i < threads; ++i) {
   
    struct threadinfo_t tinfo;
    tinfo.thread = std::thread(
        std::bind(&ThreadPool::threadloop, this, pooltotalnum.load()));
    tinfo.id = tinfo.thread.get_id();
    threadlist[tinfo.id] = std::move(tinfo);
    pooltotalnum++;

  }
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool() {
  {
    std::unique_lock<std::mutex> lock(queue_mutex);
    stop = true;
  }
  condition.notify_all();
  
  for (auto &worker : threadlist) {
    if (worker.second.thread.joinable()) {
      worker.second.thread.join();
    }
  }
   
}

bool ThreadPool::addclient(std::shared_ptr<clientpeer> peer) {
  if (!stop) {
    std::unique_lock<std::mutex> lock(queue_mutex);
    clienttasks.emplace(peer);
  }

  condition.notify_one();
  return false;
}

void ThreadPool::http_clientrun(std::shared_ptr<clientpeer> peer) {
 try
 { 
  http::_threadclientpeer=peer.get();
  
  std::thread::id thread_id=std::this_thread::get_id();
   clientapi& pnn =clientapi::get();
  
   if(!peer->header->getfinish()){
        peer->send(400,"Request bad");
        return;
    }
   unsigned int offsetnum=0;
    for(;offsetnum<peer->header->host.size();offsetnum++){
          threadlist[thread_id].url[offsetnum]=peer->header->host[offsetnum];
          if(offsetnum>60){
              break;
          }
    }
    for(int j=0;j<peer->header->urlpath.size();j++){
        threadlist[thread_id].url[offsetnum]=peer->header->urlpath[j];
        offsetnum++;
        if(offsetnum>63){
            break;
        }
    }
    threadlist[thread_id].url[offsetnum]=0x00;
    

    { 
        unsigned int offsetnum=peer->remote_ip.size();
        if(offsetnum<46){
            memcpy(threadlist[thread_id].ip, peer->remote_ip.data(),offsetnum);
            threadlist[thread_id].ip[offsetnum]=0x00;
        }
    }
   std::cout<<"--------------------------------------------"<<std::endl;
   std::cout<<"remote_ip:"<<peer->remote_ip<<std::endl;
   std::cout<<"remote_port:"<<peer->remote_port<<std::endl;
   std::cout<<"local_ip:"<<peer->local_ip<<std::endl;
   std::cout<<"local_port:"<<peer->local_port<<std::endl;
   std::cout<<"--------------------------------------------"<<std::endl;
    peer->getfileinfo();
   unsigned char visttype=0;
                         
                        if(peer->pathtype==1){
                             
                            peer->sendfileto();
                            visttype=1;
                        }else{
                            if(_serverconfig.find(peer->header->host)!=_serverconfig.end()){
                                if(_serverconfig[peer->header->host].find("controlsopath")!=_serverconfig[peer->header->host].end()){
                                        _thishostcontrolsopath=_serverconfig[peer->header->host]["controlsopath"];
                                }
                                    if(_serverconfig[peer->header->host].find("viewsopath")!=_serverconfig[peer->header->host].end()){
                                        _thishostviewsopath=_serverconfig[peer->header->host]["viewsopath"];
                                }
                           }
                        
                            if(peer->header->pathinfo.size()>0){
                                struct stat modso;
                                std::string modulemethod,moduleso;
                                if(peer->header->pathinfo.size()>1){
                                    if(peer->header->pathinfo[1][0]=='h'&&strcasecmp(peer->header->pathinfo[1].c_str(),"home.html")==0){
                                        modulemethod=peer->header->pathinfo[0]+"/home";
                                    }else{
                                        modulemethod=peer->header->pathinfo[0]+"/"+peer->header->pathinfo[1];
                                    }
                                }else{
                                    modulemethod=peer->header->pathinfo[0];
                                }
                                
                                if(methodcallback.find(modulemethod)!=methodcallback.end()){
                                                visttype=6;
                                                std::string sitecontent=methodcallback[modulemethod](peer->getpeer());               
                                                if(sitecontent.empty()){
                                                    if(peer->vobj.as_int()==0){
                                                        peer->send(200);
                                                    }
                                                }else{
                                                    peer->send(200,sitecontent);
                                                }
                                }else{
                                        if(peer->header->pathinfo.size()==1){
                                            modulemethod.append("/home");
                                        }
                                        if(_serverconfig.find(peer->header->host)!=_serverconfig.end()){
                                                if(_serverconfig[peer->header->host].find("controlsopath")!=_serverconfig[peer->header->host].end()){
                                                        moduleso=_serverconfig[peer->header->host]["controlsopath"];
                                                }
                                        } 
                                        if(moduleso.empty()){
                                            moduleso=_serverconfig["default"]["controlsopath"];
                                        }
                                        if(moduleso.size()>0&&moduleso.back()!='/'){
                                            moduleso.append("/");
                                        }
                                        moduleso=moduleso+peer->header->pathinfo[0]+".so";
                                        if (stat(moduleso.c_str(),&modso)==0){
                                                visttype=3;
                                                auto sitemodloadis=http::loadcontrol(modulemethod);
                                                std::string sitecontent=sitemodloadis(peer->getpeer());
                                                    
                                                if(sitecontent.empty()){
                                                    if(peer->vobj.as_int()==0){
                                                      peer->send(200);
                                                    }
                                                }else{
                                                    peer->send(200,sitecontent);
                                                }
                                                            
                                        }else if(peer->pathtype==3){
                                            peer->sendfileto();
                                            visttype=5;
                                        }
                                }
                                

                            }else{
                                    std::string modulemethod,moduleso;  
                                    modulemethod="default"; 
                                    if(methodcallback.find(modulemethod)!=methodcallback.end()){
                                                visttype=6;
                                                std::string sitecontent=methodcallback[modulemethod](peer->getpeer());    
                                                if(sitecontent.empty()){
                                                    if(peer->vobj.as_int()==0){
                                                        peer->send(200);
                                                    }
                                                }else{
                                                    peer->send(200,sitecontent);
                                                }
                                }else{
                                        struct stat modso;
                                        modulemethod="default/home";
                                        
                                        if(_serverconfig.find(peer->header->host)!=_serverconfig.end()){
                                                if(_serverconfig[peer->header->host].find("controlsopath")!=_serverconfig[peer->header->host].end()){
                                                        moduleso=_serverconfig[peer->header->host]["controlsopath"];
                                                }
                                        } 
                                        if(moduleso.empty()){
                                            moduleso=_serverconfig["default"]["controlsopath"];
                                        }
                                        if(moduleso.size()>0&&moduleso.back()!='/'){
                                            moduleso.append("/");
                                        }
                                        moduleso=moduleso+"default.so";
                                        if (stat(moduleso.c_str(),&modso)==0){
                                                visttype=2;
                                                auto sitemodloadis=http::loadcontrol(modulemethod);
                                                std::string sitecontent=sitemodloadis(peer->getpeer());    
                                                if(sitecontent.empty()){
                                                    if(peer->vobj.as_int()==0){
                                                            peer->send(200);
                                                    }
                                                }else{
                                                    peer->send(200,sitecontent);
                                                }
                                                            
                                        }
                                }

                            }    
    
                        }
                        if(visttype==0){
                             if(peer->pathtype==2){
                                   
                                    bool isshowdirectory=false;
                                    
                                    if(_serverconfig.find(peer->header->host)!=_serverconfig.end()){
                                        if(_serverconfig[peer->header->host].find("directorylist")!=_serverconfig[peer->header->host].end()){
                                                 if(!_serverconfig[peer->header->host]["directorylist"].empty()){
                                                        isshowdirectory=true;
                                                 }
                                        }
                                    } 
                                    if(isshowdirectory==false){
                                         if(_serverconfig["default"].find("directorylist")!=_serverconfig["default"].end()){
                                                 if(!_serverconfig["default"]["directorylist"].empty()){
                                                        isshowdirectory=true;
                                                 }
                                        }
                                    }
                                    if(isshowdirectory){
                                         visttype=4;
                                         peer->displaydirectory(serverconfigpath);
                                    }
                            } 
                            if(visttype==0){
                                
                                peer->send(404,peer->header->urlpath);
                                visttype=7;
                            }
                        }
                         peer->_output.clear(); 
                         peer->vobj.clear(); 
                         if(peer->header->state.keeplive&&peer->keeplive){
                                peer->keeplivemax-=1;
                                peer->header->headerfinish=0;
                                peer->header->headerstep=0;
                                
                            }
      peer->looprunpromise.set_value(1);
   }catch (std::exception& e)
    {
           peer->looprunpromise.set_exception(std::current_exception());
    }              
}

void ThreadPool::http_websocketsrun(std::shared_ptr<clientpeer> peer) {
  try
  { 
      if(peer->ws->isfile){
          peer->websocket->onfiles(peer->ws->filename);
      }else{
        peer->websocket->onmessage(peer->ws->indata);
      }
      peer->ws->filename.clear();
      peer->ws->indata.clear();
    }catch (std::exception& e)
    {
        
    }
}

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
    // peer->globalconfig=&_serverconfig;
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
                  auto wsiter= websocketmethodcallback.find(peer->header->pathinfo[0]);   
                  if(wsiter==websocketmethodcallback.end()){
                      co_return;
                  }
                  auto myclientwsplugin=websocketmethodcallback[peer->header->pathinfo[0]];
                   peer->websocket=myclientwsplugin(peer);
                   peer->websocket->onopen();
                   if(peer->websocket->timeloop_num>0){
                      websockettasks.emplace_back(peer);
                   }
                   
                   for (;;) {
                  
                    for (;;) {
 
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

    tcp::acceptor acceptor(executor);

    asio::ip::tcp::endpoint endpoint(asio::ip::tcp::v4(), 4444);
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

      perror("acceptor listen error");
      exit(1);
    }

    for (;;) {
      //clientpeer peer;
      std::shared_ptr<clientpeer> clientp= std::make_shared<clientpeer>();
      clientp->globalconfig=&_serverconfig;
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
    tcp::acceptor acceptor(executor, {tcp::v4(), 443});

    std::string filepath=serverconfigpath;
    filepath.append("www.869869.com.pem");

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
    asio::error_code ec_error;

    for (;;) {
 
      std::shared_ptr<clientpeer> clientp= std::make_shared<clientpeer>();
      clientp->globalconfig=&_serverconfig;
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
     if(serverconfigpath.empty()){
       serverconfigpath="config/";
    }
         if(serverconfigpath.back()!='/'){
       serverconfigpath.push_back('/');
    }
      bool reloadmysql=true; 
    bool reloadserverconfig=true; 
    bool alonehttpserver=true; 
     unsigned int  updatetimetemp=0;
     _initwebsocketmethodregto(websocketmethodcallback);
    _inithttpmethodregto(methodcallback);
    ctxmar* ctxptr = ctxmar::instance();
    ctxptr->setconfigpath(serverconfigpath);

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

     std::string exfile="/tmp/httpexpid.locksocket";
     asio::io_context io_c;
     asio::local::stream_protocol::socket s(io_c);
    try{
         s.connect(asio::local::stream_protocol::endpoint(exfile.c_str()));
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

        std::this_thread::sleep_for(std::chrono::seconds(4));  
        
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

     

      
     }   
  }
  void run() {
    try {
      total_count = 0;
       std::thread httpwatch(std::bind(&httpserver::httpwatch, this));

      std::this_thread::sleep_for(std::chrono::seconds(2)); 
      std::thread http(std::bind(&httpserver::http_run, this));
      std::thread http2(std::bind(&httpserver::https_run, this));
 

       for (int i = 0; i < 1; ++i) {
        websocketthreads.emplace_back(std::bind(&httpserver::websocket_loop, this, i));
      }

      for (int i = 0; i < 4; ++i) {
 
        runthreads.emplace_back(std::bind(&httpserver::http_loop, this, i));
      }

      if (http.joinable()) {
        http.join();
      }
      if (http2.joinable()) {
        http2.join();
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

  ThreadPool clientrunpool{32};
  
};
