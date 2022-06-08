#include "httpserver.hpp"
#include "init_deamon.hpp"
#include <atomic>
/*
mac os
 g++ forkserver.cpp src/httpserver/request.cpp src/httpserver/unicode.cpp  -std=c++20 -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Iinclude/httpserver -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp src/httpserver/Clientpeer.cpp src/httpserver/WebSocketparse.cpp -Iwebsockets src/httpserver/gzip.cpp src/httpserver/datetime.cpp src/httpserver/urlcode.cpp -Icontroller -Icommon src/httpserver/mysqlpool.cpp src/httpserver/httpparse.cpp src/httpserver/httpsocommonapi.cpp
*/
/*
ubuntu20.04
g++-11 -std=c++20 forkserver.cpp src/httpserver/request.cpp src/httpserver/unicode.cpp   -lboost_filesystem -lssl -lcrypto -ldl -lssl -lcrypto -ldl -lz -Iinclude/httpserver -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib  -lmysqlcppconn8 models/sms/News.cpp  -Imodels -I models/include  models/Moduleauth.cpp src/httpserver/Clientpeer.cpp src/httpserver/WebSocketparse.cpp -Iwebsockets src/httpserver/gzip.cpp src/httpserver/datetime.cpp src/httpserver/urlcode.cpp -Icontroller -Icommon src/httpserver/mysqlpool.cpp src/httpserver/httpparse.cpp src/httpserver/httpsocommonapi.cpp -lpthread -I/usr/include/mysql-cppconn-8
*/
static sigjmp_buf env_startacs;
static void sig_child(int signo);
 
int forkcount_=0;
unsigned char livprocessnum=2;//产生进程
unsigned char checkprocesssecond=12;
 

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

        siglongjmp(env_startacs, 1);//跳转至先前的setjmp处
		break;
 
	}		
    exit(0);  
}

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
                                 
                                 if(data[0] and 0x80==0x80){

                                     pidex.c[0]=data[1];
                                     pidex.c[1]=data[2];
                                     pidex.c[2]=data[3];
                                     pidex.c[3]=data[4];
                                     
                                     int i=0;
                                     std::cout<<"pidex.i="<<pidex.i<<std::endl;
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
                                            }
                                        }  
                                       if(i==pidinfo.size()){
                                           pidinfo.push_back({(int)pidex.i,(unsigned int)time((time_t*)NULL)});  
                                            
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
    };
    std::vector<pidinfo_t> pidinfo;
    union pidtochar{
        unsigned int i=0;
        unsigned char c[4];    
    }pidex;
    std::atomic_flag lock_edit = ATOMIC_FLAG_INIT;
};

void infoserver(){

   mainloop&  mainserverloop=  get_global<mainloop>();
   mainserverloop.server();
}

int main(int argc,char *argv[]){
   // init_deamon(); 
    pid_t pid,subpid=0;
    //创建捕捉子进程退出信号
    if(argc>1){
            serverconfigpath=argv[1];
    }
    
    signal(SIGCHLD,sig_child);

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
  
                 try {
    
                    httpserver httpmy;
                    httpmy.run();

                } catch (std::exception &e) {
                    std::printf("Exception: %s\n", e.what());
                }
                exit(0);
        }else{

               if(forkcount_==0){
                            std::thread f(infoserver);
                            f.detach();
                          
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
                    while (mainserverloop.lock_edit.test_and_set()) {}

                   for(int a=0;a<mainserverloop.pidinfo.size();a++)
                    {
                        if(mainserverloop.pidinfo[a].pid==0){
                            continue;
                        }
                        int subpid=waitpid(mainserverloop.pidinfo[a].pid,NULL,WNOHANG);
                        if(subpid == 0){
                                printf("%d child exited\n",mainserverloop.pidinfo[a].pid);  
                                livenum+=1;
                        }else if(mainserverloop.pidinfo[a].pid==subpid){
                                mainserverloop.pidinfo[a].time=0;
                                mainserverloop.pidinfo[a].pid=0;
                        }

                    }
                    mainserverloop.lock_edit.clear();
                    if(livenum<livprocessnum){
                         siglongjmp(env_startacs, 1); //跳转至先前的setjmp处  
                    }

                    if(checkprocesssecond<60){
                        checkprocesssecond+=1;
                    }
              }   

        }

    return 0;        
 


}


