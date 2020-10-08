cmake_minimum_required(VERSION 3.5)

project(nextion-uploader LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
find_package(Qt5SerialPort)

include_directories(include/)

add_executable(nextion-uploader

    include/nextionuploader.hpp

    src/main.cpp
    src/nextionuploader.cpp
    )
target_link_libraries(nextion-uploader
    Qt5::Core
    Qt5::SerialPort)
