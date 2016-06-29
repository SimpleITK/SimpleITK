
#-----------------------------------------------------------------------------
# Override defaults set in initial "project" call, allow user to
# override from command line
#-----------------------------------------------------------------------------


# SimpleITK Addition: install to the common library
# directory, so that all libs/include etc ends up
# in one common tree
if( NOT DEFINED CMAKE_INSTALL_PREFIX )
  set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_BINARY_DIR} CACHE PATH "Where all the prerequisite libraries go")
endif()

cmake_minimum_required ( VERSION 3.0 )
project ( SuperBuildSimpleITK )

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------

# Actually run the super build script
set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependancies will be determined during superbuild stage.
include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")


