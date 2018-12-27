//
// Created by chenlei on 2018-12-07.
//

/**
 * 声明结构体Product ，并定义一个实例apple
 * 类成员变量 默认 public访问属性
 */
struct Product {
    int w;
    int h;
    union {
        unsigned int yuan;
        double yuanOther;
    } price;
} apple{1, 2};

#include <gtest/gtest.h>

/**
 *
 * @param product
 */
void printStr(Product *product) {
    printf("product h:%d w:%d, yuan:%d,%lf\n",
            product->h, product->w,
            product->price.yuan,
            product->price.yuanOther);
}

/***
 *
 * @param product
 */
void printStr(Product &product) {
    printf("product h:%d w:%d \n", product.h, product.w);
}

/**
 *
 */
enum Week {
    SUNDAY, MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY
} week;


/**
 *
 */
TEST(test_struct, _struct) {
    Product product{10, 19};
    product.price.yuan = 109;
    printStr(&product);
    product.price.yuanOther = 10.9;
    printStr(&product);

    Product *productPtr;
    productPtr = &product;
    printStr(productPtr);
    product.w = 100;
    product.h = 100;
    printStr(&product);
    printStr(product);
    //define objects
    printStr(apple);
    Week today = SATURDAY;
    ASSERT_TRUE(today == THURSDAY);
    ASSERT_TRUE(today == SATURDAY);
}
