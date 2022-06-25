#include "WebSocket.h"
#include "base64.hpp"
#include <cstddef>
#include <openssl/sha.h>  //for SHA1
#include <arpa/inet.h>    //for ntohl
#include <string.h>
#include<sstream>
#include<iostream>
WebSocket::WebSocket()
{
}
unsigned long long WebSocket::getprocssdata(unsigned char *inputdata,unsigned int buffersize,unsigned long long &offset){
                    
                    fin=inputdata[0]>>7&0x01;
                    opcode=inputdata[0]&0x0F;
                    mask=inputdata[1]>>7&0x01;
                    unsigned char fixlength=inputdata[1]&0x7F;
                    unsigned long long  inlength=0;
                   pos=2;
                   // unsigned char mask_key[4];

                    std::cout<<"mask:"<<std::to_string(mask)<<std::endl;
                    if(fixlength<126){
                         inlength=fixlength;
                    }else if(fixlength==126){
                         inlength=inputdata[pos]<<8|(unsigned char)inputdata[pos+1];
                         pos+=2;
                    }else if(fixlength==127){
                         inlength=(unsigned char)inputdata[pos];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+1];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+2];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+3];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+4];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+5]; 
                         inlength=inlength<<8|(unsigned char)inputdata[pos+6];
                         inlength=inlength<<8|(unsigned char)inputdata[pos+7]; 
                         pos+=8;
                    }
                    if(mask==1){
                        mask_key[0]=inputdata[pos];
                        mask_key[1]=inputdata[pos+1];
                        mask_key[2]=inputdata[pos+2];
                        mask_key[3]=inputdata[pos+3];
                        pos+=4;
                    }
                    offset=buffersize-pos;
                    std::cout<<"datalength:"<<std::to_string(fixlength)<<std::endl;
                    contentlength=inlength;
                    return inlength;

}
bool WebSocket::parseHandshake(const std::string& request)
{
    // 解析WEBSOCKET请求头信息
    bool ret = false;
    std::istringstream stream(request.c_str());
    std::string reqType;
    std::getline(stream, reqType);
    if (reqType.substr(0, 4) != "GET ")
        return ret;

    std::string header;
    std::string::size_type pos = 0;
    while (std::getline(stream, header) && header != "\r")
    {
        header.erase(header.end() - 1);
        pos = header.find(": ", 0);
        if (pos != std::string::npos)
        {
            std::string key = header.substr(0, pos);
            std::string value = header.substr(pos + 2);
            if (key == "Sec-WebSocket-Key")
            {
                ret = true;
                websocketKey_ = value;
                break;
            }
        }
    }

    return ret;
}
void WebSocket::setWebsocketkey(const std::string &key)
{
    websocketKey_=key;
}
std::string WebSocket::getWebsocketkey()
{
    return websocketKey_;
}
std::string WebSocket::respondHandshake()
{
    // 算出WEBSOCKET响应信息
    std::string response = "HTTP/1.1 101 Switching Protocols\r\n";
    response += "Upgrade: websocket\r\n";
    response += "Sec-WebSocket-Version: 13\r\n";
    response += "Connection: Upgrade\r\n";
    response += "Sec-WebSocket-Accept: ";

    //使用请求传过来的KEY+协议字符串，先用SHA1加密然后使用base64编码算出一个应答的KEY
    const std::string magicKey("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    std::string serverKey = websocketKey_ + magicKey;
    //LOG_INFO << "serverKey:" << serverKey;

    //SHA1
    unsigned char digest[SHA_DIGEST_LENGTH];
    SHA1((unsigned char*)serverKey.c_str(), serverKey.length(), (unsigned char*)&digest);
    //printf("DIGEST:"); for(int i=0; i<20; i++) printf("%02x ",digest[i]); printf("\n");

    //Base64
    //char basestr[1024] = {0};
    // std::string base64;
    // base64.resize(SHA_DIGEST_LENGTH*2);
    // int n=base64_encode((char*)digest, SHA_DIGEST_LENGTH, base64.data());
    // base64.resize(n-1);
    //printf("respstring [%s]=|%d|",base64.c_str(),SHA_DIGEST_LENGTH);
    //完整的握手应答
    //response = response + std::string(basestr) + "\r\n";
    response = response + base64_encode((char*)digest, SHA_DIGEST_LENGTH,false) + "\r\n\r\n";
    //LOG_INFO << "RESPONSE:" << response;

    return response;
}


int WebSocket::getWSFrameData(char* msg, int msgLen, std::vector<char>& outBuf, int* outLen)
{
    if(msgLen < 2)
        return INCOMPLETE_FRAME;

    uint8_t fin_ = 0;
    uint8_t opcode_ = 0;
    uint8_t mask_ = 0;
    uint8_t masking_key_[4] = {0,0,0,0};
    uint64_t payload_length_ = 0;
    int pos = 0;
    //FIN
    fin_ = (unsigned char)msg[pos] >> 7;
    //Opcode
    opcode_ = msg[pos] & 0x0f;
    pos++;
    //MASK
    mask_ = (unsigned char)msg[pos] >> 7;
    //Payload length
    payload_length_ = msg[pos] & 0x7f;
    pos++;
    if(payload_length_ == 126)
    {
        uint16_t length = 0;
        memcpy(&length, msg + pos, 2);
        pos += 2;
        payload_length_ = ntohs(length);
    }
    else if(payload_length_ == 127)
    {
        uint32_t length = 0;
        memcpy(&length, msg + pos, 4);
        pos += 4;
        payload_length_ = ntohl(length);
    }
    //Masking-key
    if(mask_ == 1)
    {
        for(int i = 0; i < 4; i++)
            masking_key_[i] = msg[pos + i];
        pos += 4;
    }
    //取出消息数据
    if (msgLen >= pos + payload_length_ )
    {
        //Payload data
        *outLen = pos + payload_length_;
        outBuf.clear();
        if(mask_ != 1)
        {
            char* dataBegin = msg + pos;
            outBuf.insert(outBuf.begin(), dataBegin, dataBegin+payload_length_);
        }
        else
        {
            
            for(uint i = 0; i < payload_length_; i++)
            {
                int j = i % 4;
                outBuf.push_back(msg[pos + i] ^ masking_key_[j]);
            }
        }
    }
    else
    {
        return INCOMPLETE_FRAME;
    }

   printf("WEBSOCKET PROTOCOL\n"
           "FIN: %d\n"
           "OPCODE: %d\n"
           "MASK: %d\n"
           "PAYLOADLEN: %d\n"
           "outLen:%d\n",
           fin_, opcode_, mask_, (int)payload_length_, *outLen);

    //断开连接类型数据包
    if ((int)opcode_ == 0x8)
        return -1;

    return 0;
}


int WebSocket::makeWSFrameData(char* msg, int msgLen, std::string& outBuf)
{
    //std::string header;
    makeWSFrameDataHeader(msgLen, outBuf);
    //outBuf.insert(outBuf.begin(), header.begin(), header.end());
    //outBuf.insert(outBuf.end(), msg, msg+msgLen);
    for(int i=0;i<msgLen;i++){
        outBuf.push_back(msg[i]);    
    }
    return 0;
}

int WebSocket::makeWSFrameDataHeader(int len, std::string& header)
{
    header.push_back((char)TEXT_FRAME);
    if(len <= 125)
    {
        header.push_back((char)len);
    }
    else if(len <= 65535)
    {
        header.push_back((char)126);//16 bit length follows
        header.push_back((char)((len >> 8) & 0xFF));// leftmost first
        header.push_back((char)(len & 0xFF));
    }
    else // >2^16-1 (65535)
    {
        header.push_back((char)127);//64 bit length follows

        // write 8 bytes length (significant first)
        // since msg_length is int it can be no longer than 4 bytes = 2^32-1
        // padd zeroes for the first 4 bytes
        for(int i=3; i>=0; i--)
        {
            header.push_back((char)0);
        }
        // write the actual 32bit msg_length in the next 4 bytes
        for(int i=3; i>=0; i--)
        {
            header.push_back((char)((len >> 8*i) & 0xFF));
        }
    }

    return 0;
}
//https://www.cnblogs.com/cnxkey/articles/9391296.html
bool WebSocket::wsEncodeFrame(std::string inMessage, std::string &outFrame, enum WSFrameType frameType)  
{  
    const uint32_t messageLength = inMessage.size();  
    if (messageLength > 32767)  
    {  
        // 暂不支持这么长的数据  
        return false;
    }  

    uint8_t payloadFieldExtraBytes = (messageLength <= 0x7d) ? 0 : 2;
    // header: 2字节, mask位设置为0(不加密), 则后面的masking key无须填写, 省略4字节  
    uint8_t frameHeaderSize = 2 + payloadFieldExtraBytes;  
    uint8_t *frameHeader = new uint8_t[frameHeaderSize];
    memset(frameHeader, 0, frameHeaderSize);  

    // fin位为1, 扩展位为0, 操作位为frameType  
    frameHeader[0] = static_cast<uint8_t>(0x80 | frameType);  

    // 填充数据长度
    if (messageLength <= 0x7d)  
    {  
        frameHeader[1] = static_cast<uint8_t>(messageLength);  
    }  
    else  
    {  
        frameHeader[1] = 0x7e;
        uint16_t len = htons(messageLength);
        memcpy(&frameHeader[2], &len, payloadFieldExtraBytes);
    }  

    // 填充数据  
    uint32_t frameSize = frameHeaderSize + messageLength;
    char *frame = new char[frameSize + 1];
    memcpy(frame, frameHeader, frameHeaderSize);  
    memcpy(frame + frameHeaderSize, inMessage.c_str(), messageLength);  
    outFrame = std::string(frame, frameSize);
    delete[] frame;
    delete[] frameHeader;
    return true;
}
