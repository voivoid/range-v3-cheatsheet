cmake_minimum_required(VERSION 3.13)
project(RANGEV3_CHEATSHEET LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/thirdparties/boost.cmake)
include(cmake/thirdparties/rangev3.cmake)


enable_testing()
add_subdirectory(src)


find_program(ClangFormat clang-format)
if(ClangFormat)
    get_target_property(Srcs CheatSheet SOURCES)
    get_target_property(Dir CheatSheet SOURCE_DIR)
    foreach(Src ${Srcs})
      list(APPEND Sources "${Dir}/${Src}")
    endforeach()

  add_custom_target(clangformat
    COMMAND clang-format -style=file -i ${Sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
endif()


