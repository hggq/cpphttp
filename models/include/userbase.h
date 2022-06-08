#ifndef ORM_DEFAULT_USERBASEMATA_H
#define ORM_DEFAULT_USERBASEMATA_H
/*
*This file is auto create from cli
*本文件为自动生成 Wed, 08 Jun 2022 04:31:40 GMT
***/
#include<iostream>
#include <cstdio>
#include <sstream>
#include <array>
#include <map> 
#include <vector>
#include <ctime>
#include <array>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <mysqlx/xdevapi.h> 
namespace orm { 
    
struct userbase
{
    struct meta{
    unsigned  int uid= 0; //
 std::string name; //显示名字
 std::string loginname; //登录名
 std::string loginpwd; //登录密码
 std::string phone; //电话
 long long regtime=0; //时间戳
 char level=0; //权限等级
 float prices=0.00; //
 } data;
 std::vector<userbase::meta> record;
std::string _rmstag="default";//this value must be default or tag value, tag in mysqlconnect config file .
std::vector<unsigned char> _keypos{0x00};
mysqlx::Row _row;
std::vector<userbase::meta>::iterator begin(){     return record.begin(); }
std::vector<userbase::meta>::iterator end(){     return record.end(); }
std::vector<userbase::meta>::const_iterator begin() const{     return record.begin(); }
std::vector<userbase::meta>::const_iterator end() const{     return record.end(); }
const std::array<std::string,8> colnames={"uid","name","loginname","loginpwd","phone","regtime","level","prices"};
const std::array<unsigned char,8> colnamestype= {1,30,30,30,30,1,1,20};
std::string tablename="user";
std::string modelname="User";

	  unsigned char findcolpos(std::string coln){
		    unsigned char  bi=coln[0];
            char colpospppc;
	         if(bi<91&&bi>64){
				bi+=32;
			}
            switch(coln[0]){


         case 'l':
 switch(coln.size()){  
case 5:
   	 return 6;
break;
case 8:
   	 return 3;
break;
case 9:
   	 return 2;
break;
 }
 break;
case 'n':
   	 return 1;
break;
case 'p':
 switch(coln.size()){  
case 5:
   	 return 4;
break;
case 6:
   	 return 7;
break;
 }
 break;
case 'r':
   	 return 5;
break;
case 'u':
   	 return 0;
break;

             }
             return 255;
           }
         
    int size(){ return record.size(); }   

    std::string getPKname(){ 
       return "uid";
}

      void _setColnamevalue(){
          userbase::meta metatemp;   
         for(unsigned char i=0;i<_keypos.size();i++){
                 switch(_keypos[i]){
        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.uid=_row[i].get<unsigned>();
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.name=(std::string)_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.loginname=(std::string)_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.loginpwd=(std::string)_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.phone=(std::string)_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.regtime=_row[i].get<int64_t>();
		 } 
			 break;
		case 6: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.level=_row[i].get<unsigned>();
		 } 
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.prices=( double )_row[i];
		 } 
			 break;

                 }

                 if(i>210){
                     break;
                 }
          }
          data=metatemp;
          record.emplace_back(metatemp);   
   } 
         void _addnewrowvalue(){
           userbase::meta metatemp;   

          for(unsigned char i=0;i<_keypos.size();i++){
 
                 switch(_keypos[i]){

        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.uid=_row[i].get<unsigned>();
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.name=(std::string)_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.loginname=(std::string)_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.loginpwd=(std::string)_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.phone=(std::string)_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.regtime=_row[i].get<int64_t>();
		 } 
			 break;
		case 6: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.level=_row[i].get<unsigned>();
		 } 
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.prices=( double )_row[i];
		 } 
			 break;

                  }
                 if(i>210){
                     break;
                 }
          }
           record.emplace_back(std::move(metatemp)); 
   } 

  inline  std::string stringaddslash(std::string &content){
        std::string temp;
        for(int i=0;i<content.size();i++){
            if(content[i]=='\''){
                temp.append("\\'");
                continue;
            }else if(content[i]=='"'){
                temp.append("\\\"");
                continue;
            }
            temp.push_back(content[i]);
        }
        return std::move(temp);
   }  
  inline  std::string jsonaddslash(std::string &content){
        std::string temp;
        for(int i=0;i<content.size();i++){
            if(content[i]=='"'){
                temp.append("\\\"");
                continue;
            }
            temp.push_back(content[i]);
        }
        return std::move(temp);
   }  

   std::string _makeinsertsql(){
       int j=0;
                std::ostringstream tempsql;
                tempsql<<"INSERT INTO ";
                    tempsql<<tablename;
                   tempsql<<" (";
                    for(;j<colnames.size();j++){
                            if(j>0){
                                tempsql<<"`,`";
                            }else{
                                tempsql<<"`";
                            }
                            tempsql<<colnames[j];
                    }
                    if(j>0){
                        tempsql<<"`";
                    }
            tempsql<<") VALUES (";

        if(data.uid==0){
tempsql<<"null";
 }else{ 
	tempsql<<std::to_string(data.uid);
}
tempsql<<",'"<<stringaddslash(data.name)<<"'";
tempsql<<",'"<<stringaddslash(data.loginname)<<"'";
tempsql<<",'"<<stringaddslash(data.loginpwd)<<"'";
tempsql<<",'"<<stringaddslash(data.phone)<<"'";
if(data.regtime==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.regtime);
}
if(data.level==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.level);
}
if(data.prices==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.prices);
}
tempsql<<")";

     
       return tempsql.str();
   }     
    std::string _makeupdatesql(std::string fileld){
       int j=0;
            std::ostringstream tempsql;
                 tempsql<<"UPDATE ";
                 tempsql<<tablename;
                 tempsql<<" SET ";

            bool isall=false;
            if(fileld.empty()){
                isall=true;
            }
            if(isall){

        if(data.uid==0){
	tempsql<<"`uid`=0";
 }else{ 
	tempsql<<"`uid`="<<std::to_string(data.uid);
}
tempsql<<",`name`='"<<stringaddslash(data.name)<<"'";
tempsql<<",`loginname`='"<<stringaddslash(data.loginname)<<"'";
tempsql<<",`loginpwd`='"<<stringaddslash(data.loginpwd)<<"'";
tempsql<<",`phone`='"<<stringaddslash(data.phone)<<"'";
if(data.regtime==0){
	tempsql<<",`regtime`=0";
 }else{ 
	tempsql<<",`regtime`="<<std::to_string(data.regtime);
}
if(data.level==0){
	tempsql<<",`level`=0";
 }else{ 
	tempsql<<",`level`="<<std::to_string(data.level);
}
if(data.prices==0){
	tempsql<<",`prices`=0";
 }else{ 
	tempsql<<",`prices`="<<std::to_string(data.prices);
}
 }else{ 

     
  int jj=0;
                  std::string keyname;
                  std::vector<unsigned char> keypos;
                  for(;jj<fileld.size();jj++){
                        if(fileld[jj]==','){
                               keypos.emplace_back(findcolpos(keyname)); 
                               keyname.clear();
                             continue;   
                        }
                        if(fileld[jj]==0x20){

                             continue;   
                        }
                        keyname.push_back(fileld[jj]);

                  }  
                 if(keyname.size()>0){
                                keypos.emplace_back(findcolpos(keyname)); 
                                keyname.clear();
                 }
                 for(jj=0;jj<keypos.size();jj++){
                       switch(keypos[jj]){

         case 0:
 if(jj>0){ tempsql<<","; } 
if(data.uid==0){
	tempsql<<"`uid`=0";
 }else{ 
	tempsql<<"`uid`="<<std::to_string(data.uid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`name`='"<<stringaddslash(data.name)<<"'";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`loginname`='"<<stringaddslash(data.loginname)<<"'";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`loginpwd`='"<<stringaddslash(data.loginpwd)<<"'";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`phone`='"<<stringaddslash(data.phone)<<"'";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(data.regtime==0){
	tempsql<<",`regtime`=0";
 }else{ 
	tempsql<<",`regtime`="<<std::to_string(data.regtime);
}
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
if(data.level==0){
	tempsql<<",`level`=0";
 }else{ 
	tempsql<<",`level`="<<std::to_string(data.level);
}
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
if(data.prices==0){
	tempsql<<",`prices`=0";
 }else{ 
	tempsql<<",`prices`="<<std::to_string(data.prices);
}
 break;

     
                  default:
                                ;
                     }
                 }   

            }        

        return std::move(tempsql.str());
   } 
   std::string datatojson(){
       std::ostringstream tempsql;

        tempsql<<"{";
if(data.uid==0){
	tempsql<<"\"uid\":0";
 }else{ 
	tempsql<<"\"uid\":"<<std::to_string(data.uid);
}
tempsql<<",\"name\":\""<<utf8_to_jsonstring(data.name);
tempsql<<"\"";
tempsql<<",\"loginname\":\""<<utf8_to_jsonstring(data.loginname);
tempsql<<"\"";
tempsql<<",\"loginpwd\":\""<<utf8_to_jsonstring(data.loginpwd);
tempsql<<"\"";
tempsql<<",\"phone\":\""<<utf8_to_jsonstring(data.phone);
tempsql<<"\"";
if(data.regtime==0){
	tempsql<<",\"regtime\":0";
 }else{ 
	tempsql<<",\"regtime\":"<<std::to_string(data.regtime);
}
if(data.level==0){
	tempsql<<",\"level\":0";
 }else{ 
	tempsql<<",\"level\":"<<std::to_string(data.level);
}
if(data.prices==0){
	tempsql<<",\"prices\":0";
 }else{ 
	tempsql<<",\"prices\":"<<std::to_string(data.prices);
}
tempsql<<"}";

     
     return std::move(tempsql.str());             
   }   
   
   std::string datatojson(std::string fileld){
       std::ostringstream tempsql;
            std::string keyname;
            unsigned char jj=0;
                  std::vector<unsigned char> keypos;
                  if(fileld.size()>0){
                    for(;jj<fileld.size();jj++){
                            if(fileld[jj]==','){
                                keypos.emplace_back(findcolpos(keyname)); 
                                keyname.clear();
                                continue;   
                            }
                            if(fileld[jj]==0x20){

                                continue;   
                            }
                            keyname.push_back(fileld[jj]);

                    }  
                    if(keyname.size()>0){
                                    keypos.emplace_back(findcolpos(keyname)); 
                                    keyname.clear();
                    }
                 }else{
                     for(jj=0;jj<colnames.size();jj++){
                         keypos.emplace_back(jj); 
                     }
                 }
                 tempsql<<"{";
                 for(jj=0;jj<keypos.size();jj++){
                       switch(keypos[jj]){
         case 0:
 if(jj>0){ tempsql<<","; } 
if(data.uid==0){
	tempsql<<"\"uid\":0";
 }else{ 
	tempsql<<"\"uid\":"<<std::to_string(data.uid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(data.name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginname\":\""<<utf8_to_jsonstring(data.loginname)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginpwd\":\""<<utf8_to_jsonstring(data.loginpwd)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"phone\":\""<<utf8_to_jsonstring(data.phone)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(data.regtime==0){
	tempsql<<"\"regtime\":0";
 }else{ 
	tempsql<<"\"regtime\":"<<std::to_string(data.regtime);
}
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
if(data.level==0){
	tempsql<<"\"level\":0";
 }else{ 
	tempsql<<"\"level\":"<<std::to_string(data.level);
}
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
if(data.prices==0){
	tempsql<<"\"prices\":0";
 }else{ 
	tempsql<<"\"prices\":"<<std::to_string(data.prices);
}
 break;

                             default:
                                ;
                     }
                 }   
      tempsql<<"}";  
     return std::move(tempsql.str());             
   }   
   
   std::string tojson(std::string fileld=""){
       std::ostringstream tempsql;
            std::string keyname;
            unsigned char jj=0;
                  std::vector<unsigned char> keypos;
                  if(fileld.size()>0){
                    for(;jj<fileld.size();jj++){
                            if(fileld[jj]==','){
                                keypos.emplace_back(findcolpos(keyname)); 
                                keyname.clear();
                                continue;   
                            }
                            if(fileld[jj]==0x20){

                                continue;   
                            }
                            keyname.push_back(fileld[jj]);

                    }  
                    if(keyname.size()>0){
                                    keypos.emplace_back(findcolpos(keyname)); 
                                    keyname.clear();
                    }
                 }else{
                     for(jj=0;jj<colnames.size();jj++){
                         keypos.emplace_back(jj); 
                     }
                 }
                tempsql<<"[";
              for(int n=0;n<record.size();n++){
                  if(n>0){
                      tempsql<<",{";
                  }else{
                      tempsql<<"{";
                  }  
                 
                 for(jj=0;jj<keypos.size();jj++){
                       switch(keypos[jj]){
         case 0:
 if(jj>0){ tempsql<<","; } 
if(record[n].uid==0){
	tempsql<<"\"uid\":0";
 }else{ 
	tempsql<<"\"uid\":"<<std::to_string(record[n].uid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(record[n].name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginname\":\""<<utf8_to_jsonstring(record[n].loginname)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginpwd\":\""<<utf8_to_jsonstring(record[n].loginpwd)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"phone\":\""<<utf8_to_jsonstring(record[n].phone)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(record[n].regtime==0){
	tempsql<<"\"regtime\":0";
 }else{ 
	tempsql<<"\"regtime\":"<<std::to_string(record[n].regtime);
}
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
if(record[n].level==0){
	tempsql<<"\"level\":0";
 }else{ 
	tempsql<<"\"level\":"<<std::to_string(record[n].level);
}
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
if(record[n].prices==0){
	tempsql<<"\"prices\":0";
 }else{ 
	tempsql<<"\"prices\":"<<std::to_string(record[n].prices);
}
 break;

                             default:
                                ;
                     }
                 }   
      tempsql<<"}";  
            }
      tempsql<<"]";
     return std::move(tempsql.str());             
   }   
   
   std::string tojson(std::function<bool(std::string&,meta&)> func,std::string fileld=""){
       std::ostringstream tempsql;
            std::string keyname;
            unsigned char jj=0;
                  std::vector<unsigned char> keypos;
                  if(fileld.size()>0){
                    for(;jj<fileld.size();jj++){
                            if(fileld[jj]==','){
                                keypos.emplace_back(findcolpos(keyname)); 
                                keyname.clear();
                                continue;   
                            }
                            if(fileld[jj]==0x20){

                                continue;   
                            }
                            keyname.push_back(fileld[jj]);

                    }  
                    if(keyname.size()>0){
                                    keypos.emplace_back(findcolpos(keyname)); 
                                    keyname.clear();
                    }
                 }else{
                     for(jj=0;jj<colnames.size();jj++){
                         keypos.emplace_back(jj); 
                     }
                 }
                tempsql<<"[";
              for(int n=0;n<record.size();n++){
                 keyname.clear();
                 if(func(keyname,record[n])){ 
                            if(n>0){
                                tempsql<<",{";
                            }else{
                                tempsql<<"{";
                            } 
                            tempsql<<keyname;
                 }else{
                    continue;
                 } 
                  
                 for(jj=0;jj<keypos.size();jj++){
                        
                       switch(keypos[jj]){
         case 0:
 if(jj>0){ tempsql<<","; } 
if(record[n].uid==0){
	tempsql<<"\"uid\":0";
 }else{ 
	tempsql<<"\"uid\":"<<std::to_string(record[n].uid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(record[n].name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginname\":\""<<utf8_to_jsonstring(record[n].loginname)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"loginpwd\":\""<<utf8_to_jsonstring(record[n].loginpwd)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"phone\":\""<<utf8_to_jsonstring(record[n].phone)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(record[n].regtime==0){
	tempsql<<"\"regtime\":0";
 }else{ 
	tempsql<<"\"regtime\":"<<std::to_string(record[n].regtime);
}
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
if(record[n].level==0){
	tempsql<<"\"level\":0";
 }else{ 
	tempsql<<"\"level\":"<<std::to_string(record[n].level);
}
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
if(record[n].prices==0){
	tempsql<<"\"prices\":0";
 }else{ 
	tempsql<<"\"prices\":"<<std::to_string(record[n].prices);
}
 break;

                             default:
                                ;
                     }
                 }   
      tempsql<<"}";  
            }
      tempsql<<"]";
     return std::move(tempsql.str());             
   }   
   long long getPK(){  return data.uid; } 
 void setPK(long long val){  data.uid=val;} 
unsigned  int  getUid(){  return data.uid; } 
 void setUid(unsigned  int  val){  data.uid=val;} 

std::string getName(){  return data.name; } 
 void setName(std::string val){  data.name=val;} 
std::string& getRefName(){  return std::ref(data.name); } 
 void setName(std::string &val){  data.name=val;} 

std::string getLoginname(){  return data.loginname; } 
 void setLoginname(std::string val){  data.loginname=val;} 
std::string& getRefLoginname(){  return std::ref(data.loginname); } 
 void setLoginname(std::string &val){  data.loginname=val;} 

std::string getLoginpwd(){  return data.loginpwd; } 
 void setLoginpwd(std::string val){  data.loginpwd=val;} 
std::string& getRefLoginpwd(){  return std::ref(data.loginpwd); } 
 void setLoginpwd(std::string &val){  data.loginpwd=val;} 

std::string getPhone(){  return data.phone; } 
 void setPhone(std::string val){  data.phone=val;} 
std::string& getRefPhone(){  return std::ref(data.phone); } 
 void setPhone(std::string &val){  data.phone=val;} 

 long long  getRegtime(){  return data.regtime; } 
 void setRegtime( long long  val){  data.regtime=val;} 

 int  getLevel(){  return data.level; } 
 void setLevel( int  val){  data.level=val;} 

 double  getPrices(){  return data.prices; } 
 void setPrices( double  val){  data.prices=val;} 

userbase::meta getnewData(){
 	 struct meta newdata;
	 return std::move(newdata); 
} 
userbase::meta getData(){
 	 return data; 
} 
std::vector<userbase::meta> getRecord(){
 	 return record; 
} 

    template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true >  
    std::vector<T> getCol(std::string keyname){
         std::vector<T> a;
         unsigned char kpos;
         kpos=findcolpos(keyname);
        for(auto &iter:record){
                switch(kpos){

   case 0: 
 	 a.emplace_back(iter.uid);
	 break;
case 5: 
 	 a.emplace_back(iter.regtime);
	 break;
case 6: 
 	 a.emplace_back(iter.level);
	 break;

          }
        }
        return a;
    }
    
    template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true >    
    std::vector<T> getCol(std::string keyname){
        std::vector<T> a;
         unsigned char kpos;
         kpos=findcolpos(keyname);
        for(auto &iter:record){
                switch(kpos){

   case 7: 
 	 a.emplace_back(iter.prices);
	 break;

    }
            }
            return a;
        }  
    
    template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true >   
    T getVal(std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
      
                switch(kpos){

   case 0: 
 	 return data.uid;
	 break;
case 5: 
 	 return data.regtime;
	 break;
case 6: 
 	 return data.level;
	 break;

    }
            return 0;
        }  
    
     template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true > 
    T getVal(userbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
       
                switch(kpos){

   case 0: 
 	 return iter.uid;
	 break;
case 5: 
 	 return iter.regtime;
	 break;
case 6: 
 	 return iter.level;
	 break;

    }
            return 0;
        }  
    
        template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
        T getVal(std::string keyname){
            
            unsigned char kpos;
            kpos=findcolpos(keyname);
        
            switch(kpos){

    case 7: 
 	 return data.prices;
	 break;

    }
            return 0.0;
        }  
    
     template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
    T getVal(userbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
         
                switch(kpos){

   case 7: 
 	 return iter.prices;
	 break;

    }
            return 0.0;
        }  
    
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
        
                switch(kpos){

   case 1: 
 	 return data.name;
	 break;
case 2: 
 	 return data.loginname;
	 break;
case 3: 
 	 return data.loginpwd;
	 break;
case 4: 
 	 return data.phone;
	 break;

  }
        return "";
    }  
   
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(userbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   case 1: 
 	 return iter.name;
	 break;
case 2: 
 	 return iter.loginname;
	 break;
case 3: 
 	 return iter.loginpwd;
	 break;
case 4: 
 	 return iter.phone;
	 break;

    }
            return "";
        }  
     
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true >   
    std::vector<std::string> getCol(std::string keyname){
        std::vector<std::string> a;
         unsigned char kpos;
        kpos=findcolpos(keyname);
 
         for(auto &iter:record){
                switch(kpos){

   case 1: 
 	 a.emplace_back(iter.name);
	 break;
case 2: 
 	 a.emplace_back(iter.loginname);
	 break;
case 3: 
 	 a.emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a.emplace_back(iter.phone);
	 break;

   }
        }       

        return a;
    }  
    std::string getstrCol(std::string keyname,bool isyinhao=false){
        std::ostringstream a;
             unsigned char kpos;
        kpos=findcolpos(keyname);
  
         int j=0;
         if(isyinhao&&record.size()>0){
             a<<'"';
         }
         for(auto &iter:record){
                if(j>0){
                    if(isyinhao){
                        a<<"\",\"";
                    }else{
                        a<<',';    
                    }
                }
                 switch(kpos){

   case 0: 
 	 a<<std::to_string(iter.uid);
	 break;
case 1: 
 	 if(isyinhao){ a<<jsonaddslash(iter.name); 
	 }else{
	 a<<iter.name;
	 }
	 break;
case 2: 
 	 if(isyinhao){ a<<jsonaddslash(iter.loginname); 
	 }else{
	 a<<iter.loginname;
	 }
	 break;
case 3: 
 	 if(isyinhao){ a<<jsonaddslash(iter.loginpwd); 
	 }else{
	 a<<iter.loginpwd;
	 }
	 break;
case 4: 
 	 if(isyinhao){ a<<jsonaddslash(iter.phone); 
	 }else{
	 a<<iter.phone;
	 }
	 break;
case 5: 
 	 a<<std::to_string(iter.regtime);
	 break;
case 6: 
 	 a<<std::to_string(iter.level);
	 break;
case 7: 
 	 a<<std::to_string(iter.prices);
	 break;

    }
                j++;
        } 
        if(isyinhao&&j>0){
             a<<'"';
        }      
        return a.str();
    }
    
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>     
    std::map<std::string,std::string> getCols(std::string keyname,std::string valname){
        std::map<std::string,std::string> a;
        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         std::string ktemp,vtemp;
         for(auto &iter:record){
                
                switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	 } 
		 switch(vpos){ 
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;

        }
                    a.emplace(ktemp,vtemp);
            }       
            return a;
        } 

  template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>    
  std::map<std::string,U> getCols(std::string keyname,std::string valname){
        std::map<std::string,U> a;
        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         std::string ktemp;
         U vtemp;
         for(auto &iter:record){
                
                switch(kpos){
 
       case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	 } 
        switch(vpos){ 
case 7: 
 	 vtemp=iter.prices;
	 break;

            }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    } 
  template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>       
  std::map<T,U> getCols(std::string keyname,std::string valname){
        std::map<T,U> a;
        unsigned char kpos,vpos;
         kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         T ktemp;
         U vtemp;
         for(auto &iter:record){
                
                switch(kpos){
 
       case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	 } 
 		   switch(vpos){ 
case 7: 
 	 vtemp=iter.prices;
	 break;

             }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    }  
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>      
    std::map<T,std::string> getCols(std::string keyname,std::string valname){
        std::map<T,std::string> a;
                unsigned char kpos,vpos;
         kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             std::string vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;

  }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    }     
     template<typename T,typename U, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>       
    std::map<std::string,U> getCols(std::string keyname,std::string valname){
        std::map<std::string,U> a;
             unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             std::string  ktemp;
             U  vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;

                 }

             
                a.emplace(ktemp,vtemp);
        }       
        return a;
    }  
    template<typename T,typename U, typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>   
    std::map<T,U> getCols(std::string keyname,std::string valname){
        std::map<T,U> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;

                   }

                    a.emplace(ktemp,vtemp);
            }       

            return a;
        }   
    template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true >         
    std::map<T,meta> getmapRows(std::string keyname){
        std::map<T,meta> a;

            unsigned char kpos;
         kpos=findcolpos(keyname);
 
          //   long long ktemp;
        
         for(auto &iter:record){
                switch(kpos){

   case 0: 
 	 a.emplace(iter.uid,iter);
	 break;
case 5: 
 	 a.emplace(iter.regtime,iter);
	 break;
case 6: 
 	 a.emplace(iter.level,iter);
	 break;

                }
        }       
        return a;
    }     
   template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true >    
   std::map<std::string,meta> getmapRows(std::string keyname){
        std::map<std::string,meta> a;

         unsigned char kpos;
 
        kpos=findcolpos(keyname);
    

        //std::string ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 a.emplace(iter.name,iter);
	 break;
case 2: 
 	 a.emplace(iter.loginname,iter);
	 break;
case 3: 
 	 a.emplace(iter.loginpwd,iter);
	 break;
case 4: 
 	 a.emplace(iter.phone,iter);
	 break;

                }

                //a.emplace(ktemp,iter);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>  
    std::vector<std::pair<std::string,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<std::string,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             std::string ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }
 switch(vpos){
case 7: 
 	 vtemp=iter.prices;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
  template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>    
  std::vector<std::pair<T,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<T,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }
 switch(vpos){
case 7: 
 	 vtemp=iter.prices;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
  template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>    
  std::vector<std::pair<T,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<T,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
  template<typename T,typename U, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>     
  std::vector<std::pair<T,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<T,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
  template<typename T,typename U, typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>    
  std::vector<std::pair<T,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<T,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
  template<typename T,typename U, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true>     
  std::vector<std::pair<T,U>> getvecCols(std::string keyname,std::string valname){
        std::vector<std::pair<T,U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             T ktemp;
             U vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;

                   }

                    a.emplace_back(ktemp,vtemp);
            }       

            return a;
        }   
    template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true >   
    std::vector<std::pair<T,meta>> getvecRows(std::string keyname){
        std::vector<std::pair<T,meta>> a;

         unsigned char kpos;
 
        kpos=findcolpos(keyname);
    

       // T ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 a.emplace_back(iter.uid,iter);
	 break;
case 5: 
 	 a.emplace_back(iter.regtime,iter);
	 break;
case 6: 
 	 a.emplace_back(iter.level,iter);
	 break;

                }

                
        }       

        return a;
    }
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true >  
    std::vector<std::pair<std::string,meta>> getvecRows(std::string keyname){
        std::vector<std::pair<std::string,meta>> a;

         unsigned char kpos;
        kpos=findcolpos(keyname);
        //std::string ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 a.emplace_back(iter.name,iter);
	 break;
case 2: 
 	 a.emplace_back(iter.loginname,iter);
	 break;
case 3: 
 	 a.emplace_back(iter.loginpwd,iter);
	 break;
case 4: 
 	 a.emplace_back(iter.phone,iter);
	 break;

                }

                
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_floating_point<D>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        
        T ktemp;
        U vtemp;
        //D vtemp;
         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_integral_v<D>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
        //D vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_same<D,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_floating_point<D>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_integral_v<D>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<D,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_floating_point<D>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        
        T ktemp;
        U vtemp;
        //D vtemp;
         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_integral_v<D>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
        //D vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true, typename std::enable_if<std::is_same<D,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.uid;
	 break;
case 5: 
 	 vtemp=iter.regtime;
	 break;
case 6: 
 	 vtemp=iter.level;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_floating_point<D>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_integral_v<D>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<D,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<D>>> getgroupCols(std::string keyname,std::string valname,std::string dataname){
        std::map<T,std::map<U,std::vector<D>>> a;

        unsigned char kpos,vpos,dpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        dpos=findcolpos(dataname);
        T ktemp;
        U vtemp;
       // D dtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.loginname;
	 break;
case 3: 
 	 vtemp=iter.loginpwd;
	 break;
case 4: 
 	 vtemp=iter.phone;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 7: 
 	 a[ktemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.loginname);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.loginpwd);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.phone);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_floating_point<U>::value,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 7: 
 	 a[ktemp].emplace_back(iter.prices);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>    
  std::map<T,std::vector<U>> getgroupCols(std::string keyname,std::string valname){
        std::map<T,std::vector<U>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);

        T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.uid);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.regtime);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.level);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename std::enable_if<std::is_integral_v<T>,bool>::type = true>    
  std::map<T,std::vector<meta>> getgroupRows(std::string keyname){
        std::map<T,std::vector<meta>> a;

        unsigned char kpos;
        kpos=findcolpos(keyname);

        //T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 a[iter.uid].emplace_back(iter);
	 break;
case 5: 
 	 a[iter.regtime].emplace_back(iter);
	 break;
case 6: 
 	 a[iter.level].emplace_back(iter);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true>    
  std::map<T,std::vector<meta>> getgroupRows(std::string keyname){
        std::map<T,std::vector<meta>> a;

        unsigned char kpos;
        kpos=findcolpos(keyname);

        //T ktemp;
        //U vtemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 a[iter.name].emplace_back(iter);
	 break;
case 2: 
 	 a[iter.loginname].emplace_back(iter);
	 break;
case 3: 
 	 a[iter.loginpwd].emplace_back(iter);
	 break;
case 4: 
 	 a[iter.phone].emplace_back(iter);
	 break;

                   }
                //a[ktemp].emplace_back(vtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename D,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true, typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<meta>>> getgroupRows(std::string keyname,std::string valname){
        std::map<T,std::map<U,std::vector<meta>>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        T ktemp;

         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.loginname].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.loginpwd].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.phone].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<meta>>> getgroupRows(std::string keyname,std::string valname){
        std::map<T,std::map<U,std::vector<meta>>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        T ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 1: 
 	 ktemp=iter.name;
	 break;
case 2: 
 	 ktemp=iter.loginname;
	 break;
case 3: 
 	 ktemp=iter.loginpwd;
	 break;
case 4: 
 	 ktemp=iter.phone;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.uid].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.regtime].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.level].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<U>,bool>::type = true,typename std::enable_if<std::is_integral_v<U>,bool>::type = true>    
  std::map<T,std::map<U,std::vector<meta>>> getgroupRows(std::string keyname,std::string valname){
        std::map<T,std::map<U,std::vector<meta>>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        T ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.uid].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.regtime].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.level].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
    template<typename T,typename U,typename std::enable_if<std::is_integral_v<T>,bool>::type = true,typename std::enable_if<std::is_same<U,std::string>::value,bool>::type = true>    
  std::map<T,std::map<U,std::vector<meta>>> getgroupRows(std::string keyname,std::string valname){
        std::map<T,std::map<U,std::vector<meta>>> a;

        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
        T ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   case 0: 
 	 ktemp=iter.uid;
	 break;
case 5: 
 	 ktemp=iter.regtime;
	 break;
case 6: 
 	 ktemp=iter.level;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.loginname].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.loginpwd].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.phone].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
};

}
#endif
   