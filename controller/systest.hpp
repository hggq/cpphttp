#include "orm.h"
#include <chrono>
#include <thread>
namespace HTTP {

std::string home(HTTP::OBJ_VALUE& obj){
    echo("hello world! this use systest inline callback");
    echo("<p><a href=\"/weibo/header\">header</a></p>");
    echo("<p><a href=\"/weibo/hello\">content</a></p>");

    orm::sms::News  comnews;

    comnews.where("newsid>",63597).order("newsid  DESC").limit(10).fetch();
     if(comnews.size()>0){
         for(auto &bb:comnews){
         echo("<p>"+std::to_string(bb.newsid)+" "+bb.newtitle+" "+bb.adddate+" "+bb.isview+"</p>");
         
       }

    }
    orm::Moduleauth  mbc;
    mbc.where("mid>",0).fetch();
    echo(mbc.getstrCol("name"));
    echo(mbc.getstrCol("name",true));
    auto ww=mbc.getCol<std::string>("name");
          for(auto &bb:ww){
         echo("<p>"+bb+"</p>");
     }
     obj["name"]="test inline callback";
    viewshow("about/head");
    //send_file("viewmodule.html");
   return "";
}

std::string helloaa(HTTP::OBJ_VALUE& obj){
 HTTP::clientpeer *peer= clientapi::get().getpeer();
    auto output=clientapi::get();  

    output<<"hello world!  weibo so file";
    output<<"<p><a href=\"/weibo/header\">header</a></p>";
    output<<"<p><a href=\"/weibo/hello\">content</a></p>";

   
   //  echo(peer->remote_ip);
   //  echo(peer->remote_port);
     output<<peer->remote_ip;
     output<<peer->remote_port;
    orm::sms::News  comnews;

    peer->session["aaa"]=1111;

    peer->save_session();

    std::this_thread::sleep_for(std::chrono::seconds(6));

    peer->clear_session();

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
    viewshow("about/show");
    //send_file("viewmodule.html");
   return "";
}

}