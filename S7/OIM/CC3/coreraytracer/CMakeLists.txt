
######################
#raytracing API


FILE(GLOB folder_source *.cpp)
FILE(GLOB folder_header *.hpp *.h)
SOURCE_GROUP("Source Files" FILES ${folder_source})
SOURCE_GROUP("Header Files" FILES ${folder_header})




add_library (raytracing STATIC ${folder_source} ${folder_header})
target_link_libraries (raytracing IlmImf Half Iex)
