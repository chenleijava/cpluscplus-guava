//
// Created by chenlei on 2018-12-11.
//

#include <gtest/gtest.h>
#include <iostream>
#include <functional>

using namespace std;
using namespace std::placeholders;

// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide (double x, double y) {return x/y;}
/**
 *
 */
struct MyPair {
    double a,b;
    double multiply() {return a*b;}
}ten_two{10,2};


TEST(test_bind,bind){

    // binding functions:
    auto fn_five = std::bind (my_divide,10,2);               // returns 10/2
    std::cout << fn_five() << '\n';                          // 5
    auto fn_half = std::bind (my_divide,_1,2);               // returns x/2
    std::cout << fn_half(10) << '\n';                        // 5
    std::function<double (double, double)> fn_invert = std::bind (my_divide,_2,_1);            // returns y/x
    std::cout << fn_invert(10,2) << '\n';                    // 0.2
    //template <class Ret, class Fn, class... Args>
    //  /* unspecified */ bind (Fn&& fn, Args&&... args);
    auto fn_rounding = std::bind<int> (my_divide,_1,_2);     // returns int(x/y)
    std::cout << fn_rounding(4,3) << '\n';                  // 1

    // binding functions:
//    auto fn_five = [] { return my_divide(10, 2); };;               // returns 10/2
//    std::cout << fn_five() << '\n';                          // 5
//    auto fn_half = [](auto arg1) { return my_divide(std::move(arg1), 2); };;               // returns x/2
//    std::cout << fn_half(10) << '\n';                        // 5
//    auto fn_invert = [](auto arg1, auto arg2) { return my_divide(std::move(arg2), std::move(arg1)); };         // returns y/x
//    std::cout << fn_invert(10,2) << '\n';                    // 0.2
//    auto fn_rounding = [](auto &&arg1, auto &&arg2) { return my_divide(arg1, arg2); };    // returns int(x/y)
//    std::cout << fn_rounding(10,3) << '\n';                  // 3


    // binding members:
    auto bound_member_fn = std::bind (&MyPair::multiply,_1); // returns x.multiply()
    std::cout << bound_member_fn(std::ref(ten_two)) << '\n';           // 20

    auto bound_member_data = std::bind (&MyPair::a,_1); // returns ten_two.a
    std::cout << bound_member_data(ten_two) << '\n';                // 10
    EXPECT_TRUE(bound_member_data(ten_two)==10);


}
