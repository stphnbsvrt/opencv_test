cmake_minimum_required (VERSION 3.9.1)

project (bg_sub)

set(source_files "main.cpp;${STREAMER_SRC_FILES}")
add_executable(bg_sub ${source_files})

#link opencv to target
find_package(OpenCV REQUIRED)
target_link_libraries(bg_sub ${OpenCV_LIBS})

#link threads to target
find_package(Threads REQUIRED)
target_link_libraries(bg_sub ${CMAKE_THREAD_LIBS_INIT})
