
#include "http.hpp"

 
/*
--compiler--begin--
--compiler--end--
*/

 
namespace HTTP {
 
std::string menubar(HTTP::OBJ_VALUE& obj){
     obj["home"]="/";
     obj["news"]="/news";
     obj["about"]="/about";
     //viewshow("home/menubar");
   //   echo_json();
   //   echo_json(vobj);
   echo("hi! Welcome to games world!");
    viewshow("about/head");
     return "";
} 

std::string home(HTTP::OBJ_VALUE& obj){
      echo("hello world!");
       echo("<p><a href=\"/weibo/header\">header</p>");
       echo("<p><a href=\"/weibo/hello\">content</p>");
     return "";
} 
std::string hello(HTTP::OBJ_VALUE& obj){
      std::cout<<"\r\nhello world!ppppppppeeee";

   // echo="hello world%%%5";
   // echo.append(obj.as_string());
   // vobj["name"]=obj["liming"];
   //viewshow("home/menubar");
   viewshow("about/jianjie");
   echo("wwwwweeebbbb");
   std::string abdd="9999999999999999999900000";
   echo(abdd);
   //  HTTP::client a;

   //  HTTP::OBJ_VALUE parameter;
   // parameter["name"]="老师短发"; 
   // parameter["num"]=345;
   //  a.getjson("https://www.tengbei.net/info.php",parameter);
   //   a.timeout(30);
   //   std::cout<<"==============content==============\r\n"<<std::endl;
   //       try {
   //     a.send();
   //          std::cout<<"========"<<a.state.code<<" "<<a.state.codemessage<<std::endl;
   //    std::cout<<"==============content==============\r\n"<<a.state.content<<std::endl;
   //    std::cout<<(std::string)a.state.json["liminghui"]<<std::endl;

   //    for(auto &bb:a.state.cookie){
   //        std::cout<<bb.first<<":"<<bb.second<<std::endl;
   //    }
   //  }catch (std::exception& e)  
   //  {  
   //      std::cout << e.what() << std::endl;  
   //  }  
   

   //viewshow("about/head");
   return "";
}

_SHOWS(menubar,header)
_SHOW(home)


_SHOW(hello)


// BOOST_DLL_ALIAS(HTTP::hello, hello)
// BOOST_DLL_ALIAS(HTTP::menubar, header)


}