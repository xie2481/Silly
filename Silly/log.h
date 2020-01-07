/*************************************************************************
	> File Name: log.h
	> Author: chaoqiangxie
	> Mail: 2481086105@qq.com 
	> Created Time: Mon 30 Dec 2019 03:57:01 AM PST
 ************************************************************************/

#ifndef _LOG_H__
#define _LOG_H__

#include <memory>
#include <string>
#include <unordered_map>
#include <sstream>
#include <time.h>
#include <vector>

namespace Silly{

//定义日志等级
struct LogLevel{
	/*
	 * brief:日志等级
	 * */
 enum Level{
	EMERG = 0,
	FATAL = 50,
	ALERT = 100,
	CRIT = 200,
	ERROR = 300,
	WARN = 400,
	NOTICE = 500,
	INFO = 600,
	DEBUG = 700,
	NOTSET = 800
 };
 /*
  * brief:输出优先级的字符串
  * */
 static std::string toString(LogLevel::Level level);
};

//格式化时间
class TimeStamp{
public:
	/*
	 * brief:TimeStamp Constructor
	 * parmarter [in] time : 设置m_time
	 * */
	TimeStamp(time_t time = ::time(0),const std::string & format = "%Y-%M-%d %H:%m:%S");

	/*
	 * brief:getTime
	 * parmarter [out] : 获取m_time的时间戳
	 * */
	std::string getTime() const;

	/*
	 * brief:setTime
	 * parmarter [in] time : 设置m_time
	 * */
	void setTime(time_t time) { m_time = time; setTimePtr();}

	/*
	 * brief:获得秒数
	 * */
	int getSecond() const { return m_info->tm_sec;} 

	/*
	 * brief:获得分钟信息
	 * */
	int getMinute() const { return m_info->tm_min;}

	/*
	 * brief:获得小时信息
	 * */
	int getHour() const { return m_info->tm_hour;}

	/*
	 * brief:获得一个月中第几天的信息
	 * */
	int getDay() const { return m_info->tm_mday;}

	/*
	 * brief:获得月份信息
	 * */
	int getMonth() const { return m_info->tm_mon;}

	/*
	 * brief:获得年份信息
	 * */
	int getYear() const { return m_info->tm_year + 1900;}

	TimeStamp & operator=(const TimeStamp & rhs);

private:
	time_t m_time;
	const std::string m_format;
	struct tm * m_info;
private:
	/*
	 * 设置指向时间的指针
	 * */
	struct tm * setTimePtr();
};

class Logger;
//定义输出事件
class LogEvent{
public:
	typedef std::shared_ptr<LogEvent> ptr;
	/*
	 * brief:get set
	 * */
	const std::string & getLogName() const { return m_logName;}
	
	void setLogName(const std::string & logName) { m_logName = logName;}


	const std::string & getContent() const { return m_content;}

	void setContent(const std::string & content) { m_content = content;}

	LogLevel::Level getLevel() const{ return m_level;}

	void setLevel(LogLevel::Level level) { m_level = level; }

	const std::string & getThreadName() const { return m_threadName;}

	void setThreadName(const std::string & threadName) { m_threadName = threadName;}

	const TimeStamp & getTimeStamp() const { return m_timeStamp;}

	void setTimeStame(const TimeStamp & timeStamp) { m_timeStamp = timeStamp;}
private:
	//日志输出器的名字
	std::string  m_logName;
	//日志内容
    std::string m_content;
	//日志优先级
	LogLevel::Level m_level;
	//线程名字
	std::string m_threadName;
	//时间戳
	TimeStamp m_timeStamp;
};

class Appender; 
//定义日志格式器
class Formatter{
public:
	typedef std::shared_ptr<Formatter> ptr;
	virtual ~Formatter() {}

	/*
	 * brief:定义纯虚函数，日志格式器的格式化函数
	 * */
	virtual std::string format(const LogEvent::ptr event) = 0;
protected:
	//格式化日志格式时使用，存储下来，防止多次创建造成的开销
	std::stringstream m_ss;
};

//定义基础的日志格式器
class BasicFormatter : public Formatter{
public:
	/*
	 * brief:实现父类的format,输出格式为[优先级] 时间戳 内容
	 * */
	std::string format(const LogEvent::ptr event) override;
};

//定义自定义格式的日志格式器
/*
 * 参数说明
 * %d 日期 可以进一步设置 用花括号包围 %H:小时 %M:月份 %S 秒 %Y 年份 %m 分钟 %d:天
 * %m 消息
 * %n 换行符
 * %p 优先级
 * */

class FormatterItem 
{
    public:
       typedef std::shared_ptr<FormatterItem> ptr;
       virtual void format(std::stringstream & ss,const LogEvent::ptr event) = 0;

       virtual ~FormatterItem() {} 
};

class ContentFormatterItem : public FormatterItem 
{
    public:
        typedef std::shared_ptr<ContentFormatterItem> ptr;
        ContentFormatterItem(const std::string & msg);

        void format(std::stringstream & ss,const LogEvent::ptr event) override;
    private:
        const std::string m_msg;
};
class DateFormatterItem : public FormatterItem 
{
    public:
        typedef std::shared_ptr<DateFormatterItem> ptr;
        DateFormatterItem(const std::string & format = "%Y-%M-%d %H:%m:%S"); 
        void format(std::stringstream & ss,const LogEvent::ptr event) override;
    private:
        std::string m_format;
};


class MessageFormatterItem : public FormatterItem
{
    public:
        typedef std::shared_ptr<MessageFormatterItem> ptr;
        void format(std::stringstream & ss,const LogEvent::ptr event) override;        
};

class LevelFormatterItem : public FormatterItem
{
    public:
        typedef std::shared_ptr<LevelFormatterItem> ptr;
        void format(std::stringstream & ss,const LogEvent::ptr event) override;        
};
class LineFormatterItem : public FormatterItem
{
    public:
        typedef std::shared_ptr<LineFormatterItem> ptr;
        void format(std::stringstream & ss,const LogEvent::ptr event) override;        
};

class PatternFormatter : public Formatter
{
    public:
        typedef std::shared_ptr<PatternFormatter> ptr;
        /*
         * brief:设置格式
         * */
        void setConversionPattern(const std::string & pattern);
        
        std::string format(const LogEvent::ptr event) override;
        static PatternFormatter::ptr getInstance();
    private:
         PatternFormatter() {}
         std::vector<FormatterItem::ptr> m_items;
    
    private:
         /*
          * brief:添加输出格式中的普通字符串
          * */
         void addContent(std::string & str);

         /*
          * brief:获取当前pattern的日期格式
          * */
         std::string getDateFormat(const std::string & pattern,int begin);

         /*
          * brief:递归处理格式串
          * */
         void setPattern(const std::string & pattern,int & begin);
};


//定义日志目的地
class Appender{
	friend class Logger;
public:
	typedef std::shared_ptr<Appender> ptr;

	/*
	 * brief:获取Appender名字
	 * */
	const char * getName() const { return m_name;}

	/*
	 * brief:记录日志函数
	 * parmarter[in] level : 日志等级
	 * parmarter[in] content : 日志内容
	 * */
	virtual ~Appender() {}

	/*
	 * brief:set Level
	 * */
	void setLevel(LogLevel::Level level) { m_level = level;}

	/*
	 * brief:get Appender level
	 * */
	LogLevel::Level getLevel() const { return m_level;}

	void setFormatter(Formatter::ptr formatter) { m_formatter = formatter; }
protected:
	/*
	 * brief:Appender Constructor
	 * parmarter[in] name : Appender名字
	 * */
	Appender(const char * name);
	//Appender名字
	const char * m_name;
	//Appender优先级
	LogLevel::Level m_level;
	//Appender的格式化器
	Formatter::ptr m_formatter;
private:
	virtual void log(LogEvent::ptr event) = 0;
};


/*
 * 输出到输出流的Appender
 * */
class OstreamAppender : public Appender{
public:
	typedef std::shared_ptr<OstreamAppender> ptr;
	
	static Appender::ptr getInstance(const char * name ,std::ostream & os);

private:
	/*
	 * brief:OstreamAppender Constructor
	 * parmarter[in] name : OstreamAppender名字
	 * parmarter[in ref] os : 目标输出流
	 * */
	OstreamAppender(const char * name ,std::ostream & os);
	/*
	 * brief:实现基类中的log
	 * */
	void log(LogEvent::ptr event) override;
private:
	std::ostream & m_os;
};


//定义日志输出器
class Logger : public std::enable_shared_from_this<Logger>{
	friend class LogEvent;
public:
	typedef std::shared_ptr<Logger> ptr;

	/*
	 * brief:所有等级的日志记录调用接口
	 * parmarter[in] level:日志等级
	 * parmarter[in] content:记录内容
	 * */
	void log(Silly::LogLevel::Level level,const std::string & content);

	/*
	 * brief:emerg级别记录
	 * parmarter[in] content:日志内容
	 * */
	void emerg(const std::string & content);

	/*
	 * brief:fatal级别记录
	 * parmarter[in] content:日志内容
	 * */
	void fatal(const std::string & content);
	
	/*
	 * brief:alert级别记录
	 * parmarter[in] content:日志内容
	 * */
	void alert(const std::string & content);

	/*
	 * brief:crit级别记录
	 * parmarter[in] content:日志内容
	 * */
	void crit(const std::string & content);
	
	/*
	 * brief:error级别记录
	 * parmarter[in] content:日志内容
	 * */
	void error(const std::string & content);
	
	/*
	 * brief:warn级别记录
	 * parmarter[in] content:日志内容
	 * */
	void warn(const std::string & content);

	/*
	 * brief:notice级别记录
	 * parmarter[in] content:日志内容
	 * */
	void notice(const std::string & content);

	/*
	 * brief:info级别记录
	 * parmarter[in] content:日志内容
	 * */
	void info(const std::string & content);

	/*
	 * brief:debug级别记录
	 * parmarter[in] content:日志内容
	 * */
	void debug(const std::string & content);

	/*
	 * brief:notset级别记录
	 * parmarter[in] content:日志内容
	 * */
	void notset(const std::string & content);
	
	/*
	 * brief:添加Appender
	 * parmarter[in] appender: 待添加的appender
	 * */
	void addAppender(Appender::ptr appender);

	/*
	 * brief:删除Appender
	 * parmarter[in] name:删除的appender名字
	 * */
	void delAppender(const char * name);

	/*
	 * brief:由根日志输出器获取新的日志输出器
	 * parmarter[in] name : 新的日志输出器的名字
	 * */
	Logger::ptr getInstance(const char * name);

	/*
	 * brief:获取根日志输出器
	 * */
	static Logger::ptr getRoot();

private:
	/*
	 * brief:Logger的名字
	 * */
	const char * m_name;
	
	/*
	 * brief:Logger Constructor
	 * parmarter[in] name : Logger name
	 * */
	Logger(const char * name = "root");

	/*
	 * 存储所有的appender
	 * */
	std::unordered_map<const char * , Appender::ptr> m_appenders;
	
	/*
	 * 定义根日志输出器
	 * */
	static Logger::ptr m_root;

private:
	/*
	 * brief:获取LogEvent指针
	 * parmarter [in] level:日志事件级别
	 * parmarter [in] content:日志事件内容
	 * parmarter [out] LogEvent指针
	 * */
    LogEvent::ptr getEvent(Silly::LogLevel::Level level,const std::string & content);
};

} //end of namespace

#endif
