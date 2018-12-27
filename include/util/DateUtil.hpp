//
// Created by chenlei on 2018-12-12.
//

#ifndef CPLUSPLUSGUAVA_DATEUTIL_H
#define CPLUSPLUSGUAVA_DATEUTIL_H

#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <time.h>
#include <stdio.h>
#include <iterator>

using namespace std;
using namespace std::chrono;
template<typename T>size_t getArrayLen(T &array) {return sizeof(array) / sizeof(array[0]);}

/***
 * 日期工具类 封装
 * 1. 获取时间戳，秒，毫秒；
 * 2、时间戳格式化 ;
 * 3、时间戳和格式化的日期相互转化；
 */
class DateUtil {

public:
    /**
   *
   * @param timeStampSeconds
   * @return  YYYY-MM-DD
   */
    static std::string timeStamp2Date(const time_t timeStampSeconds) {
        std::ostringstream s;
        s << std::put_time(localtime(&timeStampSeconds), "%F");
        return s.str();
    }


    /**
     * YYYY-MM-DD HH:MM:ss
     * @param timeStampSeconds  单位秒
     * @return
     */
    static std::string timeStampSeconds2DateTime(const time_t timeStampSeconds) {
        char buff[64];
        strftime(buff, getArrayLen(buff),"%F %T",localtime(&timeStampSeconds));
        return std::string(buff);
    }

    /**返回时间戳  单位 秒
     * @param dateTime YYYY-MM-DD HH:MM:ss
     * @return
     */
    static time_t dateTime2TimeStampSeconds(std::string& dateTime) {
        struct tm tmTime={};
        strptime(dateTime.c_str(),"%F %T", &tmTime);
        return mktime(&tmTime);
    }


    /**
     *  返回时间戳 单位 毫秒
     * @param dateTimeStamp  YYYY-MM-DD HH:MM:SS.sss
     * @return
     */
    static time_t dateTimeStamp2TimeStampMilliSeconds(std::string & dateTimeStamp){
        auto delimiter=dateTimeStamp.find('.');
        auto pre=dateTimeStamp.substr(0,delimiter);
        auto next=dateTimeStamp.substr(delimiter+1,3);
        auto pre_t=dateTime2TimeStampSeconds(pre); //单位s
       // printf("pre time:%s ,next:%s",std::to_string(pre_t).c_str(),next.c_str());
        return pre_t*1000+std::stoi(next);
    }


    /**
     * YYYY-MM-DD HH:MM:SS.sss
     * @param timeStampMilliSeconds   毫秒
     * @return
     */
    static std::string timeStampMilliSeconds2DateTimeStamp(const time_t timeStampMilliSeconds) {
        //补位0 ，至少 3位长度
        char milliseconds_str[32]; //
        sprintf(milliseconds_str,"%03d", static_cast<int>(timeStampMilliSeconds % 1000));
        char buff[64];
        auto tmp=timeStampMilliSeconds / 1000;
        strftime(buff, getArrayLen(buff),"%F %T.",localtime(&tmp)); // format pre
        return std::string(buff) + std::string(milliseconds_str);
    }


    /**
     * 获取当前时间戳 -- 毫秒
     * @return
     */
    static time_t currentTimeMillis() {
        //get current time point!
        std::chrono::time_point<std::chrono::system_clock, std::chrono::milliseconds> currentTimePoint =
                std::chrono::time_point_cast<std::chrono::milliseconds>(std::chrono::system_clock::now());
        return std::chrono::duration_cast<std::chrono::milliseconds>(currentTimePoint.time_since_epoch()).count();
    }
    /**
     *获取当前时间戳 -- 秒
     * @return
     */
    static time_t currentSeconds() {
        std::chrono::time_point<std::chrono::system_clock, std::chrono::seconds> currentTimePoint =
                std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
        return std::chrono::duration_cast<std::chrono::seconds>(currentTimePoint.time_since_epoch()).count();
    }
};

#endif //CPLUSPLUSGUAVA_DATEUTIL_H
