cmake_minimum_required (VERSION 3.9.1)

project (hello_camera)

set(source_files "main.cpp;streamerUT.cpp;filterUT.cpp")
set(source_files "${source_files};${STREAMER_SRC_FILES};${FILTER_SRC_FILES}")
add_executable(repo_test ${source_files})

#link opencv to target
find_package(OpenCV REQUIRED)
target_link_libraries(repo_test ${OpenCV_LIBS})

#link threads to target
find_package(Threads REQUIRED)
target_link_libraries(repo_test ${CMAKE_THREAD_LIBS_INIT})

#link gtest to target
find_package(GTest REQUIRED)
target_link_libraries(repo_test ${GTEST_LIBRARIES})
