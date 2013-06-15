cmake_minimum_required(VERSION 2.6)

project(MIFCity)

#set Wall annd debug mode flags
set(CMAKE_CXX_FLAGS "-g -Wall -pedantic")

if(APPLE) #mac specific
   INCLUDE_DIRECTORIES ( /System/Library/Frameworks ) 
   FIND_LIBRARY(GLUT_LIBRARY GLUT ) 
   FIND_LIBRARY(OpenGL_LIBRARY OpenGL ) 
   FIND_LIBRARY(PNG libpng)
   MARK_AS_ADVANCED (GLUT_LIBRARY 
                     OpenGL_LIBRARY) 
   SET(EXTRA_LIBS ${GLUT_LIBRARY} ${OpenGL_LIBRARY}) 

# add package glut and OpenGL
# WARNING : on linux if GLUT_Xmu_LIBRARY is UNFOUND then run following command :
# > sudo apt-get install libxmu-dev libxi-dev
ELSE(APPLE)
    find_package(GLUT)
    find_package(OpenGL)
    mark_as_advanced(GLUT_LIBRARY GLEW_LIBRARY OPENGL_LIBRARIES)
    set(EXTRA_LIBS ${GLUT_LIBRARY} ${OPENGL_LIBRARIES})
endif(APPLE)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})


include_directories(${MIFCity_SOURCE_DIR}/include)
file(GLOB CPP_FILES ${MIFCity_SOURCE_DIR}/src/*.cpp ${MIFCity_SOURCE_DIR}/include/*.h)
add_executable(mifcity ${CPP_FILES})

#add the libraries to link the target with
if(APPLE)
	target_link_libraries( mifcity ${EXTRA_LIBS} ${PNG_LIBRARY})
else(APPLE)
        target_link_libraries( mifcity ${EXTRA_LIBS} "GLEW"  ${PNG_LIBRARY})
endif(APPLE)

