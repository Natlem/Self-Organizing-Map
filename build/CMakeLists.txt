#Require
cmake_minimum_required(VERSION 2.8)

#Projet Name
project( PrPa_Projet )

#compiler
if (UNIX)
   if (APPLE)
      set (CMAKE_CXX_COMPILER g++-mp-4.8)
   else (APPLE)
      set (CMAKE_CXX_COMPILER g++-4.8)
   endif (APPLE)
endif (UNIX)

#flag
#if (UNIX)
#   if (APPLE)
#       set (CMAKE_CXX_FLAGS)
#   else (APPLE)
       set (CMAKE_CXX_FLAGS "-std=c++11 -g3")
#   endif (APPLE)
#endif (UNIX)

SET(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "-L/lib/ -ltbb")

# Add FindTBB directory to CMake's module path
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_CURRENT_SOURCE_DIR}/.")

#Execute the FindTBB macro
#find_package(TBB)
#If you want FindTBB to fail if TBB is not found, use this form:
 find_package(TBB REQUIRED)

# Here goes the actual project
include_directories(${TBB_INCLUDE_DIRS})
link_directories(${TBB_LIBRARY_DIRS})

#Check Package
find_package( OpenCV REQUIRED )

#Compiling file and binary generation
 #Get all sources files
 file(
   GLOB_RECURSE
   V_SOURCE
   ../src/color.[ch][ch]
   ../src/main.cc
   ../src/Node.[ch][ch]
   ../src/training.[ch][ch]
   ../src/tbbFindBMU.[ch][ch]
 )
 file(
   GLOB_RECURSE
   V_GENERATE
   ../src/generator.cc
 )

 #Add Files
 add_executable(
   PrPa_Projet
   ${V_SOURCE}
 )
 add_executable(
   generator
   ${V_GENERATE}
 )

#Link target
target_link_libraries( PrPa_Projet ${OpenCV_LIBS} )
target_link_libraries( generator ${OpenCV_LIBS} )

#Custom Cmd Clean
ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
  SET(DISTCLEANED
   cmake.depends
   cmake.check_depends
   CMakeCache.txt
   cmake.check_cache
   *.cmake
   Makefile
   core core.*
   bin
   PrPa_Projet
   CMakeFiles
   *~
   *.swp
  )

  ADD_CUSTOM_COMMAND(
    DEPENDS clean
    COMMENT "distribution clean"
    COMMAND rm
    ARGS    -Rf CMakeTmp ${DISTCLEANED}
    TARGET  distclean
  )
