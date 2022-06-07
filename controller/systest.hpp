#include "orm.h"
#include <chrono>
#include <thread>
namespace HTTP {

std::string home(clientpeer& client){
    client<<"hello world! this use systest inline callback";
    client<<"<p><a href=\"/weibo/header\">header</a></p>";
    client<<"<p><a href=\"/weibo/hello\">content</a></p>";
    client<<client.session["aaa"];
    orm::sms::News  comnews;

    comnews.where("newsid>",63597).order("newsid  DESC").limit(10).fetch();
     if(comnews.size()>0){
         for(auto &bb:comnews){
         client<<"<p>"<<bb.newsid<<" "<<bb.newtitle<<" "<<bb.adddate<<" "<<bb.isview<<"</p>";
       }

    }
    orm::Moduleauth  mbc;
    mbc.where("mid>",0).fetch();
    client<<mbc.getstrCol("name");
    client<<mbc.getstrCol("name",true);
    auto ww=mbc.getCol<std::string>("name");
          for(auto &bb:ww){
         client<<"<p>"<<bb<<"</p>";
     }
    client.vobj["name"]="test inline callback";
    viewshow("about/head");
    //send_file("viewmodule.html");
   return "";
}

std::string hellotest(clientpeer& peer){

      peer<<"hello world!  weibo so file";
      peer<<"<p><a href=\"/weibo/header\">header</a></p>";
      peer<<"<p><a href=\"/weibo/hello\">content</a></p>";

      peer<<peer.remote_ip;
      peer<<peer.remote_port;
      orm::sms::News  comnews;

    peer.session["aaa"]=1111;
    peer.save_session();

    std::this_thread::sleep_for(std::chrono::seconds(1));
   // peer->clear_session();
      peer.addcookie("names","wwwww",7200*24,peer.header->host,"/");
      peer.addheader("server: cpphttp");

    comnews.where("newsid>",1).order("newsid  DESC").limit(10).fetch();
     if(comnews.size()>0){
         for(auto &bb:comnews){
         peer<<"<p>"<<bb.newsid<<" "<<bb.newtitle<<" "<<bb.adddate<<" "<<bb.isview<<"</p>";
       }
    }

    orm::Moduleauth  mbc;
    mbc.where("mid>",0).fetch();

     if(mbc.size()>0){
         for(auto &bb:mbc){
         peer<<"<p>"<<bb.mid<<" "<<bb.addtime<<"  ["<<bb.testdatetime<<"] "<<bb.testenum<<"</p>";
       }
    }
    peer.vobj["name"]="view name huang";
    
    viewshow("about/show");
    //send_file("viewmodule.html");
   return "";
}

}