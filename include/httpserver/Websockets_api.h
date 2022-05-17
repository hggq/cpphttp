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
#include <memory>
// #include "Clientpeer.h"
class clientpeer;
class BOOST_SYMBOL_VISIBLE websockets_api {
public:
   virtual void onopen()  = 0;
   virtual void onmessage(std::string&) = 0;
   virtual void onfiles(std::string&) = 0;
   virtual void timeloop(std::weak_ptr<clientpeer> peer) = 0;
 //  virtual void timeloop(clientpeer*) = 0;
  //  virtual void onclose() const = 0;
  //  virtual void onping() const = 0;
  //  virtual void onpong() const = 0;
   virtual ~websockets_api() {}
   unsigned int timeloop_num;
   unsigned char state;
};
//]
   
#endif // BOOST_DLL_MY_PLUGIN_API_HPP

