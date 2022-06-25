
#ifndef PROJECT_BASEFUNC_H
#define PROJECT_BASEFUNC_H

#include <openssl/pem.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <cstring>
#include <string>
#include <string_view>

std::string base64Encode(const char * input, int length, bool with_new_line);
std::string base64Decode(const char * input, int length, bool with_new_line);
// base64 编码
int base64_encode(char *in_str, int in_len, char *out_str);

// base64 解码
int base64_decode(char *in_str, int in_len, char *out_str);
 

#endif //PROJECT_WEBSOCKET_H