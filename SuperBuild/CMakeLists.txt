
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

cmake_minimum_required ( VERSION 3.10 )
project ( SuperBuildSimpleITK )
cmake_policy( VERSION 3.10 )


#-----------------------------------------------------------------------------
# CMAKE_CXX_COMPILER_ARG1 is a CMake internal variable. It should not be
# used in SimpleITK Superbuild's configuration as it will not get
# correctly propagated to external projects. If it is set, it most
# likely means that SimpleITK is to be built with a launcher such as
# ccache or distcc. This should be done with the CMake variable
# CMAKE_CXX_COMPILER_LAUNCHER_FLAG available in CMake > 3.4.0 .
if(CMAKE_CXX_COMPILER_ARG1)
  message(WARNING "The CMake variable CMAKE_CXX_COMPILER_ARG1 is\
set. The CMake variable CMAKE_CXX_COMPILER_LAUNCHER_FLAG should be used
instead (CMake>=3.4 required).")
endif()

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------

# Actually run the super build script
set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependancies will be determined during superbuild stage.
include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")


