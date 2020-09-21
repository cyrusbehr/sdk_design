#include <iostream>

#include "my_sdk.h"
#include "mtcnn.h"
#include "opencv2/opencv.hpp"
#include "net.h"

using namespace sdk;
using namespace mtcnn;

class MySDK::Impl {
public:
    Impl() = default;
    ErrorCode getFaceBoxAndLandmarks(const std::string& imgPath, bool& faceDetected, std::vector<FaceBoxAndLandmarks>& fbAndLandmarksVec);
private:
    MTCNN m_mtcnn;
};

MySDK::~MySDK() {}

MySDK::MySDK() {
    pImpl = std::make_unique<Impl>();
}

ErrorCode MySDK::getFaceBoxAndLandmarks(const std::string& imgPath, bool& faceDetected, std::vector<FaceBoxAndLandmarks>& fbAndLandmarksVec) {
    return pImpl->getFaceBoxAndLandmarks(imgPath, faceDetected, fbAndLandmarksVec);
}

ErrorCode MySDK::Impl::getFaceBoxAndLandmarks(const std::string &imgPath, bool& faceDetected, std::vector<FaceBoxAndLandmarks>& fbAndLandmarksVec) {
    auto img = cv::imread(imgPath);
    if (img.empty()) {
        // Unable to read image
        return ErrorCode::FAILED;
    }

    auto ncnnImg = ncnn::Mat::from_pixels(img.data, ncnn::Mat::PIXEL_BGR2RGB, img.cols, img.rows);
    std::vector<Bbox> bboxVec;

    m_mtcnn.detect(ncnnImg, bboxVec);
    if (bboxVec.empty()) {
        faceDetected = false;
        return ErrorCode::NO_ERROR;
    }

    faceDetected = true;
    fbAndLandmarksVec.clear();
    fbAndLandmarksVec.reserve(bboxVec.size());

    for (const auto& bbox: bboxVec) {
        FaceBoxAndLandmarks fb;
        fb.topLeft.x = bbox.x1;
        fb.topLeft.y = bbox.y1;
        fb.bottomRight.x = bbox.x2;
        fb.bottomRight.y = bbox.y2;

        fb.faceScore = bbox.score;

        for (int i = 0; i < 5; ++i) {
            Point p;
            p.x = static_cast<int>(bbox.landmark.x[i]);
            p.y = static_cast<int>(bbox.landmark.y[i]);

            fb.landmarks[i] = p;
        }

        fbAndLandmarksVec.emplace_back(fb);
    }

    return ErrorCode::NO_ERROR;
}