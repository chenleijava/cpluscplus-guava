cmake_minimum_required(VERSION 3.10)

project(cplusplusguava)


find_package(Boost REQUIRED)

if (NOT Boost_FOUND)
    message("Boost not found!!!!!")
else ()
    message("Boost found>>>>>>>")
endif (NOT Boost_FOUND)


if (APPLE)
    set(CMAKE_MACOSX_RPATH 1)
    message("mac os>>>")
endif ()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wno-deprecated-register ")
add_definitions( -g -O0 -O2 -DNDEBUG -Wcomment -Wno-deprecated-register)

option(USE_DEBUG  "程序是否开启调试"  OFF)

if (USE_DEBUG)
    add_definitions(-DUSE_DEBUG)
    message("开启Debug调试>>>>>>>")
endif ()

#boost,protobuf include path
include_directories(
        ./include
        ./include/google
        ./include/restbed
        /usr/local/include
        ./include/redis
        ./lib/googletest-release-1.8.1/googletest/include
        ${Boost_INCLUDE_DIRS}
        ./src
        ./ast64src
)


link_directories(/usr/local/lib)
if (APPLE)
    link_directories(./lib/apple ./lib/apple/grpc)
else ()
    link_directories(./lib/unix ./lib/unix/grpc)
endif ()


#sub model
add_subdirectory(tests)
add_subdirectory(./lib/googletest-release-1.8.1)
#add_subdirectory(./cpp_redis-4.3.1)
#add_subdirectory(./restbed-4.6)
add_subdirectory(./ast64src)
#add_subdirectory(./grpc-1.17.2)

#add src ,becareful ,must reload cmake !!!
#file(GLOB_RECURSE PROJECT_SOURCE_DIR src/*)


#add_executable(${PROJECT_NAME} ${PROJECT_SOURCE_DIR})
#target_link_libraries(${PROJECT_NAME} boost_system pthread)
#add_library(${PROJECT_NAME} SHARED ${PROJECT_SOURCE_DIR})


#INSTALL(
#        DIRECTORY ./include
#        DESTINATION ${PROJECT_BINARY_DIR}/
#        FILES_MATCHING PATTERN "*.h*")


#INSTALL(TARGETS ${PROJECT_NAME}
#        LIBRARY DESTINATION ${PROJECT_BINARY_DIR}/lib
#        ARCHIVE DESTINATION ${PROJECT_BINARY_DIR}/lib
#        )

