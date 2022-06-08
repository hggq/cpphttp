#ifndef ORM_DEFAULT_MODULEAUTHBASEMATA_H
#define ORM_DEFAULT_MODULEAUTHBASEMATA_H
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
    
struct moduleauthbase
{
    struct meta{
     int mid= 0; //
 std::string name; //名称
 std::string siteurl; //url
unsigned  long long sort=0; //排序
   std::string addtime; //添加时间
   std::string dsssggg; //
   std::string testdatetime; //
 std::string testenum="已婚"; //
 float score=0; //
 float price=0.00; //
 } data;
 std::vector<moduleauthbase::meta> record;
std::string _rmstag="default";//this value must be default or tag value, tag in mysqlconnect config file .
std::vector<unsigned char> _keypos{0x00};
mysqlx::Row _row;
std::vector<moduleauthbase::meta>::iterator begin(){     return record.begin(); }
std::vector<moduleauthbase::meta>::iterator end(){     return record.end(); }
std::vector<moduleauthbase::meta>::const_iterator begin() const{     return record.begin(); }
std::vector<moduleauthbase::meta>::const_iterator end() const{     return record.end(); }
const std::array<std::string,10> colnames={"mid","name","siteurl","sort","addtime","dsssggg","testdatetime","testenum","score","price"};
const std::array<unsigned char,10> colnamestype= {1,30,30,1,60,61,60,30,20,20};
std::string tablename="moduleauth";
std::string modelname="Moduleauth";

	  unsigned char findcolpos(std::string coln){
		    unsigned char  bi=coln[0];
            char colpospppc;
	         if(bi<91&&bi>64){
				bi+=32;
			}
            switch(coln[0]){


         case 'a':
   	 return 4;
break;
case 'd':
   	 return 5;
break;
case 'm':
   	 return 0;
break;
case 'n':
   	 return 1;
break;
case 'p':
   	 return 9;
break;
case 's':
 switch(coln.size()){  
case 4:
   	 return 3;
break;
case 5:
   	 return 8;
break;
case 7:
   	 return 2;
break;
 }
 break;
case 't':
 switch(coln.size()){  
case 8:
   	 return 7;
break;
case 12:
   	 return 6;
break;
 }
 break;

             }
             return 255;
           }
         
    int size(){ return record.size(); }   

    std::string getPKname(){ 
       return "mid";
}

      void _setColnamevalue(){
          moduleauthbase::meta metatemp;   
         for(unsigned char i=0;i<_keypos.size();i++){
                 switch(_keypos[i]){
        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.mid=_row[i].get<unsigned>();
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.name=(std::string)_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.siteurl=(std::string)_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.sort=_row[i].get<uint64_t>();
		 } 
			 break;
		case 4: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>7){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                          if(datetimekey[4]<10){
                              datetime<<" 0"<<std::to_string(datetimekey[4]);
                          }else{
                              datetime<<" "<<std::to_string(datetimekey[4]);
                          }
                          if(datetimekey[5]<10){
                              datetime<<":0"<<std::to_string(datetimekey[5]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[5]);
                          }
                          if(datetimekey[6]<10){
                              datetime<<":0"<<std::to_string(datetimekey[6]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[6]);
                          }
                         
                 metatemp.addtime=datetime.str();
}
			 break;
		case 5: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>4){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                         
                         
                 metatemp.dsssggg=datetime.str();
}
			 break;
		case 6: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>7){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                          if(datetimekey[4]<10){
                              datetime<<" 0"<<std::to_string(datetimekey[4]);
                          }else{
                              datetime<<" "<<std::to_string(datetimekey[4]);
                          }
                          if(datetimekey[5]<10){
                              datetime<<":0"<<std::to_string(datetimekey[5]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[5]);
                          }
                          if(datetimekey[6]<10){
                              datetime<<":0"<<std::to_string(datetimekey[6]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[6]);
                          }
                         
                 metatemp.testdatetime=datetime.str();
}
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.testenum=(std::string)_row[i];
		 } 
			 break;
		case 8: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.score=( double )_row[i];
		 } 
			 break;
		case 9: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.price=( double )_row[i];
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
           moduleauthbase::meta metatemp;   

          for(unsigned char i=0;i<_keypos.size();i++){
 
                 switch(_keypos[i]){

        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.mid=_row[i].get<unsigned>();
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.name=(std::string)_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.siteurl=(std::string)_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.sort=_row[i].get<uint64_t>();
		 } 
			 break;
		case 4: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>7){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                          if(datetimekey[4]<10){
                              datetime<<" 0"<<std::to_string(datetimekey[4]);
                          }else{
                              datetime<<" "<<std::to_string(datetimekey[4]);
                          }
                          if(datetimekey[5]<10){
                              datetime<<":0"<<std::to_string(datetimekey[5]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[5]);
                          }
                          if(datetimekey[6]<10){
                              datetime<<":0"<<std::to_string(datetimekey[6]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[6]);
                          }
                         
                 metatemp.addtime=datetime.str();
}
			 break;
		case 5: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>4){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                         
                         
                 metatemp.dsssggg=datetime.str();
}
			 break;
		case 6: 
 if(mysqlx::Value::Type::RAW==_row[i].getType()){
                        // const mysqlx::bytes& raw_bytes = _row[i].getRawBytes();                       
                        int aa=0;
                         unsigned char datetimekey[8]={0x00}; 
                          for (const mysqlx::byte *ptr = _row[i].getRawBytes().begin(); ptr < _row[i].getRawBytes().end(); ++ptr){
                              datetimekey[aa]=*ptr;
                              aa++;
                              if(aa>7){
                                  break;
                              }
                          }
                         
                          std::ostringstream datetime;
                          aa=datetimekey[0]-128+datetimekey[1]*128;
                          datetime<<std::to_string(aa);
                          if(datetimekey[2]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[2]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[2]);
                          }
                          if(datetimekey[3]<10){
                              datetime<<"-0"<<std::to_string(datetimekey[3]);
                          }else{
                              datetime<<"-"<<std::to_string(datetimekey[3]);
                          }  

                          if(datetimekey[4]<10){
                              datetime<<" 0"<<std::to_string(datetimekey[4]);
                          }else{
                              datetime<<" "<<std::to_string(datetimekey[4]);
                          }
                          if(datetimekey[5]<10){
                              datetime<<":0"<<std::to_string(datetimekey[5]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[5]);
                          }
                          if(datetimekey[6]<10){
                              datetime<<":0"<<std::to_string(datetimekey[6]);
                          }else{
                              datetime<<":"<<std::to_string(datetimekey[6]);
                          }
                         
                 metatemp.testdatetime=datetime.str();
}
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.testenum=(std::string)_row[i];
		 } 
			 break;
		case 8: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.score=( double )_row[i];
		 } 
			 break;
		case 9: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::FLOAT||_row[i].getType()==mysqlx::Value::Type::DOUBLE){ 
				 metatemp.price=( double )_row[i];
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

        if(data.mid==0){
tempsql<<"null";
 }else{ 
	tempsql<<std::to_string(data.mid);
}
tempsql<<",'"<<stringaddslash(data.name)<<"'";
tempsql<<",'"<<stringaddslash(data.siteurl)<<"'";
if(data.sort==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.sort);
}
  
if(data.addtime.size()==0){ 
tempsql<<", CURRENT_TIMESTAMP ";
 }else{ 
 tempsql<<",'"<<data.addtime<<"'";
 }
  
if(data.dsssggg.size()==0){ 
tempsql<<", CURRENT_DATE ";
 }else{ 
 tempsql<<",'"<<data.dsssggg<<"'";
 }
  
if(data.testdatetime.size()==0){ 
tempsql<<", CURRENT_TIMESTAMP ";
 }else{ 
 tempsql<<",'"<<data.testdatetime<<"'";
 }
tempsql<<",'"<<stringaddslash(data.testenum)<<"'";
if(data.score==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.score);
}
if(data.price==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.price);
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

        if(data.mid==0){
	tempsql<<"`mid`=0";
 }else{ 
	tempsql<<"`mid`="<<std::to_string(data.mid);
}
tempsql<<",`name`='"<<stringaddslash(data.name)<<"'";
tempsql<<",`siteurl`='"<<stringaddslash(data.siteurl)<<"'";
if(data.sort==0){
	tempsql<<",`sort`=0";
 }else{ 
	tempsql<<",`sort`="<<std::to_string(data.sort);
}
  
if(data.addtime.size()==0){ 
tempsql<<",`addtime`=CURRENT_TIMESTAMP";
 }else{ 
 tempsql<<",`addtime'='"<<data.addtime<<"'";
 }
  
if(data.dsssggg.size()==0){ 
tempsql<<",`dsssggg`=CURRENT_DATE";
 }else{ 
 tempsql<<",`dsssggg'='"<<data.dsssggg<<"'";
 }
  
if(data.testdatetime.size()==0){ 
tempsql<<",`testdatetime`=CURRENT_TIMESTAMP";
 }else{ 
 tempsql<<",`testdatetime'='"<<data.testdatetime<<"'";
 }
tempsql<<",`testenum`='"<<stringaddslash(data.testenum)<<"'";
if(data.score==0){
	tempsql<<",`score`=0";
 }else{ 
	tempsql<<",`score`="<<std::to_string(data.score);
}
if(data.price==0){
	tempsql<<",`price`=0";
 }else{ 
	tempsql<<",`price`="<<std::to_string(data.price);
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
if(data.mid==0){
	tempsql<<"`mid`=0";
 }else{ 
	tempsql<<"`mid`="<<std::to_string(data.mid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`name`='"<<stringaddslash(data.name)<<"'";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`siteurl`='"<<stringaddslash(data.siteurl)<<"'";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(data.sort==0){
	tempsql<<",`sort`=0";
 }else{ 
	tempsql<<",`sort`="<<std::to_string(data.sort);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
  
if(data.addtime.size()==0){ 
tempsql<<",`addtime`=CURRENT_TIMESTAMP";
 }else{ 
 tempsql<<",`addtime'='"<<data.addtime<<"'";
 }
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
  
if(data.dsssggg.size()==0){ 
tempsql<<",`dsssggg`=CURRENT_DATE";
 }else{ 
 tempsql<<",`dsssggg'='"<<data.dsssggg<<"'";
 }
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
  
if(data.testdatetime.size()==0){ 
tempsql<<",`testdatetime`=CURRENT_TIMESTAMP";
 }else{ 
 tempsql<<",`testdatetime'='"<<data.testdatetime<<"'";
 }
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`testenum`='"<<stringaddslash(data.testenum)<<"'";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
if(data.score==0){
	tempsql<<",`score`=0";
 }else{ 
	tempsql<<",`score`="<<std::to_string(data.score);
}
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
if(data.price==0){
	tempsql<<",`price`=0";
 }else{ 
	tempsql<<",`price`="<<std::to_string(data.price);
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
if(data.mid==0){
	tempsql<<"\"mid\":0";
 }else{ 
	tempsql<<"\"mid\":"<<std::to_string(data.mid);
}
tempsql<<",\"name\":\""<<utf8_to_jsonstring(data.name);
tempsql<<"\"";
tempsql<<",\"siteurl\":\""<<utf8_to_jsonstring(data.siteurl);
tempsql<<"\"";
if(data.sort==0){
	tempsql<<",\"sort\":0";
 }else{ 
	tempsql<<",\"sort\":"<<std::to_string(data.sort);
}
  
if(data.addtime.size()==0){ 
tempsql<<",\"addtime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<",\"addtime\":\""<<data.addtime<<"\"";
 }
  
if(data.dsssggg.size()==0){ 
tempsql<<",\"dsssggg\":\"0000-00-00\"";
 }else{ 
 tempsql<<",\"dsssggg\":\""<<data.dsssggg<<"\"";
 }
  
if(data.testdatetime.size()==0){ 
tempsql<<",\"testdatetime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<",\"testdatetime\":\""<<data.testdatetime<<"\"";
 }
tempsql<<",\"testenum\":\""<<utf8_to_jsonstring(data.testenum);
tempsql<<"\"";
if(data.score==0){
	tempsql<<",\"score\":0";
 }else{ 
	tempsql<<",\"score\":"<<std::to_string(data.score);
}
if(data.price==0){
	tempsql<<",\"price\":0";
 }else{ 
	tempsql<<",\"price\":"<<std::to_string(data.price);
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
if(data.mid==0){
	tempsql<<"\"mid\":0";
 }else{ 
	tempsql<<"\"mid\":"<<std::to_string(data.mid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(data.name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"siteurl\":\""<<utf8_to_jsonstring(data.siteurl)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(data.sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(data.sort);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
  
if(data.addtime.size()==0){ 
tempsql<<"\"addtime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"addtime\":\""<<data.addtime<<"\"";
 }
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
  
if(data.dsssggg.size()==0){ 
tempsql<<"\"dsssggg\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"dsssggg\":\""<<data.dsssggg<<"\"";
 }
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
  
if(data.testdatetime.size()==0){ 
tempsql<<"\"testdatetime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"testdatetime\":\""<<data.testdatetime<<"\"";
 }
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"testenum\":\""<<utf8_to_jsonstring(data.testenum)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
if(data.score==0){
	tempsql<<"\"score\":0";
 }else{ 
	tempsql<<"\"score\":"<<std::to_string(data.score);
}
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
if(data.price==0){
	tempsql<<"\"price\":0";
 }else{ 
	tempsql<<"\"price\":"<<std::to_string(data.price);
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
if(record[n].mid==0){
	tempsql<<"\"mid\":0";
 }else{ 
	tempsql<<"\"mid\":"<<std::to_string(record[n].mid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(record[n].name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"siteurl\":\""<<utf8_to_jsonstring(record[n].siteurl)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(record[n].sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(record[n].sort);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
  
if(data.addtime.size()==0){ 
tempsql<<"\"addtime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"addtime\":\""<<record[n].addtime<<"\"";
 }
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
  
if(data.dsssggg.size()==0){ 
tempsql<<"\"dsssggg\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"dsssggg\":\""<<record[n].dsssggg<<"\"";
 }
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
  
if(data.testdatetime.size()==0){ 
tempsql<<"\"testdatetime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"testdatetime\":\""<<record[n].testdatetime<<"\"";
 }
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"testenum\":\""<<utf8_to_jsonstring(record[n].testenum)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
if(record[n].score==0){
	tempsql<<"\"score\":0";
 }else{ 
	tempsql<<"\"score\":"<<std::to_string(record[n].score);
}
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
if(record[n].price==0){
	tempsql<<"\"price\":0";
 }else{ 
	tempsql<<"\"price\":"<<std::to_string(record[n].price);
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
if(record[n].mid==0){
	tempsql<<"\"mid\":0";
 }else{ 
	tempsql<<"\"mid\":"<<std::to_string(record[n].mid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"name\":\""<<utf8_to_jsonstring(record[n].name)<<"\"";
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"siteurl\":\""<<utf8_to_jsonstring(record[n].siteurl)<<"\"";
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(record[n].sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(record[n].sort);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
  
if(data.addtime.size()==0){ 
tempsql<<"\"addtime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"addtime\":\""<<record[n].addtime<<"\"";
 }
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
  
if(data.dsssggg.size()==0){ 
tempsql<<"\"dsssggg\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"dsssggg\":\""<<record[n].dsssggg<<"\"";
 }
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
  
if(data.testdatetime.size()==0){ 
tempsql<<"\"testdatetime\":\"0000-00-00 00:00:00\"";
 }else{ 
 tempsql<<"\"testdatetime\":\""<<record[n].testdatetime<<"\"";
 }
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"testenum\":\""<<utf8_to_jsonstring(record[n].testenum)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
if(record[n].score==0){
	tempsql<<"\"score\":0";
 }else{ 
	tempsql<<"\"score\":"<<std::to_string(record[n].score);
}
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
if(record[n].price==0){
	tempsql<<"\"price\":0";
 }else{ 
	tempsql<<"\"price\":"<<std::to_string(record[n].price);
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
   long long getPK(){  return data.mid; } 
 void setPK(long long val){  data.mid=val;} 
 int  getMid(){  return data.mid; } 
 void setMid( int  val){  data.mid=val;} 

std::string getName(){  return data.name; } 
 void setName(std::string val){  data.name=val;} 
std::string& getRefName(){  return std::ref(data.name); } 
 void setName(std::string &val){  data.name=val;} 

std::string getSiteurl(){  return data.siteurl; } 
 void setSiteurl(std::string val){  data.siteurl=val;} 
std::string& getRefSiteurl(){  return std::ref(data.siteurl); } 
 void setSiteurl(std::string &val){  data.siteurl=val;} 

unsigned  long long  getSort(){  return data.sort; } 
 void setSort(unsigned  long long  val){  data.sort=val;} 

   std::string  getAddtime(){  return data.addtime; } 
 void setAddtime(   std::string  val){  data.addtime=val;} 
   std::string & getRefAddtime(){  return std::ref(data.addtime); } 
 void setAddtime(   std::string  &val){  data.addtime=val;} 

   std::string  getDsssggg(){  return data.dsssggg; } 
 void setDsssggg(   std::string  val){  data.dsssggg=val;} 
   std::string & getRefDsssggg(){  return std::ref(data.dsssggg); } 
 void setDsssggg(   std::string  &val){  data.dsssggg=val;} 

   std::string  getTestdatetime(){  return data.testdatetime; } 
 void setTestdatetime(   std::string  val){  data.testdatetime=val;} 
   std::string & getRefTestdatetime(){  return std::ref(data.testdatetime); } 
 void setTestdatetime(   std::string  &val){  data.testdatetime=val;} 

std::string getTestenum(){  return data.testenum; } 
 void setTestenum(std::string val){  data.testenum=val;} 
std::string& getRefTestenum(){  return std::ref(data.testenum); } 
 void setTestenum(std::string &val){  data.testenum=val;} 

 double  getScore(){  return data.score; } 
 void setScore( double  val){  data.score=val;} 

 double  getPrice(){  return data.price; } 
 void setPrice( double  val){  data.price=val;} 

moduleauthbase::meta getnewData(){
 	 struct meta newdata;
	 return std::move(newdata); 
} 
moduleauthbase::meta getData(){
 	 return data; 
} 
std::vector<moduleauthbase::meta> getRecord(){
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
 	 a.emplace_back(iter.mid);
	 break;
case 3: 
 	 a.emplace_back(iter.sort);
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

   case 8: 
 	 a.emplace_back(iter.score);
	 break;
case 9: 
 	 a.emplace_back(iter.price);
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
 	 return data.mid;
	 break;
case 3: 
 	 return data.sort;
	 break;

    }
            return 0;
        }  
    
     template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true > 
    T getVal(moduleauthbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
       
                switch(kpos){

   case 0: 
 	 return iter.mid;
	 break;
case 3: 
 	 return iter.sort;
	 break;

    }
            return 0;
        }  
    
        template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
        T getVal(std::string keyname){
            
            unsigned char kpos;
            kpos=findcolpos(keyname);
        
            switch(kpos){

    case 8: 
 	 return data.score;
	 break;
case 9: 
 	 return data.price;
	 break;

    }
            return 0.0;
        }  
    
     template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
    T getVal(moduleauthbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
         
                switch(kpos){

   case 8: 
 	 return iter.score;
	 break;
case 9: 
 	 return iter.price;
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
 	 return data.siteurl;
	 break;
case 4: 
 	 return data.addtime;
	 break;
case 5: 
 	 return data.dsssggg;
	 break;
case 6: 
 	 return data.testdatetime;
	 break;
case 7: 
 	 return data.testenum;
	 break;

  }
        return "";
    }  
   
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(moduleauthbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   case 1: 
 	 return iter.name;
	 break;
case 2: 
 	 return iter.siteurl;
	 break;
case 4: 
 	 return iter.addtime;
	 break;
case 5: 
 	 return iter.dsssggg;
	 break;
case 6: 
 	 return iter.testdatetime;
	 break;
case 7: 
 	 return iter.testenum;
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
 	 a.emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a.emplace_back(iter.addtime);
	 break;
case 5: 
 	 a.emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a.emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a.emplace_back(iter.testenum);
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
 	 a<<std::to_string(iter.mid);
	 break;
case 1: 
 	 if(isyinhao){ a<<jsonaddslash(iter.name); 
	 }else{
	 a<<iter.name;
	 }
	 break;
case 2: 
 	 if(isyinhao){ a<<jsonaddslash(iter.siteurl); 
	 }else{
	 a<<iter.siteurl;
	 }
	 break;
case 3: 
 	 a<<std::to_string(iter.sort);
	 break;
case 4: 
 	 if(isyinhao){ a<<jsonaddslash(iter.addtime); 
	 }else{
	 a<<iter.addtime;
	 }
	 break;
case 5: 
 	 if(isyinhao){ a<<jsonaddslash(iter.dsssggg); 
	 }else{
	 a<<iter.dsssggg;
	 }
	 break;
case 6: 
 	 if(isyinhao){ a<<jsonaddslash(iter.testdatetime); 
	 }else{
	 a<<iter.testdatetime;
	 }
	 break;
case 7: 
 	 if(isyinhao){ a<<jsonaddslash(iter.testenum); 
	 }else{
	 a<<iter.testenum;
	 }
	 break;
case 8: 
 	 a<<std::to_string(iter.score);
	 break;
case 9: 
 	 a<<std::to_string(iter.price);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	 } 
		 switch(vpos){ 
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	 } 
        switch(vpos){ 
case 8: 
 	 vtemp=iter.score;
	 break;
case 9: 
 	 vtemp=iter.price;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	 } 
 		   switch(vpos){ 
case 8: 
 	 vtemp=iter.score;
	 break;
case 9: 
 	 vtemp=iter.price;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
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
 	 a.emplace(iter.mid,iter);
	 break;
case 3: 
 	 a.emplace(iter.sort,iter);
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
 	 a.emplace(iter.siteurl,iter);
	 break;
case 4: 
 	 a.emplace(iter.addtime,iter);
	 break;
case 5: 
 	 a.emplace(iter.dsssggg,iter);
	 break;
case 6: 
 	 a.emplace(iter.testdatetime,iter);
	 break;
case 7: 
 	 a.emplace(iter.testenum,iter);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }
 switch(vpos){
case 8: 
 	 vtemp=iter.score;
	 break;
case 9: 
 	 vtemp=iter.price;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }
 switch(vpos){
case 8: 
 	 vtemp=iter.score;
	 break;
case 9: 
 	 vtemp=iter.price;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
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
 	 a.emplace_back(iter.mid,iter);
	 break;
case 3: 
 	 a.emplace_back(iter.sort,iter);
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
 	 a.emplace_back(iter.siteurl,iter);
	 break;
case 4: 
 	 a.emplace_back(iter.addtime,iter);
	 break;
case 5: 
 	 a.emplace_back(iter.dsssggg,iter);
	 break;
case 6: 
 	 a.emplace_back(iter.testdatetime,iter);
	 break;
case 7: 
 	 a.emplace_back(iter.testenum,iter);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.price);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.price);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.price);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 3: 
 	 vtemp=iter.sort;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.price);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 2: 
 	 vtemp=iter.siteurl;
	 break;
case 4: 
 	 vtemp=iter.addtime;
	 break;
case 5: 
 	 vtemp=iter.dsssggg;
	 break;
case 6: 
 	 vtemp=iter.testdatetime;
	 break;
case 7: 
 	 vtemp=iter.testenum;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 8: 
 	 a[ktemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp].emplace_back(iter.price);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.sort);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.siteurl);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.addtime);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.dsssggg);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.testdatetime);
	 break;
case 7: 
 	 a[ktemp].emplace_back(iter.testenum);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 8: 
 	 a[ktemp].emplace_back(iter.score);
	 break;
case 9: 
 	 a[ktemp].emplace_back(iter.price);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.mid);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.sort);
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
 	 a[iter.mid].emplace_back(iter);
	 break;
case 3: 
 	 a[iter.sort].emplace_back(iter);
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
 	 a[iter.siteurl].emplace_back(iter);
	 break;
case 4: 
 	 a[iter.addtime].emplace_back(iter);
	 break;
case 5: 
 	 a[iter.dsssggg].emplace_back(iter);
	 break;
case 6: 
 	 a[iter.testdatetime].emplace_back(iter);
	 break;
case 7: 
 	 a[iter.testenum].emplace_back(iter);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.siteurl].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.addtime].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.dsssggg].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.testdatetime].emplace_back(iter);
	 break;
case 7: 
 	 a[ktemp][iter.testenum].emplace_back(iter);
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
 	 ktemp=iter.siteurl;
	 break;
case 4: 
 	 ktemp=iter.addtime;
	 break;
case 5: 
 	 ktemp=iter.dsssggg;
	 break;
case 6: 
 	 ktemp=iter.testdatetime;
	 break;
case 7: 
 	 ktemp=iter.testenum;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.mid].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.sort].emplace_back(iter);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.mid].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.sort].emplace_back(iter);
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
 	 ktemp=iter.mid;
	 break;
case 3: 
 	 ktemp=iter.sort;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.siteurl].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.addtime].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.dsssggg].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.testdatetime].emplace_back(iter);
	 break;
case 7: 
 	 a[ktemp][iter.testenum].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
};

}
#endif
   