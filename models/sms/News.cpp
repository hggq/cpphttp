
#include "mysqlmodel.hpp" 
#include "sms/include/newsbase.h"
#include "sms/include/News.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

	 
using namespace orm::sms;	 

 News::News(std::string dbtag):mysqlclientDB(dbtag){}
	 News::News():mysqlclientDB(){}
	  
