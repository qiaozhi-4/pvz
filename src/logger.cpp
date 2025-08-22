#include "logger.h"

#include <iostream>
#include <cstdarg>
#include <filesystem>

void Logger::Log(Logger::Level logLevel, const char *filepath, int line, const char *fmt, ...) {
    switch (logLevel) {
        case Logger::Level::None:
            std::cout << "[" << RESET << "None" << RESET << "]";
            break;
        case Logger::Level::Critical:
            std::cout << "[" << RED << "Critical" << RESET << "]";
            break;
        case Logger::Level::Error:
            std::cout << "[" << RED << "Error" << RESET << "]";
            break;
        case Logger::Level::Warning:
            std::cout << "[" << YELLOW << "Warning" << RESET << "]";
            break;
        case Logger::Level::Info:
            std::cout << "[" << GREEN << "Info" << RESET << "]";
            break;
        case Logger::Level::Debug:
            std::cout << "[" << CYAN << "Debug" << RESET << "]";
            break;
        case Logger::Level::Trace:
            std::cout << "[" << MAGENTA << "Trace" << RESET << "]";
            break;
        default:
            break;
    }

    // 处理变长参数(获取并格式化)
    char buffer[1024];
    va_list args;
    va_start(args, fmt);
    vsprintf_s(buffer, fmt, args);
    va_end(args);

    // 获取文件名称
    std::string fileName = std::filesystem::path(filepath).filename().string();

    std::cout << " [" << fileName << ":" << line << "] " << buffer << std::endl;
}