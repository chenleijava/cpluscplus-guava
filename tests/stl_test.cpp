//
// Created by chenlei on 2018/11/11.
//

#include "gtest/gtest.h"


#include <thread>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <boost/thread.hpp>
#include <mutex>
std::mutex _lock;
using namespace std;

/**
 * get thread id
 * @return
 */
uint64_t get_thread_id() {
    static_assert(sizeof(std::thread::id) == sizeof(uint64_t),
                  "this function only works if size of "
                  "thead::id is equal to the size of uint_64");
    auto id = std::this_thread::get_id();
    uint64_t *ptr = (uint64_t *) &id;
    return (*ptr);
}


auto consoleLogger =spdlog::stdout_color_st("console");

/**
 * @tparam T
 * @param array
 * @return
 */
template<typename T>size_t getArrayLen(T &array) {return sizeof(array) / sizeof(array[0]);}

/**
 * Swap value
 * @tparam T
 * @param a
 * @param b
 */
template<typename T> void Swap(T &a,T&b){
    T tmp(std::move(a)); // a to tmp
    a=std::move(b);  // b to a
    b=std::move(tmp);  // tmp to  b
}



//lambda function
auto add = []() -> int { return 1; };
/**
 * 测试pointer
 */
TEST(test_pointer, pointer) {
    EXPECT_EQ(1, add()); //
    spdlog::set_level(spdlog::level::debug);
    auto logger = spdlog::stdout_color_st("pointerLogger");
    float mynumber;
    const double pi = 3.1415926;
    extern int error_number;
    const char *name = "blue";// char *类型的指针，指针指向的类型是 char
    const char *season[] = {"spring", "summer", "fall", "winter"};
    // 遍历数组
    for (auto &v:season) {
        logger->info("season:{}", v);
    }
    auto len=getArrayLen(season);
    for (auto j = 0; j < len; ++j) { //
        logger->info("2 season:{}", *(season + j));
    }

    int a=10,b=20;
    Swap<int>(a,b);
    EXPECT_TRUE(a==20&&b==10);

}


TEST(test_vector, verctor) {
    //
    std::vector<int> v{2, 3, 5, 7};
    v.emplace_back(1);
    v.emplace_back(2);
    v.emplace_back(3);
    for (int i = 0; i < v.size(); ++i) {
        printf("for:%d\n", v[1]);
    }
    for (auto item = v.begin(); item != v.end(); ++item) {
        printf("data:%d\n", *item);
    }

    try {
        v.at(19);
    } catch (std::exception &e) {
        spdlog::stderr_color_mt("testVectorLogger")->error("error {}", e.what());
    }

    //del second data
    v.erase(v.begin() + 1);
}


/**
 * test json
 */

//迭代器 ，像指针一样的去访问
#include "nlohmann/json.hpp"

//basic_json 的别名 为json
typedef nlohmann::json json;
using WORD=unsigned int;

TEST(test_json, json) {
    //json
    //https://blog.csdn.net/fengxinlinux/article/details/71037244
    json object = {{"one", 1},
                   {"two", 2}};
    json null;
    // print values
    std::cout << object << '\n';
    std::cout << null << '\n';

    WORD age = 10;

    // add values
    auto res1 = object.emplace("three", 3);
    null.emplace("A", "a");
    null.emplace("B", "b");

    // the following call will not add an object, because there is already
    // a value stored at key "B"
    auto res2 = null.emplace("B", "c");

    // print values
    std::cout << object << '\n';
    std::cout << *res1.first << " " << std::boolalpha << res1.second << '\n';

    std::cout << null << '\n';
    std::cout << *res2.first << " " << std::boolalpha << res2.second << '\n';
}


TEST(test_map, map) {
    //map
    std::map<string, int> m1; //<>里的第一个参数表示key的类型,第二个参数表示value的类型
    m1["Kobe"] = 100;
    m1["James"] = 99;
    m1["Curry"] = 98;
    cout << m1["Kobe"] << endl;
    cout << m1["James"] << endl;

    {
        _lock.lock();
        //insert data
        m1.insert(make_pair<string, int>("key", 9999));
        auto value = m1["key"];
        printf("%d\n", value);
        m1.erase("key");
        if (!m1.empty()) {
            cout << "not empty!!!\n";
            //inter all data
            for (auto &item:m1) {
                cout << "key:" << item.first << " value:" << item.second << endl;
            }
            // for c++17, struct  binding
            for (auto &[k, v]:m1) {
                cout << "key:" << k << " value:" << v << endl;
            }
        }
        m1.clear();
        _lock.unlock();

    }


}

/**
 *
 */
TEST(test_thread, thread) {
    spdlog::set_level(spdlog::level::debug);
    auto logger = spdlog::stdout_color_st("testThread");
    //thread
    thread t([&]() {
        //sleep 3 seconds
        logger->debug("sleep 3 seconds>>>>");
        this_thread::sleep_for(std::chrono::seconds(3));
        logger->debug("sleep done>>>>");
        auto id = get_thread_id();
        logger->debug("thread id:{}", id);

        //boost sleep
        logger->info("boost sleep");
        boost::this_thread::sleep(boost::posix_time::seconds(3));
        logger->info("boost sleep done>>>>>");
    });

    logger->debug("block current thread>>>>");
    t.join();//block current thread
}


/**
 *
 * @param a
 * @param b
 * @return
 */
int addFunc(int a, int b) {
    return a + b;
}

//function pointer
//typedef int (*PtrAddFunc)(int, int);
//c++11, 14, 17
using PtrAddFunc=int (*)(int, int);
PtrAddFunc p = &addFunc;

/**
 *
 * @param ptrAddFunc  func ptr
 * @param a
 * @param b
 * @return
 */
int ptrFunc(PtrAddFunc ptrAddFunc, int a, int b) {
    consoleLogger->info("params:{},{}", a, b);
    return (*ptrAddFunc)(a, b); //decode ref
}


/**
 * 函数指针 测试
 */
TEST(test_ptrFunc, ptrFunc) {
    auto value = (*p)(10, 10);
    auto value2 = ptrFunc(&addFunc, 10, 10);
    EXPECT_EQ(20, value);
    spdlog::stdout_color_st("ptr_func_logger")->info("value:{} value2:{}", value,value2);
}




