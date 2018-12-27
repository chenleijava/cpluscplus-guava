//
// Created by chenlei on 2018-12-14.
//

#include <gtest/gtest.h>
#include <future>
#include <util/Logger.hpp>
#include <stdexcept>
#include <util/SingleInstance.hpp>
#include <redis/CppRedis.h>
#include <redis/CppReidsPubSub.h>

#include <scheduler/Scheduler.h>
using namespace Bosma;
//
///**
// *
// */
//TEST(test_cpp_redis,cpp_redis){
//    std::promise<bool> p;
//    auto logger=Logger::createLogger("cpp_redis_logger");
//
//    auto instance=SingleInstance<CppRedis>::getInstance();
//    instance->init("127.0.0.1",6379);
//    auto client=instance->getClient();
//
//
//    // same as client->send({ "SET", "hello", "42" }, ...)
//    client->set("hello", "42", [](cpp_redis::reply& reply) {
//        std::cout << "set hello 42: " << reply << std::endl;
////         if (reply.is_string())
////         {
////             auto tmp=reply.as_string();
////         }
//    });
//
//    // same as client->send({ "DECRBY", "hello", 12 }, ...)
//    client->decrby("hello", 12, [](cpp_redis::reply& reply) {
//        std::cout << "decrby hello 12: " << reply << std::endl;
//        // if (reply.is_integer())
//        //   do_something_with_integer(reply.as_integer())
//    });
//
//    // same as client->send({ "GET", "hello" }, ...)
//    client->get("hello", [](cpp_redis::reply& reply) {
//        std::cout << "get hello: " << reply << std::endl;
//        // if (reply.is_string())
//        //   do_something_with_string(reply.as_string())
//    });
//
//
//    // commands are pipelined and only sent when client->commit() is called
//    // client->commit();
//
//
//    // synchronous commit, no timeout
//    client->sync_commit();
//
//    // synchronous commit, timeout
//    // client->sync_commit(std::chrono::milliseconds(100));
//
//    p.get_future().get();
//
//}
//
//
///**
// * 测试基于cpp_redis 的订阅发布
// */
//TEST(test_pub_sub,pub_sub){
//    std::promise<bool > _p;
//   auto f= _p.get_future();
//    std::string host="127.0.0.1";
//    size_t  port=6379;
//    auto instance=SingleInstance<CppRedis>::getInstance();
//    instance->init(host,port);
//    auto redisClient=instance->getClient();
//    auto pubSub=SingleInstance<CppReidsPubSub>::getInstance("x2cache",redisClient,"user_region");
//    pubSub->subScribe(host,port, false);
//    Scheduler s(1);
//    s.every(1s,[&](){
//        pubSub->sendEvictCmd("user_region","cpp_redis_key");
//    });
//    f.get();
//}
