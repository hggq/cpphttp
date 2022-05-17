 

#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <list>
#include <filesystem>
#include <mysqlx/xdevapi.h>

namespace fs = std::filesystem;

int main(int argc,char *argv[]){
 
    fs::path current_path=fs::current_path();

    std::cout<<"\033[36m 🍄 current path:\033[0m \033[1m\033[35m"<<current_path.string()<<"\033[0m"<<std::endl;
    std::string controlpath="controller/";
    std::string controlrunpath="module/controller/";
    fs::path vpath=controlpath;

    if(!fs::exists(vpath)){
        std::cout<<" controller directory not in current path "<<std::endl;
    }
    std::string mysqlconnect="mysqlx://root:123456@127.0.0.1/aaa";
    std::shared_ptr<mysqlx::Session> sess=std::make_shared<mysqlx::Session>(mysqlconnect);   
    std::string tablename;
    if(argc>1){
          tablename=argv[1];
    }else{
          tablename="user";
    }
    std::string realtablename=tablename;
    std::string modelspath="models/";
    std::string sqlqueryring="SHOW FULL COLUMNS FROM ";
    sqlqueryring.append(realtablename);
    std::cout<<"create \033[1m\033[31m"<<realtablename<<"\033[0m table to models"<<std::endl;
    std::string rmstag="default";
    mysqlx::RowResult res= sess->sql(sqlqueryring).execute();
 const mysqlx::Columns &columns = res.getColumns();
         std::vector<std::string>  table,tablecollist;
         std::vector<int>          tablecelwidth;       
         table.resize(res.getColumnCount());
         tablecelwidth.resize(res.getColumnCount());
        
        std::map<std::string,std::map<std::string,std::string>>  tableinfo;

        for (unsigned char index=0; index < res.getColumnCount(); index++)
        {   
            tablecelwidth[index]=0;    
     
            table[index].append(columns[index].getColumnName());
            std::transform(table[index].begin(),table[index].end(),table[index].begin(),::tolower);
            if(tablecelwidth[index]<table[index].size()){
                  tablecelwidth[index]=table[index].size();
            }
         
        }

                std::cout<<std::endl;
    
                mysqlx::Row row;
                int j=0;
                std::ostringstream tp;
                std::string temp;
                std::string fieldname;
                std::string tablepkname;
                 
                tablecollist.reserve(res.count());
                while ((row = res.fetchOne()))
                {
                        fieldname=(std::string)row[0];
                       
                        std::transform(fieldname.begin(),fieldname.end(),fieldname.begin(),::tolower);
                        tablecollist.push_back(fieldname);
                      
                    for(int i=1;i<res.getColumnCount();i++){
                         tp<<row[i];
                         temp=tp.str();
                         std::transform(temp.begin(),temp.end(),temp.begin(),::tolower);
                         bool isc=false;
                         bool isnum=false;
                         std::string limitchar;
                         for(int n=0;n<temp.size();n++){
                             if(temp[n]=='('){
                                    isc=true;
                                    temp[n]=0x00;
                                    isnum=true;
                                    limitchar.clear();
                                    continue;
                             }
                             if(isc){
                                   
                                  if(temp[n]==')'){
                                    tableinfo[fieldname]["limitchar"]= limitchar; 
                                    isnum=false;
                                    
                                 }
                                 if(isnum){
                                     limitchar.push_back(temp[n]);
                                 } 
                                 temp[n]=0x00;
                             }

                         }
                         tableinfo[fieldname][table[i]]=temp;
                         if(table[i]=="extra"){
                              if(temp=="auto_increment"){
                                   tablepkname=fieldname;
                              } 
                         }
                          
                         tp.str("");
                         

                    }
                    
                    j++;
                     
                }
                std::string temptype;
                std::vector<std::string>  metalist;
                std::string outlist; 
                int colpos=0;
                std::vector<std::pair<int,std::string>>  stringcollist;
                std::vector<std::pair<int,std::string>>  numbercollist;
                std::vector<std::pair<int,std::string>>  floatcollist; 
                std::map<unsigned char,std::string>  collisttype; 

                std::map<unsigned char,unsigned char>  colltypeshuzi; 

                std::string collnametemp;
              for(auto &bb:tablecollist){
           
                  outlist.clear();
                  collnametemp.clear();
                  temptype=tableinfo[bb]["type"];  
                  if(temptype[0]=='i'&&temptype[1]=='n'&&temptype[2]=='t'){
                       std::string pretype;
                      std::string typedifinde;
                       
                       if(temptype.size()>3){
                             for(int n=0;n<temptype.size();n++){
                                    if(temptype[n]==0x20){
                                        if(temptype[n+1]=='u'){
                                            pretype="unsigned ";
                                        }
                                        break;
                                    }
                                     
                             }
                       } 
                         typedifinde=" int ";
                        
                       outlist.append(pretype);
                       outlist.append(typedifinde);
                       outlist.append(bb);

                         std::string defaultvalue;
                         if(tableinfo[bb]["default"][0]=='n'||tableinfo[bb]["default"][1]=='n'){
                                defaultvalue.append("0");
                         }else{
                             defaultvalue.append(tableinfo[bb]["default"]);
                         }
                       
                           outlist.append("= ");
                            outlist.append(defaultvalue);
                           outlist.append("; //");
                       
                       
                       outlist.append(tableinfo[bb]["comment"]);


                      metalist.push_back(outlist);  
                      numbercollist.push_back({colpos,bb});
                      collnametemp=pretype+typedifinde; 

                      colltypeshuzi[colpos]=1;
                  }
                  if(temptype[0]=='c'&&temptype[1]=='h'&&temptype[2]=='a'&&temptype[3]=='r'){

                        int limitnumber=std::stoi(tableinfo[bb]["limitchar"].c_str());
                        limitnumber+=1;

                         outlist.append(" std::string ");
                   
                       outlist.append(bb);
                         std::string defaultvalue;
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("; //");
                         }else{
                             outlist.append("=\"");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("\"; //"); 
                         }
                       
                            

                       outlist.append(tableinfo[bb]["comment"]);

                        metalist.push_back(outlist);  
                        stringcollist.push_back({colpos,bb});
                        collnametemp="std::string"; 
                        colltypeshuzi[colpos]=30;
                  }
                   if(temptype[0]=='t'&&temptype[1]=='e'&&temptype[2]=='x'&&temptype[3]=='t'){


                         outlist.append(" std::string ");
                   
                       outlist.append(bb);
                  
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("; //");
                         }else{
                             outlist.append("=\"");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("\"; //"); 
                         }
                       
                            

                       outlist.append(tableinfo[bb]["comment"]);

                        metalist.push_back(outlist);  
                        stringcollist.push_back({colpos,bb});
                        collnametemp="std::string"; 
                        colltypeshuzi[colpos]=30;
                  }
                   if(temptype[0]=='m'&&temptype[1]=='e'&&temptype[2]=='d'&&temptype[3]=='i'&&temptype[4]=='u'&&temptype[5]=='m'&&temptype[6]=='t'&&temptype[7]=='e'&&temptype[8]=='x'&&temptype[9]=='t'){

                        //mediumtext 
                         outlist.append(" std::string ");
                   
                       outlist.append(bb);
                  
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("; //");
                         }else{
                             outlist.append("=\"");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("\"; //"); 
                         }
                       
                            

                       outlist.append(tableinfo[bb]["comment"]);

                        metalist.push_back(outlist);  
                        stringcollist.push_back({colpos,bb});
                        collnametemp="std::string"; 
                        colltypeshuzi[colpos]=30;
                  }
                  if(temptype[0]=='l'&&temptype[1]=='o'&&temptype[2]=='n'&&temptype[3]=='g'&&temptype[4]=='t'&&temptype[5]=='e'&&temptype[6]=='x'&&temptype[7]=='t'){

                        //longtext 

                         outlist.append(" std::string ");
                   
                       outlist.append(bb);
                  
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("; //");
                         }else{
                             outlist.append("=\"");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("\"; //"); 
                         }
                       

                       outlist.append(tableinfo[bb]["comment"]);

                        metalist.push_back(outlist);  
                        stringcollist.push_back({colpos,bb});
                        collnametemp="std::string"; 
                        colltypeshuzi[colpos]=30;
                  }
                   if(temptype[0]=='v'&&temptype[1]=='a'&&temptype[2]=='r'&&temptype[3]=='c'&&temptype[4]=='h'&&temptype[5]=='a'&&temptype[6]=='r'){

                        int limitnumber=std::stoi(tableinfo[bb]["limitchar"].c_str());
                        limitnumber+=1;
             
                           outlist.append(" std::string ");
                   
                       outlist.append(bb);
                       std::string defaultvalue;
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("; //");
                         }else{
                             outlist.append("=\"");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("\"; //"); 
                         }
                       outlist.append(tableinfo[bb]["comment"]);

                        metalist.push_back(outlist);  
                        stringcollist.push_back({colpos,bb});
                        collnametemp="std::string"; 
                        colltypeshuzi[colpos]=30;
                  }
                  if(temptype[0]=='t'&&temptype[1]=='i'&&temptype[2]=='n'&&temptype[3]=='y'&&temptype[4]=='i'&&temptype[5]=='n'&&temptype[6]=='t'){

                     
                     std::string pretype;
                      std::string typedifinde;
                       
                       if(temptype.size()>8){
                             for(int n=0;n<temptype.size();n++){
                                    if(temptype[n]==0x20){
                                        if(temptype[n+1]=='u'){
                                            pretype="unsigned ";
                                        }
                                        break;
                                    }
                                    
                             }
                       } 
                        outlist.append(pretype);
                          outlist.append(" char ");
                   
                       outlist.append(bb);
                        if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0; //");
                         }else{
                             if(tableinfo[bb]["default"][0]>='0'&&tableinfo[bb]["default"][0]<='9'){
                                 outlist.append("=");
                                outlist.append(tableinfo[bb]["default"]);
                                outlist.append("; //"); 
                             }else{
                                 outlist.append("='");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("'; //"); 
                             }
                             
                         }
                       outlist.append(tableinfo[bb]["comment"]);
                       metalist.push_back(outlist);  
                       numbercollist.push_back({colpos,bb});
                       collnametemp=pretype+" int "; 
                       colltypeshuzi[colpos]=1;
                  }
                   if(temptype[0]=='b'&&temptype[1]=='i'&&temptype[2]=='g'&&temptype[3]=='i'&&temptype[4]=='n'&&temptype[5]=='t'){

                     
                     std::string pretype;
                      std::string typedifinde;
                       
                       if(temptype.size()>7){
                             for(int n=0;n<temptype.size();n++){
                                    if(temptype[n]==0x20){
                                        if(temptype[n+1]=='u'){
                                            pretype="unsigned ";
                                        }
                                        break;
                                    }
                                    
                             }
                       } 

                       outlist.append(pretype);
                          outlist.append(" long long ");
                   
                       outlist.append(bb);
                     
                         if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0; //");
                         }else{
                             outlist.append("=");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("; //"); 
                         }

                       outlist.append(tableinfo[bb]["comment"]);
                       metalist.push_back(outlist); 
                       numbercollist.push_back({colpos,bb}); 
                       collnametemp=pretype+" long long "; 
                       colltypeshuzi[colpos]=1;
                  }

                  if(temptype[0]=='s'&&temptype[1]=='m'&&temptype[2]=='a'&&temptype[3]=='l'&&temptype[4]=='l'&&temptype[5]=='i'&&temptype[6]=='n'&&temptype[7]=='t'){

                     //smallint
                     std::string pretype;
                      std::string typedifinde;
                       
                       if(temptype.size()>8){
                             for(int n=0;n<temptype.size();n++){
                                    if(temptype[n]==0x20){
                                        if(temptype[n+1]=='u'){
                                            pretype="unsigned ";
                                        }
                                        break;
                                    }
                                    
                             }
                       } 

                        outlist.append(pretype);
                          outlist.append(" short ");
                   
                       outlist.append(bb);
                       if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0; //");
                         }else{
                             outlist.append("=");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("; //"); 
                         }
                       outlist.append(tableinfo[bb]["comment"]);

                       metalist.push_back(outlist);  
                       numbercollist.push_back({colpos,bb});
                       collnametemp=pretype+" int "; 
                       colltypeshuzi[colpos]=1;
                  }

                    //decimal
                 if(temptype[0]=='d'&&temptype[1]=='e'&&temptype[2]=='c'&&temptype[3]=='i'&&temptype[4]=='m'&&temptype[5]=='a'&&temptype[6]=='l'){

                          outlist.append(" float ");
                   
                       outlist.append(bb);
                       if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0.0; //");
                         }else{
                             outlist.append("=");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("; //"); 
                         }
                       outlist.append(tableinfo[bb]["comment"]);
                        metalist.push_back(outlist);  
                        floatcollist.push_back({colpos,bb});
                        collnametemp=" double "; 
                        colltypeshuzi[colpos]=20;
                  }
                   if(temptype[0]=='f'&&temptype[1]=='l'&&temptype[2]=='o'&&temptype[3]=='a'&&temptype[4]=='t'){
                        
                          outlist.append(" float ");
                   
                       outlist.append(bb);
                       if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0.0; //");
                         }else{
                             outlist.append("=");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("; //"); 
                         }
                       outlist.append(tableinfo[bb]["comment"]);
 
                        metalist.push_back(outlist); 
                        floatcollist.push_back({colpos,bb}); 
                        collnametemp=" double "; 
                        colltypeshuzi[colpos]=20;
                  }
                 if(temptype[0]=='d'&&temptype[1]=='o'&&temptype[2]=='u'&&temptype[3]=='b'&&temptype[4]=='l'&&temptype[5]=='e'){

 

                          outlist.append(" double ");
                   
                       outlist.append(bb);
                       if(tableinfo[bb]["default"]=="<null>"||tableinfo[bb]["default"]=="null"){
                                outlist.append("=0.0; //");
                         }else{
                             outlist.append("=");
                             outlist.append(tableinfo[bb]["default"]);
                             outlist.append("; //"); 
                         }
                       outlist.append(tableinfo[bb]["comment"]);
                       
                        metalist.push_back(outlist);  

                         floatcollist.push_back({colpos,bb});
                         collnametemp=" double "; 
                         colltypeshuzi[colpos]=20;
                  }
                  if(collnametemp.size()==0){
                      collnametemp=" int ";
                  }
                  collisttype[colpos]=collnametemp;
                  colpos++;
              } 



        std::string filebasename=modelspath;
        std::string modelfileclass=modelspath;
        std::string createfilename;
        std::string headtxt;
             if(modelfileclass.back()!='/'){
                modelfileclass.push_back('/');
            }

    createfilename=tablename;

 if(createfilename[0]>96&&createfilename[0]<123){
				createfilename[0]=createfilename[0]-32;
			}

            modelfileclass.append(createfilename);
        std::string modelfileclasscpp=modelfileclass;    
                modelfileclasscpp.append(".cpp");


std::ostringstream filemodelstremcpp;

filemodelstremcpp<<"#include \"mysqlmodel.hpp\" \n#include \""<<tablename<<"base.h\"\n#include \""<<createfilename<<".h\"\n";


filemodelstremcpp<<"\n/* 如果此文件存在不会自动覆盖，没有则会自动生成。\n*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */\n";
filemodelstremcpp<<"\n";
// filemodelstremcpp<<"class "<<createfilename<<" : public HTTP::mysqlclienDB<"<<createfilename<<","<<tablename<<"base>{\n";
// filemodelstremcpp<<"\t public:\n";
filemodelstremcpp<<"\t "<<createfilename<<"::"<<createfilename<<"(std::string dbtag):mysqlclienDB(dbtag){}\n";
filemodelstremcpp<<"\t "<<createfilename<<"::"<<createfilename<<"():mysqlclienDB(){}\n";
// filemodelstremcpp<<"};\n";

 headtxt.append(filemodelstremcpp.str());
            filemodelstremcpp.str("");


if(!fs::exists(modelfileclasscpp)){

     FILE *ff=fopen(modelfileclasscpp.c_str(),"wb"); 
 fwrite(&headtxt[0],1,headtxt.size(),ff); 

 fclose(ff);

}
 headtxt.clear();
modelfileclasscpp=modelfileclass;    
 modelfileclasscpp.append(".h");


filemodelstremcpp<<"#include \"mysqlmodel.hpp\" \n #include \""<<tablename<<"base.h\"\n";
filemodelstremcpp<<"\n/* 如果此文件存在不会自动覆盖，没有则会自动生成。\n*If this file exists, it will not be overwritten automatically. If not, it will be generated automatically. */\n";
filemodelstremcpp<<"\n";
filemodelstremcpp<<"class "<<createfilename<<" : public orm::mysqlclienDB<"<<createfilename<<","<<tablename<<"base>{\n";
filemodelstremcpp<<"\t public:\n";
filemodelstremcpp<<"\t "<<createfilename<<"(std::string dbtag):mysqlclienDB(dbtag){}\n";
filemodelstremcpp<<"\t "<<createfilename<<"():mysqlclienDB(){}\n";
filemodelstremcpp<<"};\n";


 headtxt.append(filemodelstremcpp.str());
            filemodelstremcpp.str("");
            
if(!fs::exists(modelfileclasscpp)){

     FILE *ff=fopen(modelfileclasscpp.c_str(),"wb"); 
 fwrite(&headtxt[0],1,headtxt.size(),ff); 

 fclose(ff);

}
 headtxt.clear();

            if(filebasename.back()!='/'){
                filebasename.push_back('/');
            }
            filebasename.append("meta/");
            filebasename.append(tablename);
            filebasename.append("base.h");



            FILE *f=fopen(filebasename.c_str(),"wb"); 

            

      headtxt=R"(/*
*This file is auto create from cli
*本文件为自动生成
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
//namespace orm {
struct )";
    headtxt.append(tablename);
    headtxt+=R"(base
{
    struct meta{
    )";    

        std::ostringstream filemodelstrem;
            
       for(int j=0;j<metalist.size();j++){
                    filemodelstrem<<metalist[j]<<std::endl;
              }
             filemodelstrem<<" } data;\n ";
             filemodelstrem<<"std::vector<"<<tablename<<"base::meta> record;\n";
             filemodelstrem<<"std::string _rmstag=\""<<rmstag<<"\";//this value must be default or tag value, tag in mysqlconnect config file .\n";
             filemodelstrem<<"std::vector<unsigned char> _keypos;\n";
             filemodelstrem<<"mysqlx::Row _row;\n";
             
             filemodelstrem<<"std::vector<"<<tablename<<"base::meta>::iterator begin(){     return record.begin(); }\n";
             filemodelstrem<<"std::vector<"<<tablename<<"base::meta>::iterator end(){     return record.end(); }\n";
             filemodelstrem<<"std::vector<"<<tablename<<"base::meta>::const_iterator begin() const{     return record.begin(); }\n";
             filemodelstrem<<"std::vector<"<<tablename<<"base::meta>::const_iterator end() const{     return record.end(); }\n";

             filemodelstrem<<"const std::array<std::string,"<<std::to_string(tablecollist.size())<<"> colnames={";   

                 for(int j=0;j<tablecollist.size();j++){
                    if(j>0){
                        filemodelstrem<<",";
                    } 
                    filemodelstrem<<"\""<<tablecollist[j]<<"\"";
              }
              filemodelstrem<<"};\r\n";

            //     filemodelstrem<<" std::map<std::string,unsigned char> colnamespos={";   

            //      for(int j=0;j<tablecollist.size();j++){
            //         if(j>0){
            //             filemodelstrem<<",";
            //         } 
            //         filemodelstrem<<"{\""<<tablecollist[j]<<"\","<<std::to_string(j)<<"}";
            //   }
            //   filemodelstrem<<"};\r\n";

                 filemodelstrem<<"const std::array<unsigned char,"<<std::to_string(tablecollist.size())<<"> colnamestype= {";
 
            for(unsigned char j=0;j<tablecollist.size();j++){
                    
                    if(j>0){
                         filemodelstrem<<",";  
                    }
                    filemodelstrem<<std::to_string(colltypeshuzi[j]);

            }   
             filemodelstrem<<"};\r\n";

            headtxt.append(filemodelstrem.str());
            filemodelstrem.str("");
            //头部定义
           
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();
               headtxt="std::string tablename=\"";
               headtxt.append(realtablename);
               headtxt+="\";\n";

              headtxt+=R"(
	  unsigned char findcolpos(std::string coln){
		    unsigned char  bi=coln[0];
            char colpospppc;
	         if(bi<91&&bi>64){
				bi+=32;
			}
            switch(coln[0]){


         )";    
              filemodelstrem.str("");
              std::map<char,std::vector<unsigned char>> alpaz;
              for(unsigned char j=0;j<tablecollist.size();j++){
                   char taa=tablecollist[j][0];
                   alpaz[taa].emplace_back(j);
             } 
                for(auto itter=alpaz.begin();itter!=alpaz.end();itter++){
                        filemodelstrem<<"case '"<<itter->first<<"':\n";
                                            if(itter->second.size()==1){
                                                        filemodelstrem<<"   \t return "<<std::to_string(itter->second[0])<<";\nbreak;\n";
                                            }else{
                                                  filemodelstrem<<" switch(coln.size()){  \n";
                                                    std::map<unsigned char,std::vector<unsigned char>> sizecolz;

                                                    for(int m=0;m<itter->second.size();m++){

                                                                   unsigned char taa=tablecollist[itter->second[m]].size();
                                                                     sizecolz[taa].emplace_back(itter->second[m]);

                                                          
                                                    }
                                                    for(auto ittter=sizecolz.begin();ittter!=sizecolz.end();ittter++){
                                                            filemodelstrem<<"case "<<std::to_string(ittter->first)<<":\n";
                                                            if(ittter->second.size()==1){
                                                                         filemodelstrem<<"   \t return "<<std::to_string(ittter->second[0])<<";\nbreak;\n";
                                                            }else{
                                                                    char ttttp=0x00; 
                                                                    std::map<unsigned char,std::vector<unsigned char>> backcolz;
                                                                   for(int mm=0;mm<ittter->second.size();mm++){
                                                                        ttttp=tablecollist[ittter->second[mm]].back();
                                                                        backcolz[ttttp].emplace_back(ittter->second[mm]);
                                                                   }
                                                                   std::ostringstream backcachep; 
                                                                   backcachep<<"  colpospppc=coln.back();\n    if(colpospppc<91&&bi>64){ colpospppc+=32; }\n";
                                                                   bool isbackppp=false;
                                                                   std::map<unsigned char,unsigned char> hasbackpos;
                                                                   for(auto ipper=backcolz.begin();ipper!=backcolz.end();ipper++){

                                                                             if(ipper->second.size()==1){
                                                                                       backcachep<<" if(colpospppc=='"<<tablecollist[ipper->second[0]].back()<<"'){ return "<<std::to_string(ipper->second[0])<<"; }\n";
                                                                                    isbackppp=true;
                                                                                    hasbackpos[ipper->second[0]]=1;
                                                                             }
                                                                   }
                                                                   if(isbackppp){
                                                                       filemodelstrem<<backcachep.str();
                                                                   }
                                                                   for(int mm=0;mm<ittter->second.size();mm++){
                                                                           auto ippter =hasbackpos.find(ittter->second[mm]);
                                                                           if(ippter==hasbackpos.end()){
                                                                               filemodelstrem<<" if(strcasecmp(coln.c_str(), \""<<tablecollist[ittter->second[mm]]<<"\") == 0){ return "<<std::to_string(ittter->second[mm])<<"; }\n";
                                                                           }
                                                                           

                                                                   }
                                                                   filemodelstrem<<"   \t break;\n";
                                                            }
                                                    }

                                                   
                                                  filemodelstrem<<" }\n break;\n";           
                                            }
                }

             headtxt.append(filemodelstrem.str());
            filemodelstrem.str("");

        headtxt+=R"(
             }
             return 255;
           }
         )"; 
              headtxt+=R"(
    int size(){ return record.size(); }   

    std::string getPKname(){ 
       return ")";   
             headtxt.append(tablepkname);   
             headtxt.append("\";\n}\n");

             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();

             headtxt=R"(
      void _setColnamevalue(){
          )";
           headtxt+=tablename;
           headtxt+=R"(base::meta metatemp;   
         for(unsigned char i=0;i<_keypos.size();i++){
                 switch(_keypos[i]){
        )"; 

               fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();   

                 filemodelstrem.str("");   
                 for(int j=0;j<tablecollist.size();j++){
                     
                        filemodelstrem<<"\t\tcase "<<std::to_string(j)<<": \n ";
                   
                    filemodelstrem<<"\t\t\t\t metatemp."<<tablecollist[j]<<"=("<<collisttype[j]<<")_row[i];\n";
                    filemodelstrem<<"\t\t\t break;\n";
                    }

            headtxt.append(filemodelstrem.str());
           // filemodelstrem.str("");
              fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();   



             headtxt=R"(
                 }

                 if(i>210){
                     break;
                 }
          }
          data=metatemp;
          record.emplace_back(metatemp);   
   } 
         void _addnewrowvalue(){
           )";
           headtxt+=tablename;
           headtxt+=R"(base::meta metatemp;   

          for(unsigned char i=0;i<_keypos.size();i++){
 
                 switch(_keypos[i]){

        )"; 

               fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();   

            headtxt.append(filemodelstrem.str());
            filemodelstrem.str("");
              fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


               headtxt=R"(
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

        )";  

                    fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


      std::string insertstring;
              std::ostringstream insertstrem;
             
               for(int j=0;j<tablecollist.size();j++){
                     
                     //数字
                    if(j==0){
                        insertstrem<<"if(data."<<tablecollist[j]<<"==0){\n";
                        insertstrem<<"tempsql<<\"null\";\n";
                         insertstrem<<" }else{ \n";
                         insertstrem<<"\ttempsql<<std::to_string(data."<<tablecollist[j]<<");\n";   
                          insertstrem<<"}\n";
                        continue;
                    }    
                    if(colltypeshuzi[j]<30){
                         insertstrem<<"if(data."<<tablecollist[j]<<"==0){\n";
                         
                              insertstrem<<"\ttempsql<<\",0\";\n";        
                          
                           insertstrem<<" }else{ \n";
                        
                              insertstrem<<"\ttempsql<<\",\"<<std::to_string(data."<<tablecollist[j]<<");\n";        
                                                  
                         insertstrem<<"}\n";
                    }else{
                          
                          insertstrem<<"tempsql<<\",'\"<<stringaddslash(data."<<tablecollist[j]<<")<<\"'\";\n";       
                         
                    }
                    
              }
                insertstrem<<"tempsql<<\")\";\n";
              headtxt.append(insertstrem.str());
             
               fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

  headtxt=R"(
     
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

        )";  

                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


  std::string updatestring;
              std::ostringstream updatestrem;
        
               for(int j=0;j<tablecollist.size();j++){
                     
                     //数字
                    if(colltypeshuzi[j]<30){
                         updatestrem<<"if(data."<<tablecollist[j]<<"==0){\n";
                         if(j>0){
                            updatestrem<<"\ttempsql<<\",`"<<tablecollist[j]<<"`=0\";\n";        
                         }else{
                            updatestrem<<"\ttempsql<<\"`"<<tablecollist[j]<<"`=0\";\n";    
                         }
                         updatestrem<<" }else{ \n";
                         if(j>0){
                            updatestrem<<"\ttempsql<<\",`"<<tablecollist[j]<<"`=\"<<std::to_string(data."<<tablecollist[j]<<");\n";        
                         }else{
                            updatestrem<<"\ttempsql<<\"`"<<tablecollist[j]<<"`=\"<<std::to_string(data."<<tablecollist[j]<<");\n";  
                              
                         }
                        
                         
                         updatestrem<<"}\n";
                    }else{
                         if(j>0){
                             updatestrem<<"tempsql<<\",`"<<tablecollist[j]<<"`='\"<<stringaddslash(data."<<tablecollist[j]<<")<<\"'\";\n";       
                         }else{
                             updatestrem<<"tempsql<<\"`"<<tablecollist[j]<<"`='\"<<stringaddslash(data."<<tablecollist[j]<<")<<\"'\";\n";   
                         }
                        
                         
                    }
                    
              }
              headtxt.append(updatestrem.str());
         
                headtxt.append(" }else{ \n");

                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


  headtxt=R"(
     
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

        )";  

                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  



            std::string update2string;
              std::ostringstream update2strem;
           
               for(int j=0;j<tablecollist.size();j++){
                     
                     //数字
                     update2strem<<" case "<<std::to_string(j)<<":\n";            
                     update2strem<<" if(jj>0){ tempsql<<\",\"; } \n";  
                    if(colltypeshuzi[j]<30){
                         update2strem<<"if(data."<<tablecollist[j]<<"==0){\n";
                         if(j>0){
                            update2strem<<"\ttempsql<<\",`"<<tablecollist[j]<<"`=0\";\n";        
                         }else{
                            update2strem<<"\ttempsql<<\"`"<<tablecollist[j]<<"`=0\";\n";    
                         }
                         update2strem<<" }else{ \n";
                         if(j>0){
                            update2strem<<"\ttempsql<<\",`"<<tablecollist[j]<<"`=\"<<std::to_string(data."<<tablecollist[j]<<");\n";        
                         }else{
                            update2strem<<"\ttempsql<<\"`"<<tablecollist[j]<<"`=\"<<std::to_string(data."<<tablecollist[j]<<");\n";  
                              
                         }
                        
                         
                         update2strem<<"}\n";
                    }else{
                         if(j>0){
                             update2strem<<"tempsql<<\",`"<<tablecollist[j]<<"`='\"<<stringaddslash(data."<<tablecollist[j]<<")<<\"'\";\n";       
                         }else{
                             update2strem<<"tempsql<<\"`"<<tablecollist[j]<<"`='\"<<stringaddslash(data."<<tablecollist[j]<<")<<\"'\";\n";   
                         }
                        
                         
                    }
                    update2strem<<" break;\n";  
                    
              }
              headtxt.append(update2strem.str());
             
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
     
                  default:
                                ;
                     }
                 }   

            }        

        return std::move(tempsql.str());
   } 
   std::string tojson(){
       std::ostringstream tempsql;

        )";  

                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  
 
              std::ostringstream jsonstrem;
              headtxt="tempsql<<\"[\";\n";
               for(int j=0;j<tablecollist.size();j++){
                     
                     //数字
                    if(colltypeshuzi[j]<30){
                         jsonstrem<<"if(data."<<tablecollist[j]<<"==0){\n";
                         if(j>0){
                            jsonstrem<<"\ttempsql<<\",{\\\""<<tablecollist[j]<<"\\\":0}\";\n";        
                         }else{
                            jsonstrem<<"\ttempsql<<\"{\\\""<<tablecollist[j]<<"\\\":0}\";\n";    
                         }
                         jsonstrem<<" }else{ \n";
                         if(j>0){
                            jsonstrem<<"\ttempsql<<\",{\\\""<<tablecollist[j]<<"\\\":\"<<std::to_string(data."<<tablecollist[j]<<");\n";        
                         }else{
                            jsonstrem<<"\ttempsql<<\"{\\\""<<tablecollist[j]<<"\\\":\"<<std::to_string(data."<<tablecollist[j]<<");\n";  
                              
                         }
                         jsonstrem<<"\ttempsql<<\"}\";\n";
                         
                         jsonstrem<<"}\n";
                    }else{
                         if(j>0){
                             jsonstrem<<"tempsql<<\",{\\\""<<tablecollist[j]<<"\\\":\\\"\"<<jsonaddslash(data."<<tablecollist[j]<<");\n";       
                         }else{
                             jsonstrem<<"tempsql<<\"{\\\""<<tablecollist[j]<<"\\\":\\\"\"<<jsonaddslash(data."<<tablecollist[j]<<");\n";  
                         }
                        
                         jsonstrem<<"tempsql<<\"\\\"}\";\n";
                    }
                    
              }
              headtxt.append(jsonstrem.str());
              headtxt.append("tempsql<<\"]\";\n");
            
                         fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

 headtxt=R"(
     
     return std::move(tempsql.str());             
   }   
   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

              headtxt="long long getPK(){  return data."+tablepkname+"; } \n";
               headtxt.append(" void setPK(long long val){  data."+tablepkname+"=val;} \n");  
                      fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  



              std::ostringstream getsetstrem;  
              std::string uptempstring;
                //自动get set方法
              for(int j=0;j<tablecollist.size();j++){
                 getsetstrem<<collisttype[j];  
                 uptempstring=tablecollist[j];
                    if(uptempstring[0]>='a'&&uptempstring[0]<='z'){
                       uptempstring[0]=uptempstring[0]-32;
                    }
                 getsetstrem<<" get"<<uptempstring<<"(){  return data."+tablecollist[j]+"; } \n";
                 getsetstrem<<" void set"<<uptempstring<<"("<<collisttype[j]<<" val){  data."+tablecollist[j]+"=val;} \n";  
                 if(colltypeshuzi[j]>29){
                      getsetstrem<<collisttype[j]; 
                      getsetstrem<<"& getRef"<<uptempstring<<"(){  return std::ref(data."+tablecollist[j]+"); } \n";
                      getsetstrem<<" void set"<<uptempstring<<"("<<collisttype[j]<<" &val){  data."+tablecollist[j]+"=val;} \n";  
                 }
                  getsetstrem<<"\n";     
              }

             headtxt.append(getsetstrem.str());  

             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

            headtxt=tablename+"base::meta getnewData(){\n \t struct meta newdata;\n\t return std::move(newdata); \n} \n";
            
            headtxt.append(tablename);
            headtxt.append("base::meta getData(){\n \t return data; \n} \n");
            headtxt.append("std::vector<");
            headtxt.append(tablename);
            headtxt.append("base::meta> getRecord(){\n \t return record; \n} \n");
  
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  



 headtxt=R"(
    std::vector<unsigned long long> getulongtCol(std::string keyname){
         std::vector<unsigned long long> a;
         unsigned char kpos;
         kpos=findcolpos(keyname);
        for(auto &iter:record){
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

 
     std::ostringstream getcollstrem;  

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t a.emplace_back(iter."<<kaa.second<<");"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  



 headtxt=R"(
          }
        }
        return a;
    }
    std::vector<long long> getlongCol(std::string keyname){
        std::vector<long long> a;
         unsigned char kpos;
        kpos=findcolpos(keyname);
        for(auto &iter:record){
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t a.emplace_back(iter."<<kaa.second<<");"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        }
        return a;
    }  
   )"; 

 fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

/////////////////////////////////////////
  
 headtxt=R"(

    std::vector<float> getfloatCol(std::string keyname){
        std::vector<float> a;
         unsigned char kpos;
         kpos=findcolpos(keyname);
        for(auto &iter:record){
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

           for(auto &kaa:floatcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t a.emplace_back(iter."<<kaa.second<<");"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        }
        return a;
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  
////////////////////////////////////////////////
  
 headtxt=R"(

    long long getlongVal(std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
      
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t return data."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return 0;
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  
///------------------
 headtxt=R"(

    long long getlongVal()";
           headtxt+=tablename;
           headtxt+=R"(base::meta & iter,std::string keyname){
         
         unsigned char kpos;
         kpos=findcolpos(keyname);
       
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t return iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return 0;
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

//////////////////////////

  
 headtxt=R"(

    float getfloatVal(std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
                    for(auto &kaa:floatcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t return data."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return 0.0;
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  
//--------------------
 headtxt=R"(

    float getfloatVal()";
           headtxt+=tablename;
           headtxt+=R"(base::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
         
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
                    for(auto &kaa:floatcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t return iter."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return 0.0;
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

/////////////////////////
  
 headtxt=R"(

    std::string getstringVal(std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
        
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
                    for(auto &kaa:stringcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t return data."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return "";
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

//-----------------------

 headtxt=R"(

    std::string getstringVal()";
           headtxt+=tablename;
           headtxt+=R"(base::meta & iter,std::string keyname){
         
         unsigned char kpos;
        kpos=findcolpos(keyname);
       
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

             getcollstrem.str("");  

          
                    for(auto &kaa:stringcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t return iter."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
        return "";
    }  
   )";            
        fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

/////////////////////////
  headtxt=R"( 
    std::vector<std::string> getstrCol(std::string keyname){
        std::vector<std::string> a;
         unsigned char kpos;
        kpos=findcolpos(keyname);
 
         for(auto &iter:record){
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


             getcollstrem.str("");  

              for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t a.emplace_back(iter."<<kaa.second<<");"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
   }
        }       

        return a;
    }  
    std::string getstringCol(std::string keyname,bool isyinhao=false){
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

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  

 

            
             getcollstrem.str("");  

               for(int jj=0;jj<tablecollist.size();jj++){
                     
                        getcollstrem<<"case "<<std::to_string(jj)<<": \n ";
                   
                    getcollstrem<<"\t a<<iter."<<tablecollist[jj]<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
    }
                j++;
        } 
        if(isyinhao&&j>0){
             a<<'"';
        }      
        return a.str();
    }
    std::map<std::string,std::string> getstrstrCols(std::string keyname,std::string valname){
        std::map<std::string,std::string> a;
        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         std::string ktemp,vtemp;
         for(auto &iter:record){
                
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 
             getcollstrem.str("");  

              for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

          
                getcollstrem<<"\t } \n        switch(vpos){ \n";
 

                   for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

               headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 


 headtxt=R"(
    }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    } )";
      fwrite(&headtxt[0],1,headtxt.size(),f); 
      headtxt.clear(); 

///////////////////////
 headtxt=R"(
  std::map<std::string,float> getstrfloatCols(std::string keyname,std::string valname){
        std::map<std::string,float> a;
        unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         std::string ktemp;
         float vtemp;
         for(auto &iter:record){
                
                switch(kpos){
 
       )";
      fwrite(&headtxt[0],1,headtxt.size(),f); 
      headtxt.clear(); 


      getcollstrem.str("");  

              for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

          
                getcollstrem<<"\t } \n        switch(vpos){ \n";
 

                    for(auto &kaa:floatcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }

              
    headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 


 headtxt=R"(
    }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    } )";
      fwrite(&headtxt[0],1,headtxt.size(),f); 
      headtxt.clear(); 

///////////////////////////////////////////////////////
 headtxt=R"(
  std::map<long long,float> getlongfloatCols(std::string keyname,std::string valname){
        std::map<long long,float> a;
        unsigned char kpos,vpos;
         kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
         long long ktemp;
         float vtemp;
         for(auto &iter:record){
                
                switch(kpos){
 
       )";
      fwrite(&headtxt[0],1,headtxt.size(),f); 
      headtxt.clear(); 


      getcollstrem.str("");  

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

          
                getcollstrem<<"\t } \n        switch(vpos){ \n";
 

                    for(auto &kaa:floatcollist){
                                    
                                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                                
                                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                                    getcollstrem<<"\t break;\n";
                            }

              
    headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 


 headtxt=R"(
    }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    } )";
      fwrite(&headtxt[0],1,headtxt.size(),f); 
      headtxt.clear(); 

/////////////////////////
     headtxt=R"( 
    std::map<long long,std::string> getlongstrCols(std::string keyname,std::string valname){
        std::map<long long,std::string> a;
                unsigned char kpos,vpos;
         kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             long long ktemp;
             std::string vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


     getcollstrem.str("");  
 
              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            getcollstrem<<"\t  }\n switch(vpos){\n";



                for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }


            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 headtxt=R"(
  }
                a.emplace(ktemp,vtemp);
        }       
        return a;
    }  
    std::map<std::string,long long> getstrlongCols(std::string keyname,std::string valname){
        std::map<std::string,long long> a;
             unsigned char kpos,vpos;
        kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             std::string  ktemp;
             long long  vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 getcollstrem.str("");  
 

 for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            getcollstrem<<"\t  }\n switch(vpos){\n";

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 



 headtxt=R"(
    }

             
                a.emplace(ktemp,vtemp);
        }       
        return a;
    }   
    std::map<long long,long long> getlonglongCols(std::string keyname,std::string valname){
        std::map<long long,long long> a;

           unsigned char kpos,vpos;
         kpos=findcolpos(keyname);
        vpos=findcolpos(valname);
             long long ktemp;
             long long vtemp;
         for(auto &iter:record){
             
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


 getcollstrem.str("");  
 

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

            getcollstrem<<"\t  }\n switch(vpos){\n";

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t vtemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }
            

            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 


 headtxt=R"(
  }

                a.emplace(ktemp,vtemp);
        }       

        return a;
    }   
    std::map<long long,meta> getlongmetaCols(std::string keyname){
        std::map<long long,meta> a;

            unsigned char kpos;
         kpos=findcolpos(keyname);
 
             long long ktemp;
        
         for(auto &iter:record){
             
                switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  



 getcollstrem.str("");  
 

              for(auto &kaa:numbercollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }

         
            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 

 headtxt=R"(
  }

                a.emplace(ktemp,iter);
        }       

        return a;
    }  
   std::map<std::string,meta> getstrmetaCols(std::string keyname){
        std::map<std::string,meta> a;

         unsigned char kpos;
 
             kpos=findcolpos(keyname);
          
 
             std::string ktemp;
        
         for(auto &iter:record){
             
                   switch(kpos){

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


getcollstrem.str("");  
 
  for(auto &kaa:stringcollist){
                     
                        getcollstrem<<"case "<<std::to_string(kaa.first)<<": \n ";
                   
                    getcollstrem<<"\t ktemp=iter."<<kaa.second<<";"<<"\n";
                    getcollstrem<<"\t break;\n";
              }


         
            headtxt.append(getcollstrem.str());   
             fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear(); 


 headtxt=R"(
                }

                a.emplace(ktemp,iter);
        }       

        return a;
    }


};

   )";   
  
                  fwrite(&headtxt[0],1,headtxt.size(),f); 
             headtxt.clear();  


             fclose(f);


    return 0;
}