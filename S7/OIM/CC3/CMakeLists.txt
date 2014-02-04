cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

project(small_raytracer)


#######################
#compilation configuration
#set(CMAKE_VERBOSE_MAKEFILE FALSE)

#######################
#compilation flags

#common
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ansi -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-unsafe-loop-optimizations -Wextra -fdiagnostics-show-option -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmmx -msse -msse2 -msse3 -mfpmath=sse -ffast-math -lrt")

#debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

#release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -finline -DNDEBUG")

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE} -g3")

if (APPLE)
include_directories (/opt/local/include/OpenEXR/)
link_directories(/opt/local/lib/)
else ()
include_directories (/usr/include/OpenEXR)
endif ()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

# output dirs
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib-debug)
  set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib-debug)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin-debug)
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
  set(LIB_INSTALL_DIR ${CMAKE_SOURCE_DIR}/lib)
  set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)
endif()

add_subdirectory(coreraytracer)
add_subdirectory(main)
