#ifndef FRAME_MIME_UTILITY
#define FRAME_MIME_UTILITY

#include <iostream>
#include <map>
#include <string>

namespace http{
// static const std::map<std::string,std::string> mime={
//         {"html","text/html"},
//         {"json","application/json"},
//         {"css","text/css"},
//         {"js","text/javascript"},
//         {"ts","text/javascript"},

//         {"jpg","image/jpeg"},
//         {"jpeg","image/jpeg"},
//         {"gif","image/gif"},
//         {"png","image/png"},
//         {"webp","image/webp"},
//         {"svg","image/svg+xml"},

//         {"pdf","application/pdf"},

//         {"docx","application/vnd.openxmlformats-officedocument.wordprocessingml.document"},
//         {"doc","application/msword"},

//         {"xlsx","application/vnd.openxmlformats-officedocument.spreadsheetml.sheet"},
//         {"xls","application/vnd.ms-excel"},

//         {"pptx","application/vnd.openxmlformats-officedocument.presentationml.presentation"},
//         {"ppt","application/vnd.ms-powerpoint"},

//         {"rar","application/octet-stream"},
//         {"zip","application/x-zip-compressed"},
//      };
struct mime{


    std::map<std::string,std::string> _map;
    mime(){
    _map["txt"]="text/plain";    
    _map["md"]="text/plain"; 
    _map["html"]="text/html";
    _map["htm"]="text/html";
    _map["xml"]="text/xml";
    _map["json"]="application/json";
    _map["css"]="text/css";
    _map["js"]="application/javascript";

    _map["jpg"]="image/jpeg";
    _map["jpeg"]="image/jpeg";
    _map["gif"]="image/gif";
    _map["png"]="image/png";
    _map["bmp"]="image/bmp";
    _map["webp"]="image/webp";
    _map["svg"]="image/svg+xml";

    _map["pdf"]="application/pdf";
    _map["zip"]="application/x-zip-compressed";
    _map["rar"]="application/octet-stream";
    _map["map"]="text/plain";    
    _map["docx"]="application/vnd.openxmlformats-officedocument.wordprocessingml.document";
    _map["doc"]="application/msword";

    _map["xlsx"]="application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
    _map["xls"]="application/vnd.ms-excel";

    _map["ppt"]="application/vnd.ms-powerpoint";
    _map["pptx"]="application/vnd.openxmlformats-officedocument.presentationml.presentation";

    _map["mp4"]="video/mp4"; 
    _map["mp3"]="audio/mp3";
    _map["m4a"]="audio/mp4";  
    _map["ico"]="image/x-icon"; 
    _map["m3u8"]="application/vnd.apple.mpegurl"; 
     
    }
  };
}

#endif     