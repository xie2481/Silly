#ifndef _SILLY_UTIL_H_
#define _SILLY_UTIL_H_

#include <stdint.h>
#include <vector>
#include <string>

namespace Silly{

uint32_t GetThreadID();

uint64_t GetFiberID();
void BackTrace(std::vector<std::string> & info , int size = 100 , int skip = 2);

std::string BackTrace(const std::string & prefix ="",int size = 100,int skip = 2);

}// end of namespace

#endif
