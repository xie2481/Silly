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
namespace Silly{

//定义日志等级
struct LogLevel{
	/*
	 * brief:日志等级
	 * */
 enum Level{
	EMERG = 0,
	FATAL = 0,
	ALERT = 100,
	CRIT = 200,
	ERROR = 300,
	WARN = 400,
	NOTICE = 500,
	INFO = 600,
	DEBUG = 700,
	NOTSET = 800
 };
};

//定义日志目的地
class Appender{
public:
	typedef std::shared_ptr<Appender> ptr;

	/*
	 * brief:Appender Constructor
	 * parmarter[in] name : Appender名字
	 * */
	Appender(const char * name);
	
	/*
	 * brief:获取Appender名字
	 * */
	const char * getName() const { return m_name;}

	/*
	 * brief:记录日志函数
	 * parmarter[in] level : 日志等级
	 * parmarter[in] content : 日志内容
	 * */
	virtual void log(LogLevel::Level level,const std::string & content) = 0;
	virtual ~Appender() {}
protected:
	//Appender名字
	const char * m_name;
};

/*
 * 输出到输出流的Appender
 * */
class OstreamAppender : public Appender{
public:
	typedef std::shared_ptr<OstreamAppender> ptr;
	/*
	 * brief:OstreamAppender Constructor
	 * parmarter[in] name : OstreamAppender名字
	 * parmarter[in ref] os : 目标输出流
	 * */
	OstreamAppender(const char * name ,std::ostream & os);

	/*
	 * brief:实现基类中的log
	 * */
	void log(LogLevel::Level level , const std::string & content) override;
private:
	std::ostream & m_os;
};

//定义日志输出器
class Logger : public std::enable_shared_from_this<Logger>{
public:
	typedef std::shared_ptr<Logger> ptr;

	/*
	 * brief:所有等级的日志记录调用接口
	 * parmarter[in] level:日志等级
	 * parmarter[in] content:记录内容
	 * */
	void log(LogLevel::Level level,const std::string & content);

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
	 * brief:设置Logger优先级
	 * parmarter[in] level:优先级的设置参数
	 * */
	void setLevel(LogLevel::Level level) { m_level = level;}

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
	 * brief:Logger优先级
	 * */
	LogLevel::Level m_level;

	/*
	 * 存储所有的appender
	 * */
	std::unordered_map<const char * , Appender::ptr> m_appenders;
	
	/*
	 * 定义根日志输出器
	 * */
	static Logger::ptr m_root;
};

}//end of namespace

#endif
