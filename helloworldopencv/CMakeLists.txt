cmake_minimum_required(VERSION 3.15)
project(helloworldopencv)

set(CMAKE_CXX_STANDARD 11)

#Vcpkg
if(DEFINED ENV{VCPKG_ROOT} AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
            CACHE STRING "")
    message(" [INFO] VCPKG CMAKE_TOOLCHAIN_FILE = ${CMAKE_TOOLCHAIN_FILE}")
endif()

add_executable(helloworldopencv main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ss.jpeg ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/SS.jpg ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/small.avi ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

# Find Package
find_package( OpenCV REQUIRED )
# find_package(OpenCV CONFIG REQUIRED)

if( OpenCV_FOUND )
    # Additional Include Directories
    include_directories( ${OpenCV_INCLUDE_DIRS} )

    # Additional Library Directories
    link_directories( ${OpenCV_LIB_DIR} )

    # Additional Dependencies
    target_link_libraries( helloworldopencv ${OpenCV_LIBS} )
    # target_link_libraries(main PRIVATE quirc opencv_ml opencv_dnn opencv_core)

endif()