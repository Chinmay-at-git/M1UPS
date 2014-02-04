cmake_minimum_required(VERSION 2.6)

set(CMAKE_ALLOW_LOOSE_LOOP_CONSTRUCTS true)

project(small_raytracer_c)


#######################
#compilation configuration
set(CMAKE_VERBOSE_MAKEFILE FALSE)

######################
#raytracing API

if (APPLE)
include_directories (/opt/local/include/OpenEXR/)
link_directories(/opt/local/lib/)
else ()
include_directories (/usr/include/OpenEXR)
endif ()

set(Sources
  raytracing.cpp
  solidesplaton.cpp
)

add_library (raytracing STATIC ${Sources})
target_link_libraries (raytracing IlmImf Half Iex)

######################
#main program

set(Sources
  main.cpp
)

add_executable (main ${Sources})
target_link_libraries (main raytracing)



#######################
#compilation flags

#common
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -ansi -fPIC")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unknown-pragmas -Wno-unsafe-loop-optimizations -Wextra -fdiagnostics-show-option -Wno-unused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -mmmx -msse -msse2 -msse3 -mfpmath=sse -lrt")

#debug
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")

#release
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -mfpmath=sse -ffast-math -finline") 
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -DQT_NO_DEBUG -DQT_NO_CHECK")

set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${CMAKE_CXX_FLAGS_RELEASE}")

