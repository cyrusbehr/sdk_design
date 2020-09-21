cmake_minimum_required(VERSION 3.0)

project(my_sdk VERSION 0.1.0 LANGUAGES CXX C)

set(OPENCV_BUILD_DIR build_amd64)
set(NCNN_BUILD_DIR build_amd64)

set(MY_SDK_SRC_FILES
        src/my_sdk.cpp
        src/mtcnn.cpp)

# Our SDK library
add_library(my_sdk ${MY_SDK_SRC_FILES})

find_package(OpenMP REQUIRED)
find_package(OpenCV REQUIRED)

target_include_directories(my_sdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_include_directories(my_sdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(my_sdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/include/opencv4)
target_include_directories(my_sdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/ncnn-20200916/${NCNN_BUILD_DIR}/install/include/ncnn)


# Unit test
add_executable(test tests/test.cpp)
# TODO: Need to combine ncnn into sdk and remove this target_link_libraries
target_link_libraries(test my_sdk /home/cyrus/work/vcv/sdk_design/3rdparty/ncnn-20200916/build_amd64/install/lib/libncnn.a OpenMP::OpenMP_CXX ${OpenCV_LIBS})
target_include_directories(test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/catch2)
