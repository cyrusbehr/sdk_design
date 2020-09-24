[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![CircleCI](https://circleci.com/gh/cyrusbehr/sdk_design.svg?style=shield)](https://circleci.com/gh/cyrusbehr/sdk_design)
[![LinkedIn][linkedin-shield]][linkedin-url]



<!-- PROJECT LOGO -->
<br />
<p align="center">
  <a href="https://github.com/github_username/repo_name">
    <img src="images/logo.png" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">SDK Design</h3>

  <p align="center">
    How to Design a Language Agnostic SDK for Cross Platform Deployment and Maximum Extensibility
    <br />
    A Venice Computer Vision presentation
    <br />
    <br />
    <a href="https://www.youtube.com/watch?v=R4KH2V5pTLI&feature=youtu.be">Video Presentation</a>
    ·
    <a href="https://medium.com/@cyrus.behroozi">Blog Post</a>
    ·
    <a href="https://venicecomputervision.com/">Venice Computer Vision</a>
  </p>
</p>


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


<!-- MARKDOWN LINKS & IMAGES -->
<!-- https://www.markdownguide.org/basic-syntax/#reference-style-links -->
[stars-shield]: https://img.shields.io/github/stars/cyrusbehr/sdk_design.svg?style=flat-square
[stars-url]: https://github.com/cyrusbehr/sdk_design/stargazers
[issues-shield]: https://img.shields.io/github/issues/cyrusbehr/sdk_design.svg?style=flat-square
[issues-url]: https://github.com/cyrusbehr/sdk_design/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=flat-square&logo=linkedin&colorB=555
[linkedin-url]: https://linkedin.com/in/cyrus-behroozi/
