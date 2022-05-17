#ifndef HTTP_MODULEMAR_HPP
#define HTTP_MODULEMAR_HPP

namespace HTTP {

class modulemar{
    public:
        ~modulemar(){
              std::cout<<" thread exit; "<<std::endl;
        }
};
}
#endif