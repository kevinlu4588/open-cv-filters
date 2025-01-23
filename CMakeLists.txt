cmake_minimum_required(VERSION 3.15)

# Project name
project(VideoFilters)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV package
find_package(OpenCV REQUIRED)

# Debugging output
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV libs: ${OpenCV_LIBS}")

# Add the executable for vidDisplay
add_executable(vidDisplay vidDisplay.cpp filter.cpp)

# Link OpenCV libraries to vidDisplay
target_include_directories(vidDisplay PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(vidDisplay PRIVATE ${OpenCV_LIBS})

# Add the executable for timeBlur
add_executable(timeBlur timeBlur.cpp filter.cpp)

# Link OpenCV libraries to timeBlur
target_include_directories(timeBlur PRIVATE ${OpenCV_INCLUDE_DIRS})
target_link_libraries(timeBlur PRIVATE ${OpenCV_LIBS})

# Force CMake to use the correct architecture
set(CMAKE_OSX_ARCHITECTURES arm64)
