#ifndef ORM_DEFAULT_USER_H
#define ORM_DEFAULT_USER_H
#include "mysqlmodel.hpp" 
#include "userbase.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

 namespace orm {
		class User : public mysqlclientDB<User,userbase>{
		 public:
		 User(std::string dbtag);
		 User();
		};
};
#endif
