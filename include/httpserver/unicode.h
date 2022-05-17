#ifndef PROJECT_UNICODE_HPP
#define PROJECT_UNICODE_HPP

#include <string>
#include <cstdlib>
#include <charconv>
#include <cstring>
#include <string>
#include <vector>

namespace HTTP {
/*
*  utf-16转utf8
*/
std::string unicode_to_utf8(std::string &source);
/*
*  utf8转unicode 
*/
std::string utf8_to_unicode(std::string &source);
/*
*  utf8转unicodestring 
*/
std::string utf8_to_unicodestring(std::string &source);
/*
*  utf8转jsonstring 
*/
std::string utf8_to_jsonstring(std::string &source);
/*
*  unicode转unicodestring 
*/
std::string unicode_to_unicodestring(std::string &source);
/*
*  unicode转unicodestring 
*/
std::string utf8_to_string(std::string &source);
/*
*  long转hexstring 
*/
std::string to_hexstring(unsigned long long soucr);
/*
* unicode 数字字符转utf8
*/

std::string stringunicode_to_utf8(std::string &source);
}
#endif