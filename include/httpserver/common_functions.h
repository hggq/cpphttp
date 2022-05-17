#ifndef HTTP_COMMON_FUNCTIONS_H
#define HTTP_COMMON_FUNCTIONS_H

#include <boost/dll/import.hpp>
#include <boost/dll/shared_library.hpp>
#include <boost/function.hpp>
#include <iostream>
#include <mutex>
#include <string>
#include <map>
#include <set>
#include <string_view>
#include <thread>
#include <mysqlx/xdevapi.h>
//#include "http.hpp"
#include "request.h"
#include "modulemar.hpp"
#include "http_header.hpp"
#include "mysqlmodule.h"

namespace HTTP {

    //   std::mutex sessedit_mutex,sessselect_mutex;
    //   struct mysqllinkpool;
    //   std::map<size_t,mysqllinkpool> mysqldbpoolglobal;
    //   struct mysqlconnect_t;
    //   std::vector<mysqlconnect_t> getmysqlconfig(std::string filename);
         class mysqllinkpool;
         std::map<size_t,mysqllinkpool> mysqldbpoolglobal;
class clientpeer;   
typedef boost::function<void()> callback_t;
typedef boost::function<void(std::string)> echo_callback_t;
typedef boost::function<void(std::string&)> echo_callbackand_t;
typedef boost::function<mysqlx::RowResult(std::string&,size_t)> mysql_callbackand_t;
typedef boost::function<mysqlx::SqlResult(std::string&,size_t)> mysql_callbacksql_t;
typedef boost::function<std::string(HTTP::OBJ_VALUE&)> method_callback_t;
typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
 
std::string siteviewpath;
std::string sitecontrolpath;
std::map<std::size_t,std::vector<std::string>>  sharedmethodchache;
std::map<std::size_t,method_callback_t>  sharedpathchache,controlpathchache;

std::string httpempty(HTTP::OBJ_VALUE& a);
std::string echoempty(HTTP::OBJ_VALUE& a);


/////test/////
thread_local modulemar bbb;
thread_local http_header _http_header;

thread_local std::string _output;
thread_local std::string _outputtemp;
thread_local unsigned int _output_type;
thread_local bool loadmoduleinitcall=false;
thread_local HTTP::OBJ_VALUE vobj;
thread_local clientpeer *_threadclientpeer;
thread_local std::map<std::string,std::map<std::string,std::string>> *_thishostsiteconfig;
thread_local std::string _thishostcontrolsopath;
thread_local std::string _thishostviewsopath;
thread_local std::vector<std::string> _header;



method_callback_t loadview(std::string);
method_callback_t loadviewnotcall(std::string);
method_callback_t loadviewfetchnotcall(std::string);
method_callback_t loadviewobjcall(std::string);

method_callback_t loadcontrol(std::string);
method_callback_t modulesendfile(std::string);
method_callback_t modulesenddata(std::string);//websocket使用
std::map<std::string,modulemethod_callback_t> rendercallback;
std::map<std::string,echo_callback_t> _renderechocallback;
std::map<std::string,echo_callbackand_t> _renderechocallbackand;
std::map<std::string,mysql_callbackand_t> _mysqlselectcallback;
std::map<std::string,mysql_callbacksql_t> _mysqlplugineditcallback;
std::once_flag rendercallback_flag;

void send_data(std::string name);
void send_data(std::string &name);
void send_data(unsigned int statecode,std::string name);
void send_data(unsigned int statecode,std::string &name);

std::string httpempty(HTTP::OBJ_VALUE& a);
std::string echoempty(HTTP::OBJ_VALUE& a);

method_callback_t modulesendfile(std::string name);
method_callback_t modulesenddata(std::string name);
void echoassign(std::string name);

void echo_flush(std::string name);
void echoassignand(std::string& name);
void send_file(std::string name);

void header(std::string namevalue);
void header(std::string name,std::string value);

void setcookie(std::string name,std::string value,std::string path,unsigned int timeout);
void setcookie(std::string name,std::string &value,std::string path,unsigned int timeout);

HTTP::OBJ_VALUE getsession(std::string keyname);
void setsession(std::string keyname,std::string value);
void setsession(std::string keyname,std::string &value);
void setsession(HTTP::OBJ_VALUE &value);
std::string renderjsonfetchtosend(HTTP::OBJ_VALUE& b);
std::string renderjsonlocaltosend(HTTP::OBJ_VALUE& b);
method_callback_t sendjsoncall(std::string modulemethod);
 mysqlx::SqlResult domysqleditexecute(std::string &sql,size_t dbhash);
        mysqlx::RowResult domysqlexecute(std::string &sql,size_t dbhash);
void initcallbackmap();
method_callback_t viewmodulecreate(std::string module,std::string name);


method_callback_t controlmodulecreate(std::string module,std::string name,size_t tt);

method_callback_t loadcontrol(std::string modulemethod);
method_callback_t loadview(std::string modulemethod);
method_callback_t loadviewnotcall(std::string modulemethod);
std::string renderviewobjfetch(HTTP::OBJ_VALUE& b);

method_callback_t loadviewobjcall(std::string modulemethod);
std::string renderviewfetch(HTTP::OBJ_VALUE& a);
method_callback_t loadviewfetchnotcall(std::string modulemethod);
void viewmoduleclear(std::string module,std::string method);
void controlmoduleclear(std::string module,std::string method);

std::string loadmodule(std::string modulemethod);
std::string loadmodule(std::string modulemethod,HTTP::OBJ_VALUE &b);

void viewshow(std::string modulemethod);
std::string viewfetch(std::string modulemethod);
void viewshow(std::string modulemethod,HTTP::OBJ_VALUE &b);
std::string viewfetch(std::string modulemethod,HTTP::OBJ_VALUE &b);


void echo_json(std::string b);
void echo_json();
void echo_json(HTTP::OBJ_VALUE &obj);


   unsigned int get_controlversion();

     inline  long long intval(std::string &content);

void echo(std::string &b);
void echo(int b);
void echo(unsigned int b);
void echo(long long b);
void echo(unsigned long long b);
void echo(std::string &&b);
void echo(HTTP::OBJ_VALUE &b);
 



}
#endif 