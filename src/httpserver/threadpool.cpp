#ifndef FRAME_THREADPOOL_CPP
#define FRAME_THREADPOOL_CPP


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

namespace HTTP {


          void ThreadPool::printthreads(){
               std::unique_lock<std::mutex> lck(livemtx);           
              for(auto iter=threadlist.begin();iter!=threadlist.end();iter++){
                        std::cout<<iter->first<<" isbusy:"<<iter->second.busy<<" ip:"<<(iter->second.ip)<<" url:"<<iter->second.url<<std::endl;
              }
        }

         unsigned int ThreadPool::getpoolthreadnum(){
                    
          return threadlist.size();
        }

        bool ThreadPool::live_end(std::thread::id id){
            std::unique_lock<std::mutex> lck(livemtx); 
            auto iter=threadlist.find(id);
            if(iter!=threadlist.end()){
                  
                  unsigned long long temp=time((time_t *)NULL);
                  threadlist[id].end=temp;  
                  return true;
            }else{
                return false;
            }
        }
        bool ThreadPool::live_add(std::thread::id id){
                  unsigned long long temp=time((time_t *)NULL);
                  std::unique_lock<std::mutex> lck(livemtx);
                  threadlist[id].begin=temp;  
          return true;
        }

        
        inline void ThreadPool::threadloop(int index){
                        std::thread::id thread_id=std::this_thread::get_id();
                        while(!this->stop)
                        {
                            //std::cout<<"\r\n-------begin loop-------\r\n";
                            {
                                memset(threadlist[thread_id].url,0,100); 
                                memset(threadlist[thread_id].ip,0,45); 
                            std::unique_lock<std::mutex> lock(this->queue_mutex);

                            this->condition.wait(lock,
                                    [this,thread_id]{ return this->stop || !this->socketlists.empty() || this->threadlist[thread_id].stop; });
                                if(this->stop && this->socketlists.empty())
                                    break;

                                if(this->threadlist[thread_id].stop){
                                    break;
                                }
                                if(this->socketlists.empty())
                                    continue;   

                            
                                socketlists_t b(std::move(this->socketlists.front()));
                                this->socketlists.pop();
                        
                                lock.unlock();
                                
                            live_add(thread_id);
                            livethreadcount+=1;
                            this->threadlist[thread_id].busy=true;
                            
                            if(b.isssl){
                                this->sitehttpsslprocess(std::move(b.socket),b.context_,b.isssl);
                            }else{
                                this->sitehttpprocess(std::move(b.socket),b.context_,b.isssl);
                            }
                            
                            livethreadcount-=1;
                            this->threadlist[thread_id].busy=false;
                            live_end(thread_id);
                            //std::cout<<" livethreadcount "<<livethreadcount<<std::endl;            
                            }
                        }
                
                this->threadlist[thread_id].close=true;
                
        }
        bool ThreadPool::fixthread()
        {
            
            unsigned int tempcount=threadlist.size();

            if(tempcount<(mixthreads.load()+2)){
                    return false;
            }

            std::cout<<"\r\n=========fixthread=="<<pooltotalnum<<"======\r\n";
            {      
                    
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    for(auto &iter:threadlist){
                        if(tempcount<=mixthreads.load()){
                            break;
                        }
                        if(iter.second.busy==false){
                            iter.second.stop=true; 
                            tempcount--;
                        }
                       
                        
                    }
                    lock.unlock();
            }

            condition.notify_all();

            std::unique_lock<std::mutex> lock(queue_mutex);
            for(auto iter=threadlist.begin();iter!=threadlist.end();){
                        if(iter->second.close){
                            if(iter->second.thread.joinable())
                            {
                                iter->second.thread.join();   
                                threadlist.erase(iter++); 
                                pooltotalnum-=1;
                                std::cout<<"\r\n<<<<<<<=========>>>>>>>fixthread=="<<pooltotalnum<<">>>>>>>>>>>\r\n";
                            }else{
                                iter++;
                            }
                        }else{
                            iter++;
                        }
                    
                    }
            lock.unlock();
            
            return true;
        }

        bool ThreadPool::addthread(size_t threads)
        {
            
            if(pooltotalnum>2048){
                return false;
            }
            std::cout<<"\r\n=========addthread=="<<pooltotalnum<<"======\r\n";
            unsigned int offset=threadlist.size();
            for(size_t i = 0;i<threads;++i)
            {
                struct threadinfo_t tinfo;
                
                tinfo.thread=std::thread(std::bind(&ThreadPool::threadloop,this,pooltotalnum.load()));
                std::thread::id temp=tinfo.thread.get_id();
                tinfo.id=temp;
                threadlist[tinfo.id]=std::move(tinfo);
                pooltotalnum++;
                if(pooltotalnum>1000000){
                    pooltotalnum=0;
                }
            }
            return true;
        }

       ThreadPool::ThreadPool()
            :   stop(false)
        {

        }
        // the constructor just launches some amount of workers
        ThreadPool::ThreadPool(unsigned long threads)
            :   stop(false)
        {
            pooltotalnum.store(0);  
            livethreadcount.store(0);  
            mixthreads.store(threads);
            for(size_t i = 0;i<threads;++i)
            {
                struct threadinfo_t tinfo;
                //tinfo.index=i;
                tinfo.thread=std::thread(std::bind(&ThreadPool::threadloop,this,pooltotalnum.load()));
                //tinfo.thread=std::thread(&ThreadPool::threadloop,this,pooltotalnum.load());
                tinfo.id=tinfo.thread.get_id();
                threadlist[tinfo.id]=std::move(tinfo);
                pooltotalnum++;
                if(pooltotalnum>100000000){
                    pooltotalnum.store(1); 
                } 
            }     
        }

        void ThreadPool::addtask(asio::ip::tcp::socket socket, asio::ssl::context &context_,bool isssl){ 
                if(!stop){
                    std::unique_lock<std::mutex> lock(queue_mutex);
                    socketlists_t a{std::move(socket),context_,isssl};
                    socketlists.emplace(std::move(a));
                }
            condition.notify_one();
        
        }

        // the destructor joins all threads
        ThreadPool::~ThreadPool()
        {
            {
                std::unique_lock<std::mutex> lock(queue_mutex);
                stop = true;
            }
            condition.notify_all();
            std::cout<<"------------ join begin------------ "<<std::endl;
            for(auto &worker: threadlist){
                if(worker.second.thread.joinable())
                {
                    worker.second.thread.join();

                }
            }
            std::cout<<"------------ join end------------ "<<std::endl;    
        }
        inline void ThreadPool::sitehttpprocess(asio::ip::tcp::socket socket,asio::ssl::context &context_,bool isssl){

                            try
                        {

                            std::thread::id thread_id=std::this_thread::get_id();

                            std::cout<<"---------------------"<<this->threadlist.size()<<std::endl;  

                            //std::unique_lock<std::mutex> lck(livemtx);
                            // threadlist[thread_id].url=temp;  


                            HTTP::_output.clear();      

                            char data[2051];
                            std::string httpheader;
                            std::size_t n = socket.read_some(asio::buffer(data));
                            
                            memcpy(threadlist[thread_id].url, data,99);
                            threadlist[thread_id].url[99]=0x00;
                            httpheader=socket.remote_endpoint().address().to_string();
                            memcpy(threadlist[thread_id].ip, httpheader.data(),15);
                            threadlist[thread_id].ip[15]=0x00;

                            // std::this_thread::sleep_for(std::chrono::seconds(5));
                            int i=0;
                            for(;i<n;i++){
                                if(data[i]==0x20){
                                    i++;
                                    break;
                                }
                            }
                            int urlmaxoffset=i;
                            for(;urlmaxoffset<n;urlmaxoffset++){
                                if(data[urlmaxoffset]==0x20){
                                    
                                    break;
                                }
                                
                            }

                            if(data[i]=='/'){
                                i++;
                            }
                            std::string filename,method;
                            for(;i<urlmaxoffset;i++){
                                if(data[i]=='/'||data[i]==0x20){
                                    i++;
                                    break;
                                }
                                filename.push_back(data[i]);
                            }
                            for(;i<urlmaxoffset;i++){
                                if(data[i]=='/'||data[i]==0x20||data[i]=='?'){
                                    //i++;
                                    break;
                                }
                                method.push_back(data[i]);
                            }
                            std::string sofile="["+filename+"]["+method+"]";

                            if(urlmaxoffset[i]=='?'){
                                 i++;
                                 std::string varkey;
                                 std::string varvalue;   
                                   for(;i<urlmaxoffset;i++){
                                        if(data[i]=='='){
                                            //i++;
                                            varkey=varvalue;
                                            varvalue.clear();
                                            continue;
                                        }else if(data[i]=='&'){
                                            _viewobj[varkey]=varvalue;
                                            varkey.clear();
                                            varvalue.clear();
                                                continue;
                                        }
                                        varvalue.push_back(data[i]);
                                    }
                                if(varkey.size()>0){
                                    _viewobj[varkey]=varvalue;
                                            varkey.clear();
                                            varvalue.clear();
                                }
                            }
                    // livethread[std::this_thread::get_id()]=time((time_t *)NULL);

                    if(method.size()==1){
                        HTTP::controlmoduleclear("weibo","header");
                            HTTP::controlmoduleclear("weibo","home");
                            HTTP::controlmoduleclear("weibo","hello");
                            HTTP::viewmoduleclear("about","jianjie");
                            HTTP::viewmoduleclear("about","head");
                            method="home";
                    }

            _viewobj["name"]="网民吗悲伤";
            std::string methodcontent;
                        methodcontent.append(filename);
                        methodcontent.push_back('/');
                        methodcontent.append(method);
            auto bb=HTTP::loadcontrol(methodcontent);
        // methodcontent=HTTP::loadcontrol("chat/hello")(obj);
            methodcontent.clear();
            methodcontent=bb(_viewobj);
            bb.clear();
                if(methodcontent.empty()){
                //std::cout << HTTP::_output<< std::endl;  
                sofile.append(_output);
            }else{
            // std::cout << methodcontent<< std::endl;  
            sofile.append(methodcontent);
            }
            _output.clear();
        // std::cout << "After library unload." << std::endl;

                            sofile=respdata(sofile);
                            asio::write(socket, asio::buffer(sofile));
                            socket.close();   
                            //std::this_thread::sleep_for(std::chrono::seconds(5));

                    // auto iter=livethread.find(std::this_thread::get_id());
                    // if(iter!=livethread.end()){
                    //       livethread.erase(iter);
                    // }
                        }catch (std::exception& e)
                        {
                            std::cout<<" http content error "<<e.what() << std::endl;
                        }


        }
        inline void ThreadPool::sitehttpsslprocess(asio::ip::tcp::socket rawsocket,asio::ssl::context &context_,bool isssl){

            try
            {
                //  std::cout<<"---------------------------------"<<std::endl;
                
                asio::ssl::stream<asio::ip::tcp::socket> socket(std::move(rawsocket), context_);
                asio::error_code error;
                socket.handshake(asio::ssl::stream_base::server,error);
                
                _output.clear();  

                char data[2051];
                std::size_t n = socket.read_some(asio::buffer(data));
                          int i=0;
                            for(;i<n;i++){
                                if(data[i]==0x20){
                                    i++;
                                    break;
                                }
                            }
                            int urlmaxoffset=i;
                            for(;urlmaxoffset<n;urlmaxoffset++){
                                if(data[urlmaxoffset]==0x20){
                                    
                                    break;
                                }
                                
                            }

                            if(data[i]=='/'){
                                i++;
                            }
                            std::string filename,method;
                            for(;i<urlmaxoffset;i++){
                                if(data[i]=='/'||data[i]==0x20){
                                    i++;
                                    break;
                                }
                                filename.push_back(data[i]);
                            }
                            for(;i<urlmaxoffset;i++){
                                if(data[i]=='/'||data[i]==0x20){
                                    i++;
                                    break;
                                }
                                method.push_back(data[i]);
                            }
                            std::string sofile=filename;//+"/"+method;
                            if(method.size()>0){
                                sofile.push_back('/'); 
                                sofile.append(method); 
                            }else{

                            }    

                

                std::string resp;
                _viewobj["name"]="网民吗悲伤";
                auto iter=modulemethodcallfun.find(sofile);
                if(iter!=modulemethodcallfun.end()){
                       resp="HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\nConnection: keep-alive\r\nContent-length: 9\r\n\r\nIt works!";
                }else{
                       resp=iter->second(_viewobj); 
                }
                
                asio::write(socket, asio::buffer(resp));

                //socket.shutdown();
            // 	//   rawsocket.close();   
            //         boost::system::error_code ec;
            // socket.cancel(ec);
            // socket.async_shutdown([&](...) { socket.close(); };
            
            }catch (std::exception& e)
            {
                std::printf("echo Exception: %s\n", e.what());
            }
        }
}
#endif