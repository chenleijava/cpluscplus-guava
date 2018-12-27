//
// Created by chenlei on 2018-12-12.
//

#ifndef CPLUSPLUSGUAVA_LOGGER_H
#define CPLUSPLUSGUAVA_LOGGER_H

#include <memory>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/daily_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>


/**
 *
 */
class Logger{
public:
    /**
     * @param loggerName  logger name
     * @return shared_ptr;
     */
    inline static std::shared_ptr<spdlog::logger> createLogger(std::string &&loggerName){
        spdlog::set_level(spdlog::level::debug);
        spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [thread %t] %v");
        return spdlog::stdout_color_st(loggerName);
    }
};
//别名 防止和其他包冲突
using logger=Logger;

#endif //CPLUSPLUSGUAVA_LOGGER_H
