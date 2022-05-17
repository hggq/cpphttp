#ifndef ORM_DEFAULT_MODULEAUTH_H
#define ORM_DEFAULT_MODULEAUTH_H
#include "mysqlmodel.hpp" 
#include "moduleauthbase.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

 namespace orm {
		class Moduleauth : public mysqlclientDB<Moduleauth,moduleauthbase>{
		 public:
		 Moduleauth(std::string dbtag);
		 Moduleauth();
		};
};
#endif
