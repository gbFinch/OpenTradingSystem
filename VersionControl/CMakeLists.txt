cmake_minimum_required(VERSION 3.16)
project(VersionControl)


set(PRE_CONFIGURE_FILE "git.cpp.in")
set(POST_CONFIGURE_FILE "${CMAKE_CURRENT_BINARY_DIR}/git.cpp")
include(./git_watcher.cmake)
add_library(VersionControl STATIC ${POST_CONFIGURE_FILE})
target_include_directories(VersionControl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(VersionControl check_git)