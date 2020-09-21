#define CATCH_CONFIG_MAIN

#include <iostream>

#include "my_sdk.h"
#include "catch.hpp"

TEST_CASE("Core functionality", "[core]")
{
    sdk::MySDK mySdk;

    SECTION("Non-existent image") {

        // Ensure the SDK can return an error and exit gracefully
        std::vector<sdk::FaceBoxAndLandmarks> faceBoxAndLandmarksVec;
        bool faceDetected;
        auto errorCode = mySdk.getFaceBoxAndLandmarks("../tests/images/non-existent-image.jpg", faceDetected, faceBoxAndLandmarksVec);
        REQUIRE(errorCode == sdk::ErrorCode::FAILED);
    }

    SECTION("Non face image") {
        std::vector<sdk::FaceBoxAndLandmarks> faceBoxAndLandmarksVec;
        bool faceDetected;
        auto errorCode = mySdk.getFaceBoxAndLandmarks("../tests/images/car.jpg", faceDetected, faceBoxAndLandmarksVec);
        REQUIRE(errorCode == sdk::ErrorCode::NO_ERROR);
        REQUIRE(faceDetected == false);
    }

    SECTION("Faces in image") {
        std::vector<sdk::FaceBoxAndLandmarks> faceBoxAndLandmarksVec;
        bool faceDetected;
        auto errorCode = mySdk.getFaceBoxAndLandmarks("../tests/images/face.jpg", faceDetected, faceBoxAndLandmarksVec);
        REQUIRE(errorCode == sdk::ErrorCode::NO_ERROR);
        REQUIRE(faceDetected == true);

        // Ensure the correct number of faces were detected
        REQUIRE(faceBoxAndLandmarksVec.size() == 6);

        // TODO: Can add other checks here to ensure the landmark and bounding box locations are correct
    }
}