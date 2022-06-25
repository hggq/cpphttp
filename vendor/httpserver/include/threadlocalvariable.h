#pragma once
#ifndef HTTP_THREADLOCALVARIABLES_HPP
#define HTTP_THREADLOCALVARIABLES_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include <mysqlx/xdevapi.h>
#include "request.h"
#include <boost/function.hpp>
#include "threadlocalconfig.h"
#include "serverconfig.h"
namespace http {

typedef boost::function<void()> callback_t;
typedef boost::function<void(std::string)> echo_callback_t;
typedef boost::function<void(std::string&)> echo_callbackand_t;
typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
typedef boost::function<bool(std::list<std::string>&,size_t)> mysql_callbacksql_rollback;
typedef boost::function<std::string(http::OBJ_VALUE&)> method_callback_t;
typedef boost::function<std::string(http::clientpeer&)> www_method_call;
typedef boost::function<boost::function<std::string(http::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
typedef boost::function<boost::function<std::string(http::clientpeer&)>(std::string)> module_method_call;



method_callback_t loadview(std::string);
method_callback_t loadviewnotcall(std::string);
method_callback_t loadviewfetchnotcall(std::string);
method_callback_t loadviewobjcall(std::string);

www_method_call loadcontrol(std::string);
www_method_call modulesendfile(std::string);
www_method_call modulesenddata(std::string);//websocket使用

threadlocalconfig& getthreadlocalobj();
serverconfig& getserversysconfig();


}

#endif 