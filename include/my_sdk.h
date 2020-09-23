#pragma once

#include <array>
#include <vector>
#include <memory>

namespace sdk {

    /** Error codes returned by methods */
    enum class ErrorCode {
        NO_ERROR,
        FAILED
    };

    struct Point {
        /** Coordinate along the horizontal axis, or pixel column */
        int x;
        /** Coordinate along the vertical axis, or pixel row */
        int y;
    };

    struct FaceBoxAndLandmarks {
        /**  The top left corner of the bounding box */
        Point topLeft;
        /**  The bottom right corner of the bounding box */
        Point bottomRight;
        /**  The facial landmark points: left eye, right eye, nose, left mouth corner, right mouth corner */
        std::array<Point, 5> landmarks;
    };

    class MySDK {
    public:
        MySDK();

        ~MySDK();
        /**
         *
         * Detect all the faces in an image and return the corresponding face bounding boxes and landmarks
         *
         * @param[in] imgPath path to the image which will be used for face detection.
         * @param[out] faceDetected indicates if one or more faces were detected in the image.
         * @param[out] fbAndLandmarksVec the resulting bounding boxes and landmarks for the detected faces.
         * @return error code, see ErrorCode
         */
        ErrorCode getFaceBoxAndLandmarks(const std::string& imgPath, bool& faceDetected, std::vector<FaceBoxAndLandmarks>& fbAndLandmarksVec);

    private:
        class Impl;
        std::unique_ptr<Impl> pImpl;
    };
}

