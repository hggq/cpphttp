
#include "http.hpp"
#include "orm.h"
#include "httpclient.h"
/*
--compiler--begin--
--compiler--end--
*/

namespace HTTP {
 


std::string menubar(HTTP::clientpeer *peer,HTTP::OBJ_VALUE& obj){
     obj["home"]="/";
     obj["news"]="/news";
     obj["about"]="/about";
     //viewshow("home/menubar");
   //   echo_json();
   //   echo_json(vobj);
   echo("<p align=\"center\">newqefqqqq!</p>");
   echo("<p><a href=\"/weibo/home\">home</p>");
       echo("<p><a href=\"/weibo/hello\">content</p>");
    viewshow("about/head");
     return "";
} 

std::string home(HTTP::clientpeer *peer, HTTP::OBJ_VALUE& obj){
    echo("hello world!  weibo so file");
    echo("<p><a href=\"/weibo/header\">header</a></p>");
    echo("<p><a href=\"/weibo/hello\">content</a></p>");
    echo(peer->remote_ip);
    orm::sms::News  comnews;

    comnews.where("newsid>",1).order("newsid  DESC").limit(10).fetch();
     if(comnews.size()>0){
         for(auto &bb:comnews){
         echo("<p>"+std::to_string(bb.newsid)+" "+bb.newtitle+" "+bb.adddate+" "+bb.isview+"</p>");
         
       }

    }

    orm::Moduleauth  mbc;

    mbc.where("mid>",0).fetch();

     if(mbc.size()>0){
         for(auto &bb:mbc){
         echo("<p>"+std::to_string(bb.mid)+" "+bb.addtime+" "+" ["+bb.testdatetime+"] "+bb.testenum+"</p>");
         
       }

    }
    obj["name"]="view name huang";
   //  HTTP::OBJ_VALUE dateobj= mbc.where("mid>",0).limit(5).fetchOBJ();
   //     dateobj.set_array();
   //     for(auto [first,second]:dateobj.as_array()){
   //       echo("<p>json:"+dateobj[first]["mid"].to_string()+"="+dateobj[first]["addtime"].as_string()+" "+dateobj[first]["dsssggg"].as_string()+"</p>");
   //      }

   //   mbc.clear();
   //        mbc.data.mid=0;
   //        mbc.data.name="cc";
   //        mbc.data.modurl="www.baidu.com";
   //        mbc.save();

   //    orm::Applyproduct ap;
   //  ap.select("appid,name").where("compid>",1000).where("status",0).order("appid asc").limit(10).fetch();
   //  if(ap.size()>0){
   //       for(auto &bb:ap){
   //       echo("<p>"+std::to_string(bb.appid)+" "+bb.name+"</p>");
          
   //     }
   //  }

   //  orm::Company agentcp;
   //  agentcp.select("userid,companyname").where("userid>",490).where("superid",1).order("userid asc").limit(10).fetch();
   //  if(agentcp.size()>0){
   //       for(auto &bb:agentcp){
   //       echo("<p>"+std::to_string(bb.userid)+" "+bb.companyname+"</p>");
          
   //     }
   //  }
   //  orm::Email siteemail;
   //     siteemail.where("id<",10).fetch();
   //     for(auto &bb:siteemail){
   //       echo("<p>"+bb.time+" "+bb.target+"</p>");
          
   //     }
    // orm::User myu;
    // if(obj.isset("id")){
    //    // myu.select("id,name").where("id",obj["id"]).group("userid").order("level desc").limit(5).fetch();

    //    HTTP::OBJ_VALUE testobj= myu.select("id,name").where("id<",obj["id"]).limit(5).fetchOBJ();
    //    testobj.set_array();
    //    for(auto [first,second]:testobj.as_array()){
    //      echo("<p>json:"+std::to_string(testobj[first]["id"].as_int())+"="+testobj[first]["name"].as_string()+"</p>");
    //     }
    //     myu.clear();  
    //     myu.select("id,name,loginpwd").where("id<",obj["id"].to_int()).limit(10).fetch();
    //     echo(myu.sqlstring);
    // }

    //  echo("<p>aa"+myu.data.name+"aa</p>"); 
    //  for(auto &bb:myu){
    //      echo("<p>"+bb.name+"</p>");
    //      echo("<p>("+myu.getstringVal(bb,"name")+")</p>");
    //      echo("<p>("+myu.getstringVal(bb,"loginpwd")+")</p>");
          
    //  }
    //  echo("<p>查询统计："+std::to_string(myu.count())+"</p>");
    //   echo(myu.getstringCol("name",true));
    //   echo(myu.getstringCol("id"));
    //  auto rd=myu.getlongstrCols("id","name");
    //   for(auto &bb:rd){
    //      echo("<p>"+std::to_string(bb.first)+":"+bb.second+"</p>");
    //  }
    //  echo("<p>"+rd[28]+"</p>");
    //  myu.clear();  
    //  myu.getone(1598); 
    //  echo(myu.tojson());
    //  myu.clear(false);     
    // // myu.data.id=4;
    //  myu.data.name="bb'bb";
    //  myu.data.loginname="bb'bb";
    //  myu.data.loginpwd="bb\"bb";
    //  myu.where("id",1598);
    // // int effectnum=myu.update();
    //  //myu.update("id,name,loginname,loginpwd");
    // int i=0; 
    // //while(true){
    //     auto newperson=myu.getnewData();
    //     newperson.name="马上'发";    
    //     newperson.loginname="adminlo'gin马上";
    //     newperson.loginpwd="ec89bec068e9\"f29a281bbd7264fd2357";
    //     myu.setData(newperson);
    //     myu.setPK(0);
    //     std::cout<<"insert id:"<<myu.save()<<std::endl;  
    //     std::cout<<"-----------"<<std::endl; 
    //     std::cout<<"-----------"<<std::endl; 
    //     std::cout<<"-----"<<i<<"------"<<std::endl; 
    //     i++;
    // //}
    //  echo("insert id:");
    //  echo(myu.getPK());
    //  std::cout<<myu.sqlstring<<std::endl;
    //  myu.clear();
    //  int id=0;
    // //  if(obj["id"].is_num()){
    // //      if(obj["id"].is_int()){
    // //          id=obj["id"].as_int();
    // //      }
    // //  }else{
    // //      id=std::stoi(obj["id"].as_string());
    // //  }
    // id=obj["id"].to_int();
    //  echo("delete id:");  
    //   echo(myu.remove(id));
    viewshow("about/show");
     return "";
} 
std::string hello(HTTP::clientpeer *peer,HTTP::OBJ_VALUE& obj){
    //  std::cout<<"\r\nhello world!ppppppppeeee";

   // echo="hello world%%%5";
   // echo.append(obj.as_string());
   // vobj["name"]=obj["liming"];
   //viewshow("home/menubar");
   clientapi& pn =clientapi::get();
 
    std::string abdd="来发撒大阿斯顿发<p><a href=\"/weibo/header\">header</p>";
   echo(abdd);


   echo("<p><a href=\"/weibo/home\">home</p>");
       echo("<p><a href=\"/weibo/hello\">content</p>");


       
        pn<<abdd;
        pn<<"常量abaaaaa"<<333333;
  //      std::cout<<"weibo:"<<std::hex<<&pn.output<<std::endl;
     //   echo(pn._output);
//std::cout<<pn.vobj["in"]<<std::endl;
 std::cout<<"thread_id2"<<std::this_thread::get_id()<<std::endl;
    //  std::cout<<pn.output<<std::endl;

        
   //viewshow("about/jianjie");



  // echo("wwwwweeebbbb");
  
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
std::string _init404(HTTP::clientpeer *peer,HTTP::OBJ_VALUE& obj){
   echo("<p><a href=\"/weibo/home\">home</p>");
   echo(obj["get"]["aa"]);
   return "";
}
_SHOWS(menubar,header)
_SHOW(home)

_SHOW(hello)
_SHOW(_init404)


// BOOST_DLL_ALIAS(HTTP::hello, hello)
// BOOST_DLL_ALIAS(HTTP::menubar, header)


}