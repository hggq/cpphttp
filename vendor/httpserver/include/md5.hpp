
#ifndef PROJECT_MD5_HPP
#define PROJECT_MD5_HPP

#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>

/*
https://github.com/ZTao-z/WebSecurity/blob/master/MD5/MD5.cpp
*/

const char str16[] = "0123456789abcdef";

const unsigned int T[] = {
    0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,
    0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
    0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,
    0x6b901122,0xfd987193,0xa679438e,0x49b40821,
    0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,
    0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
    0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,
    0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
    0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,
    0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
    0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,
    0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
    0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,
    0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
    0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,
    0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391 };

const unsigned int s[] = { 7,12,17,22,7,12,17,22,7,12,17,22,7,12,17,22,
                           5,9,14,20,5,9,14,20,5,9,14,20,5,9,14,20,
                           4,11,16,23,4,11,16,23,4,11,16,23,4,11,16,23,
                           6,10,15,21,6,10,15,21,6,10,15,21,6,10,15,21};
class MD5 {
private:
    unsigned int tempA, tempB, tempC, tempD, strlength;
public:
    MD5() {
        tempA = 0x67452301;
        tempB = 0xefcdab89;
        tempC = 0x98badcfe;
        tempD = 0x10325476;
        strlength = 0;
    }
    // F函数
    unsigned int F(unsigned int b, unsigned int c, unsigned int d) {
        return (b & c) | ((~b) & d);
    }
    // G函数
    unsigned int G(unsigned int b, unsigned int c, unsigned int d) {
        return (b & d) | (c & (~d));
    }
    // H函数
    unsigned int H(unsigned int b, unsigned int c, unsigned int d) {
        return b ^ c ^ d;
    }
    // I函数
    unsigned int I(unsigned int b, unsigned int c, unsigned int d) {
        return c ^ (b | (~d));
    }
    // 移位操作函数
    unsigned int shift(unsigned int a, unsigned int n) {
        return (a << n) | (a >> (32 - n));
    }
    // 编码函数
    std::string encode(std::string src) {
        tempA = 0x67452301;
        tempB = 0xefcdab89;
        tempC = 0x98badcfe;
        tempD = 0x10325476;
        strlength = 0;
        std::vector<unsigned int> rec = padding(src);
        for(unsigned int i = 0; i < strlength/16; i++) {
            unsigned int num[16];
            for(int j = 0; j < 16; j++) {
                num[j] = rec[i*16+j];
            }
            iterateFunc(num, 16);
        }
        return format(tempA) + format(tempB) + format(tempC) + format(tempD);
    }
    // 循环压缩
    void iterateFunc(unsigned int* X, int size = 16) {
        unsigned int a = tempA,
                     b = tempB,
                     c = tempC,
                     d = tempD,
                     rec = 0,
                     g, k;
        for(int i = 0; i < 64; i++) {
            if(i < 16) {
                // F迭代
                g = F(b, c, d);
                k = i;
            }
            else if(i < 32) {
                // G迭代
                g = G(b, c, d);
                k = (1 + 5*i) % 16;
            }
            else if(i < 48) {
                // H迭代
                g = H(b, c, d);
                k = (5 + 3*i) % 16;
            }
            else {
                // I迭代
                g = I(b, c, d);
                k = (7*i) % 16;
            }
            rec = d;
            d = c;
            c = b;
            b = b + shift(a + g + X[k] + T[i], s[i]);
            a = rec;
        }
        tempA += a;
        tempB += b;
        tempC += c;
        tempD += d;
    }
    // 填充字符串
    std::vector<unsigned int> padding(std::string src) {
        // 以512位,64个字节为一组
        unsigned int num = ((src.length() + 8) / 64) + 1;
        std::vector<unsigned int> rec(num*16);
        strlength = num*16;
        for(unsigned int i = 0; i < src.length(); i++){
            // 一个unsigned int对应4个字节，保存4个字符信息
            rec[i>>2] |= (int)(src[i]) << ((i % 4) * 8);
        }
        // 补充1000...000
        rec[src.length() >> 2] |= (0x80 << ((src.length() % 4)*8));
        // 填充原文长度
        rec[rec.size()-2] = (src.length() << 3);
        return rec;
    }
    // 整理输出
    std::string format(unsigned int num) {
        std::string res = "";
        unsigned int base = 1 << 8;
        for(int i = 0; i < 4; i++) {
            std::string tmp = "";
            unsigned int b = (num >> (i * 8)) % base & 0xff;
            for(int j = 0; j < 2; j++) {
                tmp = str16[b%16] + tmp;
                b /= 16;
            }
            res += tmp;
        }
        return res;
    }
};

#endif 