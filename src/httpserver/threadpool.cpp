#include <cstdio>
#include <cstddef>
#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <setjmp.h>
#include <ctime>
#include <iostream>
#include <string>
#include <asio.hpp>
#include <asio/ssl.hpp>
#include <thread>
#include <cstdlib>
#include <fstream>
#include <algorithm>
#include <sys/types.h> 
#include <sys/wait.h>
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
 
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>

#include <boost/dll/import.hpp>
#include <boost/function.hpp>
#include "serverconfig.h"
#include "request.h"
#include "pluginmodule.hpp"
#include "threadpool.h"

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