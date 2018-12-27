//
// Created by chenlei on 2018-12-10.
//

#include <gtest/gtest.h>
#include <spdlogger/SpdLogger.h>
#include <future>
#include <functional>
#include <thread>
#include <util/SingleInstance.hpp>


/**
 *
 */
auto  futureLogger=SingleInstance<SpdLogger>::getInstance("futureLogger");
/**
 *
 * @param p
 */
void println_value(std::future<int> &f,int threadID){
    futureLogger->getConsole()->info("future 阻塞当前线程,theadID:{} ,wait until get value",threadID);
    int x= f.get(); //block current thread-- new thread
    futureLogger->getConsole()->info("get promise data:{}",x);
    //done
    SingleInstance<SpdLogger>::desInstance();
}


/**
 * test promise
 */
TEST(test_promise,promise){
    std::promise<int> _promise;
    std::future<int> f=_promise.get_future();
    std::thread tt(println_value,std::ref(f),100); // pass std::ref
    futureLogger->getConsole()->info("main thread sleep 5 seconds");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    futureLogger->getConsole()->info("main thread promise set value");
    _promise.set_value(12);
    tt.detach();
}


/**
 * @param a
 * @param b
 * @return
 */
int package_task_show(int &&a,int &&b){
    futureLogger->getConsole()->info("a:{},b:{}",a,b);
    futureLogger->getConsole()->info("current thread sleep 3 seconds!");
    std::this_thread::sleep_for(std::chrono::seconds(3));
    return 4; // return something
}

//
TEST(test_package_task,task){

    //template <class Ret, class... Args> class packaged_task<Ret(Args...)>;
    std::packaged_task<int(int&&,int&&)> task([](int &&a,int &&b)->int {
        futureLogger->getConsole()->info("a:{},b:{}",a,b);
        futureLogger->getConsole()->info("current thread sleep 3 seconds!");
        std::this_thread::sleep_for(std::chrono::seconds(3));
        return 4; // return something
    });

    //get future
    auto ret=task.get_future();


    //decode message
    // thread pass a task ?
    std::thread t(std::move(task),10,12);  //move
    t.detach();


    //handle result
    std::thread handle([&](){
        futureLogger->getConsole()->info("block !!!!!");
        int value=ret.get();//block current thread,util some done!
        futureLogger->getConsole()->info("last get value:{}",value);
//        futureLogger->show();
    });
    handle.join();
}


