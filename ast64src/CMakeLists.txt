cmake_minimum_required(VERSION 3.10)
project(astrolog)

add_definitions(-O -Wno-write-strings -Wno-narrowing -fPIC -Wcomment)

include_directories(
        ./
)

file(GLOB_RECURSE PROJECT_SOURCE_DIR ./*)

link_directories(/usr/local/lib)
add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_DIR})
#add_executable(${PROJECT_NAME}  ${PROJECT_SOURCE_DIR})
target_link_libraries(${PROJECT_NAME} m dl)