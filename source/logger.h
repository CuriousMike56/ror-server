#ifndef LOGGER_H_
#define LOGGER_H_

#include <string>


enum LogLevel
{
	LOG_DEBUG=0,
	LOG_VERBOSE,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR
};

enum LogType
{
	LOGTYPE_FILE=0,
	LOGTYPE_DISPLAY
};

//extern int loglevel;
void logmsgf(const LogLevel& level, const char* format, ...);

class Logger
{
public:
	virtual ~Logger();
	
	static void log(const LogLevel& level, const char* format, ...);
	static void log(const LogLevel& level, const std::string& msg);
	
	static void setOutputFile(const std::string& filename);
	static void setLogLevel(const LogType type, const LogLevel level);
	
private:
	Logger();
	Logger instance();
	static Logger theLog;
	static FILE *file;
	static LogLevel log_level[2];
	static char *loglevelname[5];
};

class ScopeLog
{
public:
	ScopeLog(std::string func)
	{
		msg = func;
		logmsgf(LOG_DEBUG, "%s - %s", "ENTER", msg.c_str());
	}
	
	~ScopeLog()
	{
		logmsgf(LOG_DEBUG, "%s - %s", "EXIT", msg.c_str());
	}
private:
	std::string msg;
};

#define STACKLOG Logger::log( LOG_DEBUG, __PRETTY_FUNCTION__ )

#endif // LOGGER_H_