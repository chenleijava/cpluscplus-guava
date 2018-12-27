//
// Created by chenlei on 2018/11/9.
//

#include "gtest/gtest.h"
#include "../src/spdlogger/SpdLogger.h"

TEST(spdlog_case, gtestTest) {
    SpdLogger spdLogger("spdLogggerTestLogger");
    spdLogger.show();
    spdLogger.setAge(10);
    spdLogger.getConsole()->info("age:{}",spdLogger.getAge());
}


