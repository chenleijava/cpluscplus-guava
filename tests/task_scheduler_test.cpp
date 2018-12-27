//
// Created by chenlei on 2018-12-14.
//
#include <util/Logger.hpp>
#include <gtest/gtest.h>
#include <thread>
#include <future>

#include <scheduler/Scheduler.h>
using namespace Bosma;


/**
 *
 * @param msg
 * @param logger
 */
void message(std::string &&msg,shared_ptr<spdlog::logger> &logger){
    logger->info("{}",msg);
}

/**
 *
 */
TEST(test_scheduler, scheduler) {

    auto logger = Logger::createLogger("test_scheduler_logger");

    std::promise<bool> _p;
    std::future<bool> f=_p.get_future();
    // number of tasks that can run simultaneously
    // Note: not the number of tasks that can be added,
    //       but number of tasks that can be run in parallel
    unsigned int max_n_threads = 1;
    // Make a new scheduling object.
    // Note: s cannot be moved or copied
    Bosma::Scheduler s(max_n_threads);

    // every second call message("every second")
    s.every(1s, message, "every second",logger);

    // in one minute
    s.in(1min, [&]() {
        logger->info("in one minute");
    });

    // in one second run lambda, then wait a second, run lambda, and so on
    // different from every in that multiple instances of the function will not be run concurrently
    s.interval(3s, [&]() {
      logger->info("interval 3 seconds");
    });



//    s.every(1min, []() { std::cout << "every minute" << std::endl; });
//
//
//    // https://en.wikipedia.org/wiki/Cron
//    s.cron("* * * * *", []() { std::cout << "top of every minute" << std::endl; });
//
//    // Time formats supported:
//    // %Y/%m/%d %H:%M:%S, %Y-%m-%d %H:%M:%S, %H:%M:%S
//    // With only a time given, it will run tomorrow if that time has already passed.
//    // But with a date given, it will run immediately if that time has already passed.
//    s.at("2017-04-19 12:31:15", []() { std::cout << "at a specific time." << std::endl; });
    //s.cron("5 0 * * *", []() { std::cout << "every day 5 minutes after midnight" << std::endl; });
//

/***
 *
  ┌───────────── minute (0 - 59)
# │ ┌───────────── hour (0 - 23)
# │ │ ┌───────────── day of the month (1 - 31)
# │ │ │ ┌───────────── month (1 - 12)
# │ │ │ │ ┌───────────── day of the week (0 - 6) (Sunday to Saturday;
# │ │ │ │ │                                   7 is also Sunday on some systems)
# │ │ │ │ │
# │ │ │ │ │
# * * * * * command to execute
 *
 */

    f.get();//block current thread
}
