#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-err58-cpp"
#include <memory>

//
// Created by chenlei on 2018-12-11.
//

#include <gtest/gtest.h>
#include <util/SingleInstance.hpp>
#include <spdlogger/SpdLogger.h>



auto ptrLogger = SingleInstance<SpdLogger>::getInstance("ptrLogger");
using namespace std;

class Person {
public:
    explicit Person(int v) {
        value = v;
        ptrLogger->getConsole()->info("init code:{}", value);
    }

    ~Person() {
        ptrLogger->getConsole()->info("des code:{}", value);
    }
    int value;
};


// shared_ptr 初始化方式： 1.构造函数 ；2.辅助函数 make_shared<T>()
TEST(test_shared_ptr, shared_ptr) {
    ptrLogger->getConsole()->info("begin>>>>>");
    {
        std::shared_ptr<Person> p1(new Person(1));
        std::shared_ptr<Person> p2 = p1; // ref inc 1  --->
        ptrLogger->getConsole()->info("p2 copy p1 ,value:{}", p2->value);
        p2 = std::make_shared<Person>(2); //change pointer ,p1 ref dec1
        ptrLogger->getConsole()->info("p1 value:{}", p1->value);
        p1.reset(); // p1 release
        ptrLogger->getConsole()->info("p2 value:{}", p2->value);
        p2.reset(); //p2 release
        ptrLogger->getConsole()->info("ref eq 0, des");
    }
    ptrLogger->getConsole()->info("end>>>>>");


}


class ClassB;

class ClassA
{
public:
    ClassA() { cout << "ClassA Constructor..." << endl; }
    ~ClassA() { cout << "ClassA Destructor..." << endl; }
    std::weak_ptr<ClassB> b_weak_ptr;  // ref B object
};

class ClassB
{
public:
    ClassB() { cout << "ClassB Constructor..." << endl; }
    ~ClassB() { cout << "ClassB Destructor..." << endl; }
    std::weak_ptr<ClassA> a_weak_ptr;  //ref A ptr
};


//weak_ptr 不控制所指向对象生存期，通过 绑定到 shared_ptr 对象上 进行初始化，
//shared_ptr 所指向的对象被销毁，weak_ptr 此时所指向的对象不复存在
//lock() 返回 weak_ptr 指向的 share_ptr 对象 ，expired 判断所指对象是否已经被销毁。
TEST(test_weak_ptr, weak_ptr) {

    {

        std::shared_ptr<ClassA> sa(new ClassA);  //
        std::shared_ptr<ClassB> sb=std::make_shared<ClassB>();
        sb->a_weak_ptr=sa;
        sa->b_weak_ptr=sb; // sb  release ,sa->b_weak_ptr cut off!
        //case sb reset
        sb.reset();
        EXPECT_TRUE(sa->b_weak_ptr.expired());
        std::shared_ptr<ClassB> b=sa->b_weak_ptr.lock();
        if(b!= nullptr){
            ptrLogger->getConsole()->info("b not empty");
        } else{
            ptrLogger->getConsole()->info("b empty!!!");
        }
    }



    {
        auto p=new Person(3);
        std::shared_ptr<Person> p3(p); // bad error!!!
        std::shared_ptr<Person> p4(p3);
        EXPECT_TRUE(p3.use_count()==2);
        EXPECT_TRUE(p4.use_count()==2);
        //not change  p  ref!!!
        std::weak_ptr<Person> w_p5=p3; //w_p5 pointer p
        EXPECT_TRUE(w_p5.use_count()==2);
        p3.reset();
        p4.reset();
        EXPECT_TRUE(w_p5.use_count()==0); // yes !!!
    }


}

//1、拥有它指向的对象
//2、无法进行复制构造，无法进行复制赋值操作。即无法使两个unique_ptr指向同一个对象。
//    但是可以进行移动构造和移动赋值操作
//3、保存指向某个对象的指针，当它本身被删除释放的时候，会使用给定的删除器释放它指向的对象
TEST(test_unique_ptr, unique_ptr) {

    ptrLogger->getConsole()->info("begin>>>>>");
    {
        std::unique_ptr<Person> p1=std::make_unique<Person>(8);
        std::unique_ptr<Person> p2(std::move(p1));
        EXPECT_TRUE(p1== nullptr);// moved!> auto remove !
        ptrLogger->getConsole()->info("p2 value:{}",p2->value);
    }
    ptrLogger->getConsole()->info("end>>>>>");


    {
        //int unique _ptr
        std::unique_ptr<int> auto_pointer (new int);
        int * manual_pointer;
        *auto_pointer=101;
        //release 这里不破坏托管的对象
        manual_pointer = auto_pointer.release();
        // (auto_pointer is now empty)
        EXPECT_TRUE(auto_pointer== nullptr);
        ptrLogger->getConsole()->info("manual_pointer points to: {}",*manual_pointer);
        delete manual_pointer;
    }
}
#pragma clang diagnostic pop