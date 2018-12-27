//
// Created by chenlei on 2018-12-17.
//

#ifndef CPLUSPLUSGUAVA_CPPREDISCLIENT_H
#define CPLUSPLUSGUAVA_CPPREDISCLIENT_H

#include <future>
#include <stdexcept>
#include <cpp_redis/cpp_redis>
#include <util/Logger.hpp>
#include <chrono>
#include <atomic>
#include <functional>

using namespace std;

/**
 * redis client
 */
class CppRedis{

private:
    /**
     * logger
     */
    std::shared_ptr<spdlog::logger> logger;
    /**
     * redis client
     */
    std::shared_ptr<cpp_redis::client> client;
public:

    /**
    * init redis client
    * @param host  redis host
    * @param port  redis port
    * @param sub  if true ,add sub and  publish
    */
    void init(string host,std::size_t port){
        logger=Logger::createLogger("cppRedisLogger");
        client=std::make_shared<cpp_redis::client>();
        do_connect(std::move(host),port);
    }

    /***
     *
     * @return
     */
    const shared_ptr<cpp_redis::client> &getClient() const {
        return client;
    }

private:
    /**
                //! high availability (re)connection states
                //!  * dropped: connection has dropped 0
                //!  * start: attemp of connection has started 1
                //!  * sleeping: sleep between two attemps 2
                //!  * ok: connected 3
                //!  * failed: failed to connect 4
                //!  * lookup failed: failed to retrieve master sentinel 5
                //!  * stopped: stop to try to reconnect 6
                //!
     * @param host
     * @param port
     */
    void do_connect(const  string &host,std::size_t port) {
        logger->info("begin connect host:{} port:{} redis server.",host,port);
        while (1){//first connect >>>>
            if(client->is_connected()){
             //   logger->info("..............................");
                break;
            }
            try {
                client->connect(host, port, [&](const std::string &host, std::size_t port,
                                                cpp_redis::client::connect_state status) {
                    if (status == cpp_redis::client::connect_state::dropped) {
                        logger->info("connect dis connect ,stop to try to reconnect");
                    }
                    if (status == cpp_redis::client::connect_state::ok) {
                        logger->info("connect host:{} port:{} redis server successful .",host,port);
                    }
                    if (status == cpp_redis::client::connect_state::start) {
                        logger->info("attemp of connection has started");
                    }

                    if (status == cpp_redis::client::connect_state::sleeping) {
                        logger->info("sleep between two attemps ");
                    }
                    if (status == cpp_redis::client::connect_state::failed) {
                        logger->info("failed connecting>>>>> ");
                        logger->info("..............................");
                    }
                },0,-1,1000); //  try to endless! interval 1 seonds
            } catch (std::exception &e) {
                logger->info("connect error:{} ,sleep {} seconds ,then retry", e.what(),1);
                std::this_thread::sleep_for(std::chrono::milliseconds( 1000));//sleep 100ms,retry
            }
        }
    }
};
#endif //CPLUSPLUSGUAVA_CPPREDISCLIENT_H
