cmake_minimum_required (VERSION 3.9.1)

project (hello_camera)

set(source_files "main.cpp;${STREAMER_SRC_FILES}")
add_executable(show_video ${source_files})

#link opencv to target
find_package(OpenCV REQUIRED)
target_link_libraries(show_video ${OpenCV_LIBS})

#link threads to target
find_package(Threads REQUIRED)
target_link_libraries(show_video ${CMAKE_THREAD_LIBS_INIT})
