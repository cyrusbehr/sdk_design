# get the header files
test -e pybind11.zip || wget -O pybind11.zip https://github.com/pybind/pybind11/archive/v2.3.0.zip

test -e pybind11-2.3.0 || unzip ./pybind11.zip
