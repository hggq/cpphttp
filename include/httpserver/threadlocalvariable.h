#pragma once
#ifndef HTTP_THREADLOCALVARIABLE_HPP
#define HTTP_THREADLOCALVARIABLE_HPP

#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
//#include "http.hpp"
#include "request.h"
#include "modulemar.hpp"
#include "http_header.hpp"
// #include "mysqlplugin.hpp"
 #include "mysqlconfig.hpp"
// #include "mysqlpool.h"
#include "Clientpeer.h"
#include "mysqlproxyfun.h"

namespace HTTP {

typedef boost::function<void()> callback_t;
typedef boost::function<void(std::string)> echo_callback_t;
typedef boost::function<void(std::string&)> echo_callbackand_t;
typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
typedef boost::function<bool(std::list<std::string>&,size_t)> mysql_callbacksql_rollback;
typedef boost::function<std::string(HTTP::OBJ_VALUE&)> method_callback_t;
typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;

std::map<std::size_t,std::vector<std::string>>  sharedmethodchache;
std::map<std::size_t,method_callback_t>  sharedpathchache,controlpathchache;
std::mutex loadcontrolmtx,loadviewmtx,moudulecachemethod;


/////test/////
thread_local modulemar bbb;
thread_local http_header _http_header;

thread_local std::string _output;
thread_local std::string _outputtemp;
thread_local unsigned int _output_type;
thread_local bool loadmoduleinitcall=false;
thread_local HTTP::OBJ_VALUE vobj;
//thread_local wwwserver *_wwwhttpserver;
thread_local HTTP::clientpeer* _threadclientpeer;
thread_local std::map<std::string,std::map<std::string,std::string>> *_thishostsiteconfig;
thread_local std::string _thishostcontrolsopath;
thread_local std::string _thishostviewsopath;
thread_local std::vector<std::string> _header;

}

#endif 