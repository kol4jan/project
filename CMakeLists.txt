cmake_minimum_required(VERSION 3.8)
project(Tetris)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_STANDARD 11)

#find_library (LIBSTDCXX NAMES stdc++)
#add_compile_options(-stdlib=libstdc++)
if(APPLE)
    include_directories(AFTER "/opt/X11/include")
endif()

set(SOURCE_FILES main.cpp CImg.h)
add_executable(Tetris ${SOURCE_FILES})

if(1) #${YOU_NEED_X11})
    message(STATUS "Looking for X11...")
    find_package(X11 REQUIRED)
    include_directories(${X11_INCLUDE_DIR})
    message(${X11_INCLUDE_DIR})

    target_link_libraries(Tetris ${X11_LIBRARIES})
else()
    message("X11 DOES NOT REQUIRED WHAT THE HELL")
endif()