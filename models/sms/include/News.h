#ifndef ORM_SMS_NEWS_H
#define ORM_SMS_NEWS_H
#include "mysqlmodel.hpp" 
#include "sms/include/newsbase.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

 namespace orm {
	 namespace sms { 
		class News : public mysqlclientDB<News,newsbase>{
		 public:
		 News(std::string dbtag);
		 News();
		};
	 }
 };
#endif
