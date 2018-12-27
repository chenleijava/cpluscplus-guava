//
// Created by chenlei on 2018/11/9.
//

#include "SpdLogger.h"


/**
 *
 * @param loggerName
 */
 SpdLogger::SpdLogger(std::string loggerName) {
    spdlog::set_level(spdlog::level::debug);
    spdlog::set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [thread %t] %v");
    console = spdlog::stdout_color_mt(loggerName);
}

/**
 *
 */
void SpdLogger::show() {
    console->info("Welcome to spdlog!");
    console->error("Some error message with arg: {}", 1);

    auto err_logger = spdlog::stderr_color_mt("stderr");
    err_logger->error("Some error message");

    // Formatting examples
    console->warn("Easy padding in numbers like {:02d}", 12);
    console->critical("Support for int: {0:d};  hex: {0:x};  oct: {0:o}; bin: {0:b}", 11);
    console->info("Support for floats {:03.2f}", 1.23456);
    console->info("Positional args are {0} {1}..", "too", "supported");
    console->info("{:<30}", "left aligned");
    spdlog::get("console")->info("loggers can be retrieved from a global registry using the spdlog::get(logger_name)");


    // Runtime log levels
    spdlog::set_level(spdlog::level::info); // Set global log level to info
    console->debug("This message should not be displayed!");
    console->set_level(spdlog::level::trace); // Set specific logger's log level
    console->debug("This message should be displayed..");

    // Customize msg format for all loggers

    console->debug("This an info message with custom format");

    // Compile time log levels
    // define SPDLOG_DEBUG_ON or SPDLOG_TRACE_ON
    SPDLOG_TRACE(console, "Enabled only #ifdef SPDLOG_TRACE_ON..{} ,{}", 1, 3.23);
    SPDLOG_DEBUG(console, "Enabled only #ifdef SPDLOG_DEBUG_ON.. {} ,{}", 1, 3.23);
}

/**
 *
 * @return
 */
unsigned int SpdLogger::getAge() const {
    return age;
}

void SpdLogger::setAge(unsigned int age) {
    SpdLogger::age = age;
}

SpdLogger::~SpdLogger() {

}

const shared_ptr<spdlog::logger> &SpdLogger::getConsole() const {
    return console;
}
