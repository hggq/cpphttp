#ifndef ORM_DEFAULT_MARLIST_H
#define ORM_DEFAULT_MARLIST_H
#include "mysqlmodel.hpp" 
#include "marlistbase.h"

/* 如果此文件存在不会自动覆盖，没有则会自动生成。
*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */

 namespace orm {
		class Marlist : public mysqlclientDB<Marlist,marlistbase>{
		 public:
		 Marlist(std::string dbtag);
		 Marlist();
		};
};
#endif
