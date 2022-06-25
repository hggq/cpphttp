#pragma once
#include <atomic>
#include <deque>
#include <fstream>
#include <future>
#include <mutex>
#include <string>
#include <string_view>
#include <tuple>
#include <vector>
#include <asio.hpp>
#include <asio/ssl.hpp>
#include <thread>
class ctxmar{
    public:
    ctxmar(){

    }
   static ctxmar* instance()
    {
        if (singleton== NULL)
                singleton= new ctxmar();
        return singleton;
    }
    SSL_CTX* getctx(std::string filename){
         SSL_CTX* ctx = NULL;   
         std::string filepath=serverpempath;
         if(filepath.empty()){
             filepath="config/";
         }
         if(g_ctxMap.find(filename)!=g_ctxMap.end())
            {
                ctx=g_ctxMap[filename];
            }else{
                 g_ctxMap[filename]=SSL_CTX_new(SSLv23_server_method());
                 ctx=g_ctxMap[filename];
                  filename.append(".pem");
                // boost::asio::error_code ec;
                std::cout<<filename<<std::endl;
                filepath.append(filename);
                  if (::SSL_CTX_use_certificate_file(ctx, filepath.c_str(), SSL_FILETYPE_PEM) != 1)
                  {
                    // ec = boost::asio::error_code(
                    //     static_cast<int>(::ERR_get_error()),
                    //     boost::asio::error::get_ssl_category());
                    
                  }
                  filepath.erase(filepath.end()-4,filepath.end());
                  //filename.append(filename);
                
                  filepath.append(".key");
                  std::cout<<filename<<std::endl;
                    if (::SSL_CTX_use_PrivateKey_file(ctx, filepath.c_str(), SSL_FILETYPE_PEM) != 1)
                  {
                    // ec = boost::asio::error_code(
                    //     static_cast<int>(::ERR_get_error()),
                    //     boost::asio::error::get_ssl_category());
                     
                  }

                 if (!SSL_CTX_check_private_key(ctx))
                  {
                    //  ec = boost::asio::error_code(
                    //     static_cast<int>(::ERR_get_error()),
                    //     boost::asio::error::get_ssl_category());
                     
                  }
                  
            }
        return  ctx;
    }
    SSL_CTX* getdefaultctx(){
              SSL_CTX* ctx = NULL;   
            for (auto i = g_ctxMap.begin(); i != g_ctxMap.end(); ++i) {
                     ctx=i->second;
                     break;
            }
            return  ctx;
    }
    ~ctxmar(){
         std::cout<<"~ctxmar"<<std::endl;   
         for (auto i = g_ctxMap.begin(); i != g_ctxMap.end(); ++i) {
                     if(i->second!=NULL){
                            SSL_CTX_free(i->second);
                     }
            }
             
    }
    void setconfigpath(std::string path){
        serverpempath=path;
    }
    private:
            
         std::map<std::string,SSL_CTX*> g_ctxMap;   
         static ctxmar* singleton;
         std::string serverpempath;

         class ctxmarCollector {
            public:
                ~ctxmarCollector() {
                        delete ctxmar::singleton;
                        ctxmar::singleton = 0;
                         std::cout<<"~ctxmarCollector"<<std::endl;   
                }
            };
         static ctxmarCollector gc;

};
ctxmar* ctxmar::singleton =ctxmar::instance();
ctxmar::ctxmarCollector ctxmar::gc;
