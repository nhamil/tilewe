cmake_minimum_required(VERSION 3.16) 
project(tilewe C) 

message(STATUS "Building Tilewe")

include_directories(Source)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(UNIX AND NOT APPLE)
    set(LINUX TRUE)
endif()
if(LINUX) 
    message(STATUS "Building for Linux") 
elseif(WIN32) 
    message(STATUS "Building for Windows") 
else() 
    message(FATAL_ERROR "Unsupported operating system") 
endif() 

if(CMAKE_SIZEOF_VOID_P EQUAL 4) 
    message(STATUS "Building 32-bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8) 
    message(STATUS "Building 64-bit")
else() 
    math(EXPR BIT_COUNT "${CMAKE_SIZEOF_VOID_P} * 8")
endif() 

set(CMAKE_C_STANDARD 11) 
set(CMAKE_C_FLAGS "--std=c99 -Wall -Wextra -pedantic -Wno-unused-function -Wno-unused-result -Wno-unused-label")
set(CMAKE_C_FLAGS_DEBUG "-g -O3 -funroll-loops")
set(CMAKE_C_FLAGS_RELEASE "-O3 -funroll-loops")

set(SOURCES 
    Source/Tilewe/Piece.c 
    Source/Tilewe/Tables.c
)

add_library(tilewe STATIC ${SOURCES})

add_executable(testboard Source/Test/TestBoard.c)
target_link_libraries(testboard tilewe -static)
