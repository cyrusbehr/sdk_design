#include <iostream>
#include "my_sdk.h"
#include <opencv2/opencv.hpp>

int main() {
    sdk::MySDK mySdk;

    bool faceDetected;
    std::vector<sdk::FaceBoxAndLandmarks> faceBoxAndLandmarksVec;

    auto imgPath = "../tests/images/face.jpg";
    auto res = mySdk.getFaceBoxAndLandmarks(imgPath, faceDetected, faceBoxAndLandmarksVec);

    if (res != sdk::ErrorCode::NO_ERROR) {
        std::cout << "There was an error!" << std::endl;
    }

    auto img = cv::imread(imgPath);
    for (auto & bbox : faceBoxAndLandmarksVec) {
        cv::Point topLeft(bbox.topLeft.x, bbox.topLeft.y);
        cv::Point bottomRight(bbox.bottomRight.x, bbox.bottomRight.y);
        cv::rectangle(img, topLeft, bottomRight, cv::Scalar(255, 0, 0), 2);

        for (int j = 0; j < 5; ++j) {
            cv::Point p(bbox.landmarks[j].x, bbox.landmarks[j].y);
            cv::circle(img, p, 1, cv::Scalar(0, 255, 0), 3, cv::LINE_AA);
        }

    }
        cv::imshow("MyWindow", img);
        cv::waitKey();


    return 0;
}