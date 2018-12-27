#include <utility>

//
// Created by chenlei on 2018-12-18.
//

#ifndef CPLUSPLUSGUAVA_RESTBED_LOGGER_H
#define CPLUSPLUSGUAVA_RESTBED_LOGGER_H

#include <restbed/restbed>
#include <util/Logger.hpp>
#include "thread_pool/thread_pool.hpp"
#include <memory>
#include <nlohmann/json.hpp>
#include <util/DateUtil.hpp>
#include <stdio.h>
using  namespace std;
using  json=nlohmann::json ;


/**
 * 基于splog ，restbed web 服务的日志记录
 */
class RestBedLogger{
public:
    /**
     *
     * @param thread_pool_ptr
     */
    RestBedLogger(shared_ptr<tp::ThreadPool> thread_pool_ptr) :
    thread_pool_ptr(std::move(thread_pool_ptr)),logger(logger::createLogger("webInfoLogger")) {}

    /**
     *
     */
    RestBedLogger(): thread_pool_ptr(std::make_shared<tp::ThreadPool >()), logger(logger::createLogger("webInfoLogger")) {}
public:
    /**
     * 日志分发器
     * @param request
     * @param response
     */
    void webInfoLogger(const std::shared_ptr< const restbed::Session > &session,
                         restbed::Response &response){

        //解析上行 ，下行数据
        auto request=session->get_request();
        std::string path= request->get_path();
        std::string method =request->get_method();
        std::multimap< std::string, std::string >queryStringMap=request->get_query_parameters();
        auto size=queryStringMap.size();
        std::string queryString;
        for (const auto &entry:queryStringMap){
            queryString+=entry.first+"="+entry.second;
            --size;
            if(size!=0){
                queryString+="&";
            }
        }
        std::string userAgent=request->get_header("User-Agent");
        std::string clientIp=getClientIp(session);
        int status=response.get_status_code();
        ::string status_message=response.get_status_message();
        restbed::Bytes bytes=response.get_body();
        std::string responseData=::string(bytes.begin(),bytes.end());


        //序列化json字符串
        json j={
                {"path",path},
                {"method",method},
                {"query_string",queryString},
                {"user_agent",userAgent},
                {"client_ip",clientIp},
                {"status",status},
                {"status_message",status_message},
                {"response_data",responseData},
                {"date",DateUtil::timeStampMilliSeconds2DateTimeStamp(DateUtil::currentTimeMillis())},
        };

        const  std::string data=j.dump();
        //show logger or record  into log files
        //lambad 不能够捕获const的引用
        thread_pool_ptr->post([=](){
            this->logger->info("{}",data);
            //todo log to file!!!
        });
    }



    /**
     *
     * @param session  restbed session
     * @return
     */
    std::string getClientIp(const std::shared_ptr< const restbed::Session > &session){
        auto request=session->get_request();
        ::string clientIp=request->get_header("X-Forwarded-For");
        if(!clientIp.empty()){
            return clientIp;
        }
        clientIp=request->get_header("X-Real-Ip");
        if(!clientIp.empty()){
            return clientIp;
        }
        clientIp=request->get_header("X-Appengine-Remote-Addr");
        if(!clientIp.empty()){
            return clientIp;
        }
        return session->get_origin();
    }

private:
    /**
     * thread pool
     * default is core size, queue eq 1024u
     */
    std::shared_ptr<tp::ThreadPool> thread_pool_ptr;

    /**
     * logger
     */
    std::shared_ptr<spdlog::logger> logger;
};
#endif //CPLUSPLUSGUAVA_RESTBED_LOGGER_H
