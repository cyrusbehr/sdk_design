cmake_minimum_required(VERSION 3.0)

project(my_sdk VERSION 0.1.0 LANGUAGES CXX C)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

set(MY_SDK_SRC_FILES
        src/my_sdk.cpp)

add_library(my_sdk ${MY_SDK_SRC_FILES})

add_executable(my_sdk_runner src/main.cpp)
target_link_libraries(my_sdk_runner my_sdk)