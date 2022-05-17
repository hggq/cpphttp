c++ http server framework

Runtime environment
asio boost openssl 

C++ standard request c++20


Running desktop Mac OS and Linux

mac os request >=big sur  
---------

asio 1.22.1

boost 1.78

mysql 8.0.26

MySQL Connector/C++ 8.0.26


ubuntu 20.04
-------------------
gcc11

asio 1.22.1

msyql 8.0.26

MySQL Connector/C++ 8.0.26

boost 1.71


ubuntu 20.04 必须安装gcc11
默认是g++-11 
在编译时候要把g++ 换成g++-11


config 目录
---------------
config/gcc.conf 文件

里面内容必须改为g++-11

conifg/server.conf 服务器文件

里面路径改为你存放当前目录路径，不然看不到内容


config/mysqlorm.conf 文件为数据库配置文件
里面改成你的，config 目录有两个数据库sql文件演示




