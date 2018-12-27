#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by chenlei on 2018-12-25.
//

#include "AstrologUtil.h"



/**
 * astrolog 主程序访问 单例
 */
const  std::shared_ptr<AstrologUtil> AstrologUtil::instance=SingleInstance<AstrologUtil>::getInstance();
const  std::shared_ptr<spdlog::logger> AstrologUtil::logger=Logger::createLogger("astrolog_util_logger");
char* AstrologUtil::filePath= const_cast<char*>("resources/them/astrolog.as");
FILE *AstrologUtil::astrologFile=FileOpen(filePath, 0, nullptr);
char* AstrologUtil::writeFilePath=const_cast<char*>("~/Desktop/xx");
const int AstrologUtil::fGraphics=0;  // 是否导出图片


/**
 * init load astrolog.as file
 */
AstrologUtil::AstrologUtil() {
    FProcessSwitchFile(filePath, astrologFile);
}


/**
 * 合盘计算
 * @param chartInfo0
 * @param chartInfo1
 * @param relationshipchart    合盘类型
 * @param fGraphics  是否绘制
 * @param nHouseSystem 宫位设置
 * @return
 */
std::string AstrologUtil::relationChart(ChartBaseInfo &chartInfo0,ChartBaseInfo &chartInfo1,
        int relationshipchart,int fGraphics,int  nHouseSystem){
    std::lock_guard<std::mutex>lockGuard(astrolog_mutex);
#ifdef USE_DEBUG
    time_t begin=DateUtil::currentTimeMillis();
#endif
    InitProgram();
    ciTran = ciFour = ciThre = ciTwin = ciCore;
    is.fDst=fTrue;//夏令时自动检查
    is.fSzPersist= fTrue; //处理时参数字符串是否持久？
    is.fHaveInfo=1; // 禁止 pop  user，防止主程序挂起；


    // init first person chart info
    std::vector<std::string> tmpV;
    Strings::split(chartInfo0.hours_min,tmpV,":");
    real  hours=std::stod(tmpV[0])+std::stod(tmpV[1])/60.0;
    tmpV.clear();
    ciCore={
            chartInfo0. mon,
            chartInfo0. day,
            chartInfo0. year,
            hours,
            chartInfo0. dst,
            chartInfo0.timeZone,
            chartInfo0.longitude,
            chartInfo0. latitude,
            chartInfo0.userName.data(),
            chartInfo0. location.data()
    };



    // init second person chart info
    Strings::split(chartInfo1.hours_min,tmpV,":");
    hours=std::stod(tmpV[0])+std::stod(tmpV[1])/60.0;
    tmpV.clear();
    ciTwin={
            chartInfo1. mon,
            chartInfo1. day,
            chartInfo1. year,
            hours,
            chartInfo1. dst,
            chartInfo1.timeZone,
            chartInfo1.longitude,
            chartInfo1. latitude,
            chartInfo1.userName.data(),
            chartInfo1. location.data()
    };


    char *v0= const_cast<char *>("Astrolog");
    char *v1= const_cast<char *>("-Xo");
    char tmp[32];
    sprintf(tmp,"./img/%s.bmp",ciCore.nam);
    char *v2= tmp;
    char *v[]={v0,v1,v2};
    int do_flg=FProcessSwitches(3,v); // 处理输入命令

    us.nRel=relationshipchart; //合盘类型
    us.fGraphics=fGraphics; //不绘制图片  -- 文本 输出
    us.fAnsiColor=0; // 不输出 彩色 字体 转义
    us.fAnsiChar=0; //ansi 转义输出符号 丢弃
    us.nHouseSystem=nHouseSystem;// 宫位设置

    std::string tmpData;
    if(do_flg){
        Action(); // do
        if(us.fGraphics){
            PrintChart(is.fProgress);
        }
        tmpData=std::move(std::string(is.data));
    }
    memset(is.data,0, sizeof(is.data)/ sizeof(is.data[0]));// reset
    InitVariables(); //reset var
#ifdef USE_DEBUG
    logger->info("astrolog cost time:{} ms \n ;result:{}",(DateUtil::currentTimeMillis()-begin),tmpData);
#endif
    return  tmpData;
}


/**
 * 本命盘计算
 * @param chartInfo
 * @param fGraphics
 * @param nHouseSystem 宫位设置
 * @return
 */
std::string AstrologUtil::noRelationChart(ChartBaseInfo &chartInfo,int fGraphics,int nHouseSystem){

    std::lock_guard<std::mutex>lockGuard(astrolog_mutex);
#ifdef USE_DEBUG
    time_t begin=DateUtil::currentTimeMillis();
#endif
    InitProgram();
    ciTran = ciFour = ciThre = ciTwin = ciCore;
    is.fDst=fTrue;//夏令时自动检查
    is.fSzPersist= fTrue; //处理时参数字符串是否持久？
    is.fHaveInfo=1; // 禁止 pop  user，防止主程序挂起；

    //
    std::vector<std::string> tmpV;
    Strings::split(chartInfo.hours_min,tmpV,":");
    real  hours=std::stod(tmpV[0])+std::stod(tmpV[1])/60.0;
    tmpV.clear();


    //init chart info
    ciCore={
            chartInfo. mon,
            chartInfo. day,
            chartInfo. year,
            hours,
            chartInfo. dst,
            chartInfo.timeZone,
            chartInfo.longitude,
            chartInfo. latitude,
            chartInfo.userName.data(),
            chartInfo. location.data()
    };

    char *v0= const_cast<char *>("Astrolog");
    char *v1= const_cast<char *>("-Xo");
    char tmp[32];
    sprintf(tmp,"./img/%s.bmp",ciCore.nam);
    char *v2= tmp;
    char *v[]={v0,v1,v2};
    int do_flg=FProcessSwitches(3,v); // 处理输入命令


    // 基础参数设置
    us.nRel=None; //计算本命盘
    us.fGraphics=fGraphics; //不绘制图片  -- 文本 输出
    us.fAnsiColor=0; // 不输出 彩色 字体 转义
    us.fAnsiChar=0; //ansi 转义输出符号 丢弃
    us.nHouseSystem=nHouseSystem;// 宫位设置


    std::string tmpData;
    if(do_flg){
        Action(); // do
        if(us.fGraphics){
            PrintChart(is.fProgress);
        }
        tmpData=std::move(std::string(is.data));
    }
    memset(is.data,0, sizeof(is.data)/ sizeof(is.data[0]));// reset
    InitVariables(); //reset var
#ifdef USE_DEBUG
    logger->info("astrolog cost time:{} ms \n ;result:{}",(DateUtil::currentTimeMillis()-begin),tmpData);
#endif
    return  tmpData;
}

#pragma clang diagnostic pop