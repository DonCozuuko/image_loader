cmake_minimum_required(VERSION 3.10)

project(Image-Loader CXX)

set(CMAKE CXX_STANDARD 17)
set(CMAKE CXX_STANDARD_REQUIRED True)

file(GLOB SOURCES "Source/*.cpp")

add_executable(imager_loader ${SOURCES})



