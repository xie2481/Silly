/*************************************************************************
	> File Name: test.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:37:25 AM PST
 ************************************************************************/

#include "../Silly/log.h"
#include <iostream>
using namespace Silly;
int main(){
	
	/*Logger::ptr root = Logger::getRoot();
	Logger::ptr info = root->getInstance("test");
	auto appender = OstreamAppender::getInstance("test",std::cout);
	appender->setFormatter(BasicFormatter::ptr(new BasicFormatter()));
	info->addAppender(appender);
	info->log(LogLevel::DEBUG,"test");*/
    /*auto info = LoggerManager::getLogger("test");
    auto appender = FileAppender::getInstance("test","test.txt");
    auto appender1 = OstreamAppender::getInstance("test1",std::cout);
    appender1->setFormatter(BasicFormatter::ptr(new BasicFormatter()));
    PatternFormatter::ptr pattern = PatternFormatter::getInstance(); 
    pattern->setConversionPattern("[%%%%%%%%%%%%%m]%T%t_%d_{dsad}");
    appender->setFormatter(pattern);
    info->addAppender(appender);
    info->addAppender(appender1);
    info->emerg("test%d",1);*/
    SILLY_LOG_ALERT("test%d",1);
    //std::cout << SILLY_LOG_PREFIX << std::endl;;
	return 0;
}
