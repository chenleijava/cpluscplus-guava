//
// Created by chenlei on 2018/11/9.
//

#ifndef CPLUSPLUSGUAVA_SPDLOGGER_H
#define CPLUSPLUSGUAVA_SPDLOGGER_H
#include <string>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"

using namespace std;

/**
 * spdlogger   工具类
 */
class SpdLogger {
public:

    SpdLogger(std::string loggerName);


    virtual ~SpdLogger();

    /**
     *
     * @return
     */
    unsigned int getAge() const;

    /**
     *
     * @param age
     */
    void setAge(unsigned int age);

    /**
     *
     */
    void  show();

    /**
     *
     * @return
     */
    const shared_ptr<spdlog::logger> &getConsole() const;

private:
    /**
     *
     */
    unsigned  int age;
    /**
     *
     */
    std::shared_ptr<spdlog::logger> console;
};


#endif //CPLUSPLUSGUAVA_SPDLOGGER_H
