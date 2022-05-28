
#include <algorithm>
#include <asio.hpp>
#include <asio/ssl.hpp>
#include <asio/co_spawn.hpp>
#include <asio/detached.hpp>
#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include <asio/signal_set.hpp>
#include <asio/write.hpp>
#include <cstdio>
#include <list>
#include <map>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <memory>
#include <cstdio> 
#include <sys/fcntl.h>
#include "datetime.h"
#include "urlcode.h"


#ifndef WIN32
#include <unistd.h>
#endif

#ifdef WIN32
#define stat _stat
#endif

#include "Clientpeer.h"
// #include "common_functions.h"
namespace HTTP { 
        namespace fs = std::filesystem;
          void clientpeer::cookietoheader(){
              std::string temph;
              for(auto &iter:cookie){
                  temph.clear();  
                  std::string key=iter.first;
                  std::string domain=cookie.getDomain(key);
                  std::string domainpath=cookie.getPath(key);
                   unsigned long timeexp=cookie.getExpires(key);
                   unsigned char issecure=cookie.getSecure(key);
                    unsigned char isonly=cookie.getHttponly(key);

                    temph.append("Set-Cookie: ");
                    temph.append(url_encode(iter.first.data(),iter.first.size()));
                    temph.push_back('=');
                    temph.append(url_encode(iter.second.data(),iter.second.size()));
 
                    if(timeexp>0&&timeexp<63072000){
                        timeexp=timeid()+timeexp;
                    }

                    key.clear();
                    if(timeexp>0){
                        key=HTTP::getGmtTime((unsigned long long)timeexp);
                        temph.append("; Expires=");
                        temph.append(key);
                    }

                    if(domain.size()>1){
                        temph.append("; Domain=");
                        temph.append(domain);     
                    }

                     if(domainpath.size()>1){
                        temph.append("; Path=");
                        temph.append(domainpath);     
                    }
                    

                     if(issecure>0){
                        temph.append("; Secure");
                          
                    }

                      if(isonly>0){
                        temph.append("; HttpOnly");
                          
                    }

                   headerlists.emplace_back(temph);
              }
        }  
        void clientpeer::addcookie(std::string key,std::string val,unsigned long exptime=0,std::string domain="",std::string path="",bool secure=false,bool httponly=false){
             cookie.set(key,val,exptime,domain,path,secure,httponly);
             header->cookie.set(key,val,exptime,domain,path,secure,httponly);
        }
        void clientpeer::addcookie(std::string key,std::string val,unsigned long exptime=0){
             cookie.set(key,val,exptime);
             header->cookie.set(key,val,exptime);
        }
    void clientpeer::addheader(std::string_view str){
            headerlists.emplace_back(str);
    }
    void clientpeer::addheader(const char * str){
             headerlists.emplace_back(str);
   }
   void clientpeer::addheader(std::string vkey,std::string vstr){
         vkey.append(": ");
         vkey.append(vstr);
         headerlists.emplace_back(vkey);
   }

    void clientpeer::parse_session(){
         if(header->cookie.check("CPPSESSID")){
               std::string root_path;
               if(globalconfig){
               std::map<std::string,std::map<std::string,std::string>> &config=*globalconfig;
                    root_path.clear(); 
                            if(config.find("default")!=config.end()){
                                     root_path=config["default"]["serverpath"];
                                     if(root_path.size()>0&&root_path.back()!='/'){
                                          root_path.push_back('/');
                                     }
                                     root_path.append("tmp/");
                            }else{
                                root_path="tmp/";
                            }
               }  
               std::string sessionfile= header->cookie.get("CPPSESSID");
               if(sessionfile.empty()){
                   return;
               }
               sessionfile.append("_sess");
               root_path.append(sessionfile);

                struct stat sessfileinfo;
                unsigned long long  tempsesstime=0;
                 memset(&sessfileinfo,0,sizeof(sessfileinfo));
                if(stat(root_path.c_str(),&sessfileinfo)==0){
                    tempsesstime =   sessfileinfo.st_mtime;
                }

                if(tempsesstime>0&&tempsesstime==sessionfile_time){
                     return;         
                }
              int fd = open(root_path.c_str(), O_RDONLY);
                if (fd == -1) {
                    //perror("open");
                    return;
                }  

                 // 锁住整个文件
                struct flock lock = {};
                lock.l_type = F_RDLCK;
                lock.l_whence = 0;
                lock.l_start = 0;
                lock.l_len = 0;

                lock.l_pid =0;

                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    return;
                }
                int filelen= lseek(fd,0L,SEEK_END);  
                sessionfile.clear();
                sessionfile.resize(filelen);
                 lseek(fd,0L,SEEK_SET); 
                 int  readsize= read(fd,sessionfile.data(),filelen);
                if(readsize>0){
                    sessionfile.resize(readsize);
                    session.fromjson(sessionfile);
                }

                lock.l_type = F_UNLCK;
                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    
                    return;
                }
                close(fd);
                sessionfile_time=tempsesstime;
        }
    }
     void clientpeer::save_session(){
         std::string sessionfile;
         if(header->cookie.check("CPPSESSID")){
              sessionfile= header->cookie.get("CPPSESSID");
               
          }
          if(sessionfile.empty()){
                sessionfile=remote_ip+std::to_string(remote_port)+std::to_string(timeid())+std::to_string(rand()); 
                sessionfile=std::to_string(std::hash<std::string>{}(sessionfile));
                cookie.set("CPPSESSID",sessionfile,7200);
                header->cookie.set("CPPSESSID",sessionfile,7200);
           }   
               std::string root_path;

               std::map<std::string,std::map<std::string,std::string>> &config=*globalconfig;
                    root_path.clear();

                            if(config.find("default")!=config.end()){
                                     root_path=config["default"]["serverpath"];
                                     if(root_path.size()>0&&root_path.back()!='/'){
                                          root_path.push_back('/');
                                     }
                                     root_path.append("tmp/");
                            }else{
                                root_path="tmp/";
                            }

              
               sessionfile.append("_sess");
               root_path.append(sessionfile);
               
              int fd = open(root_path.c_str(), O_RDWR|O_CREAT,0666);
                if (fd == -1) {
                    //perror("open");
                    return;
                }  
                 
                 // 锁住整个文件
                struct flock lock = {};
                lock.l_type = F_WRLCK;
                lock.l_whence = 0;
                lock.l_start = 0;
                lock.l_len = 0;

                lock.l_pid =0;

                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    return;
                }

                sessionfile=session.tojson();
                 
                write(fd,sessionfile.data(),sessionfile.size());

                lock.l_type = F_UNLCK;
                if (fcntl(fd, F_SETLKW, &lock) == -1) {
                    
                    return;
                }
                close(fd);
                sessionfile_time=timeid();
        
    }
   void clientpeer::clear_session(){
        if(header->cookie.check("CPPSESSID")){
               std::string root_path;

               std::map<std::string,std::map<std::string,std::string>> &config=*globalconfig;
                    root_path.clear();

                            if(config.find("default")!=config.end()){
                                     root_path=config["default"]["serverpath"];
                                     if(root_path.size()>0&&root_path.back()!='/'){
                                          root_path.push_back('/');
                                     }
                                     root_path.append("tmp/");
                            }else{
                                root_path="tmp/";
                            }

               std::string sessionfile= header->cookie.get("CPPSESSID");
               if(sessionfile.empty()){
                   return;
               }
               sessionfile.append("_sess");
               root_path.append(sessionfile);

                struct stat sessfileinfo;
                unsigned long long  tempsesstime=0;
                 memset(&sessfileinfo,0,sizeof(sessfileinfo));
                         if(stat(root_path.c_str(),&sessfileinfo)==0){

                              if(sessfileinfo.st_mode & S_IFREG){
                                    remove(root_path.c_str());
                                    sessionfile_time=0;
                                    session.clear();
                              }
                                
                         }else{
                             return;
                         }

            

        }
   } 
   clientpeer& clientpeer::operator<<(HTTP::OBJ_VALUE &a){
                    _output.append(a.to_string());
                    return *this;
                }
             clientpeer& clientpeer::operator<<(std::string &&a){
                    _output.append(a);
                    return *this;
                }
                 clientpeer& clientpeer::operator<<(std::string &a){
                    _output.append(a);
                    return *this;
                }
                 clientpeer& clientpeer::operator<<(std::string_view a){
                    _output.append(a);
                    return *this;
                }
                clientpeer& clientpeer::operator<<(char const *a){
                    _output.append(a);
                    return *this;
                }
                clientpeer& clientpeer::operator<<(float a){
                    _output.append(std::to_string(a));
                    return *this;
                } 
                clientpeer& clientpeer::operator<<(long long a){
                    _output.append(std::to_string(a));
                    return *this;
                }
                 clientpeer& clientpeer::operator<<(int a){
                    _output.append(std::to_string(a));
                    return *this;
                }
                 clientpeer& clientpeer::operator<<(short a){
                    _output.append(std::to_string(a));
                    return *this;
                }
                clientpeer& clientpeer::operator<<(unsigned long long a){
                    _output.append(std::to_string(a));
                    return *this;
                }
                 clientpeer& clientpeer::operator<<(unsigned int a){
                    _output.append(std::to_string(a));
                    return *this;
                }
                clientpeer& clientpeer::operator<<(double a){
               
                    _output.append(std::to_string(a));
                    return *this;
                }
                template<typename T>
                clientpeer& clientpeer::operator<<(T &a){
                    _output.append(a.to_string());
                    return *this;
                }

 std::string clientpeer::getremoteip(){
       if(isssl){
           remote_ip=https_socket.front().lowest_layer().remote_endpoint().address().to_string();
       }else{
           remote_ip=http_socket.front().remote_endpoint().address().to_string();
       }
       return remote_ip;
  }
 unsigned short clientpeer::getremoteport(){
       if(isssl){
           remote_port=https_socket.front().lowest_layer().remote_endpoint().port();
       }else{
           remote_port=http_socket.front().remote_endpoint().port();
       }
       return remote_port;
  }  
  std::string clientpeer::getlocalip(){
       if(isssl){
           local_ip=https_socket.front().lowest_layer().local_endpoint().address().to_string();
       }else{
           local_ip=http_socket.front().local_endpoint().address().to_string();
       }
       return local_ip;
  }
 unsigned short clientpeer::getlocalport(){
       if(isssl){
           local_port= https_socket.front().lowest_layer().local_endpoint().port();
       }else{
           local_port= http_socket.front().local_endpoint().port();
       }
       return local_port;
  }   
 void clientpeer::send(std::string &data){
       std::unique_lock<std::mutex> lock(writemutex);
       if(isssl){
           asio::write(https_socket.front(), asio::buffer(data));
       }else{
           asio::write(http_socket.front(), asio::buffer(data));
       }
       lock.unlock();
  }
 void clientpeer::send(const char *data,int sendsize){
       std::unique_lock<std::mutex> lock(writemutex);
       if(isssl){
           asio::write(https_socket.front(), asio::buffer(data,sendsize));
       }else{
           asio::write(http_socket.front(), asio::buffer(data,sendsize));
       }
       lock.unlock();
  }   



                void clientpeer::send(unsigned int statecode,std::string &str){
                    std::string outstr;
                    outstr.append("HTTP/1.1 ");

                    switch (statecode) {
                        case 500:
                            outstr.append("500 Internal Server Error\r\n");
                            str.append("<hr />500 Internal Server Error");
                            break;   
                        case 404:
                            outstr.append("404 Not Found\r\n");
                             str.append("<hr />404 Not Found");
                            break;   
                        case 400:
                            outstr.append("404 Bad Request\r\n");
                            break;
                        case 301:
                            outstr.append("301 Moved Permanently\r\n");
                            keeplive=false;
                            cookietoheader();
                            for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                            }
                            
                            outstr.append("Connection: close\r\n");
                            outstr.append("\r\n");
                            if(isssl){
                                asio::write(https_socket.front(), asio::buffer(outstr));
                            }else{
                                asio::write(http_socket.front(), asio::buffer(outstr));
                            }
                            return;
                            break;       
                        case 200:
                                outstr.append("200 OK\r\n");
                                break; 
                                
                    }  
                    outstr.append("Content-Type: text/html; charset=UTF-8\r\n");
                    if(header->state.keeplive){
                        outstr.append("Connection: keep-alive\r\n");
                        keeplive=true;
                    }else{
                        outstr.append("Connection: close\r\n");
                    }
                    cookietoheader();
                     for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                    }
                    outstr.append("Content-Length: ");
                    outstr.append(std::to_string(str.size()));
                    outstr.append("\r\n\r\n");
                    //outstr.append(str);
                    if(isssl){
                        asio::write(https_socket.front(), asio::buffer(outstr));
                    }else{
                        asio::write(http_socket.front(), asio::buffer(outstr));
                    }
                    if(isssl){
                        asio::write(https_socket.front(), asio::buffer(str));
                    }else{
                        asio::write(http_socket.front(), asio::buffer(str));
                    }
                } 

                void clientpeer::send(int statecode,std::string &&str){
                    std::string outstr;
                    outstr.append("HTTP/1.1 ");

                    switch (statecode) {
                        case 500:
                            outstr.append("500 Internal Server Error\r\n");
                            str.append("<hr />500 Internal Server Error");
                            break;   
                        case 404:
                            outstr.append("404 Not Found\r\n");
                             str.append("<hr />404 Not Found");
                            break;   
                        case 400:
                            outstr.append("404 Bad Request\r\n");
                            break;
                        case 301:
                            outstr.append("301 Moved Permanently\r\n");
                            keeplive=false;
                            cookietoheader();
                            for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                            }
                            
                            outstr.append("Connection: close\r\n");
                            outstr.append("\r\n");
                            if(isssl){
                                asio::write(https_socket.front(), asio::buffer(outstr));
                            }else{
                                asio::write(http_socket.front(), asio::buffer(outstr));
                            }
                            return;
                            break;       
                        case 200:
                                outstr.append("200 OK\r\n");
                                break; 
                                
                    }  
                    outstr.append("Content-Type: text/html; charset=UTF-8\r\n");
                    if(header->state.keeplive){
                        outstr.append("Connection: keep-alive\r\n");
                        keeplive=true;
                    }else{
                        outstr.append("Connection: close\r\n");
                    }
                    cookietoheader();
                    for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                    }
                    outstr.append("Content-Length: ");
                    outstr.append(std::to_string(str.size()));
                    outstr.append("\r\n\r\n");
                    //outstr.append(str);
                    if(isssl){
                        asio::write(https_socket.front(), asio::buffer(outstr));
                    }else{
                        asio::write(http_socket.front(), asio::buffer(outstr));
                    }
                    if(isssl){
                        asio::write(https_socket.front(), asio::buffer(str));
                    }else{
                        asio::write(http_socket.front(), asio::buffer(str));
                    }
                } 

 void clientpeer::sendfile(std::string sendfile_name){
 
                 std::string sendfileinfo;

                 if(globalconfig!=nullptr){
                         auto configiter=globalconfig->find(header->host);
                        if(configiter!=globalconfig->end()){
                                     
                                auto wwwconfigiter=configiter->second.find("wwwpath");
                                if(wwwconfigiter!=configiter->second.end()){
                                            sendfileinfo=wwwconfigiter->second;
                                            
                                    }
                                        
                        }
                         
                        if(sendfileinfo.empty()){
                            auto configdef=globalconfig->find("default");
                            if(configdef!=globalconfig->end()){
                                        
                                            auto wwwconfigiter=configdef->second.find("wwwpath");
                                            if(wwwconfigiter!=configiter->second.end()){
                                                        sendfileinfo=wwwconfigiter->second;
                                                        
                                                }

                                    }
                        }   
                 }
                
                if(sendfileinfo.size()>0&&sendfileinfo.back()!='/'){
                    sendfileinfo.append("/");
                }  
                sendfileinfo.append(sendfile_name);
                FILE *ff=fopen(sendfileinfo.c_str(),"rb");
 
                if(ff){
                    unsigned long long mustnum,readnum=0;
                    fseek(ff, 0, SEEK_END);
                    mustnum= ftell(ff);
                    fseek(ff, 0, SEEK_SET);
                    sendheader(200,mustnum+_output.size());   

                    if(_output.size()>0){  
                          if(isssl){
                                asio::write(https_socket.front(), asio::buffer(_output));
                            }else{
                                asio::write(http_socket.front(), asio::buffer(_output));
                            }       

                    }
                                                                
                    while(readnum<mustnum){
                            memset(_data,0x00,2048);
                            auto nread =fread(&_data[0], 1,2048, ff);
                            
                            if(isssl){
                                    asio::write(https_socket.front(), asio::buffer(_data,nread));
                                }else{
                                    asio::write(http_socket.front(),asio::buffer(_data,nread));
                                }
                            readnum+=nread;
                    }
                    fclose(ff);
                    vobj.set_int();
                    vobj=111;
                    vobj.set_array();
                }
                
            }

 void clientpeer::sendheader(unsigned int statecode,unsigned long long contentlength=0){
                    std::string outstr;
                    outstr.append("HTTP/1.1 ");

                    switch (statecode) {
                        case 500:
                            outstr.append("500 Internal Server Error\r\n");
                            break;   
                        case 404:
                            outstr.append("404 Not Found\r\n");
                            break;   
                        case 400:
                            outstr.append("404 Bad Request\r\n");
                            break;
                        case 301:
                            outstr.append("301 Moved Permanently\r\n");
                            keeplive=false;
                            cookietoheader();
                            for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                            }
                            
                            outstr.append("Connection: close\r\n");
                            outstr.append("\r\n");
                            if(isssl){
                                asio::write(https_socket.front(), asio::buffer(outstr));
                            }else{
                                asio::write(http_socket.front(), asio::buffer(outstr));
                            }
                            return;
                            break;    
                        case 200:
                                outstr.append("200 OK\r\n");
                                break; 
                                
                    }  
                    outstr.append("Content-Type: text/html; charset=UTF-8\r\n");
                    if(header->state.keeplive){
                        outstr.append("Connection: keep-alive\r\n");
                        keeplive=true;
                    }else{
                        outstr.append("Connection: close\r\n");
                    }
                    cookietoheader();
                    for(auto &sh:headerlists){
                                outstr.append(sh);
                                if(sh.back()!='\n'){
                                   outstr.append("\r\n");     
                                }
                    }
                    outstr.append("Content-Length: ");
                    outstr.append(std::to_string(contentlength));
                    outstr.append("\r\n\r\n");
                    
                    if(isssl){
                        asio::write(https_socket.front(), asio::buffer(outstr));
                    }else{
                        asio::write(http_socket.front(), asio::buffer(outstr));
                    }
                }


                std::string clientpeer::makeetag(){
                     etag.clear();
                     modifytime=fileinfo.st_mtime;
                     filesize=fileinfo.st_size;
                     etag.append(HTTP::to_hexstring(filesize));  
                                    etag.append("-");
                                    etag.append(HTTP::to_hexstring(modifytime)); 
                    return etag;
                }
                std::string clientpeer::writetime_tostring(fs::file_time_type const& ftime){
                            systimeid= std::chrono::duration_cast<std::chrono::seconds>(ftime.time_since_epoch()).count();
                            lsystemTime = localtime(&systimeid);
                            unsigned char timeformat;
                            tempchache.str("");
                            tempchache<<(lsystemTime->tm_year +1900);
                            tempchache<<"-";
                            timeformat=lsystemTime->tm_mon+1;
                            if(timeformat<10){
                                tempchache<<"0"<<std::to_string(timeformat);
                            }else{
                                tempchache<<std::to_string(timeformat);
                            }
                            tempchache<<"-";
                            
                            if(lsystemTime->tm_mday<10){
                                tempchache<<"0"<<std::to_string(lsystemTime->tm_mday);
                            }else{
                                tempchache<<std::to_string(lsystemTime->tm_mday);
                            }

                            tempchache<<" ";
                            
                            if(lsystemTime->tm_hour<10){
                                tempchache<<"0"<<std::to_string(lsystemTime->tm_hour);
                            }else{
                                tempchache<<std::to_string(lsystemTime->tm_hour);
                            }

                            tempchache<<":";
                            
                            if(lsystemTime->tm_min<10){
                                tempchache<<"0"<<std::to_string(lsystemTime->tm_min);
                            }else{
                                tempchache<<std::to_string(lsystemTime->tm_min);
                            }

                            tempchache<<":";
                            
                            if(lsystemTime->tm_sec<10){
                                tempchache<<"0"<<std::to_string(lsystemTime->tm_sec);
                            }else{
                                tempchache<<std::to_string(lsystemTime->tm_sec);
                            }
                            return tempchache.str();
                }
        void clientpeer::getfileinfo(){
                        // if(globalconfig->empty()){
                        //     globalconfig=&config;
                        // }   
                        std::map<std::string,std::map<std::string,std::string>> &config=*globalconfig;
                       
                        if(sitepath.size()==0){
                            getsitepath();
                        }   

                        sendfilename=sitepath;
                        fileexttype.clear();
                      
                        for(int i=0;i<header->pathinfo.size();i++){
                               if(i>0){
                                   sendfilename.append("/");
                               } 
                               sendfilename.append(header->pathinfo[i]); 
                        }
                        
                        if(header->pathinfo.size()>0){
                            filenamebase=header->pathinfo.back();    
                        }else{
                            filenamebase.clear();
                        }    

                        unsigned int filebasesize=filenamebase.size();
                        unsigned int filenameoffset=0;
                        
                        if(filebasesize>0){
                                for(filenameoffset=filebasesize-1;filenameoffset>0;filenameoffset--){
                                    if(filenamebase[filenameoffset]=='.'){
                                        break;
                                    }
                                }
                                filenameoffset+=1;
                                for(;filenameoffset<filebasesize;filenameoffset++){
                                    fileexttype.push_back(filenamebase[filenameoffset]);
                                }
                        } 
 
                         pathtype=0;  
                         memset(&fileinfo,0,sizeof(fileinfo));
                         if(stat(sendfilename.c_str(),&fileinfo)==0){

                            if(fileinfo.st_mode & S_IFDIR){
                                pathtype=2;
                                unsigned int nowpathsize=sendfilename.size();
                                if(sendfilename.back()=='/'){
                                        sendfilename.append(config["default"]["index"]); 
                                }else{
                                        sendfilename.push_back('/'); 
                                        sendfilename.append(config["default"]["index"]); 
                                }
                                if(stat(sendfilename.c_str(),&fileinfo)==0){

                                    if(fileinfo.st_mode & S_IFREG){
                                        pathtype=1;
                                        fileexttype="html";
                                    } 
                                }
                                if(pathtype==2){
                                    sendfilename.resize(nowpathsize);
                                }
                            }else if(fileinfo.st_mode & S_IFREG){
                                pathtype=1;
                                // use cahce html ,modulepath same urlpath
                                // sample: /module/method/202204/22333.html
                                if(isusehtmlcache&&header->pathinfo.size()>2&&chachefiletime>10&&chachefiletime<(HTTP::timeid()-(unsigned long)fileinfo.st_mtime)){
                                    pathtype=3;
                                }                                    
                            }   
                           
                        } 
                     
                }
                 void clientpeer::getsitepath(){
                     
                    std::map<std::string,std::map<std::string,std::string>> &config=*globalconfig;
                    sitepath.clear();

                            if(config.find("default")!=config.end()){
                                     sitepath=config["default"]["wwwpath"];
                                     if(sitepath.empty()){
                                         sitepath="www/";
                                     }
                                  
                            }else{
                                sitepath="www/";
                           
                            }
                            if(sitepath.back()!='/'){
                                sitepath.push_back('/');
                            }


                            if(config.find(header->host)!=config.end()){
                                 if(config[header->host]["wwwpath"].empty()){
                                    sitepath.append(header->host);
                                }else{
                                    sitepath=config[header->host]["wwwpath"];
                                }
                                
                            }else{                   
                              if(header->host.size()>3&&header->host[0]!='w'&&header->host[1]!='w'&&header->host[2]!='w'&&header->host[3]!='.'){
                                    std::string dddmod="*.";
                                    bool isplithost=true;
                                    std::string splithostpre;
                                    for(int i=0;i<header->host.size();i++){
                                            if(isplithost&&header->host[i]=='.'){
                                                isplithost=false;
                                                continue;
                                            }
                                            if(isplithost){
                                                splithostpre.push_back(header->host[i]);
                                                
                                            }else{
                                                dddmod.push_back(header->host[i]);
                                            }
                                    }
                                    if(config.find(dddmod)!=config.end()){
                                            if(config[dddmod]["aliaspath"].empty()){
                                                sitepath.append(dddmod.substr(2));    
                                                if(sitepath.back()!='/'){
                                                    sitepath.push_back('/');
                                                }
                                                sitepath.append(splithostpre);
                                                 
                                            }else{
                                                sitepath=config[dddmod]["aliaspath"];
                                                if(sitepath.back()!='/'){
                                                    sitepath.push_back('/');
                                                }
                                                sitepath.append(splithostpre);
                                                
                                            }
                                    }else{
                                        sitepath.append(header->host);
                                    }

                                
                                }else{
                                        sitepath.append(header->host);
                                }
                               
                            }
                             if(sitepath.back()!='/'){
                                    sitepath.push_back('/');
                             }
                }

                 void clientpeer::displaydirectory(std::string configpath){
 
                        std::string httpquestpath,parentpath,templatea,templateb;
                        if(header->urlpath[0]!='/'){
                            httpquestpath.push_back('/');    
                        }
                        httpquestpath.append(header->urlpath);
                        if(httpquestpath.size()>0&&httpquestpath.back()!='/'){
                            httpquestpath.push_back('/'); 
                        }
                        if(configpath.size()>0&&configpath.back()!='/'){
                            configpath.push_back('/'); 
                        }

                        senddatastring.clear();
                        parentpath=configpath+"directory.html";
                            FILE *ff=fopen(parentpath.c_str(),"rb");
                        if(ff){
                                fseek(ff, 0, SEEK_END);
                                auto const size = ftell(ff);
                                fseek(ff, 0, SEEK_SET);
                                senddatastring.resize(size);
                                auto nread =fread(&senddatastring[0], 1,size, ff);

                                auto beginpos=senddatastring.find("<!---directorycontentlist---->");
                                if(beginpos!=std::string::npos){
                                    templatea=senddatastring.substr(0,beginpos);
                                    templateb=senddatastring.substr(beginpos+sizeof("<!---directorycontentlist---->"));
                                }
                                senddatastring=templatea;
                                fclose(ff);
                        }
                    parentpath.clear();
                    int i=httpquestpath.size();
                    if(i>2){
                        i-=2;
                    }
                    for(;i>1;i--){
                        if(httpquestpath[i]=='/'){
                            for(int j=0;j<i;j++){
                                parentpath.push_back(httpquestpath[j]);
                            }
                            break;
                        }
                    }  
                        fs::path path(sendfilename);
                          
                            senddatastring.append("<ul class=\"directorycontent\">");
                            senddatastring.append("<li class=\"rowhead\">");
                                    senddatastring.append("<span class=\"filename\"><a href=\"");
                                    senddatastring.append(header->urlpath);
                                    senddatastring.append("\">");

                                    senddatastring.append("Filename");
                                    senddatastring.append("</a></span>");
                                    senddatastring.append("<span class=\"filesize\"><a href=\"");
                                    senddatastring.append(header->urlpath);
                                    senddatastring.append("?sort=size\">Size");
                                    senddatastring.append("</a></span>");
                                    senddatastring.append("<span class=\"time\"><a href=\"");
                                    senddatastring.append(header->urlpath);
                                    senddatastring.append("?sort=time\">Time");
                                        
                                    senddatastring.append("</a></span>");
                                    senddatastring.append("</li>");

                        if (parentpath.size()>0)
                        {
                            
                                    senddatastring.append("<li class=\"directoryrow\">");
                                    senddatastring.append("<span class=\"filename\"><a href=\"");
                                    senddatastring.append(parentpath);
                                    senddatastring.append("\">");
                                    senddatastring.append("..");
                                    senddatastring.append("</a></span>");
                                    senddatastring.append("<span class=\"filesize\">-");
                                    senddatastring.append("</span>");
                                    senddatastring.append("<span class=\"time\">-");
                                        
                                    senddatastring.append("</span>");
                                    senddatastring.append("</li>");
                        }     
                        struct directorylist_t{
                                std::string filename;
                                unsigned long long  size;
                                std::string time;
                                std::string ext;
                        };
                        std::vector<directorylist_t> fileslists;
                        if (fs::exists(path) && fs::is_directory(path))
                        {
                        
                            for (const auto& entry : fs::directory_iterator(path))
                            {
                                directorylist_t pathfilelists;
                                auto filename = entry.path().filename();
                                if (fs::is_regular_file(entry.status()))
                                    {
                                    pathfilelists.filename= filename.string();
                                    pathfilelists.ext= entry.path().extension();    
 

                                    long long filesize=fs::file_size(entry);
                                     pathfilelists.size=filesize; 
                                    pathfilelists.time= writetime_tostring(entry.last_write_time());
 

                                    
                                }else if (fs::is_directory(entry.status()))
                                {

                                    pathfilelists.filename= filename.string();
                                     pathfilelists.size=0;
                                    pathfilelists.time= "-";
                                }
                                fileslists.emplace_back(pathfilelists);
                            }

                        }
                        if(header->get["sort"].as_string()=="size"){
                             std::sort(fileslists.begin(), fileslists.end(),[](directorylist_t const& a, directorylist_t const& b) {
                                 return a.size < b.size;
                            });
                        }else if(header->get["sort"].as_string()=="time"){
                             std::sort(fileslists.begin(), fileslists.end(),[](directorylist_t const& a, directorylist_t const& b) {
                                 return a.time < b.time;
                            });
                        }else{
                            std::sort(fileslists.begin(), fileslists.end(),[](directorylist_t const& a, directorylist_t const& b) {
                                 return a.filename < b.filename;
                            });
                        }
                        

                        for(int i=0;i<fileslists.size();i++){
                                    senddatastring.append("<li class=\"directoryrow\">");
                                    if(fileslists[i].time.size()<3){
                                        senddatastring.append("<span class=\"filename\"><i class=\"bi bi-folder");   
                                        senddatastring.append("\"></i> <a href=\"");  
                                    }else{
                                        senddatastring.append("<span class=\"filename\"><i class=\"bi bi-filetype-");

                                            if(fileslists[i].ext.size()>0&&fileslists[i].ext[0]=='.'){
                                                senddatastring.append(fileslists[i].ext.substr(1));
                                            }else{
                                                senddatastring.append(fileslists[i].ext);
                                            }
                                       senddatastring.append("\"></i> <a href=\"");  
                                       
                                    }
                                    
                                    
                                      senddatastring.append(httpquestpath);
                                       senddatastring.append(fileslists[i].filename);   
                                   
                                    senddatastring.append("\">");
                                    senddatastring.append(fileslists[i].filename);
                                    senddatastring.append("</a></span>");
                                    senddatastring.append("<span class=\"filesize\">");
                                    senddatastring.append(std::to_string(fileslists[i].size));
                                    senddatastring.append("</span>");
                                    senddatastring.append("<span class=\"time\">");
                                    senddatastring.append(fileslists[i].time);      
                                    senddatastring.append("</span>");
                                    senddatastring.append("</li>");
                        }


                        senddatastring.append("</ul>");
                        senddatastring.append(templateb);
                        parentpath="HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n";;
                            if(header->state.keeplive){
                                    parentpath.append("Connection: keep-alive\r\n");
                                    keeplive=true;
                                }else{
                                    parentpath.append("Connection: close\r\n");
                                }
                                parentpath.append("Cache-Control: max-age=15\r\nContent-length: "+std::to_string(senddatastring.size())+"\r\n\r\n");
                                parentpath.append(senddatastring); 
                        
                            if(isssl){
                            asio::write(https_socket.front(), asio::buffer(parentpath));
                        }else{
                            asio::write(http_socket.front(),asio::buffer(parentpath));
                        }
                                         
                }
                void clientpeer::sendfileto(){
                           
                                    if(fileexttype.size()>0){
                                        http::mime mime;
                                        mimetype=mime._map[fileexttype];
                                        if(mimetype.empty()){
                                            mimetype="application/octet-stream";
                                        }  
                                        
                                    }
                                    if(mimetype.size()==0){
                                        if(fileinfo.st_size<20480){
                                            mimetype="text/plan";
                                        }else{
                                            mimetype="application/octet-stream";
                                        }
                                    }
                                   unsigned long long filebytesize=fileinfo.st_size;
                                   unsigned long long filemodifytime=fileinfo.st_mtime+header->urlpath.size();
                                   
                                    etag.clear(); 
                                    etag.append(HTTP::to_hexstring(filebytesize));  
                                    etag.append("-");
                                    etag.append(HTTP::to_hexstring(filemodifytime)); 
                                    filemodifytime=fileinfo.st_mtime; 
                                    bool iscompress=false;
                                    bool iscompok=false;
                                    if(header->state.rangebytes==false){
                                            if(header->state.ifmodifiedsince>0&&header->state.ifmodifiedsince==filemodifytime){
                                                        senddatastring="HTTP/1.1 304 Not Modified\r\nDate:"+HTTP::getGmtTime()+"\r\n";
                                                        if(header->state.keeplive){
                                                                senddatastring.append("Connection: keep-alive\r\n");
                                                                keeplive=true;
                                                            }else{
                                                                senddatastring.append("Connection: close\r\n");
                                                                keeplive=false;
                                                            }
                                                        senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\nLast-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\n\r\n"); 
                                                         
                                                        if(isssl){
                                                            asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                        }else{
                                                            asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                        }
                                                        return;

                                            }else if(header->etag.size()>0&&etag==header->etag){
                                                        senddatastring="HTTP/1.1 304 Not Modified\r\nDate:"+HTTP::getGmtTime()+"\r\n";
                                                        
                                                        if(header->state.keeplive){
                                                                senddatastring.append("Connection: keep-alive\r\n");
                                                                keeplive=true;
                                                            }else{
                                                                senddatastring.append("Connection: close\r\n");
                                                                keeplive=false;
                                                            }
                                                        senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\nLast-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\n\r\n");  
                                                         
                                                        if(isssl){
                                                            asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                        }else{
                                                            asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                        }
                                                        return ;
                                            }
                                            senddatastring.clear();
                                            
                                            if(header->state.gzip&&filebytesize<3145728&&mimetype.size()>0){
                                                switch (mimetype[0]) {
                                                    case 'T':
                                                    case 't':
                                                            if(strcasecmp(mimetype.c_str(),"text/css")==0){
                                                                    iscompress=true;
                                                            }
                                                            if(strcasecmp(mimetype.c_str(),"text/plain")==0){
                                                                    iscompress=true;
                                                            }
                                                            if(strcasecmp(mimetype.c_str(),"text/html")==0){
                                                                    iscompress=true;
                                                            }
                                                            if(strcasecmp(mimetype.c_str(),"text/javascript")==0){
                                                                    iscompress=true;
                                                            }
                                                            break;
                                                    case 'a':
                                                            
                                                            if(strcasecmp(mimetype.c_str(),"application/json")==0){
                                                                    iscompress=true;
                                                            }
                                                            if(strcasecmp(mimetype.c_str(),"application/javascript")==0){
                                                                    iscompress=true;
                                                            }
                                                            break;     
                                                     case 'i':
                                                            
                                                            if(strcasecmp(mimetype.c_str(),"image/svg+xml")==0){
                                                                    iscompress=true;
                                                            }
                                                            
                                                            break;              

                                                }
                                            }

                                                    if(iscompress){

                                                            FILE *ff=fopen(sendfilename.c_str(),"rb");
                                                            if(ff){
                                                                    fseek(ff, 0, SEEK_END);
                                                                    auto const size = ftell(ff);
                                                                    fseek(ff, 0, SEEK_SET);
                                                                    senddatastring.resize(size);
                                                                    auto nread =fread(&senddatastring[0], 1,size, ff);
                                                                    fclose(ff);
                                                                    std::string out_compress;
                                                                    if(compress(senddatastring.data(),senddatastring.size(),out_compress,Z_DEFAULT_COMPRESSION) == Z_OK){

                                                                            senddatastring="HTTP/1.1 200 OK\r\nContent-Type: "+mimetype+"\r\nDate: "+HTTP::getGmtTime()+"\r\nLast-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\n";//
                                                                            
                                                                            if(header->state.keeplive){
                                                                                senddatastring.append("Connection: keep-alive\r\n");
                                                                                keeplive=true;
                                                                            }else{
                                                                                senddatastring.append("Connection: close\r\n");
                                                                                keeplive=false;
                                                                            }
                                                                            senddatastring.append("Content-Encoding: gzip\r\n");
                                                                            senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\nCache-Control: max-age=691200\r\nContent-length: "+std::to_string(out_compress.size())+"\r\n\r\n");//+lm;
                                                                            unsigned long long sendsize=0;
                        
                                                                                if(isssl){
                                                                                    asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                                                }else{
                                                                                    asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                                                }
                                                                            if(isssl){
                                                                                    asio::write(https_socket.front(), asio::buffer(out_compress));
                                                                                }else{
                                                                                    asio::write(http_socket.front(),asio::buffer(out_compress));
                                                                                }
                                                                            out_compress.clear();

                                                                        iscompok=true;    
                                                                    }//zok
                                                            }
                                                    }
                                            } //is range

                                            if(iscompok==false){
                                                    senddatastring.clear();
                                                 if(header->state.rangebytes==false){
                                                        FILE *ff=fopen(sendfilename.c_str(),"rb");
                                                        if(ff){
                                                                fseek(ff, 0, SEEK_END);
                                                                auto const size = ftell(ff);
                                                                fseek(ff, 0, SEEK_SET);

                                                                senddatastring="HTTP/1.1 200 OK\r\nContent-Type: "+mimetype+"\r\nDate: "+HTTP::getGmtTime()+"\r\nLast-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\n";//
                                                                
                                                                if(header->state.keeplive){
                                                                    senddatastring.append("Connection: keep-alive\r\n");
                                                                    keeplive=true;
                                                                }else{
                                                                    senddatastring.append("Connection: close\r\n");
                                                                    keeplive=false;
                                                                }
                                                                senddatastring.append("Accept-Ranges: bytes\r\n");
                                                                senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\nCache-Control: max-age=691200\r\nContent-length: "+std::to_string(size)+"\r\n\r\n");//+lm;
                                                                unsigned long long sendsize=0;
            
                                                            
                                                                if(isssl){
                                                                                asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                                            }else{
                                                                                asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                                            }
                                                                
                                                                while(sendsize<size){
                                                                        memset(_data,0x00,2048);
                                                                        auto nread =fread(&_data[0], 1,2048, ff);
                                                                         
                                                                        if(isssl){
                                                                                asio::write(https_socket.front(), asio::buffer(_data,nread));
                                                                            }else{
                                                                                asio::write(http_socket.front(),asio::buffer(_data,nread));
                                                                            }
                                
                                                                        sendsize+=nread;
                                                                }
                                                                fclose(ff);       
                                                                    

                                                        }else{
                                                             
                                                            send(404,sendfilename);
                                                        }
                                                 }else{
                                                     //is range
                                                     unsigned short statecode=200;   
                                                        
                                                     unsigned long long readnum=0,mustnum=0;

                                                     FILE *ff=fopen(sendfilename.c_str(),"rb");
                                                     if(ff){
                                                                fseek(ff, 0, SEEK_END);
                                                                mustnum= ftell(ff);
                                                                fseek(ff, 0, SEEK_SET);
                                                               
                                                                if(header->state.rangebegin>=mustnum||header->state.rangeend<0||header->state.rangeend>mustnum){
                                                                        statecode=416;
                                                                        senddatastring="HTTP/1.1 416 Range Not Satisfiable\r\nDate:"+HTTP::getGmtTime()+"\r\nConnection: close\r\nCache-Control: max-age=0\r\nContent-length: 0\r\n\r\n";
                                                                        keeplive=false;
                                                                        if(isssl){
                                                                            asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                                        }else{
                                                                            asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                                        }
                                                                        fclose(ff);
                                                                        return;
                                                                }
                                                                
                                                                if(header->state.rangebegin>0){
                                                                    readnum=header->state.rangebegin;
                                                                
                                                                    if(header->state.rangeend>0){
                                                                        mustnum=header->state.rangeend;
                                                                    }      
                                                                    statecode=206;
                                                                } 
                                                            
                                                                if(statecode==206){
                                                                    senddatastring="HTTP/1.1 206 Partial Content\r\nDate:"+HTTP::getGmtTime()+"\r\nContent-Type: "+mimetype+"\r\n";
                                                                    if(header->state.keeplive){
                                                                        senddatastring.append("Connection: keep-alive\r\n");
                                                                        keeplive=true;
                                                                    }else{
                                                                        senddatastring.append("Connection: close\r\n");
                                                                        keeplive=false;
                                                                    }
                                                                    senddatastring.append("Accept-Ranges: bytes\r\n");
                                                                    senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\n");//+lm;
                                                                    senddatastring.append("Last-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\nCache-Control: max-age=691200\r\nAccept-Ranges: bytes\r\nContent-Range: bytes "+std::to_string(readnum)+"-"+std::to_string(mustnum-1)+"/"+std::to_string(mustnum)+"\r\nContent-length: "+std::to_string(mustnum-readnum)+"\r\n\r\n");
                                                                    
                                                                }else{
                                                                    senddatastring="HTTP/1.1 200 OK\r\nContent-Type: "+mimetype+"\r\nDate: "+HTTP::getGmtTime()+"\r\nLast-Modified: "+HTTP::getGmtTime((unsigned long long)fileinfo.st_mtime)+"\r\nETag: \""+etag+"\"\r\n";//
                                                                            
                                                                    if(header->state.keeplive){
                                                                        senddatastring.append("Connection: keep-alive\r\n");
                                                                        keeplive=true;
                                                                    }else{
                                                                        senddatastring.append("Connection: close\r\n");
                                                                        keeplive=false;
                                                                    }
                                                                    senddatastring.append("Accept-Ranges: bytes\r\n");
                                                                    senddatastring.append("Keep-Alive: timeout=5, max="+std::to_string(keeplivemax)+"\r\nCache-Control: max-age=691200\r\nContent-length: "+std::to_string(mustnum)+"\r\n\r\n");//+lm; 
                                                                    
                                                                }
                                                                // unsigned long long sendsize=0;
                                                            
                                                                if(isssl){
                                                                    asio::write(https_socket.front(), asio::buffer(senddatastring));
                                                                }else{
                                                                    asio::write(http_socket.front(),asio::buffer(senddatastring));
                                                                }
                                                                fseek(ff, readnum, SEEK_SET);
                                                                 
                                                                while(readnum<mustnum){
                                                                        memset(_data,0x00,2048);
                                                                        auto nread =fread(&_data[0], 1,2048, ff);
                                                                        
                                                                        if(isssl){
                                                                                asio::write(https_socket.front(), asio::buffer(_data,nread));
                                                                            }else{
                                                                                asio::write(http_socket.front(),asio::buffer(_data,nread));
                                                                            }
                                
                                                                        readnum+=nread;
                                                                }
                                                             fclose(ff);
                                                     }else{
                                                            
                                                            send(404,sendfilename);
                                                     }    


                                                 }
                                          }   
                                      
                }
}            