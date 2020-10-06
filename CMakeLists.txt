cmake_minimum_required(VERSION 3.0)

# Build options for cross compiling
option(BUILD_ARM32 "Cross compile the SDK for arm32" OFF)
option(BUILD_ARM64 "Cross compile the SDK for arm64" OFF)

# -fpic required by python bindings library
# OpenMP required by ncnn which is used by our library.
# All executables which link against our lib need to link against OpenMP too
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fpic -fopenmp")

# Choose the appropriate toolchain file
if (BUILD_ARM32)
    SET (CMAKE_TOOLCHAIN_FILE tools/toolchain-arm32.cmake)
    set(OPENCV_BUILD_DIR build_arm32)
    set(NCNN_BUILD_DIR build_arm32)
elseif(BUILD_ARM64)
    SET (CMAKE_TOOLCHAIN_FILE tools/toolchain-aarch64.cmake)
    set(OPENCV_BUILD_DIR build_arm64)
    set(NCNN_BUILD_DIR build_arm64)
else()
    set(OPENCV_BUILD_DIR build_amd64)
    set(NCNN_BUILD_DIR build_amd64)
endif()

project(my_sdk VERSION 0.1.0 LANGUAGES CXX C)

# SDK source files
set(MY_SDK_SRC_FILES
        src/my_sdk.cpp
        src/mtcnn.cpp)

# Our SDK library
add_library(my_sdk_static ${MY_SDK_SRC_FILES})

target_include_directories(my_sdk_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/)
target_include_directories(my_sdk_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(my_sdk_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/include/opencv4)
target_include_directories(my_sdk_static PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/ncnn-20200916/${NCNN_BUILD_DIR}/install/include/ncnn)

# Dependency libraries which we will merge into our final static library
set(LIBCNN ${CMAKE_CURRENT_LIST_DIR}/3rdparty/ncnn-20200916/${NCNN_BUILD_DIR}/install/lib/libncnn.a)
set(LIBOPENCV_CORE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/libopencv_core.a)
set(LIBOPENCV_IMGCODECS ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/libopencv_imgcodecs.a)
set(LIBOPENCV_IMGPROC ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/libopencv_imgproc.a)
set(LIBOPENCV_ZLIB ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/opencv4/3rdparty/libzlib.a)
set(LIBOPENCV_JPG ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/opencv4/3rdparty/liblibjpeg-turbo.a)
set(LIBOPENCV_PNG ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/opencv4/3rdparty/liblibpng.a)
set(LIBOPENCV_TIFF ${CMAKE_CURRENT_LIST_DIR}/3rdparty/opencv-4.4.0/${OPENCV_BUILD_DIR}/packaged/usr/local/lib/opencv4/3rdparty/liblibtiff.a)

# Combine all the static libraries into a single library: libmy_sdk.a
if (BUILD_ARM32)
    add_custom_target(my_sdk
            COMMAND
            /bin/echo -e 'create libmy_sdk.a\\naddlib libmy_sdk_static.a\\naddlib ${LIBCNN}\\naddlib ${LIBOPENCV_CORE}\\naddlib ${LIBOPENCV_IMGCODECS}\\naddlib ${LIBOPENCV_IMGPROC}\\naddlib ${LIBOPENCV_ZLIB}\\naddlib ${LIBOPENCV_PNG}\\naddlib ${LIBOPENCV_TIFF}\\naddlib ${LIBOPENCV_JPG}\\nsave\\nend' | arm-linux-gnueabihf-ar -M
            DEPENDS
            my_sdk_static
            COMMENT
            "Merging dependency libraries into my_sdk_static to create libmy_sdk.a"
            )
elseif(BUILD_ARM64)
    add_custom_target(my_sdk
            COMMAND
            /bin/echo -e 'create libmy_sdk.a\\naddlib libmy_sdk_static.a\\naddlib ${LIBCNN}\\naddlib ${LIBOPENCV_CORE}\\naddlib ${LIBOPENCV_IMGCODECS}\\naddlib ${LIBOPENCV_IMGPROC}\\naddlib ${LIBOPENCV_ZLIB}\\naddlib ${LIBOPENCV_PNG}\\naddlib ${LIBOPENCV_TIFF}\\naddlib ${LIBOPENCV_JPG}\\nsave\\nend' | aarch64-linux-gnu-ar -M
            DEPENDS
            my_sdk_static
            COMMENT
            "Merging dependency libraries into my_sdk_static to create libmy_sdk.a"
            )
else()
    add_custom_target(my_sdk
            COMMAND
            /bin/echo -e 'create libmy_sdk.a\\naddlib libmy_sdk_static.a\\naddlib ${LIBCNN}\\naddlib ${LIBOPENCV_CORE}\\naddlib ${LIBOPENCV_IMGCODECS}\\naddlib ${LIBOPENCV_IMGPROC}\\naddlib ${LIBOPENCV_ZLIB}\\naddlib ${LIBOPENCV_PNG}\\naddlib ${LIBOPENCV_TIFF}\\naddlib ${LIBOPENCV_JPG}\\nsave\\nend' | ar -M
            DEPENDS
            my_sdk_static
            COMMENT
            "Merging dependency libraries into my_sdk_static to create libmy_sdk.a"
            )
endif()

# Unit test
add_executable(run_tests tests/test.cpp)
target_link_libraries(run_tests ${CMAKE_CURRENT_BINARY_DIR}/libmy_sdk.a)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(run_tests PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/catch2)
add_dependencies(run_tests my_sdk)

# Create python bindings library
# Only build for amd64
if (NOT BUILD_ARM64 AND NOT BUILD_ARM32)
    add_subdirectory(3rdparty/pybind11-2.3.0)
    add_library(mysdk SHARED python/py_binding.cpp)
    add_dependencies(mysdk my_sdk)

    target_link_libraries(mysdk PRIVATE ${CMAKE_CURRENT_BINARY_DIR}/libmy_sdk.a pybind11::module)

    set_target_properties(mysdk PROPERTIES PREFIX "${PYTHON_MODULE_PREFIX}"
            SUFFIX "${PYTHON_MODULE_EXTENSION}")

    target_include_directories(mysdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
    target_include_directories(mysdk PRIVATE ${CMAKE_CURRENT_LIST_DIR}/3rdparty/pybind11-2.3.0/include)
endif()

add_subdirectory(docs)

install(DIRECTORY DESTINATION ${CMAKE_CURRENT_LIST_DIR}/dist)
install(FILES ${CMAKE_CURRENT_LIST_DIR}/include/my_sdk.h DESTINATION ${CMAKE_CURRENT_LIST_DIR}/dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libmy_sdk.a DESTINATION ${CMAKE_CURRENT_LIST_DIR}/dist)