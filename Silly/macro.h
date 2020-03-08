//
// Created by add on 2020/3/2.
//

#ifndef SILLY_MACRO_H
#define SILLY_MACRO_H

#include "log.h"
#include "util.h"

#define SILLY_ASSERT(expression) \
    if(!(expression)) {\
        SILLY_LOG_ERROR("system") << "Assertion '"\
                                  << #expression << "' failed.\n"\
                                  <<Silly::BackTrace("Backtrace:");\
    }

#define SILLY_ASSERT2(expression,prefix) \
    if(!(expression)) {\
        SILLY_LOG_ERROR("system") << "Assertion '"\
                                  << #expression << "' failed." << prefix\
                                  << "\n"\
                                  <<Silly::BackTrace("Backtrace:");\
    }
#endif //SILLY_MACRO_H
