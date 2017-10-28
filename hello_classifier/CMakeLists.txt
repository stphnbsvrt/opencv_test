cmake_minimum_required (VERSION 3.9.1)

project (hello_classifier)

set(source_files "main.cpp;${CLASSIFIER_SRC_FILES}")
add_executable(show_classifier ${source_files})

#link opencv to target
find_package(OpenCV REQUIRED)
target_link_libraries(show_classifier ${OpenCV_LIBS})

#link threads to target
find_package(Threads REQUIRED)
target_link_libraries(show_classifier ${CMAKE_THREAD_LIBS_INIT})
