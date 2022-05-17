#ifndef FRAME_DATETIME_UTILITY
#define FRAME_DATETIME_UTILITY

#include <iostream>
#include <ctime>
#include <array>
#include <string>
#include <sys/time.h>
#include <unistd.h>

namespace HTTP {

std::string getGmtTime(time_t inputtime=0);
unsigned long timeid();

std::string date(std::string format,unsigned long inputtime=0);

//Sat, 02 Jan 2021 00:12:45 GMT to sec
unsigned long strgmttotime(std::string gmtstr);

//2022-02-09 08:12:45 to sec
unsigned long strtotime(std::string str);
}
#endif 