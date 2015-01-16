cmake_minimum_required ( VERSION 2.8.4 )
project ( SuperBuildSimpleITK )

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------

# 
# Global configuration
#

# Add needed flag for gnu on linux like enviroments
if(NOT APPLE AND "${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
  if(NOT "${CMAKE_CXX_FLAGS}" MATCHES "-fPIC")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
  endif()
  if(NOT "${CMAKE_C_FLAGS}" MATCHES "-fPIC")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fPIC")
  endif()
endif()



# Actually run the super build script
set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependancies will be determined during superbuild stage.
include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")


