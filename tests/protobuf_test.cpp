#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by chenlei on 2018/11/10.
//

#include <spdlog/sinks/stdout_color_sinks.h>
#include "gtest/gtest.h"
#include "pb/Sdk2TrackingMqApi.pb.h"
#include <mutex>
using namespace std;
mutex l;

#include <iostream>

TEST(test_protobuf, protbuf) {

    spdlog::set_level(spdlog::level::debug);
    auto console = spdlog::stdout_color_mt("protobuf_info");

    pb::AdInfo adInfo;
    adInfo.set_adspacename("测试广告位");
    adInfo.set_appname("小宝贝APP");

    //serialize data
    std::string data;
    adInfo.SerializeToString(&data);

    size_t size = adInfo.ByteSizeLong();
    char *otherData = new char[size]; // 指针 ，存储地址的变量
    //required filed must be set
    adInfo.SerializeToArray(otherData, static_cast<int>(size));
    std::string tmp(otherData);
    console->info(">>>>>>>>>> {0}", tmp);

    //
    printf("printf data :%s\n", otherData);
    delete[] otherData;

    auto debugInfo = adInfo.Utf8DebugString(); //
    console->debug("test data:{0} debug info: {1}", data, debugInfo);

    printf("c_str test:%s\n", data.c_str());

    //reset object filed
    adInfo.Clear();
    adInfo.ParseFromString(data);

    printf("appName:%s\n", adInfo.appname().c_str());
    goto done;


    {
        std::lock_guard<std::mutex> lock_guard(l);
        google::protobuf::ShutdownProtobufLibrary();
    }
done:
    console->debug(">>>>>>>>>>done!!!!");
}

#pragma clang diagnostic pop