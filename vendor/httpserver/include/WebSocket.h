//
// Description: WebSocket RFC6544 codec, written in C++.
//

#ifndef PROJECT_WEBSOCKET_H
#define PROJECT_WEBSOCKET_H

 
#include <cstddef>
#include <string>
#include <vector>

enum WSFrameType {
    ERROR_FRAME=0xFF00,
    INCOMPLETE_FRAME=0xFE00,

    OPENING_FRAME=0x3300,
    CLOSING_FRAME=0x3400,

    INCOMPLETE_TEXT_FRAME=0x01,
    INCOMPLETE_BINARY_FRAME=0x02,

    TEXT_FRAME=0x81,
    BINARY_FRAME=0x82,

    PING_FRAME=0x19,
    PONG_FRAME=0x1A
};


enum FRAMETYPE {
    CONT=0x00,
    CONT_TEXT=0x01,
    CONT_BINARY=0x02,

    TEXT=0x81,
    BINARY=0x82,

    CLOSE=0x88,

    PING=0x89,
    PONG=0x8A
};


enum WSStatus
{
    WS_STATUS_UNCONNECT = 1,
    WS_STATUS_CONNECT = 2,
};

class WebSocket
{
public:
    WebSocket();

    //解析 WebSocket 的握手数据
    bool parseHandshake(const std::string& request);

    //应答 WebSocket 的握手
    std::string respondHandshake();
    //应答 WebSocket 的握手
    void setWebsocketkey(const std::string& request);

    //取得数据包长度
    unsigned long long getprocssdata(unsigned char* inputdata,unsigned int buffersize,unsigned long long &offset);
    
    //解析 WebSocket 的协议具体数据，客户端-->服务器
    int getWSFrameData(char* msg, int msgLen, std::vector<char>& outBuf, int* outLen);

    //封装 WebSocket 协议的数据，服务器-->客户端
    int makeWSFrameData(char* msg, int msgLen, std::string& outBuf);

    //封装 WebSocket 协议的数据头（二进制数据）
    static int makeWSFrameDataHeader(int len, std::string& header);
    bool wsEncodeFrame(std::string inMessage, std::string &outFrame, enum WSFrameType frameType);  

    std::string getWebsocketkey();
     
private:
    std::string websocketKey_;//握手中客户端发来的key
    FRAMETYPE state;
    
    bool      isfinish=false;
public:    
    std::string indata;
    // std::string outdata;
    bool islock=false; 
    bool      isopen=false;  //是否还活着
    bool isfile=false;
    unsigned char fin=0x0B;
    unsigned char opcode;
    unsigned int  pos=0;
    unsigned long long contentlength;
    unsigned long long readlength;
    FILE *rawfile;//临时文件
    std::string filename;
     unsigned char mask;
     unsigned char mask_key[4];
     
    
};


#endif //PROJECT_WEBSOCKET_H

