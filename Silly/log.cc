/*************************************************************************
	> File Name: log.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:16:58 AM PST
 ************************************************************************/

#include "log.h"
#include <string>
#include <ostream>


namespace Silly{

Logger::ptr Logger::m_root = Logger::ptr(new Logger("root"));

Logger::Logger(const char * name)
	:m_name(name)
	,m_level(LogLevel::NOTSET){
	
}

void Logger::log(LogLevel::Level level,const std::string & content){
	//日志等级高于当前优先级时，该日志被记录
	//数值越小，优先级越高
	if(level <= m_level){
		//记录日志
		for(auto & it : m_appenders){//每个appender都要记录
			it.second->log(level,content);
		}
	}
}

void Logger::emerg(const std::string & content){
	log(LogLevel::EMERG,content);
}

void Logger::fatal(const std::string & content){
	log(LogLevel::FATAL,content);
}

void Logger::alert(const std::string & content){
	log(LogLevel::ALERT,content);
}

void Logger::crit(const std::string & content){
	log(LogLevel::CRIT,content);
}

void Logger::error(const std::string & content){
	log(LogLevel::ERROR,content);
}

void Logger::warn(const std::string & content){
	log(LogLevel::WARN,content);
}

void Logger::notice(const std::string & content){
	log(LogLevel::NOTICE,content);
}

void Logger::info(const std::string & content){
	log(LogLevel::INFO,content);
}

void Logger::debug(const std::string & content){
	log(LogLevel::DEBUG,content);
}

void Logger::notset(const std::string & content){
	log(LogLevel::NOTSET,content);
}

void Logger::addAppender(Appender::ptr appender){
	/*
	 * 如果该appender已存在，则忽略此次操作，否则加入到列表中
	 * */
	if(m_appenders.find(appender->getName()) == m_appenders.end()){//not found
		m_appenders.insert(std::make_pair(appender->getName(),appender));
	}
}

void Logger::delAppender(const char * name){
	/*
	 * 如果该appender存在列表中，则删除它
	 * */
	auto it = m_appenders.find(name);
	if(it != m_appenders.end()){
		m_appenders.erase(it);
	}
}

Logger::ptr Logger::getRoot(){
	return m_root;
}

Logger::ptr Logger::getInstance(const char * name){
	/*
	 * 与m_root做比较，当前变量为m_root时，才创建新实例
	 * */
	auto self = shared_from_this();
	if(self == m_root)
		return Logger::ptr(new Logger(name));
	else
		return nullptr;
}

Appender::Appender(const char * name)
	:m_name(name) {
	
	}

OstreamAppender::OstreamAppender(const char * name,std::ostream & os)
:Appender(name),
m_os(os) {

}

void OstreamAppender::log(LogLevel::Level level , const std::string & content){
	m_os << content;	
}

}//end of namespace
