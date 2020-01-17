/************************************************************************
	> File Name: log.cc
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 04:16:58 AM PST
 ************************************************************************/

#include "log.h"
#include "util.h"
#include "config.h"
#include <string>
#include <ostream>
#include <iostream>
#include <algorithm>
#include <string.h>
#define MAXBUFFER 1024

namespace Silly{

//公用日志记录内存,Logger::emerg等函数使用
static char sprint_buf[MAXBUFFER] = {0};
Logger::ptr Logger::m_root = Logger::ptr(new Logger("root"));

std::unordered_map<std::string , Logger::ptr> LoggerManager::m_loggers; 

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

LogLevel::Level LogLevel::fromString(std::string & level){
    std::transform(level.begin(),level.end(),level.begin(),::toupper);
#define XX(lev) \
    if(level == #lev) \
        return LogLevel::lev
    
    XX(ALERT);
    XX(CRIT);
    XX(ERROR);
    XX(WARN);
    XX(NOTICE);
    XX(INFO);
    XX(DEBUG);
    XX(NOTSET);
#undef XX
    return LogLevel::INFO;
}

void Logger::log(LogLevel::Level level,const std::string & content){
	//记录日志
	auto event = getEvent(level,content);
	for(auto & it : m_appenders){//每个appender都要记录
		it.second->log(event);
	}
}

#define XX(msg,level) \
    va_list args;  \
    va_start(args,msg);\
    ::vsprintf(sprint_buf,msg,args); \
    va_end(args); \
    level(std::string(sprint_buf)) 

void Logger::emerg(const std::string & content){
	log(LogLevel::EMERG,content);
}

void Logger::emerg(const char * msg,...){
    XX(msg,emerg);
}

void Logger::fatal(const std::string & content){
	log(LogLevel::FATAL,content);
}
void Logger::fatal(const char * msg,...){
    XX(msg,fatal);
}

void Logger::alert(const std::string & content){
	log(LogLevel::ALERT,content);
}
void Logger::alert(const char * msg,...){
    XX(msg,alert);
}

void Logger::crit(const std::string & content){
	log(LogLevel::CRIT,content);
}
void Logger::crit(const char * msg,...){
    XX(msg,crit);
}

void Logger::error(const std::string & content){
	log(LogLevel::ERROR,content);
}
void Logger::error(const char * msg,...){
    XX(msg,error);
}

void Logger::warn(const std::string & content){
	log(LogLevel::WARN,content);
}
void Logger::warn(const char * msg,...){
    XX(msg,warn);
}

void Logger::notice(const std::string & content){
	log(LogLevel::NOTICE,content);
}
void Logger::notice(const char * msg,...){
    XX(msg,notice);
}

void Logger::info(const std::string & content){
	log(LogLevel::INFO,content);
}
void Logger::info(const char * msg,...){
    XX(msg,info);
}

void Logger::debug(const std::string & content){
	log(LogLevel::DEBUG,content);
}
void Logger::debug(const char * msg,...){
    XX(msg,debug);
}

void Logger::notset(const std::string & content){
	log(LogLevel::NOTSET,content);
}
void Logger::notset(const char * msg,...){
    XX(msg,notset);
}
#undef XX
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

Logger::ptr Logger::getDefaultLogger(){
    auto logger = Logger::getRoot()->getInstance("");
    auto ostreamAppender = OstreamAppender::getInstance("",std::cout); 
    ostreamAppender->setFormatter(BasicFormatter::ptr(new BasicFormatter()));
    logger->addAppender(ostreamAppender);
    return logger;
}

Logger::ptr LoggerManager::getLogger(const char * name){
    auto it = m_loggers.find(name);
    if(it != m_loggers.end()){//当前logger存在
        return it->second;
    } else {//创造一个新的
        if(!::strcmp(name,"")){
            m_loggers.insert(std::make_pair(name,Logger::getRoot()->getDefaultLogger()));
        } else {
            m_loggers.insert(std::make_pair(name,Logger::getRoot()->getInstance(name)));
        }
        return m_loggers[name];
    }
}

/*
 * logs:
 *   - name: root
 *     appenders:
 *       - type: FileAppender
 *         file: /logs/root.txt
 *         level: info
 *         formatter: PatternFormatter
 *         pattern: xxxxxx
 *       - type: OstreamAppender 
 * */
//void LoggerManager::loadFromYaml(const std::string & file){
//    Config::loadFromYaml(file);
//    //搜索logs的配置项
//    int count = 0;
//    while(1){
//        auto var = Config::lookup<YAML::Node>("logs" + std::to_string(count++));
//        if(!var){//搜索完毕
//            break;
//        }
//        YAML::Node node = var->getVal();
//        auto logger = createLogger(node);
//        if(!logger)
//            break;
//        auto appenders = createAppenders(node);
//        for(auto & appender : appenders){
//            logger->addAppender(appender);
//        }
//    }
//}

//Logger::ptr LoggerManager::createLogger(YAML::Node & node){
//    for(auto it = node.begin();
//        it != node.end(); ++it){
//        if(it->first.Scalar() == "name"){
//            return getLogger(it->second.Scalar().c_str());
//        }
//    }    
//    return nullptr;
//}

/*
 * type
 * file
 * level
 * formatter
 * pattern
 * */
//Appender::ptr LoggerManager::getAppenderByNode(const YAML::Node & node){
//    Appender::ptr appender = nullptr;
//    std::string type,file,level,format,pattern;
//    for(auto it = node.begin();it != node.end();++it){
//        if(it->first.Scalar() == "type")
//           type = it->second.Scalar();
//        if(it->first.Scalar() == "file")
//           file = it->second.Scalar();
//        if(it->first.Scalar() == "level")
//           level = it->second.Scalar();
//        if(it->first.Scalar() == "formatter")
//           format = it->second.Scalar();
//        if(it->first.Scalar() == "pattern")
//           pattern = it->second.Scalar(); 
//    }
//    if(type == "OstreamAppender"){
//        appender = OstreamAppender::getInstance("OstreamAppender",std::cout); 
//    }
//    if(type == "FileAppender"){
//        appender = FileAppender::getInstance(file.c_str(),file); 
//    }
//    setAppener(appender,level,format,pattern);
//    return appender;
//}

//void LoggerManager::setAppener(Appender::ptr appender,std::string & level,const std::string & format,
//                             const std::string & pattern){
//    if(!level.empty()){
//        appender->setLevel(LogLevel::fromString(level));
//    }
//    if(format.empty() || format == "BasicFormatter"){
//        appender->setFormatter(BasicFormatter::ptr(new BasicFormatter()));
//        return;
//    }
//    if(format == "PatternFormatter"){
//        if(pattern.empty()){
//            appender->setFormatter(PatternFormatter::getInstance());
//        } else {
//            PatternFormatter::ptr formatPtr = PatternFormatter::getInstance();
//            formatPtr->setConversionPattern(pattern);
//            appender->setFormatter(formatPtr);            
//        }
//    }
//}
//std::vector<Appender::ptr> LoggerManager::createAppenders(YAML::Node & node){
//    std::vector<Appender::ptr> appenders;
//    for(auto it = node.begin();
//            it != node.end(); ++it){
//        if(it->first.Scalar() == "appenders"){
//            for(size_t i = 0; i < it->second.size();++i){
//                appenders.push_back(getAppenderByNode(it->second[i]));
//            }
//        }
//    }
//    return appenders;
//}

LogEvent::ptr Logger::getEvent(LogLevel::Level level,const std::string & content){
	LogEvent::ptr event = LogEvent::ptr(new LogEvent());
	event->setLevel(level);
	event->setContent(content);
	return event;
}

LoggerWrap::LoggerWrap(const std::string & loggerName,LogLevel::Level level,const std::string & filename,
                const std::string & func,int line)
:m_loggerName(loggerName),
 m_level(level){
     m_ss << filename << " " << func << " " << line << " " << Silly::getThreadID() << " ";   
}

LoggerWrap::~LoggerWrap(){
    LoggerManager::getLogger(m_loggerName.c_str())->log(m_level,m_ss.str());
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

FileAppender::FileAppender(const char * name ,const std::string & filename)
:Appender(name){
    m_ofs.open(filename,std::ios::out | std::ios::app);
}

Appender::ptr FileAppender::getInstance(const char * name ,const std::string & filename){
    return FileAppender::ptr(new FileAppender(name,filename));
}

void FileAppender::log(LogEvent::ptr event){
	//格式化器存在且输出日志级别高于Appender级别时，输出
	if(m_formatter){
		if(m_level >= event->getLevel()){
			m_ofs << m_formatter->format(event) << std::endl;
		}
	} else {
		m_ofs << "[Error] Formatter is Null!" << std::endl;
	}	
}
FileAppender::~FileAppender(){
    m_ofs.close();
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
    m_ss.str("");
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

void TabFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event) {
    ss << '\t';
}

void ThreadFormatterItem::format(std::stringstream & ss,const LogEvent::ptr event){
    ss << Silly::getThreadID();      
}

std::string PatternFormatter::format(const LogEvent::ptr event){
    m_ss.str("");
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
 * %T Tab
 * %t ThreadID
 * 基本格式 %xx %xx{} %%转义
 * */
void PatternFormatter::setConversionPattern(const std::string & pattern){
    m_items.clear();
    std::string str;
    for(unsigned i = 0; i < pattern.size();){
        if(pattern[i] != '%'){
            str += pattern[i++];
        } else {
            addContent(str);
            ++i;
            unsigned tmp = i;
            setPattern(pattern,i);
            if(tmp == i){//非特殊字符
                str += pattern[i++];
            }
        }
    } 
    addContent(str);
}

void PatternFormatter::setPattern(const std::string & pattern,unsigned & begin){
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
        case 'T':
             m_items.push_back(TabFormatterItem::ptr(new TabFormatterItem()));
             break;
        case 't':
             m_items.push_back(ThreadFormatterItem::ptr(new ThreadFormatterItem()));
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

std::string PatternFormatter::getDateFormat(const std::string & pattern,unsigned begin){
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
