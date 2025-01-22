cmake_minimum_required(VERSION 3.10)
project(image_viewer)

find_package(OpenCV REQUIRED)

add_executable(image_view image_view.cpp)

target_include_directories(image_view PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(image_view PRIVATE ${OpenCV_LIBS})