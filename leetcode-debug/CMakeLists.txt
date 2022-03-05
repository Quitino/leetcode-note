cmake_minimum_required(VERSION 3.0)

project(leetcode_debug)

SET(CMAKE_BUILD_TYPE "debug")

add_compile_options(-g)

find_package(OpenCV 3 REQUIRED)
if(OpenCV_FOUND)
    message(STATUS "OpenCV Found")
endif(OpenCV_FOUND)

include_directories(
    ${PROJECT_SOURCE_DIR}
    ${OpenCV_INCLUDE_DIRS}
)

add_executable(leetcode_debug
leetcode_debug.cpp
        )
target_link_libraries(leetcode_debug
${OpenCV_LIBS} 
)

