/*
*  @author 黄自权 huangziquan
*  @date 2022-04-15
*  @dest 命令行管理mvc文件 
*/
#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <list>
#include <filesystem>
#include "templateparse.hpp"
#include "controllerparse.hpp"

#include "tmplatefun.hpp"
#include "ccontrollfun.hpp"
#include "modelfun.hpp"
namespace fs = std::filesystem;
//macos  g++ vendor/httpserver/cli/http_cli.cpp -o clihttp -std=c++20 -Ivendor/httpserver/include -lmysqlcppconn8
//ubuntu20.04  g++-11 vendor/httpserver/cli/http_cli.cpp -o clihttp -std=c++20 -Ivendor/httpserver/include -lmysqlcppconn8 -I/usr/include/mysql-cppconn-8
int main(int argc, char *argv[]){
    std::string commandstr;
    if(argc==1){
        std::cout<<argv[0]<<" \033[1m\033[31m model ｜ view | control \033[0m  \n 🎉 Welcome to use \033[4m\033[31mcli\033[0m to manage your MVC files。\n";
        
    }
    if(argc>1)
    {
        commandstr=argv[1];
    }
   // std::string commandstr{argv[1]};
    while(1){
          if(commandstr=="view"){
             viewcli();
         }
         if(commandstr=="control"){
             controlcli();
         }
         if(commandstr=="model"){
             modelcli();
        }
        commandstr.clear();
         std::cout<<"(m)model (v)view or (c)control,x or q to exit[input\033[1m\033[32m m|v|c|\033[0m]:";
         std::cin>>commandstr;

         if(commandstr.size()==1&&(commandstr[0]=='x'||commandstr[0]=='q')){
                break;
         }
         if(commandstr.size()==1&&(commandstr[0]=='v'||commandstr[0]=='V')){
                
               viewcli();
         }
          if(commandstr.size()==1&&(commandstr[0]=='c'||commandstr[0]=='C')){
                
               controlcli();
         }
           if(commandstr.size()==1&&(commandstr[0]=='m'||commandstr[0]=='M')){
                
               modelcli();
         }
         if(commandstr=="view"){
             viewcli();
         }
        if(commandstr=="control"){
             controlcli();
        }
        if(commandstr=="model"){
             modelcli();
        }
        commandstr.clear();
    }    

    
    return 0;
}