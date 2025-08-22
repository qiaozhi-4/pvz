#pragma once

// ANSI 转义序列定义
#define RESET   "\033[0m" // 重置为默认值
#define RED     "\033[31m" // 红色
#define GREEN   "\033[32m" // 绿色
#define YELLOW  "\033[33m" // 黄色
#define BLUE    "\033[34m" // 蓝色
#define MAGENTA "\033[35m" // 洋红色
#define CYAN    "\033[36m" // 青色
#define WHITE   "\033[37m" // 白色

// 处理变长参数
#define VA_ARGS(...) , ##__VA_ARGS__
#define EXTLOG(level, fmt, ...) Logger::Log(level, __FILE__, __LINE__, fmt VA_ARGS(__VA_ARGS__))
#define LOG_CRIT(fmt, ...) EXTLOG(Logger::Level::Critical, fmt, __VA_ARGS__)
#define LOG_ERROR(fmt, ...) EXTLOG(Logger::Level::Error, fmt, __VA_ARGS__)
#define LOG_WARNING(fmt, ...) EXTLOG(Logger::Level::Warning, fmt, __VA_ARGS__)
#define LOG_INFO(fmt, ...) EXTLOG(Logger::Level::Info, fmt, __VA_ARGS__)
#define LOG_DEBUG(fmt, ...) EXTLOG(Logger::Level::Debug, fmt, __VA_ARGS__)
#define LOG_TRACE(fmt, ...) EXTLOG(Logger::Level::Trace, fmt, __VA_ARGS__)


class Logger {
public:
    enum class Level {
        None,
        Critical,
        Error,
        Warning,
        Info,
        Debug,
        Trace
    };

    static void Log(Level logLevel, const char *filename, int line, const char *fmt, ...);
};

