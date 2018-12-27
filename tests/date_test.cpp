//
// Created by chenlei on 2018-12-12.
//

#include <util/DateUtil.hpp>
#include <util/Logger.hpp>
#include <gtest/gtest.h>

TEST(test_date,date){

    auto logger=Logger::createLogger("dateLogger");

    auto  d_seconds=DateUtil::currentSeconds();
    logger->info("current  timeStamp :{},len:{}",d_seconds ,std::to_string(d_seconds).length());

    logger->info("date:{}",DateUtil::timeStamp2Date(d_seconds));
    auto dateTime=DateUtil::timeStampSeconds2DateTime(d_seconds);
    logger->info("dateTime:{}, timeStampSeconds:{}",dateTime,d_seconds);
    auto tmpSeconds=DateUtil::dateTime2TimeStampSeconds(dateTime);
    logger->info("re cove timeStampSeconds:{} ",tmpSeconds);
    EXPECT_TRUE(tmpSeconds==d_seconds);

    logger->info("date:{}",DateUtil::timeStampSeconds2DateTime(d_seconds));


    /**
     *
     */
    auto d_mill=DateUtil::currentTimeMillis();
    logger->info("current mill:{}  timeStamp :{},len:{}",d_mill,d_mill%1000 ,std::to_string(d_mill).length());
    auto tmpFormat=DateUtil::timeStampMilliSeconds2DateTimeStamp(d_mill);
    auto d_mill_0=DateUtil::dateTimeStamp2TimeStampMilliSeconds(tmpFormat);
    logger->info("date:{} ,reccc:{}",tmpFormat,d_mill_0);
    EXPECT_TRUE(d_mill==d_mill_0);
}



