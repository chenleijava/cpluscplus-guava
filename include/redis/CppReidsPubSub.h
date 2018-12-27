//
// Created by chenlei on 2018-12-17.
//

#ifndef CPLUSPLUSGUAVA_CPPREIDSPUBSUB_H
#define CPLUSPLUSGUAVA_CPPREIDSPUBSUB_H

#include <string>
#include <CppRedis.h>
#include <thread>
#include <nlohmann/json.hpp>
#include <vector>
using namespace std;
using json=nlohmann::json ;

/**
 *  基于j2cache 封装
 */
enum  class PuSubAction{
    OptJoin     =  1, // 加入集群
    OptEvictKey   ,         // 删除集群
    OptClearKey    ,        // 清理缓存
    OptQuit         ,       // 退出集群环境
};


/**
 * 基于cpp_redis  订阅发布
 */
class CppReidsPubSub{

private:
    /**
     * 发布对应的频道
     */
    std::string channel;

    /**
     * redis 操作客户端
     */
    std::shared_ptr<cpp_redis::client> client;

    /**
     * redis 数据区域
     */
    std::string region;

    /**
     * cpp redis subscriber
     */
    cpp_redis::subscriber subscriber;

    /**
     *
     */
    std::shared_ptr<spdlog::logger> logger;

public:
    /**
     *
     * @param channel
     * @param client
     * @param region
     */
    CppReidsPubSub( string channel,  shared_ptr<cpp_redis::client> &client,  string region) : channel(
            std::move(channel)), client(client), region(std::move(region)),logger(Logger::createLogger("cppRedisPubSubLogger")) {}

public:

    /**
     * send clear cmd
     * @tparam Args  keys ... std::string
     * @param region  redis cache region
     * @param key   clear
     */
    void sendEvictCmd(std::string region,std::string key){
        json d={
                {"region",std::move(region)},
                {"keys",{std::move(key),}},
                {"operator",PuSubAction::OptClearKey},
        };
        std::string msg=d.dump();
        client->publish(this->channel,msg);
        client->commit(); // don't forget!
    }

    /**
     * subscriber init
     * @param host
     * @param port
     */
    void subScribe(std::string &host,size_t port, bool detach){
        //connect >>>>>>>>>>>
        subscriber.connect(host,port,[&](const std::string& host,
                std::size_t port,
                cpp_redis::subscriber::connect_state status){
                        /*if (status == cpp_redis::subscriber::connect_state::dropped) {
                            logger->info("connect dis connect ,stop to try to reconnect");
                        }
                        if (status == cpp_redis::subscriber::connect_state::ok) {
                            logger->info("connect host:{} port:{} redis server successful .",host,port);
                        }
                        if (status == cpp_redis::subscriber::connect_state::start) {
                            logger->info("attemp of connection has started");
                        }
                        if (status == cpp_redis::subscriber::connect_state::sleeping) {
                            logger->info("sleep between two attemps ");
                        }
                        if (status == cpp_redis::subscriber::connect_state::failed) {
                            logger->info("failed connecting>>>>> ");
                            logger->info("..............................");
                        }*/
            },0,-1,1000); //auto reconnnet

            // do  subscribe
            std::thread subThread(
                    [&,this](){
                        subscriber.subscribe(this->channel,
                                             [&](const std::string& chan, const std::string& msg) {
                                               json data=json::parse(msg);
                                               bool  obj=data.is_object();
                                              auto operatorValue= data.at("operator").get<int>();
                                              if(operatorValue==int(PuSubAction::OptEvictKey)){
                                                  auto region=data["region"].get<std::string>();
                                                  auto keys= data.at("keys").get<std::vector<std::string>>();//first
                                                  logger->info("evict key :{} region:{}",keys[0],region);
                                                  //todo clear memory cache
                                              } else  if(operatorValue==int(PuSubAction::OptJoin)){
                                                  logger->info("node-{} join >>",data.at("src").get<int>());
                                              } else  if(operatorValue==int(PuSubAction::OptQuit)){
                                                  logger->info("node-{} quit >>",data.at("src").get<int>());
                                              }
                                             });
                        subscriber.commit();
            });
            if(detach){
                subThread.detach();
            } else{
                subThread.join();
            }
    }
};


#endif //CPLUSPLUSGUAVA_CPPREIDSPUBSUB_H
