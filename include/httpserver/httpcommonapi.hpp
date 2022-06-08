// Copyright Antony Polukhin, 2016-2022.
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt
// or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_DLL_HTTP_COMMON_API_HPP
#define BOOST_DLL_HTTP_COMMON_API_HPP

//[plugapi
#include <boost/config.hpp>
#include <string>
#include <string_view>
#include <memory>
#include "request.h"
#include <mysqlx/xdevapi.h>
#include "Clientpeer.h"
 namespace http { 
// class clientpeer;
// }
class BOOST_SYMBOL_VISIBLE commonapi {
public:
     commonapi(){}

    http::OBJ_VALUE vobj;
    static commonapi* instance()
    {
        if (singleton== NULL)
                singleton= new commonapi();
        return singleton;
    }
    static commonapi* singleton;
    static commonapi* setcommonapi(commonapi* p){
            singleton=p;
            return singleton;
    } 
};
commonapi* commonapi::singleton =NULL;
//my_plugin_aggregator* my_plugin_aggregator::singleton =my_plugin_aggregator::instance();

// BOOST_DLL_ALIAS(
//     commonapi::instance, // <-- this function is exported with...
//     _commonapi                               // <-- ...this alias name
// )
// BOOST_DLL_ALIAS(
//     commonapi::setcommonapi, // <-- this function is exported with...
//     _setcommonapi                               // <-- ...this alias name
// )
//]
 }
#endif // BOOST_DLL_MY_PLUGIN_API_HPP

