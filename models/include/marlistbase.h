#ifndef ORM_DEFAULT_MARLISTBASEMATA_H
#define ORM_DEFAULT_MARLISTBASEMATA_H
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
    
struct marlistbase
{
    struct meta{
     int mid= 0; //
 std::string name; //名字
 long long phone=0; //手机号
 std::string email; //邮件
 std::string area; //区域
 int stateus= 1; //状态
 } data;
 std::vector<marlistbase::meta> record;
std::string _rmstag="default";//this value must be default or tag value, tag in mysqlconnect config file .
std::vector<unsigned char> _keypos{0x00};
mysqlx::Row _row;
std::vector<marlistbase::meta>::iterator begin(){     return record.begin(); }
std::vector<marlistbase::meta>::iterator end(){     return record.end(); }
std::vector<marlistbase::meta>::const_iterator begin() const{     return record.begin(); }
std::vector<marlistbase::meta>::const_iterator end() const{     return record.end(); }
const std::array<std::string,6> colnames={"mid","name","phone","email","area","stateus"};
const std::array<unsigned char,6> colnamestype= {1,30,1,30,30,1};
std::string tablename="marlist";
std::string modelname="Marlist";

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
case 'e':
   	 return 3;
break;
case 'm':
   	 return 0;
break;
case 'n':
   	 return 1;
break;
case 'p':
   	 return 2;
break;
case 's':
   	 return 5;
break;

             }
             return 255;
           }
         
    int size(){ return record.size(); }   

    std::string getPKname(){ 
       return "mid";
}

      void _setColnamevalue(){
          marlistbase::meta metatemp;   
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
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.phone=_row[i].get<int64_t>();
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.email=(std::string)_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.area=(std::string)_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.stateus=_row[i].get<unsigned>();
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
           marlistbase::meta metatemp;   

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
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.phone=_row[i].get<int64_t>();
		 } 
			 break;
		case 3: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.email=(std::string)_row[i];
		 } 
			 break;
		case 4: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::STRING){ 
				 metatemp.area=(std::string)_row[i];
		 } 
			 break;
		case 5: 
 
	 if(_row[i].getType()==mysqlx::Value::Type::INT64||_row[i].getType()==mysqlx::Value::Type::UINT64){ 
				 metatemp.stateus=_row[i].get<unsigned>();
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
if(data.phone==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.phone);
}
tempsql<<",'"<<stringaddslash(data.email)<<"'";
tempsql<<",'"<<stringaddslash(data.area)<<"'";
if(data.stateus==0){
	tempsql<<",0";
 }else{ 
	tempsql<<","<<std::to_string(data.stateus);
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
if(data.phone==0){
	tempsql<<",`phone`=0";
 }else{ 
	tempsql<<",`phone`="<<std::to_string(data.phone);
}
tempsql<<",`email`='"<<stringaddslash(data.email)<<"'";
tempsql<<",`area`='"<<stringaddslash(data.area)<<"'";
if(data.stateus==0){
	tempsql<<",`stateus`=0";
 }else{ 
	tempsql<<",`stateus`="<<std::to_string(data.stateus);
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
if(data.phone==0){
	tempsql<<",`phone`=0";
 }else{ 
	tempsql<<",`phone`="<<std::to_string(data.phone);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`email`='"<<stringaddslash(data.email)<<"'";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<",`area`='"<<stringaddslash(data.area)<<"'";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(data.stateus==0){
	tempsql<<",`stateus`=0";
 }else{ 
	tempsql<<",`stateus`="<<std::to_string(data.stateus);
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
if(data.phone==0){
	tempsql<<",\"phone\":0";
 }else{ 
	tempsql<<",\"phone\":"<<std::to_string(data.phone);
}
tempsql<<",\"email\":\""<<utf8_to_jsonstring(data.email);
tempsql<<"\"";
tempsql<<",\"area\":\""<<utf8_to_jsonstring(data.area);
tempsql<<"\"";
if(data.stateus==0){
	tempsql<<",\"stateus\":0";
 }else{ 
	tempsql<<",\"stateus\":"<<std::to_string(data.stateus);
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
if(data.phone==0){
	tempsql<<"\"phone\":0";
 }else{ 
	tempsql<<"\"phone\":"<<std::to_string(data.phone);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"email\":\""<<utf8_to_jsonstring(data.email)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"area\":\""<<utf8_to_jsonstring(data.area)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(data.stateus==0){
	tempsql<<"\"stateus\":0";
 }else{ 
	tempsql<<"\"stateus\":"<<std::to_string(data.stateus);
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
if(record[n].phone==0){
	tempsql<<"\"phone\":0";
 }else{ 
	tempsql<<"\"phone\":"<<std::to_string(record[n].phone);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"email\":\""<<utf8_to_jsonstring(record[n].email)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"area\":\""<<utf8_to_jsonstring(record[n].area)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(record[n].stateus==0){
	tempsql<<"\"stateus\":0";
 }else{ 
	tempsql<<"\"stateus\":"<<std::to_string(record[n].stateus);
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
if(record[n].phone==0){
	tempsql<<"\"phone\":0";
 }else{ 
	tempsql<<"\"phone\":"<<std::to_string(record[n].phone);
}
 break;
 case 3:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"email\":\""<<utf8_to_jsonstring(record[n].email)<<"\"";
 break;
 case 4:
 if(jj>0){ tempsql<<","; } 
tempsql<<"\"area\":\""<<utf8_to_jsonstring(record[n].area)<<"\"";
 break;
 case 5:
 if(jj>0){ tempsql<<","; } 
if(record[n].stateus==0){
	tempsql<<"\"stateus\":0";
 }else{ 
	tempsql<<"\"stateus\":"<<std::to_string(record[n].stateus);
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

 long long  getPhone(){  return data.phone; } 
 void setPhone( long long  val){  data.phone=val;} 

std::string getEmail(){  return data.email; } 
 void setEmail(std::string val){  data.email=val;} 
std::string& getRefEmail(){  return std::ref(data.email); } 
 void setEmail(std::string &val){  data.email=val;} 

std::string getArea(){  return data.area; } 
 void setArea(std::string val){  data.area=val;} 
std::string& getRefArea(){  return std::ref(data.area); } 
 void setArea(std::string &val){  data.area=val;} 

 int  getStateus(){  return data.stateus; } 
 void setStateus( int  val){  data.stateus=val;} 

marlistbase::meta getnewData(){
 	 struct meta newdata;
	 return std::move(newdata); 
} 
marlistbase::meta getData(){
 	 return data; 
} 
std::vector<marlistbase::meta> getRecord(){
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
case 2: 
 	 a.emplace_back(iter.phone);
	 break;
case 5: 
 	 a.emplace_back(iter.stateus);
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
 	 return data.mid;
	 break;
case 2: 
 	 return data.phone;
	 break;
case 5: 
 	 return data.stateus;
	 break;

    }
            return 0;
        }  
    
     template<typename T, typename std::enable_if<std::is_integral_v<T>,bool>::type = true > 
    T getVal(marlistbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
       
                switch(kpos){

   case 0: 
 	 return iter.mid;
	 break;
case 2: 
 	 return iter.phone;
	 break;
case 5: 
 	 return iter.stateus;
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
    T getVal(marlistbase::meta & iter,std::string keyname){
         
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

   case 1: 
 	 return data.name;
	 break;
case 3: 
 	 return data.email;
	 break;
case 4: 
 	 return data.area;
	 break;

  }
        return "";
    }  
   
    template<typename T, typename std::enable_if<std::is_same<T,std::string>::value,bool>::type = true > 
    std::string getVal(marlistbase::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   case 1: 
 	 return iter.name;
	 break;
case 3: 
 	 return iter.email;
	 break;
case 4: 
 	 return iter.area;
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
case 3: 
 	 a.emplace_back(iter.email);
	 break;
case 4: 
 	 a.emplace_back(iter.area);
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
 	 a<<std::to_string(iter.phone);
	 break;
case 3: 
 	 if(isyinhao){ a<<jsonaddslash(iter.email); 
	 }else{
	 a<<iter.email;
	 }
	 break;
case 4: 
 	 if(isyinhao){ a<<jsonaddslash(iter.area); 
	 }else{
	 a<<iter.area;
	 }
	 break;
case 5: 
 	 a<<std::to_string(iter.stateus);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	 } 
		 switch(vpos){ 
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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
case 2: 
 	 a.emplace(iter.phone,iter);
	 break;
case 5: 
 	 a.emplace(iter.stateus,iter);
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
case 3: 
 	 a.emplace(iter.email,iter);
	 break;
case 4: 
 	 a.emplace(iter.area,iter);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }
 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }
 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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
case 2: 
 	 a.emplace_back(iter.phone,iter);
	 break;
case 5: 
 	 a.emplace_back(iter.stateus,iter);
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
case 3: 
 	 a.emplace_back(iter.email,iter);
	 break;
case 4: 
 	 a.emplace_back(iter.area,iter);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.stateus);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.area);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.stateus);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.area);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
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

   case 1: 
 	 ktemp=iter.name;
	 break;
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.stateus);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 0: 
 	 vtemp=iter.mid;
	 break;
case 2: 
 	 vtemp=iter.phone;
	 break;
case 5: 
 	 vtemp=iter.stateus;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.area);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
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

   case 1: 
 	 ktemp=iter.name;
	 break;
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
	 break;
	  }

 switch(dpos){
case 0: 
 	 a[ktemp][vtemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp][vtemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp][vtemp].emplace_back(iter.stateus);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 1: 
 	 vtemp=iter.name;
	 break;
case 3: 
 	 vtemp=iter.email;
	 break;
case 4: 
 	 vtemp=iter.area;
	 break;
	  }

 switch(dpos){
case 1: 
 	 a[ktemp][vtemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp][vtemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp][vtemp].emplace_back(iter.area);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.area);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
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

   case 1: 
 	 ktemp=iter.name;
	 break;
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.stateus);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp].emplace_back(iter.name);
	 break;
case 3: 
 	 a[ktemp].emplace_back(iter.email);
	 break;
case 4: 
 	 a[ktemp].emplace_back(iter.area);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
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
 	 ktemp=iter.mid;
	 break;
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp].emplace_back(iter.mid);
	 break;
case 2: 
 	 a[ktemp].emplace_back(iter.phone);
	 break;
case 5: 
 	 a[ktemp].emplace_back(iter.stateus);
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
case 2: 
 	 a[iter.phone].emplace_back(iter);
	 break;
case 5: 
 	 a[iter.stateus].emplace_back(iter);
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
case 3: 
 	 a[iter.email].emplace_back(iter);
	 break;
case 4: 
 	 a[iter.area].emplace_back(iter);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.email].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.area].emplace_back(iter);
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
case 3: 
 	 ktemp=iter.email;
	 break;
case 4: 
 	 ktemp=iter.area;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.mid].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.phone].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.stateus].emplace_back(iter);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 0: 
 	 a[ktemp][iter.mid].emplace_back(iter);
	 break;
case 2: 
 	 a[ktemp][iter.phone].emplace_back(iter);
	 break;
case 5: 
 	 a[ktemp][iter.stateus].emplace_back(iter);
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
case 2: 
 	 ktemp=iter.phone;
	 break;
case 5: 
 	 ktemp=iter.stateus;
	 break;
	  }

 switch(vpos){
case 1: 
 	 a[ktemp][iter.name].emplace_back(iter);
	 break;
case 3: 
 	 a[ktemp][iter.email].emplace_back(iter);
	 break;
case 4: 
 	 a[ktemp][iter.area].emplace_back(iter);
	 break;

                   }
                //a[ktemp][vtemp].emplace_back(dtemp);
        }       

        return a;
    }
};

}
#endif
   