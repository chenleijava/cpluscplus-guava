//
// Created by chenlei on 2018-12-12.
//

#include <gtest/gtest.h>
#include <util/Logger.hpp>
#include "util/Properties.hpp"


/**
 *
 */
TEST(test_properties, properties) {
    auto logger = Logger::createLogger("propertiesLogger");
    logger->error("test logger message!");
    auto i = std::stoi("123");
    logger->info("string to int ,value:{}", i);

    //
    Properties properties;
    properties.loadingProperties("resources/application.properties");
    properties.debug();
    auto name = properties.get("name");
    auto age = std::stoi(properties.get("age"));
    auto address = properties.get("address");
    logger->info("name:{} age:{} address:{}", name, age, address);
}
