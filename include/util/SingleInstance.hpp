//
// Created by chenlei on 2018-12-11.
//

#ifndef CPLUSPLUSGUAVA_SINGLEINSTANCE_H
#define CPLUSPLUSGUAVA_SINGLEINSTANCE_H

#include <mutex>
#include <memory>

/**
 * build single instance , thread safe !!!
 * @tparam T
 *
 * SingleInstance<T>::getInstance(Args);
 */

 // non-copyable!!!!
#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
  TypeName(const TypeName&) = delete;      \
  TypeName& operator=(const TypeName&) = delete; \

template<class T>
class SingleInstance {
private:
    static std::once_flag onceFlag; // not alloc mem
    static std::shared_ptr<T> singleInstance; //shared_ptr
public:
    //non copyable
    DISALLOW_COPY_AND_ASSIGN(SingleInstance);
public:
    /**
     * get single instance
     * @tparam Args  可变模板参数  ,包含 0 到任意个参数模板参数 ,需要将一组参数原封不动的传递给另一个函数
     * @param args  右值引用
     * @return
     */
    template<typename  ...Args>
    static std::shared_ptr<T> getInstance(Args &&...args){
        if (!singleInstance) {
            std::call_once(onceFlag, [&]() {
                //按照参数原来的类型转发到另一个函数中
                singleInstance = std::make_shared<T>(std::forward<Args>(args)...);
            });
        }
        return singleInstance;
    }


    /**
     * des single instance
     */
    static void desInstance(){
        if (singleInstance) {
            singleInstance.reset();
            singleInstance = nullptr;
        }
    }

};

//define static members ,out of clazz,alloc mem !
template<class T>
std::once_flag SingleInstance<T>::onceFlag;
template<class T>
std::shared_ptr<T>SingleInstance<T>::singleInstance;  //init in memory

#endif //CPLUSPLUSGUAVA_SINGLEINSTANCE_H
