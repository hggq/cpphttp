
#ifndef BOOST_DLL_HTTPSOCOMMON_API_HPP
#define BOOST_DLL_HTTPSOCOMMON_API_HPP

#include <string>
#include <string_view>
#include <boost/function.hpp>
#include <memory>
#include <list>
#include "request.h"
#include <mysqlx/xdevapi.h>
#include "Clientpeer.h"
 
using namespace HTTP;
 namespace HTTP { 
        
        class BOOST_SYMBOL_VISIBLE clientapi {
        public:
            clientapi(){}
         typedef boost::function<std::string(std::string)> http_callback_t;//header("");getheader setcookie() cookie
    typedef boost::function<void(std::string)> echo_callback_t;//header("");getheader setcookie() cookie
    typedef boost::function<void(std::string&)> echo_callbackand_t;
    typedef boost::function<int(const char *,int)> webscoket_callback_t;//websocket send
   // typedef boost::function<void(const char *,int)> webscoket_readcall_t;//websocket read
   typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
   typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
    typedef boost::function<boost::function<std::string(HTTP::clientpeer *,HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_peert;

    typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
    typedef boost::function<bool(std::list<std::string>&,size_t)> mysql_callbacksql_rollback;
 

             modulemethod_callback_t api_loadview;
             modulemethod_callback_t api_loadviewnotcall;
             modulemethod_callback_t api_loadviewfetchnotcall;
             modulemethod_callback_t api_loadviewobjcall;

             modulemethod_callback_t api_loadcontrol;
             modulemethod_callback_t api_sendjsoncall;
             modulemethod_callback_t api_modulesenddata;

             echo_callbackand_t api_echoassignand;

             echo_callback_t    api_echoassign;
             echo_callback_t    api_echo_flush;
             echo_callback_t    api_send_file;

             mysql_callbackand_t api_mysqlselect;
             mysql_callbacksql_t api_mysqledit;

             mysql_callbacksql_rollback api_mysqlcommit;   
     
             std::string output;
            //  /*static*/ thread_local  HTTP::OBJ_VALUE vobj;
               clientapi& operator<<(HTTP::OBJ_VALUE &a){
                    output.append(a.to_string());
                    return *this;
                }
             clientapi& operator<<(std::string &&a){
                    output.append(a);
                    return *this;
                }
                 clientapi& operator<<(std::string &a){
                    output.append(a);
                    return *this;
                }
                 clientapi& operator<<(std::string_view a){
                    output.append(a);
                    return *this;
                }
                clientapi& operator<<(char const *a){
                    output.append(a);
                    return *this;
                }
                clientapi& operator<<(float a){
                    output.append(std::to_string(a));
                    return *this;
                } 
                clientapi& operator<<(long long a){
                    output.append(std::to_string(a));
                    return *this;
                }
                 clientapi& operator<<(int a){
                    output.append(std::to_string(a));
                    return *this;
                }
                 clientapi& operator<<(short a){
                    output.append(std::to_string(a));
                    return *this;
                }
                clientapi& operator<<(unsigned long long a){
                    output.append(std::to_string(a));
                    return *this;
                }
                 clientapi& operator<<(unsigned int a){
                    output.append(std::to_string(a));
                    return *this;
                }
                clientapi& operator<<(double a){
               
                    output.append(std::to_string(a));
                    return *this;
                }
                template<typename T>
                clientapi& operator<<(T &a){
                    output.append(a.show());
                    return *this;
                }
            static clientapi* instance()
            {
                if (singleton== NULL)
                        singleton= new clientapi();
                return singleton;
            }
            static clientapi& get()
            {
                if (singleton== NULL)
                        singleton= new clientapi();
                return *singleton;
            }
            static clientapi* singleton;
            static clientapi* setclientapi(clientapi* p){
                    singleton=p;
                    return singleton;
            } 
        };
       
 }
#endif 