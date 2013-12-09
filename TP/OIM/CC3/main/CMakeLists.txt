######################
#main program

FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.hpp *.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})


include_directories (../coreraytracer)

add_executable (main ${folder_source})
target_link_libraries (main raytracing )

