cmake_minimum_required (VERSION 3.9.1)
project (camera_test)
find_package(OpenCV REQUIRED)

set(source_files main.cpp)
add_executable(camera_test ${source_files})


target_link_libraries(camera_test ${OpenCV_LIBS})

