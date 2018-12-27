//
// Created by chenlei on 2018-12-07.
//

#ifndef CPLUSPLUSGUAVA_STATCK_H
#define CPLUSPLUSGUAVA_STATCK_H

#include <vector>
#include <mutex>
using namespace std;

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/**
 *
 * @tparam T
 */
template <class  T> class Stack {
public:
    explicit Stack(string loggerName);
    virtual ~Stack();
    bool  isEmpty();
    void  push(T &v);
    void  push(T&& v);
    T pop();
    int size();

public:
      shared_ptr<spdlog::logger> logger;
private:
    int index=0;
    T * ptr;
    mutex mutex_;
    int max=100;
};



#endif //CPLUSPLUSGUAVA_STATCK_H
