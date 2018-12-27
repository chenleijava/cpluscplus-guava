//
// Created by chenlei on 2018-12-25.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wmissing-declarations"
#ifndef CPLUSPLUSGUAVA_ASTROLOGUTIL_H
#define CPLUSPLUSGUAVA_ASTROLOGUTIL_H

#include "astrolog.h"
#include <stdio.h>
#include <mutex>
#include <memory>
#include "util/SingleInstance.hpp"
#include "util/DateUtil.hpp"
#include "util/Logger.hpp"
#include "util/Strings.h"


/**
 *
 */
enum RelationShipchart {
    None       = 0,  //本命盘
    Synastry   = 1, // 配对盘
    Composite  = 2,  // 组合中点盘
    TimeSpaceMidpoint   = 3, // 时空中点盘（time/space）
    Dual       = -1, //比较盘
};

/**
 *
 */
typedef struct ChartBaseInfo{
    int year;
    int mon;
    int day;
    std::string hours_min;// 字符串  18:30
    real dst;  // 夏令时  -- 自动转换  0|1
    real timeZone;//  时区
    real longitude; //经度  字符串  118E4
    real latitude;//维度 字符串 34N56
    std::string userName; // 字符串
    std::string location; //34N56
};

/**
 *
 * 基于 astrolog 封装库
 * 参考 //https://blog.csdn.net/lyx_zhl/article/details/53955914
 * AstrologUtil must be single instance
 */
class AstrologUtil{

private:
        std::mutex astrolog_mutex;
        static FILE *astrologFile;
        static char* filePath;
        static char* writeFilePath;
public:
    AstrologUtil();

public:
    /**
     *
     */
    const static std::shared_ptr<AstrologUtil> instance;

    /**
     *
     */
    const static std::shared_ptr<spdlog::logger> logger;

    /**
     * 是否导出图片
     */
    const static int fGraphics;

/**
     *
     * @return
     */
    static const shared_ptr<AstrologUtil> &getInstance() {
        return instance;
    }

public:

/**
 * 计算本命盘
 * @param chartInfo 基础信息
 * @param fGraphics 是否绘制图片 默认不处理
 * @param nHouseSystem 宫位设置  详见 astrolog.h  文件中 _housesystem 结构体，默认是 hsPlacidus
 */
std::string noRelationChart(ChartBaseInfo &chartInfo,
        int fGraphics=AstrologUtil::fGraphics,int nHouseSystem=hsPlacidus);


/**
 * 计算合盘
 * @param chartInfo0
 * @param chartInfo1
 * @param relationshipchart  合盘类型
 * @param fGraphics
 * @param nHouseSystem 宫位设置  详见 astrolog.h  文件中 _housesystem 结构体，默认是 hsPlacidus
 * @return
 */
std::string relationChart(ChartBaseInfo &chartInfo0,ChartBaseInfo &chartInfo1,int relationshipchart,
        int fGraphics=AstrologUtil::fGraphics,int nHouseSystem=hsPlacidus);


/**
 * 转化为经度
 * @param lon eg .118E4
 * @return
 */
inline double parseLon(std::string lon){
    return RParseSz(lon.data(),pmLon);
}

/**
 * 转化为纬度
 * @param lat eg :34N56
 * @return
 */
inline  double parseLat(std::string lat){
    return RParseSz(lat.data(),pmLat);
}
};
#endif //CPLUSPLUSGUAVA_ASTROLOGUTIL_H

#pragma clang diagnostic pop