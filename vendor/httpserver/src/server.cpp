#include "httpserver.hpp"
#include "init_deamon.hpp"
#include <atomic>
#include <chrono>
#include <thread>
#include "server.h"

static sigjmp_buf env_startacs;
static void sig_child(int signo);
 
int forkcount_=0;
unsigned char livprocessnum=2;//产生进程
unsigned char checkprocesssecond=12;
 


class mainloop{
    public:
        mainloop(){

        }
        awaitable<void> procssecho(asio::local::stream_protocol::socket socket) {

                try{

                        unsigned char data[1024];
                        for(;;){
                            std::size_t n =  co_await socket.async_read_some(asio::buffer(data), use_awaitable);

                            if(n>0){
                                 
                                 if(data[0]==0x84){

                                     pidex.c[0]=data[1];
                                     pidex.c[1]=data[2];
                                     pidex.c[2]=data[3];
                                     pidex.c[3]=data[4];
                                     
                                     int i=0;
                                     std::cout<<"http pidex.i="<<pidex.i<<std::endl;
                                     for(;i<pidinfo.size();i++){

                                         if(pidinfo[i].pid==pidex.i){
                                                while (lock_edit.test_and_set()) {} 
                                                pidinfo[i].time=time((time_t*)NULL);   
                                                lock_edit.clear();
                                                break;
                                         }

                                     }   

                                     if(i==pidinfo.size()){
                                         i=0;
                                         while (lock_edit.test_and_set()) {} 

                                         for(;i<pidinfo.size();i++){
                                            if(pidinfo[i].pid==0){
                                                         pidinfo[i].pid=pidex.i; 
                                                         pidinfo[i].time=time((time_t*)NULL);
                                                         pidinfo[i].iscache=false;      
                                            }
                                        }  
                                       if(i==pidinfo.size()){
                                           pidinfo.push_back({(int)pidex.i,(unsigned int)time((time_t*)NULL),false});  
                                            
                                       }
                                       lock_edit.clear();
                                     }   
                                      


                                }else if(data[0]==0x44){

                                     pidex.c[0]=data[1];
                                     pidex.c[1]=data[2];
                                     pidex.c[2]=data[3];
                                     pidex.c[3]=data[4];
                                     
                                     int i=0;
                                     std::cout<<"cache pidex.i="<<pidex.i<<std::endl;
                                     for(;i<pidinfo.size();i++){

                                         if(pidinfo[i].pid==pidex.i){
                                                while (lock_edit.test_and_set()) {} 
                                                pidinfo[i].time=time((time_t*)NULL);   
                                                lock_edit.clear();
                                                break;
                                         }

                                     }   

                                     if(i==pidinfo.size()){
                                         i=0;
                                         while (lock_edit.test_and_set()) {} 

                                         for(;i<pidinfo.size();i++){
                                            if(pidinfo[i].pid==0){
                                                         pidinfo[i].pid=pidex.i; 
                                                         pidinfo[i].time=time((time_t*)NULL);
                                                         pidinfo[i].iscache=true;      
                                            }
                                        }  
                                       if(i==pidinfo.size()){
                                           pidinfo.push_back({(int)pidex.i,(unsigned int)time((time_t*)NULL),true});  
                                            
                                       }
                                       lock_edit.clear();
                                     }   

                                }
                            }
                        }
                        


                } catch (std::exception& e) {
                     
                }
        }
        awaitable<void> serverlisten() {
               auto executor = co_await this_coro::executor;
                asio::error_code ec;
                asio::local::stream_protocol::acceptor acceptor(executor, asio::local::stream_protocol::endpoint(exfile));
                 for (;;) {
                     asio::local::stream_protocol::socket socket = co_await acceptor.async_accept(use_awaitable);
                     co_spawn(executor,procssecho(std::move(socket)), detached);
                 }

        }
        void server(){
                std::remove(exfile.c_str());
                co_spawn(this->io_context, serverlisten(), detached);
                this->io_context.run();
        }
        void client(){
              
        }
    public:
    asio::io_context io_context{1};
    std::string exfile="/tmp/httpexpid.locksocket";
    // int maxnum=10;
    // int processpids[10];
    // unsigned int processtimes[10];
    struct pidinfo_t{
       int pid;
       unsigned int time;
       bool iscache=false;
    };
    std::vector<pidinfo_t> pidinfo;
    union pidtochar{
        unsigned int i=0;
        unsigned char c[4];    
    }pidex;
    std::atomic_flag lock_edit = ATOMIC_FLAG_INIT;
};

static void sig_child(int signo)
{
     /*pid_t */ int      pid;
     int        stat;
     int        temp;
     //处理僵尸进程
	
 	switch( signo ){
		case SIGCHLD:
            
        pid = wait( &stat );  
        printf("SIGCHLD...farter id %d..%d\n",getpid(),pid);
 
        checkprocesssecond=12;
        mainloop&  mainserverloop=  get_global<mainloop>();  
        
          while (mainserverloop.lock_edit.test_and_set()) {}

                   for(int a=0;a<mainserverloop.pidinfo.size();a++)
                    {
                       if(mainserverloop.pidinfo[a].pid==pid){
                             
                                if(mainserverloop.pidinfo[a].iscache==true){
                                    forkcount_=1;
                                    printf("================ id %d..%d\n",forkcount_,pid);
                                }
                               
                        }

                    }
                    mainserverloop.lock_edit.clear();


        siglongjmp(env_startacs, 1);//跳转至先前的setjmp处
		break;
 
	}		
    exit(0);  
}


void infoserver(){

   mainloop&  mainserverloop=  get_global<mainloop>();
   mainserverloop.server();
}

void cachewatchthread(int & watchdogforcache){
     std::this_thread::sleep_for(std::chrono::seconds(5));  
     bool alonehttpserver=true;
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

    for(;;){
         buf[0]=0x44;
         buf[1]=pidex.c[0];
         buf[2]=pidex.c[1];
         buf[3]=pidex.c[2];
         buf[4]=pidex.c[3];

        std::this_thread::sleep_for(std::chrono::seconds(10));  
        
        if(alonehttpserver){
            try
            {
            asio::write(s, asio::buffer(buf, 5));
             std::cout<<" -------- send send ----- "<<std::endl;
              }catch (std::exception& e)
            {
              //std::cout<<" watch http "<<e.what() << std::endl;
              io_c.stop();  
              
              break;
            }
        }
        if(watchdogforcache==0){
                temp+=1;
                if(temp==2){
                    break;
                }
        }else{
            watchdogforcache=0;
            temp=0;
        }
        std::cout<<" -------- cache watch------ "<<std::endl;
    }

}
void cacheserver(){

    int cc=0; 
    int watchdogforcache=1;   
    std::thread f(cachewatchthread,std::ref(watchdogforcache));
    f.detach();
    while (1) {
            std::cout<<"----cache----- "<<getpid()<<std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(3));

            cc++;
            // if(cc==20){
            //   break;
            // }
            watchdogforcache=1;
    }
   
}
void webserver(const char * arg,bool isdemon=false){
   if(isdemon){
        init_deamon(); 
   } 
   try {
    
    serverconfigpath=arg;
    httpserver httpmy;
    httpmy.run();

  } catch (std::exception &e) {
    std::printf("Exception: %s\n", e.what());
  }
}
void webserver_fork(const char * arg,bool isdemon=false){
    if(isdemon){
        init_deamon(); 
    }
    pid_t pid,subpid=0;    
    signal(SIGCHLD,sig_child);
    serverconfigpath=arg;

      if( sigsetjmp(env_startacs, 1) == 0 ) //设置记号
        {
            printf("setjmp ok.....\n");
        }else
        {
            printf("longjmp ok.....\n");
        } 

        pid = fork();
        printf("fork id %d \n",pid);
        if (pid < 0)
        {
            perror("fork error:");
            exit(1);
        }else if (pid == 0)
        {
        //sub
                if(forkcount_<2){
                    cacheserver();
                }else{
                    try {
    
                    httpserver httpmy;
                    httpmy.run();

                    } catch (std::exception &e) {
                        std::printf("Exception: %s\n", e.what());
                    }
                }
               
                exit(0);
        }else{

               if(forkcount_==0){
                            std::thread f(infoserver);
                            f.detach();
                            forkcount_+=2; 
                            siglongjmp(env_startacs, 1); //跳转至先前的setjmp处   
                            //return 0;
                }
                forkcount_++;
              std::this_thread::sleep_for(std::chrono::seconds(2));
              mainloop&  mainserverloop=  get_global<mainloop>();  
              while(1)
              {

                    std::this_thread::sleep_for(std::chrono::seconds(checkprocesssecond));
                    std::cout<<"client procss num: "<<mainserverloop.pidinfo.size()<<std::endl;
                    int livenum=0;
                    bool iscachesever=false;
                    while (mainserverloop.lock_edit.test_and_set()) {}

                   for(int a=0;a<mainserverloop.pidinfo.size();a++)
                    {
                        if(mainserverloop.pidinfo[a].pid==0){
                            continue;
                        }
                        int subpid=waitpid(mainserverloop.pidinfo[a].pid,NULL,WNOHANG);
                        if(subpid == 0){
                                printf("%d child exited\n",mainserverloop.pidinfo[a].pid);  
                                if(mainserverloop.pidinfo[a].iscache==false){
                                    livenum+=1;
                                }
                        }else if(mainserverloop.pidinfo[a].pid==subpid){
                                mainserverloop.pidinfo[a].time=0;
                                mainserverloop.pidinfo[a].pid=0;
                                if(mainserverloop.pidinfo[a].iscache==true){
                                    iscachesever=true;
                                }
                                mainserverloop.pidinfo[a].pid=false;
                        }

                    }
                    mainserverloop.lock_edit.clear();
                    if(iscachesever){
                        std::this_thread::sleep_for(std::chrono::seconds(40));

                         
                         while (mainserverloop.lock_edit.test_and_set()) {}

                         for(int a=0;a<mainserverloop.pidinfo.size();a++)
                            {
                                if(mainserverloop.pidinfo[a].pid==0){
                                    continue;
                                }
                                int subpid=waitpid(mainserverloop.pidinfo[a].pid,NULL,WNOHANG);
                                if(subpid == 0){
                                    if(mainserverloop.pidinfo[a].iscache==true){
                                        iscachesever=false;
                                    }
                                }

                            }
                         mainserverloop.lock_edit.clear();

                         if(iscachesever){
                                forkcount_=1;
                                siglongjmp(env_startacs, 1); //跳转至先前的setjmp处  
                         }


                    }
                    if(livenum<livprocessnum){
                         std::this_thread::sleep_for(std::chrono::seconds(10));

                         livenum=0;
                         while (mainserverloop.lock_edit.test_and_set()) {}

                         for(int a=0;a<mainserverloop.pidinfo.size();a++)
                            {
                                if(mainserverloop.pidinfo[a].pid==0){
                                    continue;
                                }
                                int subpid=waitpid(mainserverloop.pidinfo[a].pid,NULL,WNOHANG);
                                if(subpid == 0){
                                    if(mainserverloop.pidinfo[a].iscache==false){
                                        livenum+=1;
                                    }
                                }

                            }
                         mainserverloop.lock_edit.clear();
                         if(livenum<livprocessnum){
                                siglongjmp(env_startacs, 1); //跳转至先前的setjmp处  
                         }
                    }

                    if(checkprocesssecond<60){
                        checkprocesssecond+=1;
                    }
              }   

        }



}


