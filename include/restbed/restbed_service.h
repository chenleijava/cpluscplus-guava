//
// Created by chenlei on 2018-12-19.
//

#ifndef CPLUSPLUSGUAVA_RESTBED_SERVICE_H
#define CPLUSPLUSGUAVA_RESTBED_SERVICE_H

#include <restbed>
#include <memory>
#include <cstdlib>
#include <restbed>
#include <csignal>
#include <sys/types.h>
#include <unistd.h>
#include <util/Logger.hpp>
#include <functional>

using namespace std;

/**
 *
 */
class RestBedService{

public:
    /**
     *
     * @param loggerName
     */
    RestBedService(std::string loggerName):restbedLogger(logger::createLogger(std::move(loggerName))){

    }
    /**
     *
     * @param port
     * @param resource
     */
    void start(uint16_t port,const std::shared_ptr<restbed::Resource> &resource){
        auto settings = make_shared<restbed::Settings>();
        settings->set_port(port);
        settings->set_default_headers( {
                                               {"Connection", "close"},
                                               {"Content-Type","application/json;charset=UTF-8"},
                                       } );
        settings->set_worker_limit(std::thread::hardware_concurrency()*2); //default is 0
        settings->set_connection_limit(INT_MAX); //default is 128
        settings->set_connection_timeout(std::chrono::milliseconds(5*1000)); //default is 5000ms


        restbedLogger->info("restbed  work_limit:{},connect_limit:{} connect_time_out:{} ms",
                            settings->get_worker_limit(),settings->get_connection_limit(),
                            settings->get_connection_timeout().count());

        //start rest service
        service=std::make_shared<restbed::Service>();
        service->publish(resource);
        //ervice.add_rule(std::make_shared<LogRule>());
        //service.set_authentication_handler(authentication_handler);
//        service->set_error_handler([&](const int, const exception& e, const shared_ptr< restbed::Session > session){
//          //error
//            restbedLogger->info("exception:{}",e);
//        });
        restbedLogger->info("restbed service started service pid:{} ,listen to port:{}",getpid(),port);
        service->start( settings );
    }
private:

    /**
     * restbed logger
     */
     std::shared_ptr<spdlog::logger> restbedLogger;

    /**
     * restbed service
     */
    std::shared_ptr<restbed::Service> service;

};

#endif //CPLUSPLUSGUAVA_RESTBED_SERVICE_H
