#include<iostream>
#include <cstdio>
#include <string>
#include <sstream>
#include <boost/dll/alias.hpp>
#include <boost/function.hpp>
#include <boost/dll/import.hpp>

#include "request.h"
#include <map> 
#include <vector>
#include <ctime>
#include <array>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstdlib>

//g++ cache/view/about/image.cpp -o module/view/about/image.so -shared -fPIC -std=c++20 -I../../include ../../src/request.cpp   -lssl -lcrypto -ldl -I/usr/local/opt/openssl/include -L/usr/local/opt/openssl/lib -lboost_filesystem

  namespace HTTP {

        typedef boost::function<std::string(std::string)> http_callback_t;
        typedef boost::function<std::string(HTTP::OBJ_VALUE&)> method_callback_t;
        typedef boost::function<boost::function<std::string(HTTP::OBJ_VALUE&)>(std::string)> modulemethod_callback_t;
        std::map<std::string,modulemethod_callback_t> _render;
        std::map<std::string,http_callback_t> _httpsever;
        void _initview(modulemethod_callback_t& function){
            if(_render.size()==0){
                _render["view"]=function;
                std::cout<<"_render view view view -----------"<<std::endl;
            }
            
        }
         void _initserver(std::map<std::string,http_callback_t>& function){
            if(_httpsever.size()==0){
                _httpsever=function;
                std::cout<<"_render server server server -----------"<<std::endl;
            }
            
        }
       
        std::string view(HTTP::OBJ_VALUE &obj){
            std::ostringstream echo;

        
 echo<<"<!DOCTYPE html>\n<html class=\" desktop portrait\">\n <head id=\"Head\">\n      <meta charset=\"utf-8\">\n    <title>萨芬县明天丝网制品有限公司</title>\n    <META content=\" \"　name=description>\n    <META content=\" \"　name=keywords>\n    <link href=\"dist/css/bootstrap.min.css\" rel=\"stylesheet\">\n    <link rel=\"stylesheet\" type=\"text/css\" href=\"css/style.css\">\n    <link href=\"css/header.css\" rel=\"stylesheet\">\n<link href=\"css/md_style.css\" type=\"text/css\" rel=\"stylesheet\" />\n    <!-- HTML5 shim 和 Respond.js 是为了让 IE8 支持 HTML5 元素和媒体查询（media queries）功能 -->\n    <!-- 警告：通过 file:// 协议（就是直接将 html 页面拖拽到浏览器中）访问页面时 Respond.js 不起作用 -->\n    <!--[if lt IE 9]>\n      <script src=\"dist/js/html5shiv.min.js\"></script>\n      <script src=\"dist/respond.min.js\"></script>\n    <![endif]-->\n    <!-- jQuery (Bootstrap 的所有 JavaScript 插件都依赖 jQuery，所以必须放在前边) -->\n    <script src=\"js/jquery.min.js\"></script>\n    <!-- 加载 Bootstrap 的所有 JavaScript 插件。你也可以根据需要只加载单个插件。 -->\n    <script src=\"dist/js/bootstrap.min.js\"></script>\n  <!--link rel=\"stylesheet\" type=\"text/css\" href=\"css/style2.css\" /-->\n  <link rel=\"stylesheet\" type=\"text/css\" href=\"css/animate.min.css\" />\n  <!--link href=\"css/style.css\" rel=\"stylesheet\" type=\"text/css\" /-->\n  <link rel=\"stylesheet\" type=\"text/css\" href=\"css/banner.css\" media=\"all\" />\n  <link rel=\"stylesheet\" type=\"text/css\" href=\"css/gundong.css\" media=\"all\" />\n  <script type=\"text/javascript\" src=\"js/jquery-1.8.3.min.js\"></script>\n  <script type=\"text/javascript\" src=\"js/jquery.flexslider.min.js\"></script>\n  <script type=\"text/javascript\" src=\"js/jquery.wow.min.js\"></script>\n  <script type=\"text/javascript\" src=\"js/jquery.jcarousellite.min.js\"></script>\n  <script type=\"text/javascript\">\nvar wow = new WOW(\n{\n    boxClass:'animated'}\n);\n    wow.init();\n$(function(){\n    $('.banner').flexslider();\n    });\n$(function(){\n    $(\".case\").jCarouselLite({scroll:3,speed:1500,btnNext:\".next\",btnPrev:\".prev\"});\n    });\n$(function(){\n    $(\"#goleft\").imgscroll({speed: 40,amount: 0,width: 1,dir: \"left\"});\n    });\n</script>\n </head>\n <body>\n      <header>\n    <div class=\"logo contenter\">\n        <div class=\"row\">\n        <p class=\"col-md-7\"><img src=\"images/logo.jpg\"></p>\n        <p class=\"col-md-5\"><img src=\"images/top_banner.jpg\"></p>\n    </div>\n    </div>\n    </header>\n    <nav>\n        <div>\n            <button type=\"button\" class=\"navbar-toggle collapsed\" data-toggle=\"collapse\" data-target=\"#bs-example-navbar-collapse-1\" aria-expanded=\"false\" style=\"background: #cccccc;\">\n                <span class=\"sr-only\">Toggle navigation</span>\n                <span class=\"icon-bar\"></span>\n                <span class=\"icon-bar\"></span>\n                <span class=\"icon-bar\"></span>\n            </button>\n        </div>\n        <div class=\"collapse navbar-collapse\" id=\"bs-example-navbar-collapse-1\">\n        <ul class=\"menu\">\n            <li><a href=\"index.html\">网站首页</a></li>\n            <li><a href=\"news.html\">关于我们</a>\n                  <ol>\n                    <li><a href=\"#\">企业简介</a></li>\n                    <li><a href=\"#\">企业文化</a></li>\n                    <li><a href=\"#\">企业理念</a></li>\n                    <li><a href=\"#\">企业资质</a></li>\n                </ol>\n            </li>\n            <li><a href=\"news.html\">服务优势</a></li>\n            <li><a href=\"news.html\">产品中心</a>\n                <ol>\n                    <li><a href=\"#\">雷诺护垫</a></li>\n                    <li><a href=\"#\">固滨笼</a></li>\n                    <li><a href=\"#\">加筋麦克垫</a></li>\n                    <li><a href=\"#\">电焊石笼</a></li>\n                    <li><a href=\"#\">路面加筋网</a></li>\n                </ol>\n            </li>\n            <li><a href=\"news.html\">生产设备</a></li>\n            <li><a href=\"news.html\">成功案例</a></li>\n            <li><a href=\"news.html\">新闻动态</a></li>\n            <li><a href=\"news.html\">常见问题</a></li>\n            <li><a href=\"news.html\">联系我们</a></li>\n        </ul>\n    </div>\n    </nav>\n <div class=\"contenter-full\"></div>\n <div class=\"contenter-full  animated fadeInUp animated\">\n    <div class=\"contenter\" style=\"margin:50px auto;\">\n        <div class=\"row\">\n            <div class=\"col-md-6\">\n                <h1 class=\"list_text\">应用网箱的应用</h1>\n                <ul class=\"news_list\">\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用应用\">应用应用应用应用应用应用应用</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用\">应用应用应用应用应用</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用应用？\">应用应用应用应用应用应用应用？</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用\">应用应用应用应用应用应用</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用\">应用应用应用应用应用应用</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用\">应用应用应用应用应用</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用应用？\">应用应用应用应用应用？</a></li>\n                    <li><a href=\"#\" title=\"应用应用应用应用应用\">应用应用应用应用应用应用</a></li>\n                </ul>\n            </div>\n            <div class=\"col-md-6\">\n                <h1 class=\"list_text\">技术动态</h1>\n                <ul class=\"news_list\">\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态\">动态动态动态动态动态动态动态</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态动态\">动态动态动态动态动态动态</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态？\">动态动态动态动态动态动态动态？</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态\">动态动态动态动态动态动态动态</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态\">动态动态动态动态动态动态</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态动态\">动态动态动态动态动态动态动态</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态？\">动态动态动态动态动态动态？</a></li>\n                    <li><a href=\"#\" title=\"动态动态动态动态动态动态\">动态动态动态动态动态动态</a></li>\n                </ul>\n            </div>\n        </div>\n\n    </div>\n</div>\n\n<div class=\"footer\">\n    <div class=\"contenter content_03\">\n        <p>网站首页 | 公司简介 | 公司新闻 | 产品展示 | 应用范围 | 生产设备 | 工程案例 | 公司资质 | 服务网络 | 联系我们\n萨芬县明天丝网制品有限公司 © 版权所有 后台管理</p>\n<p>地 址:XXXXX省萨芬县经济开发区  电子邮件:aa@abc.com</p>\n\n<p>ICP备111033336号</p>\n \n    </div>\n</div>\n </body>\n</html>";

            return echo.str();
        }

            BOOST_DLL_ALIAS(HTTP::view, view)
            BOOST_DLL_ALIAS(HTTP::_initview, _initview)
            BOOST_DLL_ALIAS(HTTP::_initserver, _initserver)
        }
    