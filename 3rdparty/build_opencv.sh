# Obtain release tag 20200916, set up build directories
test -e 4.4.0.zip || wget https://github.com/opencv/opencv/archive/4.4.0.zip
test -e opencv-4.4.0 || unzip 4.4.0.zip
cd opencv-4.4.0

test -e build_amd64 && rm -rf build_amd64
test -e build_arm32 && rm -rf build_arm32
test -e build_arm64 && rm -rf build_arm64

mkdir build_amd64
mkdir build_arm32
mkdir build_arm64

# Build for amd64
cd build_amd64
cmake -D BUILD_LIST=core,imgcodecs,imgproc -D BUILD_SHARED_LIBS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_DOCS=OFF -D BUILD_EXAMPLES=OFF \
-D BUILD_opencv_apps=OFF -D BUILD_opencv_python2=OFF -D BUILD_opencv_python3=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D FORCE_VTK=OFF \
-D WITH_FFMPEG=OFF -D WITH_GDAL=OFF -D WITH_IPP=OFF -D WITH_OPENEXR=OFF -D WITH_OPENGL=OFF -D WITH_QT=OFF -D WITH_TBB=OFF -D WITH_XINE=OFF \
-D BUILD_JPEG=ON -D BUILD_ZLIB=ON -D BUILD_PNG=ON -D BUILD_TIFF=ON -D BUILD_BUILD_JASPER=OFF -D WITH_ITT=OFF -D WITH_LAPACK=OFF -D WITH_OPENCL=OFF \
-D WITH_TIFF=ON -D WITH_PNG=ON -D WITH_OPENCLAMDFFT=OFF -D WITH_OPENCLAMDBLAS=OFF -D WITH_VA_INTEL=OFF -D WITH_WEBP=OFF -D WITH_JASPER=OFF -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j2 # Using -j2 b/c free tier of circleCI only has enough ram for two concurrent processes
make DESTDIR=packaged install
cd ..

# Build for arm32
cd build_arm32
cmake -DCMAKE_TOOLCHAIN_FILE="../platforms/linux/arm-gnueabi.toolchain.cmake" -D WITH_CAROTENE=OFF -D BUILD_LIST=core,imgcodecs,imgproc \
-D BUILD_SHARED_LIBS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_DOCS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_opencv_apps=OFF -D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D FORCE_VTK=OFF -D WITH_FFMPEG=OFF -D WITH_GDAL=OFF -D WITH_IPP=OFF \
-D WITH_OPENEXR=OFF -D WITH_OPENGL=OFF -D WITH_QT=OFF -D WITH_TBB=OFF -D WITH_XINE=OFF -D BUILD_JPEG=ON -D BUILD_ZLIB=ON -D BUILD_PNG=ON -D BUILD_TIFF=ON \
-D BUILD_BUILD_JASPER=OFF -D WITH_ITT=OFF -D WITH_LAPACK=OFF -D WITH_OPENCL=OFF -D WITH_TIFF=ON -D WITH_PNG=ON -D WITH_OPENCLAMDFFT=OFF -D WITH_OPENCLAMDBLAS=OFF \
-D WITH_VA_INTEL=OFF -D WITH_WEBP=OFF -D WITH_JASPER=OFF -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j2 # Using -j2 b/c free tier of circleCI only has enough ram for two concurrent processes
make DESTDIR=packaged install
cd ..

# Build for arm64
cd build_arm64
cmake -DCMAKE_TOOLCHAIN_FILE="../platforms/linux/aarch64-gnu.toolchain.cmake" -D WITH_CAROTENE=OFF -D BUILD_LIST=core,imgcodecs,imgproc \
-D BUILD_SHARED_LIBS=OFF -D CMAKE_BUILD_TYPE=RELEASE -D BUILD_DOCS=OFF -D BUILD_EXAMPLES=OFF -D BUILD_opencv_apps=OFF -D BUILD_opencv_python2=OFF \
-D BUILD_opencv_python3=OFF -D BUILD_PERF_TESTS=OFF -D BUILD_TESTS=OFF -D FORCE_VTK=OFF -D WITH_FFMPEG=OFF -D WITH_GDAL=OFF -D WITH_IPP=OFF -D WITH_OPENEXR=OFF \
-D WITH_OPENGL=OFF -D WITH_QT=OFF -D WITH_TBB=OFF -D WITH_XINE=OFF -D BUILD_JPEG=ON -D BUILD_ZLIB=ON -D BUILD_PNG=ON -D BUILD_TIFF=ON -D BUILD_BUILD_JASPER=OFF \
-D WITH_ITT=OFF -D WITH_LAPACK=OFF -D WITH_OPENCL=OFF -D WITH_TIFF=ON -D WITH_PNG=ON -D WITH_OPENCLAMDFFT=OFF -D WITH_OPENCLAMDBLAS=OFF -D WITH_VA_INTEL=OFF \
-D WITH_WEBP=OFF -D WITH_JASPER=OFF -D CMAKE_INSTALL_PREFIX=/usr/local ..
make -j2 # Using -j2 b/c free tier of circleCI only has enough ram for two concurrent processes
make DESTDIR=packaged install
cd ..