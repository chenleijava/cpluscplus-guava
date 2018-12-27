#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
//
// Created by chenlei on 2018-12-10.
//
// mutex example
#include <iostream>       // std::cout
#include <thread>         // std::thread

#include <mutex>


std::mutex mtx;           // mutex for critical section
std::recursive_mutex recursiveMutex;//  递归互斥锁---> 统一线程 多次上锁
#include "spdlogger/SpdLogger.h"

using  namespace std;

/**
 * test print
 * @param n
 * @param c
 */
void print_block(int n, char c, bool sleep) {
    std::this_thread::sleep_for(std::chrono::milliseconds(100));

    // critical section (exclusive access to std::cout signaled by locking mtx):
//    mtx.lock();
    std::lock_guard<std::mutex> l(mtx,std::adopt_lock);  //keep lock status!!!
//    recursiveMutex.lock();
    {
        //多线程环境
        if (sleep) {
            SpdLogger logger("sleepLogger");
            logger.getConsole()->info("sleep 3 seconds>>>>>>>");
            std::this_thread::sleep_for(std::chrono::seconds(3));
            logger.getConsole()->info("sleep 3 seconds done!!!!!>>>>>>>");
        }
    }

    for (int i = 0; i < n; ++i) { std::cout << c; }

//    recursiveMutex.unlock();
//    mtx.unlock();

    std::cout << '\n';
}

#include <gtest/gtest.h>

TEST(test_mutex, _mutex) {

    std::thread th1(print_block, 50, '*', false);
    std::thread th2(print_block, 50, '$', true);
    std::thread th3(print_block, 50, '^', false);

    th3.join();
    th1.join();
    th2.join();

    SpdLogger logger("mutexLogger");
    logger.getConsole()->info(">>>>>>>");
}


/**
 * maybe  init
 */
std::once_flag once;
int winID = 0;

/**
 * do
 * @param id
 * @param threadID
 */
void set0(int &id,int &threadID) {
    winID = id;
    SpdLogger logger("winnerLogger");
    logger.getConsole()->info("call once set value:{} threadID:{}",winID,threadID);
}

/**
 * call once ,init stance
 * @param id
 */
void setID(int id,int threadID) {
    //every thread sleep 1 seconds
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    if (winID == 0) {
        std::call_once(once, set0, id,threadID); //only do one
    } else{
        //todo
    }
};


/**
 * call once test
 */
TEST(test_call_once, call_once) {
    int threadNumber=100;
    std::thread threads[threadNumber];
    for (int i = 0; i < threadNumber; ++i)
        threads[i] = std::thread(setID, i + 100,i);
    //start thread
    for (auto &t:threads)
        t.join();
}



//
std::mutex cond_mutex;
std::condition_variable cond;
bool  ready= false;
static SpdLogger _logger("condtionLogger");
int  done= 0;
std::condition_variable wait_cond;
std::mutex wait_mutex;


/**
 *
 * @param threadID
 */
void logThreadID(int threadID){
    {
        unique_lock<std::mutex> lock(cond_mutex);
        _logger.getConsole()->info("hook threadID:{}",threadID);
        while (!ready)cond.wait(lock); //if true ,release lock
        _logger.getConsole()->info("notified , threadID:{}",threadID);


        {
            unique_lock<std::mutex> wait_lock(wait_mutex);
            --done;
            if(done==0){
                _logger.getConsole()->info("notify main thread continue!!!!");
                wait_cond.notify_one();
            }
        }

    }

}


SpdLogger atomicLogger("atomicLogger");
/***
 *
 */
TEST(test_condition,condtion){
    int threadNumber=3;
    std::thread threads[threadNumber];
    for (int i = 0; i < threadNumber; ++i)
    {
        threads[i] = std::thread(logThreadID, i + 100);
        ++done;
    }

    //
    auto go=[](){
        {
            unique_lock<std::mutex> lock(cond_mutex);
            ready= true;
            _logger.getConsole()->info("111");
            cond.notify_all();
            _logger.getConsole()->info("2222");
        }

        {
            unique_lock<std::mutex> wait_lock(wait_mutex);
            if (done!=0){
                _logger.getConsole()->info(" main thread hook ,wait sub thread done!!!!");
                wait_cond.wait(wait_lock);
                _logger.getConsole()->info(" main thread hook continue >>>>!!!!");
            }
        }

    };

    //
    go();

    //
    for(auto &th:threads){
        th.join();
    }


    std::atomic<bool> ok(false);
    if (!ok){
        ok= true;
    }

    atomicLogger.getConsole()->info("atomic value:{}",ok);
}


#include <atomic>


/**
 *
 */
std::atomic<bool> readyGo(false);
std::atomic<int> age;
/**
 * test_and_set() 函数检查 std::atomic_flag 标志，如果 std::atomic_flag 之前没有被设置过，
 * 则设置 std::atomic_flag 的标志，并返回先前该 std::atomic_flag 对象是否被设置过，
 * 如果之前 std::atomic_flag 对象已被设置，则返回 true，否则返回 false。
 */
std::atomic_flag is_set=ATOMIC_FLAG_INIT;
void count1m(int id){
    if(!readyGo)
        this_thread::yield(); //current thread give up exe ,if cond not true!!!
    for (volatile int j=0; j<1000000; ++j) {}
    //before not set ,return false
    if(!is_set.test_and_set()){
        atomicLogger.getConsole()->info("win threadID:{}",id);
    }
}

/**
 * test _thread yeild
 */
TEST(test_thead_yeild,yeild){
    int numThread=4;
    std::thread threads[numThread];
    for (int i = 0; i < numThread; ++i) {
        threads[i] = std::thread(count1m,i);
    }
    readyGo= true;
    age++;

    std::atomic_bool isReady;// equal atomic<bool> isReady
    isReady.store(true);
    atomicLogger.getConsole()->info("atomic_bool value:{}",isReady.load());
    for (auto &t:threads)
        t.join();
}


#pragma clang diagnostic pop