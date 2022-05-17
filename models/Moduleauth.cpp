#include "mysqlmodel.hpp" 
#include "moduleauthbase.h"
#include "Moduleauth.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

	 
using namespace orm;	 

 Moduleauth::Moduleauth(std::string dbtag):mysqlclientDB(dbtag){}
	 Moduleauth::Moduleauth():mysqlclientDB(){}
	  
