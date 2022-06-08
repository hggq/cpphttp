// Copyright Antony Polukhin, 2016-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_MY_PLUGIN_API_HPP
#define BOOST_DLL_MY_PLUGIN_API_HPP

//[plugapi
#include <boost/config.hpp>
#include <string>
#include <string_view>
#include <memory>
#include "Clientpeer.h"
namespace http { 
class clientpeer;
}
class BOOST_SYMBOL_VISIBLE websockets_api {
public:
   websockets_api(unsigned int t,unsigned char s,std::weak_ptr<http::clientpeer> p):timeloop_num(t),state(s),weakpeer(p){}
   virtual void onopen()  = 0;
   virtual void onmessage(std::string_view) = 0;
   virtual void onfiles(std::string_view) = 0;
   virtual void timeloop() = 0;
 //  virtual void timeloop(clientpeer*) = 0;
    virtual void onclose()  = 0;
  //  virtual void onping() const = 0;
  //  virtual void onpong() const = 0;
   virtual ~websockets_api() {}
   unsigned int timeloop_num;
   unsigned char state;
   std::weak_ptr<http::clientpeer>  weakpeer;
};
//]
   
#endif // BOOST_DLL_MY_PLUGIN_API_HPP

