cmake_minimum_required(VERSION 3.10)

project(Image-Loader CXX)

set(CMAKE CXX_STANDARD 17)
set(CMAKE CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "src/*.cpp")

add_executable(imager_loader ${SOURCES})

target_include_directories(image_loader, PRIVATE src)


