[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![MIT License][license-shield]][license-url]
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">YOUR_TITLE</h3>

  <p align="center">
    YOUR_SHORT_DESCRIPTION
    <br />
    <a href="https://github.com/github_username/repo_name"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/github_username/repo_name">View Demo</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Report Bug</a>
    ·
    <a href="https://github.com/github_username/repo_name/issues">Request Feature</a>
  </p>
</p>



# How to Design a Language Agnostic SDK for Cross Platform Deployment and Maximum Extensibility

## Getting Started
The following instructions assume you are using Ubuntu 18.04

### Prerequisites
- `sudo apt install build-essential`
- `sudo apt-get install g++-aarch64-linux-gnu`
- `sudo apt-get install gcc-arm-linux-gnueabihf binutils-arm-linux-gnueabihf g++-arm-linux-gnueabihf`
- `sudo apt install python3.8`
- `sudo apt install python3-pip`
- `pip3 install cmake`
- `sudo apt-get install doxygen`
- `sudo apt-get install wget`
- `sudo apt-get install zip`

### Install 3rd Party Libraries
Navigate to `3rdparty` then run the following:
- `./build_catch.sh`
- `./build_pybind11.sh`
- `./build_ncnn.sh`
- `./build_opencv.sh`

### Building the library
- `mkdir build && cd build`
- `cmake ..`
- `make -j$(nproc)`
- `make install`

The outputs will be copied to `dist`

### Cross comping for arm32
- `mkdir build && cd build`
- `cmake -D BUILD_ARM32=ON ..`
- `make -j$(nproc)`
- `make install`

### Cross compiling for arm64
- `mkdir build && cd build`
- `cmake -D BUILD_ARM64=ON ..`
- `make -j$(nproc)`
- `make install`


