#include "my_sdk.h"

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"
#include "pybind11/numpy.h"

namespace py = pybind11;
using namespace sdk;

PYBIND11_MODULE(mysdk, m) {

    py::class_<Point>(m, "Point")
            .def(py::init<>())
            .def_readwrite("x", &Point::x, "Coordinate along the horizontal axis, or pixel column.")
            .def_readwrite("y", &Point::y, "Coordinate along the vertical axis, or pixel row.");

    py::class_<FaceBoxAndLandmarks>(m, "FaceBoxAndLandmarks")
            .def(py::init<>())
            .def_readwrite("top_left", &FaceBoxAndLandmarks::topLeft, "Top left coordinate.")
            .def_readwrite("bottom_right", &FaceBoxAndLandmarks::bottomRight, "Bottom right coordinate.")
            .def_readwrite("landmarks", &FaceBoxAndLandmarks::landmarks, "Array of face landmarks.");

    py::enum_<ErrorCode>(m, "ERRORCODE")
            .value("NO_ERROR", ErrorCode::NO_ERROR)
            .value("FAILED", ErrorCode::FAILED)
            .export_values();

    py::class_<MySDK>(m, "MY_SDK")
            .def(py::init<>())
            .def("get_face_box_and_landmarks", [](MySDK& mySDK, const std::string& imgPath) {
                std::vector<FaceBoxAndLandmarks> fbVec;
                bool faceDetected;
                auto errorCode = mySDK.getFaceBoxAndLandmarks(imgPath, faceDetected, fbVec);

                return std::make_tuple(errorCode, faceDetected, fbVec);
            }, "Get a list of FaceBoxAndLandmarks for all the detected faces in the image.", py::arg("img_path"));
}