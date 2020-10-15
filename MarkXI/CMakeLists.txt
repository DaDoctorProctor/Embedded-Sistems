cmake_minimum_required(VERSION 3.9)

project(MarkXI)

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package (Threads)

find_package(PkgConfig)
pkg_check_modules(SERIAL libserial)

set(CMAKE_CXX_STANDART 14)
add_executable(MarkXI mainMarkXI.c++)

target_link_libraries( MarkXI ${OpenCV_LIBS} )
target_link_libraries( MarkXI ${SERIAL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT})
