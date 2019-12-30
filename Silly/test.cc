/*************************************************************************
	> File Name: test.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:37:25 AM PST
 ************************************************************************/

#include "log.h"
#include <iostream>

using namespace Silly;
int main(){
	
	Logger::ptr root = Logger::getRoot();
	Logger::ptr info = root->getInstance("test");
	info->addAppender(OstreamAppender::ptr(new OstreamAppender("test",std::cout)));
	info->log(LogLevel::DEBUG,"test");
	return 0;
}
