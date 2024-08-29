cmake_minimum_required(VERSION 3.15)
project(PackageTest CXX)

find_package(slc-httplib CONFIG REQUIRED)

add_executable(testApp src/example.cpp)
target_link_libraries(testApp slc-httplib::slc-httplib)


add_executable(example ../test_package/src/example.cpp)
target_link_libraries(example slc-httplib::slc-httplib)
