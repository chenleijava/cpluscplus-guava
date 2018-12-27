//
// Created by chenlei on 2018-12-06.
//

#include "gtest/gtest.h"
#include "astrolog/AstrologUtil.h"

#include "util/Logger.hpp"
#include "restbed_service.h"
#include "nlohmann/json.hpp"
using  json=nlohmann::json;

auto test_astrologLogger=Logger::createLogger("test_astrologLogger");

/**
 *
 */
TEST(test_astrolog,astrolog){

    //计算time in hours
    //18:30 -> (t.Hour+t.Minute/60.0)
    char* sz=SzTim(18+30/60.00);
    std::string tmpSz=std::string(sz);
    EXPECT_EQ("6:30pm",Strings::ltrim(tmpSz));
    //SzAltitude

    //test_astrologLogger->info("sztime:{} 经度:{} 维度:{} ",sz,SzAltitude(122.19984),SzAltitude(47.36584));

    //http://product.astro.sina.com.cn/swe/result?r=0&sex=male&geo=China&summer=0&
    // city=CH280101&longitude1=118&longitude2=4&longitude3=E&latitude1=34&latitude2=56&
    // latitude3=N&zone=8&year=2018&month=12&day=19&hour=18&minute=30&name=%E7%9F%B3%E5%A4%B4
    // 解析经度 维度 --  pmLon 118E4  pmLat 34N56
    // extern real RParseSz P((CONST char *, int));
    std::shared_ptr<AstrologUtil> astrologUtil=AstrologUtil::getInstance();
    real lon=astrologUtil->parseLon("118E4");
    real lan=astrologUtil->parseLat("34N56");
    test_astrologLogger->info("测试经度:{} 维度:{}",lon,lan);
    ChartBaseInfo chartBaseInfo={2018,12,20,"18:30",0.0,8.0,lon,lan,"江海韬","guangzhou"};
    astrologUtil->noRelationChart(chartBaseInfo);
}

#include "gzip/compress.hpp"

#pragma clang diagnostic push
#pragma ide diagnostic ignored "readability-container-size-empty"
void astrolog_handle( const std::shared_ptr<restbed::Session > session){
    restbed::Response response;

    //解析星盘个人数据
    auto request=session->get_request();
    int  year=std::stoi(request->get_query_parameter("year"));
    int  mon=std::stoi(request->get_query_parameter("mon"));
    int  day=std::stoi(request->get_query_parameter("day"));
    std::string hoursMin=request->get_query_parameter("hoursMin");
    double  dst=std::stod(request->get_query_parameter("dst"));
    double  timeZone=std::stod(request->get_query_parameter("timeZone"));

    std::shared_ptr<AstrologUtil> astrologUtil=AstrologUtil::getInstance();

    real lon=astrologUtil->parseLon(request->get_query_parameter("longitude"));
    real lan=astrologUtil->parseLat(request->get_query_parameter("latitude"));
    std::string userName=request->get_query_parameter("userName");
    std::string location=request->get_query_parameter("location");
    int  relationShipChart=std::stoi(request->get_query_parameter("rsc")); //


    //check
    if(hoursMin==""||userName==""||location==""||!(relationShipChart==-1||(relationShipChart>=0&&relationShipChart<=3))){
        session->close(restbed::OK,"parameter error");
        return;
    }
    ChartBaseInfo chartBaseInfo={year,mon,day,hoursMin,dst,timeZone,lon,lan,userName,location};


    std::string tmpData;
    if(relationShipChart==None){
        tmpData=astrologUtil->noRelationChart(chartBaseInfo);
    } else{
        year=std::stoi(request->get_query_parameter("year0"));
        mon=std::stoi(request->get_query_parameter("mon0"));
        day=std::stoi(request->get_query_parameter("day0"));
        hoursMin=request->get_query_parameter("hoursMin0");
        dst=std::stod(request->get_query_parameter("dst0"));
        timeZone=std::stod(request->get_query_parameter("timeZone0"));
        lon=astrologUtil->parseLon(request->get_query_parameter("longitude0"));
        lan=astrologUtil->parseLat(request->get_query_parameter("latitude0"));
        userName=request->get_query_parameter("userName0");
        location=request->get_query_parameter("location0");
        //check
        if(hoursMin==""||userName==""||location==""||!(relationShipChart==-1||(relationShipChart>=0&&relationShipChart<=3))){
            session->close(restbed::OK,"parameter error");
            return;
        }
        ChartBaseInfo chartBaseInfo_={year,mon,day,hoursMin,dst,timeZone,lon,lan,userName,location};
        tmpData=astrologUtil->relationChart(chartBaseInfo,chartBaseInfo_,relationShipChart);
    }

    json j={
            {"星盘结果","\n"+tmpData}
    };
    tmpData=j.dump();
    tmpData=gzip::compress(tmpData.data(),tmpData.size());
    response.set_body(tmpData);
    response.set_status_code(200);
    response.set_header("Content-length",::to_string(tmpData.size()));
    response.set_header("Content-Encoding","gzip");
    session->close(response);
}
#pragma clang diagnostic pop

//test astrolog
TEST(test_astrolog_web,astrolog_web){
    RestBedService restBedService("astrologger");
    std::shared_ptr<restbed::Resource> resource=std::make_shared<restbed::Resource>();
    resource->set_path("/astrolog");
    resource->set_method_handler("GET",astrolog_handle);
    restBedService.start(8080,resource);
}