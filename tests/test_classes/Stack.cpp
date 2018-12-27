//
// Created by chenlei on 2018-12-07.
//

#include "Stack.h"
#include "util/Base64.h"


template<class T>
Stack<T>::~Stack() {
    logger->info("stack obj destor!"); //当前对象成员已经销毁
    delete[] ptr;
}

template<class T>
bool Stack<T>::isEmpty() {
    lock_guard<mutex> lock(mutex_);
    return this->index==0;
}


template<class T>
void Stack<T>::push(T&v) {
    lock_guard<mutex> lock(mutex_);
    ptr[index++]=v;
}


template<class T>
void Stack<T>::push(T&&v) {
    lock_guard<mutex> lock(mutex_);
    ptr[index++]=v;
}


/***
 *
 * @tparam T
 * @return
 */
template<class T>
T Stack<T>::pop() {
    lock_guard<mutex> lock(mutex_);
    index--;
    T t=ptr[index];
    return t;
}


/**
 *
 * @tparam T
 * @return
 */
template<class T>
int Stack<T>::size() {
    lock_guard<mutex> lock(mutex_);
    return index;
}

/***
 * build stack with logger name
 * @tparam T
 * @param loggerName
 */
template<class T>
Stack<T>::Stack(string loggerName) {
    logger=spdlog::stdout_color_st(loggerName);
    ptr=new T[max];
}

#include <gtest/gtest.h>
#include <stdio.h>

TEST(test_stack,stack){

    {
        Stack<string> tmpStack("stringLogger");
        tmpStack.push("测试1");
        tmpStack.push("测试2");
        tmpStack.push("测试3");
        tmpStack.push("测试4");
        auto len=tmpStack.size();
        if(!tmpStack.isEmpty()){
            for (int i = 0; i !=len ; ++i) {
                tmpStack.logger->info("stack current size:{} value:{}",tmpStack.size(),tmpStack.pop());
            }
        }
    }


    {
        Stack<int> tmpStack("intLogger");
        tmpStack.push(12);
        int j=100;
        tmpStack.push(j);
        tmpStack.push(198);

        int size=tmpStack.size();
        for (int k = 0; k < size; ++k) {
            tmpStack.logger->info("stack number:{}",tmpStack.pop());
        }
    }

    {
        //base64 test
        auto encodeData=macaron::Base64::Encode("123");
        Stack<int> tmp("base64Logger");
        tmp.logger->info("base64 data:{}",encodeData);
        EXPECT_TRUE("MTIz"==encodeData);
        string out;
        macaron::Base64::Decode(encodeData,out);
        EXPECT_TRUE("123"==out);
    }


}




