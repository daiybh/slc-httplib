cmake_minimum_required(VERSION 3.15)
project(slc-httplib CXX)

option(build_test "build_testAPP" OFF)
message(STATUS "build_test: ${build_test}")
find_package(httplib  REQUIRED)

add_library(slc-httplib src/slc-httplib.cpp)
target_include_directories(slc-httplib PUBLIC include)

target_link_libraries(slc-httplib PUBLIC httplib::httplib)


set_target_properties(slc-httplib PROPERTIES PUBLIC_HEADER "include/slc-httplib.h")
install(TARGETS slc-httplib)

if(build_test)
    add_subdirectory(testapp)
endif()