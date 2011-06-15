project ( SimpleITK )
cmake_minimum_required ( VERSION 2.8 )

#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
#This CMakeFile is used twice in this build process.  The first time it
#simply delegates to the SuperBuild.cmake for building the external
#dependancies, and the uniinitialized ${CMAKE_PROJECT_NAME}_SUPERBUILD is automatically
#set to ON.  From within the SuperBuild.cmake, this cmake file is
#again called, but as an "ExternalPackage", and ${CMAKE_PROJECT_NAME}_SUPERBUILD
#explicitly set to OFF.
#-----------------------------------------------------------------------------
# Superbuild Option - Enabled by default
#-----------------------------------------------------------------------------
option(${CMAKE_PROJECT_NAME}_SUPERBUILD "Build SimpleITK and the projects it depends on via SuperBuild.cmake." ON)
mark_as_advanced(${CMAKE_PROJECT_NAME}_SUPERBUILD)

#-----------------------------------------------------------------------------
# Superbuild script
#-----------------------------------------------------------------------------
if(${CMAKE_PROJECT_NAME}_SUPERBUILD)
  set(${CMAKE_PROJECT_NAME}_DEPENDENCIES "") #Dependancies will be determined during superbuild stage.
  include("${CMAKE_CURRENT_SOURCE_DIR}/SuperBuild.cmake")
  RETURN()
else()
  include("${CMAKE_CURRENT_SOURCE_DIR}/SimpleITK.cmake")
endif()
#!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
