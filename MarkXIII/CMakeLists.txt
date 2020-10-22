cmake_minimum_required(VERSION 3.9)

SET(VTK_DIR "/usr/local/include/vtk-8.1" CACHE PATH "VTK directory override" FORCE)

PROJECT(MarkXIII)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

find_package (Threads)

add_executable(MarkXIII MACOSX_BUNDLE MarkXIII.cxx)

if(VTK_LIBRARIES)
  target_link_libraries(MarkXIII ${VTK_LIBRARIES})
else()
  target_link_libraries(MarkXIII vtkHybrid vtkWidgets)
endif()

target_link_libraries(MarkXIII ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT})
