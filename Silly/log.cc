/************************************************************************
	> File Name: log.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:16:58 AM PST
 ************************************************************************/

#include "log.h"
#include <string>
#include <ostream>
#include <iostream>


namespace Silly{

Logger::ptr Logger::m_root = Logger::ptr(new Logger("root"));

Logger::Logger(const char * name)
	:m_name(name){
	
}

std::string LogLevel::toString(LogLevel::Level level){
	switch(level){
#define XX(level) \
		case LogLevel::level: \
			return #level;\

		XX(EMERG);
		XX(FATAL);
		XX(ALERT);
		XX(CRIT);
		XX(ERROR);
		XX(WARN);
		XX(NOTICE);
		XX(INFO);
		XX(DEBUG);
		XX(NOTSET);
#undef XX
		default:
			return "UNKNOWN";
	}
}

void Logger::log(LogLevel::Level level,const std::string & content){
	//记录日志
	auto event = getEvent(level,content);
	for(auto & it : m_appenders){//每个appender都要记录
		it.second->log(event);
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

LogEvent::ptr Logger::getEvent(LogLevel::Level level,const std::string & content){
	LogEvent::ptr event = LogEvent::ptr(new LogEvent());
	event->setLevel(level);
	event->setContent(content);
	return event;
}

Appender::Appender(const char * name)
	:m_name(name),
	 m_level(LogLevel::NOTSET),
	 m_formatter(nullptr){
	
	}

OstreamAppender::OstreamAppender(const char * name,std::ostream & os)
:Appender(name),
m_os(os) {

}

void OstreamAppender::log(LogEvent::ptr event){
	//格式化器存在且输出日志级别高于Appender级别时，输出
	if(m_formatter){
		if(m_level >= event->getLevel()){
			m_os << m_formatter->format(event) << std::endl;
		}
	} else {
		std::cout << "[Error] Formatter is Null!" << std::endl;
	}	
}

TimeStamp::TimeStamp(time_t time)
	:m_time(time),
	m_format("%Y-%m-%d %H:%M:%S"),
	m_info(setTimePtr())
	{
		
	}


std::string TimeStamp::getTime() const{
	//格式化m_time
	//格式化默认格式为%Y-%m-%d %H:%M:%S
	//by strftime
	char buffer[80];
	::strftime(buffer,80,m_format.c_str(),m_info);
	return buffer;
}

TimeStamp & TimeStamp::operator=(const TimeStamp & rhs){
	if(this == &rhs)
		return *this;
	m_time = rhs.m_time;
	m_info = rhs.m_info;
	return *this;
}

struct tm * TimeStamp::setTimePtr(){
	::time(&m_time);
	return ::localtime(&m_time);
}


std::string BasicFormatter::format(const LogEvent::ptr event){
	m_ss << "[" + LogLevel::toString(event->getLevel())
			  << "] " <<  event->getTimeStamp().getTime()
			  << " " << event->getContent();
	return m_ss.str();
};

AppenderBuilder::AppenderBuilder(const char * name)
:m_name(name) {

}

AppenderBuilder & AppenderBuilder::level(LogLevel::Level level){
	m_level = level;
	return *this;
}

OstreamAppender::OstreamAppenderBuilder(const char * name,std::ostream & os)
	:m_name(name),
	m_os(os) {}

OstreamAppender::OstreamAppenderBuilder & OstreamAppender::OstreamAppenderBuilder::level(LogLevel::Level level){
	
}
}//end of namespace
