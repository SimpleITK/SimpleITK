cmake_minimum_required(VERSION 2.6)

if( POLICY CMP0042 )
  cmake_policy( SET CMP0042 NEW )
endif()
if( POLICY CMP0054 )
  cmake_policy( SET CMP0054 OLD )
endif()
## GET R-specific ENV variables
set(R_HOME $ENV{R_HOME})
SET(RLIB "${R_HOME}/lib")
set (RSCRIPT "${R_HOME}/bin/Rscript")
set(RCPP_DIR "$ENV{RCPP_DIR}/include")
set(RSITKLIB "$ENV{RSITKLIB}")
set(R_INCLUDE_DIR "$ENV{R_INCLUDE_DIR}")
set(CXX "$ENV{CXX}")

set(CXXFLAGS "$ENV{CXXFLAGS}")
set(CPPFLAGS "$ENV{CPPFLAGS}")
## set variables accordingly
set(CMAKE_CXX_FLAGS "${CXXFLAGS}")
set(CMAKE_C_FLAGS "${CPPFLAGS} ${CFLAGS}")
SET(CMAKE_CXX_COMPILER::string "${CXX}")
set(CMAKE_VERBOSE_MAKEFILE OFF)
set(RSITKLIB "$ENV{RSITKLIB}")
project(SimpleITKCxx CXX)
## look for SimpleITK
FIND_PACKAGE(SimpleITK REQUIRED)
include(${SimpleITK_USE_FILE})

## look for SimpleITK R-package dynlib
SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so" ".a" ".dylib")
SET(CMAKE_FIND_LIBRARY_PREFIXES "")
FIND_LIBRARY(SimpleITKLIB SimpleITK "${RSITKLIB}")
add_library(RSimpleITK SHARED IMPORTED)
set_target_properties(RSimpleITK PROPERTIES IMPORTED_LOCATION ${SimpleITKLIB})


include_directories(BEFORE ${R_INCLUDE_DIR} ${RCPP_DIR} "../inst/include")
add_library(SimpleITKCxx SHARED test.cpp)
target_link_libraries(SimpleITKCxx RSimpleITK ${SimpleITK_LIBRARIES} R)
if(APPLE)
  SET_TARGET_PROPERTIES(SimpleITKCxx PROPERTIES LINK_FLAGS "-undefined dynamic_lookup")
  set_property(TARGET SimpleITKCxx PROPERTY OUTPUT_NAME "SimpleITKCxx.so")
  set_property(TARGET SimpleITKCxx PROPERTY SUFFIX "")
endif()
SET_TARGET_PROPERTIES(SimpleITKCxx PROPERTIES PREFIX "")
