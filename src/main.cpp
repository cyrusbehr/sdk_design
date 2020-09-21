#include "my_sdk.h"

int main() {
    sdk::MySDK mySdk;

    bool faceDetected;
    std::vector<sdk::FaceBoxAndLandmarks> faceBoxAndLandmarksVec;

    auto res = mySdk.getFaceBoxAndLandmarks("MyPath", faceDetected, faceBoxAndLandmarksVec);

    return 0;
}