cmake_minimum_required(VERSION 3.13)
project(RANGEV3_CHEATSHEET LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/thirdparties/boost.cmake)
include(cmake/thirdparties/rangev3.cmake)

add_subdirectory(src)
