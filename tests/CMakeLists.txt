project(base_tests)


#add source
file(GLOB_RECURSE PROJECT_SOURCE_DIR ./*)
file(GLOB_RECURSE PROJECT_SOURCE_DIR_P ../src/*)

add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR_P})


file(COPY ../resources DESTINATION ${CMAKE_BINARY_DIR}/tests)
file(COPY ../resources DESTINATION ${CMAKE_BINARY_DIR})
file(COPY ../shell/start.sh DESTINATION ${CMAKE_BINARY_DIR}/tests)
file(COPY ../lib/unix DESTINATION ${CMAKE_BINARY_DIR}/tests)




if (APPLE)
    target_link_libraries(${PROJECT_NAME} boost_thread-mt)
else ()
    target_link_libraries(${PROJECT_NAME} boost_thread)
endif ()



#link gtest lib
target_link_libraries(${PROJECT_NAME}
        pthread
        boost_system
        cpp_redis tacopie
        restbed
        gtest
        gtest_main
        astrolog
        protobuf
        grpc++
        grpc
        gpr
        cares
        address_sorting
        z
        )
