# Obtain release tag 20200916, set up build directories
test -e 20200916.zip || wget https://github.com/Tencent/ncnn/archive/20200916.zip
test -e ncnn-20200916 || unzip 20200916.zip
cd ncnn-20200916

test -e build_amd64 && rm -rf build_amd64
test -e build_arm32 && rm -rf build_arm32
test -e build_arm64 && rm -rf build_arm64

mkdir build_amd64
mkdir build_arm32
mkdir build_arm64

# Build for amd64
cd build_amd64
cmake -D NCNN_BUILD_TOOLS=OFF -D NCNN_VULKAN=OFF -D NCNN_AVX2=ON -D CMAKE_BUILD_TYPE=Release -D NCNN_BUILD_EXAMPLES=OFF ..
make -j$(nproc)
make  install
cd ..

# Build for arm32
cd build_arm32   
cmake -D NCNN_BUILD_TOOLS=OFF -D NCNN_VULKAN=OFF -D CMAKE_BUILD_TYPE=Release -D NCNN_DISABLE_RTTI=OFF \
-D CMAKE_TOOLCHAIN_FILE=../toolchains/arm-linux-gnueabihf.toolchain.cmake -D NCNN_BUILD_EXAMPLES=OFF ..
make -j$(nproc)
make install
cd ..

# Build for arm64
cd build_arm64
cmake -D NCNN_BUILD_TOOLS=OFF -D NCNN_VULKAN=OFF -D CMAKE_BUILD_TYPE=Release -D NCNN_DISABLE_RTTI=OFF \
-D CMAKE_TOOLCHAIN_FILE=../toolchains/aarch64-linux-gnu.toolchain.cmake -D NCNN_BUILD_EXAMPLES=OFF ..
make -j$(nproc)
make install
cd ..