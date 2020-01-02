/*************************************************************************
	> File Name: test.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:37:25 AM PST
 ************************************************************************/

#include "log.h"
#include <iostream>
enum Test{
	Test
};
using namespace Silly;
int main(){
	
	Logger::ptr root = Logger::getRoot();
	Logger::ptr info = root->getInstance("test");
	auto appender = OstreamAppender::ptr(new OstreamAppender("test",std::cout));
	appender->setFormatter(BasicFormatter::ptr(new BasicFormatter()));
	info->addAppender(appender);
	info->log(LogLevel::DEBUG,"test");
	/*TimeStamp time;
	std::cout << time.getDay() << std::endl;
	std::cout << time.getMonth() << std::endl;
	std::cout << time.getYear() << std::endl;*/
	
	return 0;
}
