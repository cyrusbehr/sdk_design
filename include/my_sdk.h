#pragma once

#include <array>
#include <vector>
#include <memory>

namespace sdk {

    enum class ErrorCode {
        NO_ERROR,
        FAILED
    };

    struct Point {
        int x;
        int y;
    };

    struct FaceBoxAndLandmarks {
        Point topLeft;
        Point bottomRight;
        std::array<Point, 5> landmarks;
    };

    class MySDK {
    public:
        MySDK();
        ~MySDK();
        ErrorCode getFaceBoxAndLandmarks(const std::string& imgPath, bool& faceDetected, std::vector<FaceBoxAndLandmarks>& fbAndLandmarksVec);

    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };
}

