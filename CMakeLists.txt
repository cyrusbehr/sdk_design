cmake_minimum_required(VERSION 3.0)

project(my_sdk VERSION 0.1.0 LANGUAGES CXX C)


set(MY_SDK_SRC_FILES
        src/my_sdk.cpp)

add_library(my_sdk ${MY_SDK_SRC_FILES})
target_include_directories(my_sdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)

add_executable(my_sdk_runner src/main.cpp)
target_link_libraries(my_sdk_runner my_sdk)
target_include_directories(my_sdk_runner PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
