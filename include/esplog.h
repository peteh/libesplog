#pragma once
#include <Arduino.h>

enum LOG_LEVEL
{
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR,
};

const char* loglevel_to_string[4];

class Logger
{
public:
    static void _write(uint8_t logLevel, const char *file, uint32_t line, const char *func, const char *message, ...)
    {
        char bufferMessage[512];
        char bufferInfo[1024];
        va_list args;
        va_start(args, message);
        vsnprintf(bufferMessage, sizeof(bufferMessage), message, args);
        va_end(args);
        //  
        snprintf(bufferInfo, sizeof(bufferInfo), "[%s][%s %s():%d] %s\n",loglevel_to_string[logLevel], file, func, line, bufferMessage);
        Serial.print(bufferInfo);
    }
};

#define log_error(_MESSAGE_, ...) \
    Logger::_write(                \
        LOG_LEVEL_ERROR,          \
        (const char *)__FILE__,   \
        (int)__LINE__,            \
        (const char *)__func__, \
        (const char *)_MESSAGE_,  \
        ##__VA_ARGS__)

#define log_warn(_MESSAGE_, ...) \
    Logger::_write(                \
        LOG_LEVEL_WARN,          \
        (const char *)__FILE__,   \
        (int)__LINE__,            \
        (const char *)__func__, \
        (const char *)_MESSAGE_,  \
        ##__VA_ARGS__)

#define log_info(_MESSAGE_, ...) \
    Logger::_write(                \
        LOG_LEVEL_INFO,          \
        (const char *)__FILE__,   \
        (int)__LINE__,            \
        (const char *)__func__, \
        (const char *)_MESSAGE_,  \
        ##__VA_ARGS__)

#define log_debug(_MESSAGE_, ...) \
    Logger::_write(                \
        LOG_LEVEL_DEBUG,          \
        (const char *)__FILE__,   \
        (int)__LINE__,            \
        (const char *)__func__, \
        (const char *)_MESSAGE_,  \
        ##__VA_ARGS__)
