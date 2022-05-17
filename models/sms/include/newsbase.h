#ifndef ORM_SMS_NEWSBASEMATA_H
#define ORM_SMS_NEWSBASEMATA_H
/*
*This file is auto create from cli
*本文件为自动生成 Tue, 17 May 2022 10:05:26 GMT
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
     namespace sms { 

struct newsbase
{
    struct meta{
    unsigned  int newsid= 0; //
unsigned  int classid= 0; //
unsigned  int topicid= 0; //
unsigned  int channelid= 0; //
 int clicknum= 0; //
 std::string newtitle; //
 std::string titletwo; //
 std::string seotitle; //
 std::string keywork; //
 std::string depiction; //
 std::string newscolor; //
 std::string source; //
 std::string author; //
   std::string newsdate; //
 std::string isview="Y"; //
 std::string ishome="Y"; //
 std::string isnew="N"; //
 std::string isup="N"; //
 std::string iscomment="N"; //
 int sort= 0; //
 int userid= 0; //
 char language=0; //
 std::string addtime; //
   std::string adddate; //
 std::string newsico; //
 std::string newsimg; //
 std::string dest; //
 std::string newscontent; //
 } data;
 std::vector<newsbase::meta> record;
std::string _rmstag="sms";//this value must be default or tag value, tag in mysqlconnect config file .
std::vector<unsigned char> _keypos{0x00};
mysqlx::Row _row;
std::vector<newsbase::meta>::iterator begin(){     return record.begin(); }
std::vector<newsbase::meta>::iterator end(){     return record.end(); }
std::vector<newsbase::meta>::const_iterator begin() const{     return record.begin(); }
std::vector<newsbase::meta>::const_iterator end() const{     return record.end(); }
const std::array<std::string,28> colnames={"newsid","classid","topicid","channelid","clicknum","newtitle","titletwo","seotitle","keywork","depiction","newscolor","source","author","newsdate","isview","ishome","isnew","isup","iscomment","sort","userid","language","addtime","adddate","newsico","newsimg","dest","newscontent"};
const std::array<unsigned char,28> colnamestype= {1,1,1,1,1,30,30,30,30,30,30,30,30,61,30,30,30,30,30,1,1,1,30,61,30,30,30,30};
std::string tablename="web_news";
std::string modelname="News";

	  unsigned char findcolpos(std::string coln){
		    unsigned char  bi=coln[0];
            char colpospppc;
	         if(bi<91&&bi>64){
				bi+=32;
			}
            switch(coln[0]){


         case 'a':
 switch(coln.size()){  
case 6:
   	 return 12;
break;
case 7:
 if(strcasecmp(coln.c_str(), "addtime") == 0){ return 22; }
 if(strcasecmp(coln.c_str(), "adddate") == 0){ return 23; }
   	 break;
 }
 break;
case 'c':
 switch(coln.size()){  
case 7:
   	 return 1;
break;
case 8:
   	 return 4;
break;
case 9:
   	 return 3;
break;
 }
 break;
case 'd':
 switch(coln.size()){  
case 4:
   	 return 26;
break;
case 9:
   	 return 9;
break;
 }
 break;
case 'i':
 switch(coln.size()){  
case 4:
   	 return 17;
break;
case 5:
   	 return 16;
break;
case 6:
  colpospppc=coln.back();
    if(colpospppc<91&&bi>64){ colpospppc+=32; }
 if(colpospppc=='e'){ return 15; }
 if(colpospppc=='w'){ return 14; }
   	 break;
case 9:
   	 return 18;
break;
 }
 break;
case 'k':
   	 return 8;
break;
case 'l':
   	 return 21;
break;
case 'n':
 switch(coln.size()){  
case 6:
   	 return 0;
break;
case 7:
  colpospppc=coln.back();
    if(colpospppc<91&&bi>64){ colpospppc+=32; }
 if(colpospppc=='g'){ return 25; }
 if(colpospppc=='o'){ return 24; }
   	 break;
case 8:
 if(strcasecmp(coln.c_str(), "newtitle") == 0){ return 5; }
 if(strcasecmp(coln.c_str(), "newsdate") == 0){ return 13; }
   	 break;
case 9:
   	 return 10;
break;
case 11:
   	 return 27;
break;
 }
 break;
case 's':
 switch(coln.size()){  
case 4:
   	 return 19;
break;
case 6:
   	 return 11;
break;
case 8:
   	 return 7;
break;
 }
 break;
case 't':
 switch(coln.size()){  
case 7:
   	 return 2;
break;
case 8:
   	 return 6;
break;
 }
 break;
case 'u':
   	 return 20;
break;

             }
             return 255;
           }
         
    int size(){ return record.size(); }   

    std::string getPKname(){ 
       return "newsid";
}

      void _setColnamevalue(){
          newsbase::meta metatemp;   
         for(unsigned char i=0;i<_keypos.size();i++){
                 switch(_keypos[i]){
        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.newsid=(unsigned  int )_row[i];
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.classid=(unsigned  int )_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.topicid=(unsigned  int )_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.channelid=(unsigned  int )_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.clicknum=( int )_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newtitle=(std::string)_row[i];
		 } 
			 break;
		case 6: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.titletwo=(std::string)_row[i];
		 } 
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.seotitle=(std::string)_row[i];
		 } 
			 break;
		case 8: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.keywork=(std::string)_row[i];
		 } 
			 break;
		case 9: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.depiction=(std::string)_row[i];
		 } 
			 break;
		case 10: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newscolor=(std::string)_row[i];
		 } 
			 break;
		case 11: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.source=(std::string)_row[i];
		 } 
			 break;
		case 12: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.author=(std::string)_row[i];
		 } 
			 break;
		case 13: 
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

                         
                         
                 metatemp.newsdate=datetime.str();
}
			 break;
		case 14: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isview=(std::string)_row[i];
		 } 
			 break;
		case 15: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.ishome=(std::string)_row[i];
		 } 
			 break;
		case 16: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isnew=(std::string)_row[i];
		 } 
			 break;
		case 17: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isup=(std::string)_row[i];
		 } 
			 break;
		case 18: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.iscomment=(std::string)_row[i];
		 } 
			 break;
		case 19: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.sort=( int )_row[i];
		 } 
			 break;
		case 20: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.userid=( int )_row[i];
		 } 
			 break;
		case 21: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.language=( int )_row[i];
		 } 
			 break;
		case 22: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.addtime=(std::string)_row[i];
		 } 
			 break;
		case 23: 
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

                         
                         
                 metatemp.adddate=datetime.str();
}
			 break;
		case 24: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newsico=(std::string)_row[i];
		 } 
			 break;
		case 25: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newsimg=(std::string)_row[i];
		 } 
			 break;
		case 26: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.dest=(std::string)_row[i];
		 } 
			 break;
		case 27: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newscontent=(std::string)_row[i];
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
           newsbase::meta metatemp;   

          for(unsigned char i=0;i<_keypos.size();i++){
 
                 switch(_keypos[i]){

        		case 0: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.newsid=(unsigned  int )_row[i];
		 } 
			 break;
		case 1: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.classid=(unsigned  int )_row[i];
		 } 
			 break;
		case 2: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.topicid=(unsigned  int )_row[i];
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.channelid=(unsigned  int )_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.clicknum=( int )_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newtitle=(std::string)_row[i];
		 } 
			 break;
		case 6: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.titletwo=(std::string)_row[i];
		 } 
			 break;
		case 7: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.seotitle=(std::string)_row[i];
		 } 
			 break;
		case 8: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.keywork=(std::string)_row[i];
		 } 
			 break;
		case 9: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.depiction=(std::string)_row[i];
		 } 
			 break;
		case 10: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newscolor=(std::string)_row[i];
		 } 
			 break;
		case 11: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.source=(std::string)_row[i];
		 } 
			 break;
		case 12: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.author=(std::string)_row[i];
		 } 
			 break;
		case 13: 
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

                         
                         
                 metatemp.newsdate=datetime.str();
}
			 break;
		case 14: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isview=(std::string)_row[i];
		 } 
			 break;
		case 15: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.ishome=(std::string)_row[i];
		 } 
			 break;
		case 16: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isnew=(std::string)_row[i];
		 } 
			 break;
		case 17: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.isup=(std::string)_row[i];
		 } 
			 break;
		case 18: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.iscomment=(std::string)_row[i];
		 } 
			 break;
		case 19: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.sort=( int )_row[i];
		 } 
			 break;
		case 20: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.userid=( int )_row[i];
		 } 
			 break;
		case 21: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.language=( int )_row[i];
		 } 
			 break;
		case 22: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.addtime=(std::string)_row[i];
		 } 
			 break;
		case 23: 
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

                         
                         
                 metatemp.adddate=datetime.str();
}
			 break;
		case 24: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newsico=(std::string)_row[i];
		 } 
			 break;
		case 25: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newsimg=(std::string)_row[i];
		 } 
			 break;
		case 26: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.dest=(std::string)_row[i];
		 } 
			 break;
		case 27: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.newscontent=(std::string)_row[i];
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

        if(data.newsid==0){
tempsql<<"null";
 }else{ 
	tempsql<<std::to_string(data.newsid);
}
if(data.classid==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.classid);
}
if(data.topicid==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.topicid);
}
if(data.channelid==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.channelid);
}
if(data.clicknum==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.clicknum);
}
tempsql<<",'"<<stringaddslash(data.newtitle)<<"'";
tempsql<<",'"<<stringaddslash(data.titletwo)<<"'";
tempsql<<",'"<<stringaddslash(data.seotitle)<<"'";
tempsql<<",'"<<stringaddslash(data.keywork)<<"'";
tempsql<<",'"<<stringaddslash(data.depiction)<<"'";
tempsql<<",'"<<stringaddslash(data.newscolor)<<"'";
tempsql<<",'"<<stringaddslash(data.source)<<"'";
tempsql<<",'"<<stringaddslash(data.author)<<"'";
  
if(data.newsdate.size()==0){ 
tempsql<<", CURRENT_DATE ";
 }else{ 
 tempsql<<",'"<<data.newsdate<<"'";
 }
tempsql<<",'"<<stringaddslash(data.isview)<<"'";
tempsql<<",'"<<stringaddslash(data.ishome)<<"'";
tempsql<<",'"<<stringaddslash(data.isnew)<<"'";
tempsql<<",'"<<stringaddslash(data.isup)<<"'";
tempsql<<",'"<<stringaddslash(data.iscomment)<<"'";
if(data.sort==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.sort);
}
if(data.userid==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.userid);
}
if(data.language==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.language);
}
tempsql<<",'"<<stringaddslash(data.addtime)<<"'";
  
if(data.adddate.size()==0){ 
tempsql<<", CURRENT_DATE ";
 }else{ 
 tempsql<<",'"<<data.adddate<<"'";
 }
tempsql<<",'"<<stringaddslash(data.newsico)<<"'";
tempsql<<",'"<<stringaddslash(data.newsimg)<<"'";
tempsql<<",'"<<stringaddslash(data.dest)<<"'";
tempsql<<",'"<<stringaddslash(data.newscontent)<<"'";
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

        if(data.newsid==0){
	tempsql<<"`newsid`=0";
 }else{ 
	tempsql<<"`newsid`="<<std::to_string(data.newsid);
}
if(data.classid==0){
	tempsql<<",`classid`=0";
 }else{ 
	tempsql<<",`classid`="<<std::to_string(data.classid);
}
if(data.topicid==0){
	tempsql<<",`topicid`=0";
 }else{ 
	tempsql<<",`topicid`="<<std::to_string(data.topicid);
}
if(data.channelid==0){
	tempsql<<",`channelid`=0";
 }else{ 
	tempsql<<",`channelid`="<<std::to_string(data.channelid);
}
if(data.clicknum==0){
	tempsql<<",`clicknum`=0";
 }else{ 
	tempsql<<",`clicknum`="<<std::to_string(data.clicknum);
}
tempsql<<",`newtitle`='"<<stringaddslash(data.newtitle)<<"'";
tempsql<<",`titletwo`='"<<stringaddslash(data.titletwo)<<"'";
tempsql<<",`seotitle`='"<<stringaddslash(data.seotitle)<<"'";
tempsql<<",`keywork`='"<<stringaddslash(data.keywork)<<"'";
tempsql<<",`depiction`='"<<stringaddslash(data.depiction)<<"'";
tempsql<<",`newscolor`='"<<stringaddslash(data.newscolor)<<"'";
tempsql<<",`source`='"<<stringaddslash(data.source)<<"'";
tempsql<<",`author`='"<<stringaddslash(data.author)<<"'";
  
if(data.newsdate.size()==0){ 
tempsql<<",`newsdate`=CURRENT_DATE";
 }else{ 
 tempsql<<",`newsdate'='"<<data.newsdate<<"'";
 }
tempsql<<",`isview`='"<<stringaddslash(data.isview)<<"'";
tempsql<<",`ishome`='"<<stringaddslash(data.ishome)<<"'";
tempsql<<",`isnew`='"<<stringaddslash(data.isnew)<<"'";
tempsql<<",`isup`='"<<stringaddslash(data.isup)<<"'";
tempsql<<",`iscomment`='"<<stringaddslash(data.iscomment)<<"'";
if(data.sort==0){
	tempsql<<",`sort`=0";
 }else{ 
	tempsql<<",`sort`="<<std::to_string(data.sort);
}
if(data.userid==0){
	tempsql<<",`userid`=0";
 }else{ 
	tempsql<<",`userid`="<<std::to_string(data.userid);
}
if(data.language==0){
	tempsql<<",`language`=0";
 }else{ 
	tempsql<<",`language`="<<std::to_string(data.language);
}
tempsql<<",`addtime`='"<<stringaddslash(data.addtime)<<"'";
  
if(data.adddate.size()==0){ 
tempsql<<",`adddate`=CURRENT_DATE";
 }else{ 
 tempsql<<",`adddate'='"<<data.adddate<<"'";
 }
tempsql<<",`newsico`='"<<stringaddslash(data.newsico)<<"'";
tempsql<<",`newsimg`='"<<stringaddslash(data.newsimg)<<"'";
tempsql<<",`dest`='"<<stringaddslash(data.dest)<<"'";
tempsql<<",`newscontent`='"<<stringaddslash(data.newscontent)<<"'";
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
if(data.newsid==0){
	tempsql<<"`newsid`=0";
 }else{ 
	tempsql<<"`newsid`="<<std::to_string(data.newsid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
if(data.classid==0){
	tempsql<<",`classid`=0";
 }else{ 
	tempsql<<",`classid`="<<std::to_string(data.classid);
}
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
if(data.topicid==0){
	tempsql<<",`topicid`=0";
 }else{ 
	tempsql<<",`topicid`="<<std::to_string(data.topicid);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(data.channelid==0){
	tempsql<<",`channelid`=0";
 }else{ 
	tempsql<<",`channelid`="<<std::to_string(data.channelid);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
if(data.clicknum==0){
	tempsql<<",`clicknum`=0";
 }else{ 
	tempsql<<",`clicknum`="<<std::to_string(data.clicknum);
}
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`newtitle`='"<<stringaddslash(data.newtitle)<<"'";
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`titletwo`='"<<stringaddslash(data.titletwo)<<"'";
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`seotitle`='"<<stringaddslash(data.seotitle)<<"'";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`keywork`='"<<stringaddslash(data.keywork)<<"'";
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`depiction`='"<<stringaddslash(data.depiction)<<"'";
 break;
 case 10:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`newscolor`='"<<stringaddslash(data.newscolor)<<"'";
 break;
 case 11:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`source`='"<<stringaddslash(data.source)<<"'";
 break;
 case 12:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`author`='"<<stringaddslash(data.author)<<"'";
 break;
 case 13:
 if(jj>0){ tempsql<<","; } 
  
if(data.newsdate.size()==0){ 
tempsql<<",`newsdate`=CURRENT_DATE";
 }else{ 
 tempsql<<",`newsdate'='"<<data.newsdate<<"'";
 }
 break;
 case 14:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`isview`='"<<stringaddslash(data.isview)<<"'";
 break;
 case 15:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`ishome`='"<<stringaddslash(data.ishome)<<"'";
 break;
 case 16:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`isnew`='"<<stringaddslash(data.isnew)<<"'";
 break;
 case 17:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`isup`='"<<stringaddslash(data.isup)<<"'";
 break;
 case 18:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`iscomment`='"<<stringaddslash(data.iscomment)<<"'";
 break;
 case 19:
 if(jj>0){ tempsql<<","; } 
if(data.sort==0){
	tempsql<<",`sort`=0";
 }else{ 
	tempsql<<",`sort`="<<std::to_string(data.sort);
}
 break;
 case 20:
 if(jj>0){ tempsql<<","; } 
if(data.userid==0){
	tempsql<<",`userid`=0";
 }else{ 
	tempsql<<",`userid`="<<std::to_string(data.userid);
}
 break;
 case 21:
 if(jj>0){ tempsql<<","; } 
if(data.language==0){
	tempsql<<",`language`=0";
 }else{ 
	tempsql<<",`language`="<<std::to_string(data.language);
}
 break;
 case 22:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`addtime`='"<<stringaddslash(data.addtime)<<"'";
 break;
 case 23:
 if(jj>0){ tempsql<<","; } 
  
if(data.adddate.size()==0){ 
tempsql<<",`adddate`=CURRENT_DATE";
 }else{ 
 tempsql<<",`adddate'='"<<data.adddate<<"'";
 }
 break;
 case 24:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`newsico`='"<<stringaddslash(data.newsico)<<"'";
 break;
 case 25:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`newsimg`='"<<stringaddslash(data.newsimg)<<"'";
 break;
 case 26:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`dest`='"<<stringaddslash(data.dest)<<"'";
 break;
 case 27:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`newscontent`='"<<stringaddslash(data.newscontent)<<"'";
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
if(data.newsid==0){
	tempsql<<"\"newsid\":0";
 }else{ 
	tempsql<<"\"newsid\":"<<std::to_string(data.newsid);
}
if(data.classid==0){
	tempsql<<",\"classid\":0";
 }else{ 
	tempsql<<",\"classid\":"<<std::to_string(data.classid);
}
if(data.topicid==0){
	tempsql<<",\"topicid\":0";
 }else{ 
	tempsql<<",\"topicid\":"<<std::to_string(data.topicid);
}
if(data.channelid==0){
	tempsql<<",\"channelid\":0";
 }else{ 
	tempsql<<",\"channelid\":"<<std::to_string(data.channelid);
}
if(data.clicknum==0){
	tempsql<<",\"clicknum\":0";
 }else{ 
	tempsql<<",\"clicknum\":"<<std::to_string(data.clicknum);
}
tempsql<<",\"newtitle\":\""<<utf8_to_jsonstring(data.newtitle);
tempsql<<"\"";
tempsql<<",\"titletwo\":\""<<utf8_to_jsonstring(data.titletwo);
tempsql<<"\"";
tempsql<<",\"seotitle\":\""<<utf8_to_jsonstring(data.seotitle);
tempsql<<"\"";
tempsql<<",\"keywork\":\""<<utf8_to_jsonstring(data.keywork);
tempsql<<"\"";
tempsql<<",\"depiction\":\""<<utf8_to_jsonstring(data.depiction);
tempsql<<"\"";
tempsql<<",\"newscolor\":\""<<utf8_to_jsonstring(data.newscolor);
tempsql<<"\"";
tempsql<<",\"source\":\""<<utf8_to_jsonstring(data.source);
tempsql<<"\"";
tempsql<<",\"author\":\""<<utf8_to_jsonstring(data.author);
tempsql<<"\"";
  
if(data.newsdate.size()==0){ 
tempsql<<",\"newsdate\":\"0000-00-00\"";
 }else{ 
 tempsql<<",\"newsdate\":\""<<data.newsdate<<"\"";
 }
tempsql<<",\"isview\":\""<<utf8_to_jsonstring(data.isview);
tempsql<<"\"";
tempsql<<",\"ishome\":\""<<utf8_to_jsonstring(data.ishome);
tempsql<<"\"";
tempsql<<",\"isnew\":\""<<utf8_to_jsonstring(data.isnew);
tempsql<<"\"";
tempsql<<",\"isup\":\""<<utf8_to_jsonstring(data.isup);
tempsql<<"\"";
tempsql<<",\"iscomment\":\""<<utf8_to_jsonstring(data.iscomment);
tempsql<<"\"";
if(data.sort==0){
	tempsql<<",\"sort\":0";
 }else{ 
	tempsql<<",\"sort\":"<<std::to_string(data.sort);
}
if(data.userid==0){
	tempsql<<",\"userid\":0";
 }else{ 
	tempsql<<",\"userid\":"<<std::to_string(data.userid);
}
if(data.language==0){
	tempsql<<",\"language\":0";
 }else{ 
	tempsql<<",\"language\":"<<std::to_string(data.language);
}
tempsql<<",\"addtime\":\""<<utf8_to_jsonstring(data.addtime);
tempsql<<"\"";
  
if(data.adddate.size()==0){ 
tempsql<<",\"adddate\":\"0000-00-00\"";
 }else{ 
 tempsql<<",\"adddate\":\""<<data.adddate<<"\"";
 }
tempsql<<",\"newsico\":\""<<utf8_to_jsonstring(data.newsico);
tempsql<<"\"";
tempsql<<",\"newsimg\":\""<<utf8_to_jsonstring(data.newsimg);
tempsql<<"\"";
tempsql<<",\"dest\":\""<<utf8_to_jsonstring(data.dest);
tempsql<<"\"";
tempsql<<",\"newscontent\":\""<<utf8_to_jsonstring(data.newscontent);
tempsql<<"\"";
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
if(data.newsid==0){
	tempsql<<"\"newsid\":0";
 }else{ 
	tempsql<<"\"newsid\":"<<std::to_string(data.newsid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
if(data.classid==0){
	tempsql<<"\"classid\":0";
 }else{ 
	tempsql<<"\"classid\":"<<std::to_string(data.classid);
}
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
if(data.topicid==0){
	tempsql<<"\"topicid\":0";
 }else{ 
	tempsql<<"\"topicid\":"<<std::to_string(data.topicid);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(data.channelid==0){
	tempsql<<"\"channelid\":0";
 }else{ 
	tempsql<<"\"channelid\":"<<std::to_string(data.channelid);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
if(data.clicknum==0){
	tempsql<<"\"clicknum\":0";
 }else{ 
	tempsql<<"\"clicknum\":"<<std::to_string(data.clicknum);
}
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newtitle\":\""<<utf8_to_jsonstring(data.newtitle)<<"\"";
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"titletwo\":\""<<utf8_to_jsonstring(data.titletwo)<<"\"";
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"seotitle\":\""<<utf8_to_jsonstring(data.seotitle)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"keywork\":\""<<utf8_to_jsonstring(data.keywork)<<"\"";
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"depiction\":\""<<utf8_to_jsonstring(data.depiction)<<"\"";
 break;
 case 10:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscolor\":\""<<utf8_to_jsonstring(data.newscolor)<<"\"";
 break;
 case 11:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"source\":\""<<utf8_to_jsonstring(data.source)<<"\"";
 break;
 case 12:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"author\":\""<<utf8_to_jsonstring(data.author)<<"\"";
 break;
 case 13:
 if(jj>0){ tempsql<<","; } 
  
if(data.newsdate.size()==0){ 
tempsql<<"\"newsdate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"newsdate\":\""<<data.newsdate<<"\"";
 }
 break;
 case 14:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isview\":\""<<utf8_to_jsonstring(data.isview)<<"\"";
 break;
 case 15:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"ishome\":\""<<utf8_to_jsonstring(data.ishome)<<"\"";
 break;
 case 16:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isnew\":\""<<utf8_to_jsonstring(data.isnew)<<"\"";
 break;
 case 17:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isup\":\""<<utf8_to_jsonstring(data.isup)<<"\"";
 break;
 case 18:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"iscomment\":\""<<utf8_to_jsonstring(data.iscomment)<<"\"";
 break;
 case 19:
 if(jj>0){ tempsql<<","; } 
if(data.sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(data.sort);
}
 break;
 case 20:
 if(jj>0){ tempsql<<","; } 
if(data.userid==0){
	tempsql<<"\"userid\":0";
 }else{ 
	tempsql<<"\"userid\":"<<std::to_string(data.userid);
}
 break;
 case 21:
 if(jj>0){ tempsql<<","; } 
if(data.language==0){
	tempsql<<"\"language\":0";
 }else{ 
	tempsql<<"\"language\":"<<std::to_string(data.language);
}
 break;
 case 22:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"addtime\":\""<<utf8_to_jsonstring(data.addtime)<<"\"";
 break;
 case 23:
 if(jj>0){ tempsql<<","; } 
  
if(data.adddate.size()==0){ 
tempsql<<"\"adddate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"adddate\":\""<<data.adddate<<"\"";
 }
 break;
 case 24:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsico\":\""<<utf8_to_jsonstring(data.newsico)<<"\"";
 break;
 case 25:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsimg\":\""<<utf8_to_jsonstring(data.newsimg)<<"\"";
 break;
 case 26:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"dest\":\""<<utf8_to_jsonstring(data.dest)<<"\"";
 break;
 case 27:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscontent\":\""<<utf8_to_jsonstring(data.newscontent)<<"\"";
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
if(record[n].newsid==0){
	tempsql<<"\"newsid\":0";
 }else{ 
	tempsql<<"\"newsid\":"<<std::to_string(record[n].newsid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
if(record[n].classid==0){
	tempsql<<"\"classid\":0";
 }else{ 
	tempsql<<"\"classid\":"<<std::to_string(record[n].classid);
}
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
if(record[n].topicid==0){
	tempsql<<"\"topicid\":0";
 }else{ 
	tempsql<<"\"topicid\":"<<std::to_string(record[n].topicid);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(record[n].channelid==0){
	tempsql<<"\"channelid\":0";
 }else{ 
	tempsql<<"\"channelid\":"<<std::to_string(record[n].channelid);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
if(record[n].clicknum==0){
	tempsql<<"\"clicknum\":0";
 }else{ 
	tempsql<<"\"clicknum\":"<<std::to_string(record[n].clicknum);
}
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newtitle\":\""<<utf8_to_jsonstring(record[n].newtitle)<<"\"";
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"titletwo\":\""<<utf8_to_jsonstring(record[n].titletwo)<<"\"";
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"seotitle\":\""<<utf8_to_jsonstring(record[n].seotitle)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"keywork\":\""<<utf8_to_jsonstring(record[n].keywork)<<"\"";
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"depiction\":\""<<utf8_to_jsonstring(record[n].depiction)<<"\"";
 break;
 case 10:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscolor\":\""<<utf8_to_jsonstring(record[n].newscolor)<<"\"";
 break;
 case 11:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"source\":\""<<utf8_to_jsonstring(record[n].source)<<"\"";
 break;
 case 12:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"author\":\""<<utf8_to_jsonstring(record[n].author)<<"\"";
 break;
 case 13:
 if(jj>0){ tempsql<<","; } 
  
if(data.newsdate.size()==0){ 
tempsql<<"\"newsdate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"newsdate\":\""<<record[n].newsdate<<"\"";
 }
 break;
 case 14:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isview\":\""<<utf8_to_jsonstring(record[n].isview)<<"\"";
 break;
 case 15:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"ishome\":\""<<utf8_to_jsonstring(record[n].ishome)<<"\"";
 break;
 case 16:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isnew\":\""<<utf8_to_jsonstring(record[n].isnew)<<"\"";
 break;
 case 17:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isup\":\""<<utf8_to_jsonstring(record[n].isup)<<"\"";
 break;
 case 18:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"iscomment\":\""<<utf8_to_jsonstring(record[n].iscomment)<<"\"";
 break;
 case 19:
 if(jj>0){ tempsql<<","; } 
if(record[n].sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(record[n].sort);
}
 break;
 case 20:
 if(jj>0){ tempsql<<","; } 
if(record[n].userid==0){
	tempsql<<"\"userid\":0";
 }else{ 
	tempsql<<"\"userid\":"<<std::to_string(record[n].userid);
}
 break;
 case 21:
 if(jj>0){ tempsql<<","; } 
if(record[n].language==0){
	tempsql<<"\"language\":0";
 }else{ 
	tempsql<<"\"language\":"<<std::to_string(record[n].language);
}
 break;
 case 22:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"addtime\":\""<<utf8_to_jsonstring(record[n].addtime)<<"\"";
 break;
 case 23:
 if(jj>0){ tempsql<<","; } 
  
if(data.adddate.size()==0){ 
tempsql<<"\"adddate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"adddate\":\""<<record[n].adddate<<"\"";
 }
 break;
 case 24:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsico\":\""<<utf8_to_jsonstring(record[n].newsico)<<"\"";
 break;
 case 25:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsimg\":\""<<utf8_to_jsonstring(record[n].newsimg)<<"\"";
 break;
 case 26:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"dest\":\""<<utf8_to_jsonstring(record[n].dest)<<"\"";
 break;
 case 27:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscontent\":\""<<utf8_to_jsonstring(record[n].newscontent)<<"\"";
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
if(record[n].newsid==0){
	tempsql<<"\"newsid\":0";
 }else{ 
	tempsql<<"\"newsid\":"<<std::to_string(record[n].newsid);
}
 break;
 case 1:
 if(jj>0){ tempsql<<","; } 
if(record[n].classid==0){
	tempsql<<"\"classid\":0";
 }else{ 
	tempsql<<"\"classid\":"<<std::to_string(record[n].classid);
}
 break;
 case 2:
 if(jj>0){ tempsql<<","; } 
if(record[n].topicid==0){
	tempsql<<"\"topicid\":0";
 }else{ 
	tempsql<<"\"topicid\":"<<std::to_string(record[n].topicid);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
if(record[n].channelid==0){
	tempsql<<"\"channelid\":0";
 }else{ 
	tempsql<<"\"channelid\":"<<std::to_string(record[n].channelid);
}
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
if(record[n].clicknum==0){
	tempsql<<"\"clicknum\":0";
 }else{ 
	tempsql<<"\"clicknum\":"<<std::to_string(record[n].clicknum);
}
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newtitle\":\""<<utf8_to_jsonstring(record[n].newtitle)<<"\"";
 break;
 case 6:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"titletwo\":\""<<utf8_to_jsonstring(record[n].titletwo)<<"\"";
 break;
 case 7:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"seotitle\":\""<<utf8_to_jsonstring(record[n].seotitle)<<"\"";
 break;
 case 8:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"keywork\":\""<<utf8_to_jsonstring(record[n].keywork)<<"\"";
 break;
 case 9:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"depiction\":\""<<utf8_to_jsonstring(record[n].depiction)<<"\"";
 break;
 case 10:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscolor\":\""<<utf8_to_jsonstring(record[n].newscolor)<<"\"";
 break;
 case 11:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"source\":\""<<utf8_to_jsonstring(record[n].source)<<"\"";
 break;
 case 12:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"author\":\""<<utf8_to_jsonstring(record[n].author)<<"\"";
 break;
 case 13:
 if(jj>0){ tempsql<<","; } 
  
if(data.newsdate.size()==0){ 
tempsql<<"\"newsdate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"newsdate\":\""<<record[n].newsdate<<"\"";
 }
 break;
 case 14:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isview\":\""<<utf8_to_jsonstring(record[n].isview)<<"\"";
 break;
 case 15:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"ishome\":\""<<utf8_to_jsonstring(record[n].ishome)<<"\"";
 break;
 case 16:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isnew\":\""<<utf8_to_jsonstring(record[n].isnew)<<"\"";
 break;
 case 17:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"isup\":\""<<utf8_to_jsonstring(record[n].isup)<<"\"";
 break;
 case 18:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"iscomment\":\""<<utf8_to_jsonstring(record[n].iscomment)<<"\"";
 break;
 case 19:
 if(jj>0){ tempsql<<","; } 
if(record[n].sort==0){
	tempsql<<"\"sort\":0";
 }else{ 
	tempsql<<"\"sort\":"<<std::to_string(record[n].sort);
}
 break;
 case 20:
 if(jj>0){ tempsql<<","; } 
if(record[n].userid==0){
	tempsql<<"\"userid\":0";
 }else{ 
	tempsql<<"\"userid\":"<<std::to_string(record[n].userid);
}
 break;
 case 21:
 if(jj>0){ tempsql<<","; } 
if(record[n].language==0){
	tempsql<<"\"language\":0";
 }else{ 
	tempsql<<"\"language\":"<<std::to_string(record[n].language);
}
 break;
 case 22:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"addtime\":\""<<utf8_to_jsonstring(record[n].addtime)<<"\"";
 break;
 case 23:
 if(jj>0){ tempsql<<","; } 
  
if(data.adddate.size()==0){ 
tempsql<<"\"adddate\":\"0000-00-00\"";
 }else{ 
 tempsql<<"\"adddate\":\""<<record[n].adddate<<"\"";
 }
 break;
 case 24:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsico\":\""<<utf8_to_jsonstring(record[n].newsico)<<"\"";
 break;
 case 25:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newsimg\":\""<<utf8_to_jsonstring(record[n].newsimg)<<"\"";
 break;
 case 26:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"dest\":\""<<utf8_to_jsonstring(record[n].dest)<<"\"";
 break;
 case 27:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"newscontent\":\""<<utf8_to_jsonstring(record[n].newscontent)<<"\"";
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
   long long getPK(){  return data.newsid; } 
 void setPK(long long val){  data.newsid=val;} 
unsigned  int  getNewsid(){  return data.newsid; } 
 void setNewsid(unsigned  int  val){  data.newsid=val;} 

unsigned  int  getClassid(){  return data.classid; } 
 void setClassid(unsigned  int  val){  data.classid=val;} 

unsigned  int  getTopicid(){  return data.topicid; } 
 void setTopicid(unsigned  int  val){  data.topicid=val;} 

unsigned  int  getChannelid(){  return data.channelid; } 
 void setChannelid(unsigned  int  val){  data.channelid=val;} 

 int  getClicknum(){  return data.clicknum; } 
 void setClicknum( int  val){  data.clicknum=val;} 

std::string getNewtitle(){  return data.newtitle; } 
 void setNewtitle(std::string val){  data.newtitle=val;} 
std::string& getRefNewtitle(){  return std::ref(data.newtitle); } 
 void setNewtitle(std::string &val){  data.newtitle=val;} 

std::string getTitletwo(){  return data.titletwo; } 
 void setTitletwo(std::string val){  data.titletwo=val;} 
std::string& getRefTitletwo(){  return std::ref(data.titletwo); } 
 void setTitletwo(std::string &val){  data.titletwo=val;} 

std::string getSeotitle(){  return data.seotitle; } 
 void setSeotitle(std::string val){  data.seotitle=val;} 
std::string& getRefSeotitle(){  return std::ref(data.seotitle); } 
 void setSeotitle(std::string &val){  data.seotitle=val;} 

std::string getKeywork(){  return data.keywork; } 
 void setKeywork(std::string val){  data.keywork=val;} 
std::string& getRefKeywork(){  return std::ref(data.keywork); } 
 void setKeywork(std::string &val){  data.keywork=val;} 

std::string getDepiction(){  return data.depiction; } 
 void setDepiction(std::string val){  data.depiction=val;} 
std::string& getRefDepiction(){  return std::ref(data.depiction); } 
 void setDepiction(std::string &val){  data.depiction=val;} 

std::string getNewscolor(){  return data.newscolor; } 
 void setNewscolor(std::string val){  data.newscolor=val;} 
std::string& getRefNewscolor(){  return std::ref(data.newscolor); } 
 void setNewscolor(std::string &val){  data.newscolor=val;} 

std::string getSource(){  return data.source; } 
 void setSource(std::string val){  data.source=val;} 
std::string& getRefSource(){  return std::ref(data.source); } 
 void setSource(std::string &val){  data.source=val;} 

std::string getAuthor(){  return data.author; } 
 void setAuthor(std::string val){  data.author=val;} 
std::string& getRefAuthor(){  return std::ref(data.author); } 
 void setAuthor(std::string &val){  data.author=val;} 

   std::string  getNewsdate(){  return data.newsdate; } 
 void setNewsdate(   std::string  val){  data.newsdate=val;} 
   std::string & getRefNewsdate(){  return std::ref(data.newsdate); } 
 void setNewsdate(   std::string  &val){  data.newsdate=val;} 

std::string getIsview(){  return data.isview; } 
 void setIsview(std::string val){  data.isview=val;} 
std::string& getRefIsview(){  return std::ref(data.isview); } 
 void setIsview(std::string &val){  data.isview=val;} 

std::string getIshome(){  return data.ishome; } 
 void setIshome(std::string val){  data.ishome=val;} 
std::string& getRefIshome(){  return std::ref(data.ishome); } 
 void setIshome(std::string &val){  data.ishome=val;} 

std::string getIsnew(){  return data.isnew; } 
 void setIsnew(std::string val){  data.isnew=val;} 
std::string& getRefIsnew(){  return std::ref(data.isnew); } 
 void setIsnew(std::string &val){  data.isnew=val;} 

std::string getIsup(){  return data.isup; } 
 void setIsup(std::string val){  data.isup=val;} 
std::string& getRefIsup(){  return std::ref(data.isup); } 
 void setIsup(std::string &val){  data.isup=val;} 

std::string getIscomment(){  return data.iscomment; } 
 void setIscomment(std::string val){  data.iscomment=val;} 
std::string& getRefIscomment(){  return std::ref(data.iscomment); } 
 void setIscomment(std::string &val){  data.iscomment=val;} 

 int  getSort(){  return data.sort; } 
 void setSort( int  val){  data.sort=val;} 

 int  getUserid(){  return data.userid; } 
 void setUserid( int  val){  data.userid=val;} 

 int  getLanguage(){  return data.language; } 
 void setLanguage( int  val){  data.language=val;} 

std::string getAddtime(){  return data.addtime; } 
 void setAddtime(std::string val){  data.addtime=val;} 
std::string& getRefAddtime(){  return std::ref(data.addtime); } 
 void setAddtime(std::string &val){  data.addtime=val;} 

   std::string  getAdddate(){  return data.adddate; } 
 void setAdddate(   std::string  val){  data.adddate=val;} 
   std::string & getRefAdddate(){  return std::ref(data.adddate); } 
 void setAdddate(   std::string  &val){  data.adddate=val;} 

std::string getNewsico(){  return data.newsico; } 
 void setNewsico(std::string val){  data.newsico=val;} 
std::string& getRefNewsico(){  return std::ref(data.newsico); } 
 void setNewsico(std::string &val){  data.newsico=val;} 

std::string getNewsimg(){  return data.newsimg; } 
 void setNewsimg(std::string val){  data.newsimg=val;} 
std::string& getRefNewsimg(){  return std::ref(data.newsimg); } 
 void setNewsimg(std::string &val){  data.newsimg=val;} 

std::string getDest(){  return data.dest; } 
 void setDest(std::string val){  data.dest=val;} 
std::string& getRefDest(){  return std::ref(data.dest); } 
 void setDest(std::string &val){  data.dest=val;} 

std::string getNewscontent(){  return data.newscontent; } 
 void setNewscontent(std::string val){  data.newscontent=val;} 
std::string& getRefNewscontent(){  return std::ref(data.newscontent); } 
 void setNewscontent(std::string &val){  data.newscontent=val;} 

newsbase::meta getnewData(){
 	 struct meta newdata;
	 return std::move(newdata); 
} 
newsbase::meta getData(){
 	 return data; 
} 
std::vector<newsbase::meta> getRecord(){
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
 	 a.emplace_back(iter.newsid);
	 break;
case 1: 
 	 a.emplace_back(iter.classid);
	 break;
case 2: 
 	 a.emplace_back(iter.topicid);
	 break;
case 3: 
 	 a.emplace_back(iter.channelid);
	 break;
case 4: 
 	 a.emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a.emplace_back(iter.sort);
	 break;
case 20: 
 	 a.emplace_back(iter.userid);
	 break;
case 21: 
 	 a.emplace_back(iter.language);
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
 	 return data.newsid;
	 break;
case 1: 
 	 return data.classid;
	 break;
case 2: 
 	 return data.topicid;
	 break;
case 3: 
 	 return data.channelid;
	 break;
case 4: 
 	 return data.clicknum;
	 break;
case 19: 
 	 return data.sort;
	 break;
case 20: 
 	 return data.userid;
	 break;
case 21: 
 	 return data.language;
	 break;

    }
            return 0;
        }  
    
     template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true > 
    T getVal(newsbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
       
                switch(kpos){

   case 0: 
 	 return iter.newsid;
	 break;
case 1: 
 	 return iter.classid;
	 break;
case 2: 
 	 return iter.topicid;
	 break;
case 3: 
 	 return iter.channelid;
	 break;
case 4: 
 	 return iter.clicknum;
	 break;
case 19: 
 	 return iter.sort;
	 break;
case 20: 
 	 return iter.userid;
	 break;
case 21: 
 	 return iter.language;
	 break;

    }
            return 0;
        }  
    
        template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
        T getVal(std::string keyname){
            
            unsigned char kpos;
            kpos=findcolpos(keyname);
        
            switch(kpos){

    
    }
            return 0.0;
        }  
    
     template<typename T, typename std::enable_if<std::is_floating_point_v<T>,bool>::type = true > 
    T getVal(newsbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
         
                switch(kpos){

   
    }
            return 0.0;
        }  
    
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
        
                switch(kpos){

   case 5: 
 	 return data.newtitle;
	 break;
case 6: 
 	 return data.titletwo;
	 break;
case 7: 
 	 return data.seotitle;
	 break;
case 8: 
 	 return data.keywork;
	 break;
case 9: 
 	 return data.depiction;
	 break;
case 10: 
 	 return data.newscolor;
	 break;
case 11: 
 	 return data.source;
	 break;
case 12: 
 	 return data.author;
	 break;
case 13: 
 	 return data.newsdate;
	 break;
case 14: 
 	 return data.isview;
	 break;
case 15: 
 	 return data.ishome;
	 break;
case 16: 
 	 return data.isnew;
	 break;
case 17: 
 	 return data.isup;
	 break;
case 18: 
 	 return data.iscomment;
	 break;
case 22: 
 	 return data.addtime;
	 break;
case 23: 
 	 return data.adddate;
	 break;
case 24: 
 	 return data.newsico;
	 break;
case 25: 
 	 return data.newsimg;
	 break;
case 26: 
 	 return data.dest;
	 break;
case 27: 
 	 return data.newscontent;
	 break;

  }
        return "";
    }  
   
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(newsbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   case 5: 
 	 return iter.newtitle;
	 break;
case 6: 
 	 return iter.titletwo;
	 break;
case 7: 
 	 return iter.seotitle;
	 break;
case 8: 
 	 return iter.keywork;
	 break;
case 9: 
 	 return iter.depiction;
	 break;
case 10: 
 	 return iter.newscolor;
	 break;
case 11: 
 	 return iter.source;
	 break;
case 12: 
 	 return iter.author;
	 break;
case 13: 
 	 return iter.newsdate;
	 break;
case 14: 
 	 return iter.isview;
	 break;
case 15: 
 	 return iter.ishome;
	 break;
case 16: 
 	 return iter.isnew;
	 break;
case 17: 
 	 return iter.isup;
	 break;
case 18: 
 	 return iter.iscomment;
	 break;
case 22: 
 	 return iter.addtime;
	 break;
case 23: 
 	 return iter.adddate;
	 break;
case 24: 
 	 return iter.newsico;
	 break;
case 25: 
 	 return iter.newsimg;
	 break;
case 26: 
 	 return iter.dest;
	 break;
case 27: 
 	 return iter.newscontent;
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

   case 5: 
 	 a.emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a.emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a.emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a.emplace_back(iter.keywork);
	 break;
case 9: 
 	 a.emplace_back(iter.depiction);
	 break;
case 10: 
 	 a.emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a.emplace_back(iter.source);
	 break;
case 12: 
 	 a.emplace_back(iter.author);
	 break;
case 13: 
 	 a.emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a.emplace_back(iter.isview);
	 break;
case 15: 
 	 a.emplace_back(iter.ishome);
	 break;
case 16: 
 	 a.emplace_back(iter.isnew);
	 break;
case 17: 
 	 a.emplace_back(iter.isup);
	 break;
case 18: 
 	 a.emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a.emplace_back(iter.addtime);
	 break;
case 23: 
 	 a.emplace_back(iter.adddate);
	 break;
case 24: 
 	 a.emplace_back(iter.newsico);
	 break;
case 25: 
 	 a.emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a.emplace_back(iter.dest);
	 break;
case 27: 
 	 a.emplace_back(iter.newscontent);
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
 	 a<<std::to_string(iter.newsid);
	 break;
case 1: 
 	 a<<std::to_string(iter.classid);
	 break;
case 2: 
 	 a<<std::to_string(iter.topicid);
	 break;
case 3: 
 	 a<<std::to_string(iter.channelid);
	 break;
case 4: 
 	 a<<std::to_string(iter.clicknum);
	 break;
case 5: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newtitle); 
	 }else{
	 a<<iter.newtitle;
	 }
	 break;
case 6: 
 	 if(isyinhao){ a<<jsonaddslash(iter.titletwo); 
	 }else{
	 a<<iter.titletwo;
	 }
	 break;
case 7: 
 	 if(isyinhao){ a<<jsonaddslash(iter.seotitle); 
	 }else{
	 a<<iter.seotitle;
	 }
	 break;
case 8: 
 	 if(isyinhao){ a<<jsonaddslash(iter.keywork); 
	 }else{
	 a<<iter.keywork;
	 }
	 break;
case 9: 
 	 if(isyinhao){ a<<jsonaddslash(iter.depiction); 
	 }else{
	 a<<iter.depiction;
	 }
	 break;
case 10: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newscolor); 
	 }else{
	 a<<iter.newscolor;
	 }
	 break;
case 11: 
 	 if(isyinhao){ a<<jsonaddslash(iter.source); 
	 }else{
	 a<<iter.source;
	 }
	 break;
case 12: 
 	 if(isyinhao){ a<<jsonaddslash(iter.author); 
	 }else{
	 a<<iter.author;
	 }
	 break;
case 13: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newsdate); 
	 }else{
	 a<<iter.newsdate;
	 }
	 break;
case 14: 
 	 if(isyinhao){ a<<jsonaddslash(iter.isview); 
	 }else{
	 a<<iter.isview;
	 }
	 break;
case 15: 
 	 if(isyinhao){ a<<jsonaddslash(iter.ishome); 
	 }else{
	 a<<iter.ishome;
	 }
	 break;
case 16: 
 	 if(isyinhao){ a<<jsonaddslash(iter.isnew); 
	 }else{
	 a<<iter.isnew;
	 }
	 break;
case 17: 
 	 if(isyinhao){ a<<jsonaddslash(iter.isup); 
	 }else{
	 a<<iter.isup;
	 }
	 break;
case 18: 
 	 if(isyinhao){ a<<jsonaddslash(iter.iscomment); 
	 }else{
	 a<<iter.iscomment;
	 }
	 break;
case 19: 
 	 a<<std::to_string(iter.sort);
	 break;
case 20: 
 	 a<<std::to_string(iter.userid);
	 break;
case 21: 
 	 a<<std::to_string(iter.language);
	 break;
case 22: 
 	 if(isyinhao){ a<<jsonaddslash(iter.addtime); 
	 }else{
	 a<<iter.addtime;
	 }
	 break;
case 23: 
 	 if(isyinhao){ a<<jsonaddslash(iter.adddate); 
	 }else{
	 a<<iter.adddate;
	 }
	 break;
case 24: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newsico); 
	 }else{
	 a<<iter.newsico;
	 }
	 break;
case 25: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newsimg); 
	 }else{
	 a<<iter.newsimg;
	 }
	 break;
case 26: 
 	 if(isyinhao){ a<<jsonaddslash(iter.dest); 
	 }else{
	 a<<iter.dest;
	 }
	 break;
case 27: 
 	 if(isyinhao){ a<<jsonaddslash(iter.newscontent); 
	 }else{
	 a<<iter.newscontent;
	 }
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	 } 
		 switch(vpos){ 
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
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
 
       case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	 } 
        switch(vpos){ 

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	 } 
 		   switch(vpos){ 

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }
 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
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
 	 a.emplace(iter.newsid,iter);
	 break;
case 1: 
 	 a.emplace(iter.classid,iter);
	 break;
case 2: 
 	 a.emplace(iter.topicid,iter);
	 break;
case 3: 
 	 a.emplace(iter.channelid,iter);
	 break;
case 4: 
 	 a.emplace(iter.clicknum,iter);
	 break;
case 19: 
 	 a.emplace(iter.sort,iter);
	 break;
case 20: 
 	 a.emplace(iter.userid,iter);
	 break;
case 21: 
 	 a.emplace(iter.language,iter);
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

   case 5: 
 	 a.emplace(iter.newtitle,iter);
	 break;
case 6: 
 	 a.emplace(iter.titletwo,iter);
	 break;
case 7: 
 	 a.emplace(iter.seotitle,iter);
	 break;
case 8: 
 	 a.emplace(iter.keywork,iter);
	 break;
case 9: 
 	 a.emplace(iter.depiction,iter);
	 break;
case 10: 
 	 a.emplace(iter.newscolor,iter);
	 break;
case 11: 
 	 a.emplace(iter.source,iter);
	 break;
case 12: 
 	 a.emplace(iter.author,iter);
	 break;
case 13: 
 	 a.emplace(iter.newsdate,iter);
	 break;
case 14: 
 	 a.emplace(iter.isview,iter);
	 break;
case 15: 
 	 a.emplace(iter.ishome,iter);
	 break;
case 16: 
 	 a.emplace(iter.isnew,iter);
	 break;
case 17: 
 	 a.emplace(iter.isup,iter);
	 break;
case 18: 
 	 a.emplace(iter.iscomment,iter);
	 break;
case 22: 
 	 a.emplace(iter.addtime,iter);
	 break;
case 23: 
 	 a.emplace(iter.adddate,iter);
	 break;
case 24: 
 	 a.emplace(iter.newsico,iter);
	 break;
case 25: 
 	 a.emplace(iter.newsimg,iter);
	 break;
case 26: 
 	 a.emplace(iter.dest,iter);
	 break;
case 27: 
 	 a.emplace(iter.newscontent,iter);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }
 switch(vpos){

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }
 switch(vpos){

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }
 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }
 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
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
 	 a.emplace_back(iter.newsid,iter);
	 break;
case 1: 
 	 a.emplace_back(iter.classid,iter);
	 break;
case 2: 
 	 a.emplace_back(iter.topicid,iter);
	 break;
case 3: 
 	 a.emplace_back(iter.channelid,iter);
	 break;
case 4: 
 	 a.emplace_back(iter.clicknum,iter);
	 break;
case 19: 
 	 a.emplace_back(iter.sort,iter);
	 break;
case 20: 
 	 a.emplace_back(iter.userid,iter);
	 break;
case 21: 
 	 a.emplace_back(iter.language,iter);
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

   case 5: 
 	 a.emplace_back(iter.newtitle,iter);
	 break;
case 6: 
 	 a.emplace_back(iter.titletwo,iter);
	 break;
case 7: 
 	 a.emplace_back(iter.seotitle,iter);
	 break;
case 8: 
 	 a.emplace_back(iter.keywork,iter);
	 break;
case 9: 
 	 a.emplace_back(iter.depiction,iter);
	 break;
case 10: 
 	 a.emplace_back(iter.newscolor,iter);
	 break;
case 11: 
 	 a.emplace_back(iter.source,iter);
	 break;
case 12: 
 	 a.emplace_back(iter.author,iter);
	 break;
case 13: 
 	 a.emplace_back(iter.newsdate,iter);
	 break;
case 14: 
 	 a.emplace_back(iter.isview,iter);
	 break;
case 15: 
 	 a.emplace_back(iter.ishome,iter);
	 break;
case 16: 
 	 a.emplace_back(iter.isnew,iter);
	 break;
case 17: 
 	 a.emplace_back(iter.isup,iter);
	 break;
case 18: 
 	 a.emplace_back(iter.iscomment,iter);
	 break;
case 22: 
 	 a.emplace_back(iter.addtime,iter);
	 break;
case 23: 
 	 a.emplace_back(iter.adddate,iter);
	 break;
case 24: 
 	 a.emplace_back(iter.newsico,iter);
	 break;
case 25: 
 	 a.emplace_back(iter.newsimg,iter);
	 break;
case 26: 
 	 a.emplace_back(iter.dest,iter);
	 break;
case 27: 
 	 a.emplace_back(iter.newscontent,iter);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp][vtemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp][vtemp].emplace_back(iter.language);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp][vtemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp][vtemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp][vtemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp][vtemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp][vtemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp][vtemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp][vtemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp][vtemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp][vtemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp][vtemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp][vtemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp][vtemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp][vtemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp][vtemp].emplace_back(iter.newscontent);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp][vtemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp][vtemp].emplace_back(iter.language);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp][vtemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp][vtemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp][vtemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp][vtemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp][vtemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp][vtemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp][vtemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp][vtemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp][vtemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp][vtemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp][vtemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp][vtemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp][vtemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp][vtemp].emplace_back(iter.newscontent);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){

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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp][vtemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp][vtemp].emplace_back(iter.language);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.newsid;
	 break;
case 1: 
 	 vtemp=iter.classid;
	 break;
case 2: 
 	 vtemp=iter.topicid;
	 break;
case 3: 
 	 vtemp=iter.channelid;
	 break;
case 4: 
 	 vtemp=iter.clicknum;
	 break;
case 19: 
 	 vtemp=iter.sort;
	 break;
case 20: 
 	 vtemp=iter.userid;
	 break;
case 21: 
 	 vtemp=iter.language;
	 break;
	  }

 switch(dpos){
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp][vtemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp][vtemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp][vtemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp][vtemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp][vtemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp][vtemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp][vtemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp][vtemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp][vtemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp][vtemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp][vtemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp][vtemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp][vtemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp][vtemp].emplace_back(iter.newscontent);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){

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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp][vtemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp][vtemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp][vtemp].emplace_back(iter.language);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 5: 
 	 vtemp=iter.newtitle;
	 break;
case 6: 
 	 vtemp=iter.titletwo;
	 break;
case 7: 
 	 vtemp=iter.seotitle;
	 break;
case 8: 
 	 vtemp=iter.keywork;
	 break;
case 9: 
 	 vtemp=iter.depiction;
	 break;
case 10: 
 	 vtemp=iter.newscolor;
	 break;
case 11: 
 	 vtemp=iter.source;
	 break;
case 12: 
 	 vtemp=iter.author;
	 break;
case 13: 
 	 vtemp=iter.newsdate;
	 break;
case 14: 
 	 vtemp=iter.isview;
	 break;
case 15: 
 	 vtemp=iter.ishome;
	 break;
case 16: 
 	 vtemp=iter.isnew;
	 break;
case 17: 
 	 vtemp=iter.isup;
	 break;
case 18: 
 	 vtemp=iter.iscomment;
	 break;
case 22: 
 	 vtemp=iter.addtime;
	 break;
case 23: 
 	 vtemp=iter.adddate;
	 break;
case 24: 
 	 vtemp=iter.newsico;
	 break;
case 25: 
 	 vtemp=iter.newsimg;
	 break;
case 26: 
 	 vtemp=iter.dest;
	 break;
case 27: 
 	 vtemp=iter.newscontent;
	 break;
	  }

 switch(dpos){
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp][vtemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp][vtemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp][vtemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp][vtemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp][vtemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp][vtemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp][vtemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp][vtemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp][vtemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp][vtemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp][vtemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp][vtemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp][vtemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp][vtemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp][vtemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp][vtemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp][vtemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp][vtemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp][vtemp].emplace_back(iter.newscontent);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 5: 
 	 a[ktemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp].emplace_back(iter.newscontent);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){

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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp].emplace_back(iter.language);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 5: 
 	 a[ktemp].emplace_back(iter.newtitle);
	 break;
case 6: 
 	 a[ktemp].emplace_back(iter.titletwo);
	 break;
case 7: 
 	 a[ktemp].emplace_back(iter.seotitle);
	 break;
case 8: 
 	 a[ktemp].emplace_back(iter.keywork);
	 break;
case 9: 
 	 a[ktemp].emplace_back(iter.depiction);
	 break;
case 10: 
 	 a[ktemp].emplace_back(iter.newscolor);
	 break;
case 11: 
 	 a[ktemp].emplace_back(iter.source);
	 break;
case 12: 
 	 a[ktemp].emplace_back(iter.author);
	 break;
case 13: 
 	 a[ktemp].emplace_back(iter.newsdate);
	 break;
case 14: 
 	 a[ktemp].emplace_back(iter.isview);
	 break;
case 15: 
 	 a[ktemp].emplace_back(iter.ishome);
	 break;
case 16: 
 	 a[ktemp].emplace_back(iter.isnew);
	 break;
case 17: 
 	 a[ktemp].emplace_back(iter.isup);
	 break;
case 18: 
 	 a[ktemp].emplace_back(iter.iscomment);
	 break;
case 22: 
 	 a[ktemp].emplace_back(iter.addtime);
	 break;
case 23: 
 	 a[ktemp].emplace_back(iter.adddate);
	 break;
case 24: 
 	 a[ktemp].emplace_back(iter.newsico);
	 break;
case 25: 
 	 a[ktemp].emplace_back(iter.newsimg);
	 break;
case 26: 
 	 a[ktemp].emplace_back(iter.dest);
	 break;
case 27: 
 	 a[ktemp].emplace_back(iter.newscontent);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){

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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.newsid);
	 break;
case 1: 
 	 a[ktemp].emplace_back(iter.classid);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.topicid);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.channelid);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.clicknum);
	 break;
case 19: 
 	 a[ktemp].emplace_back(iter.sort);
	 break;
case 20: 
 	 a[ktemp].emplace_back(iter.userid);
	 break;
case 21: 
 	 a[ktemp].emplace_back(iter.language);
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
 	 a[iter.newsid].emplace_back(iter);
	 break;
case 1: 
 	 a[iter.classid].emplace_back(iter);
	 break;
case 2: 
 	 a[iter.topicid].emplace_back(iter);
	 break;
case 3: 
 	 a[iter.channelid].emplace_back(iter);
	 break;
case 4: 
 	 a[iter.clicknum].emplace_back(iter);
	 break;
case 19: 
 	 a[iter.sort].emplace_back(iter);
	 break;
case 20: 
 	 a[iter.userid].emplace_back(iter);
	 break;
case 21: 
 	 a[iter.language].emplace_back(iter);
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

   case 5: 
 	 a[iter.newtitle].emplace_back(iter);
	 break;
case 6: 
 	 a[iter.titletwo].emplace_back(iter);
	 break;
case 7: 
 	 a[iter.seotitle].emplace_back(iter);
	 break;
case 8: 
 	 a[iter.keywork].emplace_back(iter);
	 break;
case 9: 
 	 a[iter.depiction].emplace_back(iter);
	 break;
case 10: 
 	 a[iter.newscolor].emplace_back(iter);
	 break;
case 11: 
 	 a[iter.source].emplace_back(iter);
	 break;
case 12: 
 	 a[iter.author].emplace_back(iter);
	 break;
case 13: 
 	 a[iter.newsdate].emplace_back(iter);
	 break;
case 14: 
 	 a[iter.isview].emplace_back(iter);
	 break;
case 15: 
 	 a[iter.ishome].emplace_back(iter);
	 break;
case 16: 
 	 a[iter.isnew].emplace_back(iter);
	 break;
case 17: 
 	 a[iter.isup].emplace_back(iter);
	 break;
case 18: 
 	 a[iter.iscomment].emplace_back(iter);
	 break;
case 22: 
 	 a[iter.addtime].emplace_back(iter);
	 break;
case 23: 
 	 a[iter.adddate].emplace_back(iter);
	 break;
case 24: 
 	 a[iter.newsico].emplace_back(iter);
	 break;
case 25: 
 	 a[iter.newsimg].emplace_back(iter);
	 break;
case 26: 
 	 a[iter.dest].emplace_back(iter);
	 break;
case 27: 
 	 a[iter.newscontent].emplace_back(iter);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 5: 
 	 a[ktemp][iter.newtitle].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.titletwo].emplace_back(iter);
	 break;
case 7: 
 	 a[ktemp][iter.seotitle].emplace_back(iter);
	 break;
case 8: 
 	 a[ktemp][iter.keywork].emplace_back(iter);
	 break;
case 9: 
 	 a[ktemp][iter.depiction].emplace_back(iter);
	 break;
case 10: 
 	 a[ktemp][iter.newscolor].emplace_back(iter);
	 break;
case 11: 
 	 a[ktemp][iter.source].emplace_back(iter);
	 break;
case 12: 
 	 a[ktemp][iter.author].emplace_back(iter);
	 break;
case 13: 
 	 a[ktemp][iter.newsdate].emplace_back(iter);
	 break;
case 14: 
 	 a[ktemp][iter.isview].emplace_back(iter);
	 break;
case 15: 
 	 a[ktemp][iter.ishome].emplace_back(iter);
	 break;
case 16: 
 	 a[ktemp][iter.isnew].emplace_back(iter);
	 break;
case 17: 
 	 a[ktemp][iter.isup].emplace_back(iter);
	 break;
case 18: 
 	 a[ktemp][iter.iscomment].emplace_back(iter);
	 break;
case 22: 
 	 a[ktemp][iter.addtime].emplace_back(iter);
	 break;
case 23: 
 	 a[ktemp][iter.adddate].emplace_back(iter);
	 break;
case 24: 
 	 a[ktemp][iter.newsico].emplace_back(iter);
	 break;
case 25: 
 	 a[ktemp][iter.newsimg].emplace_back(iter);
	 break;
case 26: 
 	 a[ktemp][iter.dest].emplace_back(iter);
	 break;
case 27: 
 	 a[ktemp][iter.newscontent].emplace_back(iter);
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

   case 5: 
 	 ktemp=iter.newtitle;
	 break;
case 6: 
 	 ktemp=iter.titletwo;
	 break;
case 7: 
 	 ktemp=iter.seotitle;
	 break;
case 8: 
 	 ktemp=iter.keywork;
	 break;
case 9: 
 	 ktemp=iter.depiction;
	 break;
case 10: 
 	 ktemp=iter.newscolor;
	 break;
case 11: 
 	 ktemp=iter.source;
	 break;
case 12: 
 	 ktemp=iter.author;
	 break;
case 13: 
 	 ktemp=iter.newsdate;
	 break;
case 14: 
 	 ktemp=iter.isview;
	 break;
case 15: 
 	 ktemp=iter.ishome;
	 break;
case 16: 
 	 ktemp=iter.isnew;
	 break;
case 17: 
 	 ktemp=iter.isup;
	 break;
case 18: 
 	 ktemp=iter.iscomment;
	 break;
case 22: 
 	 ktemp=iter.addtime;
	 break;
case 23: 
 	 ktemp=iter.adddate;
	 break;
case 24: 
 	 ktemp=iter.newsico;
	 break;
case 25: 
 	 ktemp=iter.newsimg;
	 break;
case 26: 
 	 ktemp=iter.dest;
	 break;
case 27: 
 	 ktemp=iter.newscontent;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.newsid].emplace_back(iter);
	 break;
case 1: 
 	 a[ktemp][iter.classid].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.topicid].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.channelid].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.clicknum].emplace_back(iter);
	 break;
case 19: 
 	 a[ktemp][iter.sort].emplace_back(iter);
	 break;
case 20: 
 	 a[ktemp][iter.userid].emplace_back(iter);
	 break;
case 21: 
 	 a[ktemp][iter.language].emplace_back(iter);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.newsid].emplace_back(iter);
	 break;
case 1: 
 	 a[ktemp][iter.classid].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.topicid].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.channelid].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.clicknum].emplace_back(iter);
	 break;
case 19: 
 	 a[ktemp][iter.sort].emplace_back(iter);
	 break;
case 20: 
 	 a[ktemp][iter.userid].emplace_back(iter);
	 break;
case 21: 
 	 a[ktemp][iter.language].emplace_back(iter);
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
 	 ktemp=iter.newsid;
	 break;
case 1: 
 	 ktemp=iter.classid;
	 break;
case 2: 
 	 ktemp=iter.topicid;
	 break;
case 3: 
 	 ktemp=iter.channelid;
	 break;
case 4: 
 	 ktemp=iter.clicknum;
	 break;
case 19: 
 	 ktemp=iter.sort;
	 break;
case 20: 
 	 ktemp=iter.userid;
	 break;
case 21: 
 	 ktemp=iter.language;
	 break;
	  }

 switch(vpos){
case 5: 
 	 a[ktemp][iter.newtitle].emplace_back(iter);
	 break;
case 6: 
 	 a[ktemp][iter.titletwo].emplace_back(iter);
	 break;
case 7: 
 	 a[ktemp][iter.seotitle].emplace_back(iter);
	 break;
case 8: 
 	 a[ktemp][iter.keywork].emplace_back(iter);
	 break;
case 9: 
 	 a[ktemp][iter.depiction].emplace_back(iter);
	 break;
case 10: 
 	 a[ktemp][iter.newscolor].emplace_back(iter);
	 break;
case 11: 
 	 a[ktemp][iter.source].emplace_back(iter);
	 break;
case 12: 
 	 a[ktemp][iter.author].emplace_back(iter);
	 break;
case 13: 
 	 a[ktemp][iter.newsdate].emplace_back(iter);
	 break;
case 14: 
 	 a[ktemp][iter.isview].emplace_back(iter);
	 break;
case 15: 
 	 a[ktemp][iter.ishome].emplace_back(iter);
	 break;
case 16: 
 	 a[ktemp][iter.isnew].emplace_back(iter);
	 break;
case 17: 
 	 a[ktemp][iter.isup].emplace_back(iter);
	 break;
case 18: 
 	 a[ktemp][iter.iscomment].emplace_back(iter);
	 break;
case 22: 
 	 a[ktemp][iter.addtime].emplace_back(iter);
	 break;
case 23: 
 	 a[ktemp][iter.adddate].emplace_back(iter);
	 break;
case 24: 
 	 a[ktemp][iter.newsico].emplace_back(iter);
	 break;
case 25: 
 	 a[ktemp][iter.newsimg].emplace_back(iter);
	 break;
case 26: 
 	 a[ktemp][iter.dest].emplace_back(iter);
	 break;
case 27: 
 	 a[ktemp][iter.newscontent].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
};
 } 
}
#endif
   