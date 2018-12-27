//
// Created by chenlei on 2018-12-07.
//

// derived classes
#include <iostream>

using namespace std;

/**
 *
 */
class CPolygon {
protected:
    int width, height;
public:
    void set_values(int a, int b) {
        width = a;
        height = b;
    }

    /**
     * 纯虚函数
     */
    virtual int area(){
        return  0;
    };

    /**
     *
     */
    virtual int areaTwo()=0;
};

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

/**
 *
 */
class CRectangle : public CPolygon {
public:
    /**
     *
     * @return
     */
    int area() override {
        return (width * height);
    }
    /**
     *  init base class
     */
    CRectangle() : CPolygon() {
        this->logger=spdlog::stdout_color_st("CRectangleLogger");
    }

    int areaTwo() override {
        logger->info("this is CRectangle method call!!!");
        return 0;
    }
private:
    shared_ptr<spdlog::logger> logger;
};

/**
 *
 */
class CTriangle : public CPolygon {
public:
    /**
     *
     * @return
     */
    int area() override { return (width * height / 2); }

    /**
     *
     * @return
     */
    int areaTwo() override {

        return 0;
    }
};


#include <gtest/gtest.h>
#include <thread>

using namespace std;

/**
 *
 */
TEST(test_extend, extend) {
    thread t([]() {

    });
    t.detach();

    CRectangle rect;
    CPolygon*  optr=&rect;
    rect.set_values(4, 5);

    //指针-> 实际调用 CRectangle 函数，多态
    optr->areaTwo();


    rect.area();
    CTriangle trgl;
    trgl.set_values(4, 5);
    trgl.area();
}
