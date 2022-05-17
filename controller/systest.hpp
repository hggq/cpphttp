#include "orm.h"
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
    viewshow("about/image");
    //send_file("viewmodule.html");
   return "";
}

//static methodautoload *methodautoloadmap =methodautoload::instance();

//  methodautoload* methodptr = methodautoload::instance();
// methodptr->addmapmethod("systest/home");
//_SHOW(home)

}