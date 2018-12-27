
//
// Created by chenlei on 2018-12-11.
//

#include <gtest/gtest.h>
#include "util/SingleInstance.hpp"
#include "spdlogger/SpdLogger.h"

#include <iostream>

class One{
private:
    std::string name;
    int age;
public:
    /**
     * 只对右值引用才能调用转移构造函数和转移赋值函数
     * std::move ----  将左值引用转换为右值引用
     * @param _name  , here move _name tp object member name
     * @param age
     */
    One(string _name, int age) : name(std::move(_name)), age(age) {}

    /**
     *
     * @return
     */
    const string &getName() const {
        return name;
    }

    int getAge() const {
        return age;
    }


    /**
     * 左值引用
     * @param i
     */
    void process_value(int& i) {
        std::cout << "LValue processed: " << i << std::endl;
    }

    /***
     * 右值引用 消除两个对象交互时不必要的对象拷贝，节省运算存储资源，提高效率。
     * @param i
     */
    void process_value(int&& i) {
        std::cout << "RValue processed: " << i << std::endl;
    }



    /***
     *
     * @param i
     */
    void forward_value(int &&i){
        auto j=std::forward<int>(i);
        std::cout << "RValue processed: " << i << std::endl;
        process_value(j);// change left value ref ,  传递给另一个函数时 右值引用 变成了左值引用
    }
};

/**
 *
 */
TEST(test_single,single){
    std::string name="石头哥哥~~~@@@###";
    int age=19;
    auto singleOne=SingleInstance<One>::getInstance(name,age);

    singleOne->process_value(age);
    singleOne->process_value(20);
    singleOne->forward_value(21);

    auto logger=SingleInstance<SpdLogger>::getInstance("singleTestLogger");
    logger->getConsole()->info("name:{} age:{}",singleOne->getName(),singleOne->getAge());
    SingleInstance<One>::desInstance();
    SingleInstance<SpdLogger>::desInstance();
}