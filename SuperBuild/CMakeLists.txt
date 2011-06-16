project ( SuperBuildSimpleITK )
cmake_minimum_required ( VERSION 2.8 )

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------
set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependancies will be determined during superbuild stage.
include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")


