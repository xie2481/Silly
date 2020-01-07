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

Appender::ptr OstreamAppender::getInstance(const char * name ,std::ostream & os){
    return OstreamAppender::ptr(new OstreamAppender(name,os));
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

TimeStamp::TimeStamp(time_t time,const std::string & format)
	:m_time(time),
	m_format(format),
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

ContentFormatterItem::ContentFormatterItem(const std::string & msg)
:m_msg(msg) { }

void ContentFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    ss << m_msg;
}

DateFormatterItem::DateFormatterItem(const std::string & format)
:m_format(format) { }


void DateFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    TimeStamp timeStamp(::time(0),m_format);
    ss << timeStamp.getTime();
}

void MessageFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    ss << event->getContent();
}    

void LineFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    ss << '\n';
} 

void LevelFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    ss << LogLevel::toString(event->getLevel());
}

std::string PatternFormatter::format(const LogEvent::ptr event){
    for(auto & item : m_items){
        item->format(m_ss,event);
    }       
   return m_ss.str(); 
}
        
/*
 * 参数说明
 * %d 日期 可以进一步设置 用花括号包围 %H:小时 %M:月份 %S 秒 %Y 年份 %m 分钟 %d:天
 * %m 消息
 * %n 换行符
 * %p 优先级
 * 基本格式 %xx %xx{} %%转义
 * */
void PatternFormatter::setConversionPattern(const std::string & pattern){
    m_items.clear();
    std::string str;
    for(int i = 0; i < pattern.size();){
        if(pattern[i] != '%'){
            str += pattern[i++];
        } else {
            addContent(str);
            ++i;
            int tmp = i;
            setPattern(pattern,i);
            if(tmp == i){//非特殊字符
                str += pattern[i++];
            }
        }
    } 
    addContent(str);
}

void PatternFormatter::setPattern(const std::string & pattern,int & begin){
    switch(pattern[begin]){
        case 'm':
            m_items.push_back(MessageFormatterItem::ptr(new MessageFormatterItem()));
            break;
        case 'n':
            m_items.push_back(LineFormatterItem::ptr(new LineFormatterItem()));
            break;
        case 'p':
            m_items.push_back(LevelFormatterItem::ptr(new LevelFormatterItem()));
            break;
        case 'd':
             if(begin + 1 < pattern.size() && pattern[begin + 1] == '{'){
                 std::string timeFormat = getDateFormat(pattern,begin + 2);
                 begin += timeFormat.size() + 3;
                 m_items.push_back(DateFormatterItem::ptr(new DateFormatterItem(timeFormat)));
                 return;
             }
             m_items.push_back(DateFormatterItem::ptr(new DateFormatterItem()));
             break;
        default:
             --begin;
             break;
    }
    ++begin;
}
void PatternFormatter::addContent(std::string & str){
    if(str == "")
        return;
    m_items.push_back(ContentFormatterItem::ptr(new ContentFormatterItem(str)));
    str="";
}

std::string PatternFormatter::getDateFormat(const std::string & pattern,int begin){
    std::string str;
    while(begin < pattern.size() && pattern[begin] != '}'){
        str += pattern[begin++];
    }
    return str;
}

PatternFormatter::ptr PatternFormatter::getInstance(){
    return PatternFormatter::ptr(new PatternFormatter());
}

}//end of namespace
