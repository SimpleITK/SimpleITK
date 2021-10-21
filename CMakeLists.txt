cmake_minimum_required ( VERSION 3.10 FATAL_ERROR )

# Explicitly add INCREMENTAL linking option to command lines.
# http://www.cmake.org/pipermail/cmake/2010-February/035174.html
SET(MSVC_INCREMENTAL_DEFAULT ON)

project ( SimpleITK )

cmake_policy( VERSION 3.10 )

foreach(p
    )
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# Include extra CMake files
list(INSERT CMAKE_MODULE_PATH 0 "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

#-----------------------------------------------------------------------------
# Version information
include(Version.cmake)

set(SimpleITK_VERSION "${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")
if(DEFINED SimpleITK_VERSION_PATCH)
  set(SimpleITK_VERSION "${SimpleITK_VERSION}.${SimpleITK_VERSION_PATCH}")
  if(DEFINED SimpleITK_VERSION_TWEAK)
    set(SimpleITK_VERSION "${SimpleITK_VERSION}.${SimpleITK_VERSION_TWEAK}")
  endif()
endif()

if(DEFINED SimpleITK_VERSION_RC)
  set(SimpleITK_VERSION "${SimpleITK_VERSION}${SimpleITK_VERSION_RC}")
endif()
if(DEFINED SimpleITK_VERSION_POST)
  set(SimpleITK_VERSION "${SimpleITK_VERSION}.post${SimpleITK_VERSION_POST}")
elseif(DEFINED SimpleITK_VERSION_DEV)
  set(SimpleITK_VERSION "${SimpleITK_VERSION}.dev${SimpleITK_VERSION_DEV}")
endif()

option( SimpleITK_BUILD_DISTRIBUTE "Remove '-g#####' from version. ( for official distribution only )" OFF )
mark_as_advanced( SimpleITK_BUILD_DISTRIBUTE )
if( NOT SimpleITK_BUILD_DISTRIBUTE )
  set(SimpleITK_VERSION "${SimpleITK_VERSION}-g${SimpleITK_VERSION_HASH}")
endif()

message(STATUS "Building SimpleITK version \"${SimpleITK_VERSION}\"")


#-----------------------------------------------------------
# Check and set required flags for compilation
# This must be done before any other try compiles based tests are
# done.
include(sitkCheckRequiredFlags)
include(sitkCompilerWarningsSettings)

include( sitkSITKLegacyNaming )
include( sitkForbidDownloadsOption )
include( sitkTargetUseITK )

find_package(ITK REQUIRED )
#we require certain packages be turned on in ITK
include(sitkCheckForITKModuleDependencies)

if(ITK_FOUND)

  # NOTE: We are purposely not calling UseITK yet. However, we must make
  # sure the requred compilation and linker flags are set. Since, we
  # are trying to encapsulate ITK, we need to very carefully control
  # in access to the headers and libraries, hence each SimpleITK
  # library will call UseITK.

  # Add compiler flags needed to use ITK.
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${ITK_REQUIRED_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${ITK_REQUIRED_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${ITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} ${ITK_REQUIRED_LINK_FLAGS}")
  set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} ${ITK_REQUIRED_LINK_FLAGS}")

  link_directories( "${ITK_LIBRARY_DIRS}")


endif()


list(APPEND SimpleITK_PRIVATE_COMPILE_OPTIONS ${CXX_ADDITIONAL_WARNING_FLAGS})

#----------------------------------------------------------
# Place all options to go into sitkConfigure.h here
option(BUILD_SHARED_LIBS "Build SimpleITK ITK with shared libraries. This does not effect wrapped languages." OFF)
set(SITK_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

set(SimpleITK_EXPLICIT_INSTATIATION_DEFAULT OFF)
if(MSCV)
  set(SimpleITK_EXPLICIT_INSTATIATION_DEFAULT ON)
endif()
option(SimpleITK_EXPLICIT_INSTANTIATION "Enable an ITK static library of explicitly instantiated templates." ${SimpleITK_EXPLICIT_INSTATIATION_DEFAULT})
sitk_legacy_naming(SimpleITK_EXPLICIT_INSTANTIATION)

if ( MSVC AND SITK_BUILD_SHARED_LIBS )
  set( SITK_SimpleITKExplit_STATIC 1 )
endif()

set( SimpleITK_INT64_PIXELIDS_DEFAULT ON )
if( MSVC )
  # See http://www.cmake.org/cmake/help/v2.8.10/cmake.html#variable:MSVC_VERSION
  # and https://en.wikipedia.org/wiki/Microsoft_Visual_Studio#Version_history
  #   1500 = VS  9.0 (Visual Studio 2008)
  #   1600 = VS 10.0 (Visual Studio 2010)
  #   1700 = VS 11.0 (Visual Studio 2012)
  if(MSVC_VERSION VERSION_LESS 1600)
    # with this option on the linker runs out of memory
    set( SimpleITK_INT64_PIXELIDS_DEFAULT OFF )
  endif()
endif()
option( SimpleITK_INT64_PIXELIDS "Instantiate 64-bit integer pixels, including unsigned, vector and label maps."
  ${SimpleITK_INT64_PIXELIDS_DEFAULT} )
sitk_legacy_naming(SimpleITK_INT64_PIXELIDS)

include(sitkMaxDimensionOption)

# Setup build locations.
if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/bin)
endif()
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()
if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/lib)
endif()

set ( SimpleITK_INCLUDE_DIRS
      ${CMAKE_SOURCE_DIR}/Code/Common/include
      ${CMAKE_SOURCE_DIR}/Code/Registration/include
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include
      ${CMAKE_SOURCE_DIR}/Code/IO/include
      ${CMAKE_BINARY_DIR}/Code/BasicFilters/include
      ${CMAKE_BINARY_DIR}/Code/Common/include
      )

set ( SimpleITK_LIBRARIES SimpleITKCommon SimpleITKIO SimpleITKRegistration )

if (SimpleITK_EXPLICIT_INSTANTIATION)
  list ( APPEND SimpleITK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Code/Explicit/include )
  # This library is linked privately to SimpleITK libraries and is not
  # part of the public link interface
  #list ( APPEND SimpleITK_LIBRARIES  SimpleITKExplicit )
endif()

set( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES}  CACHE INTERNAL "" )

# Be sure to clear these each time
set ( GENERATED_TEST_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_TEST_SOURCE_LIST "" CACHE INTERNAL "" )

# Create cached list of all template components
file( GLOB template_components
      ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/Components/[^.]*.h.in
      ${SimpleITK_SOURCE_DIR}/ExpandTemplateGenerator/Components/[^.]*.cxx.in
    )
set ( template_components ${template_components} CACHE INTERNAL "" )


#------------------------------------------------------------------------------
# Variables for use in install rules:

if(NOT SimpleITK_INSTALL_RUNTIME_DIR)
  set(SimpleITK_INSTALL_RUNTIME_DIR "bin")
endif()
if(NOT SimpleITK_INSTALL_LIBRARY_DIR)
  set(SimpleITK_INSTALL_LIBRARY_DIR "lib")
endif()
if(NOT SimpleITK_INSTALL_ARCHIVE_DIR)
  set(SimpleITK_INSTALL_ARCHIVE_DIR "lib")
endif()
if(NOT SimpleITK_INSTALL_INCLUDE_DIR)
  set(SimpleITK_INSTALL_INCLUDE_DIR "include/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")
endif()
if(NOT SimpleITK_INSTALL_DOC_DIR)
  set(SimpleITK_INSTALL_DOC_DIR share/doc/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR})
endif()
if(NOT SimpleITK_INSTALL_PACKAGE_DIR)
  set(SimpleITK_INSTALL_PACKAGE_DIR "${SimpleITK_INSTALL_LIBRARY_DIR}/cmake/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")
endif()

function(sitk_install_exported_target tgt)
  # Remove the build tree's SimpleITKTargets file if this is the first call:
  get_property(first_time GLOBAL PROPERTY SimpleITK_FIRST_EXPORTED_TARGET)
  if(NOT first_time)
    file(REMOVE ${CMAKE_BINARY_DIR}/SimpleITKTargets.cmake)
    set_property(GLOBAL PROPERTY SimpleITK_FIRST_EXPORTED_TARGET 1)
  endif()

  get_target_property( type ${tgt} TYPE )
  if (type STREQUAL "STATIC_LIBRARY" OR
      type STREQUAL "MODULE_LIBRARY" OR
      type STREQUAL "SHARED_LIBRARY")
    set_property(TARGET ${tgt} PROPERTY VERSION 1)
    set_property(TARGET ${tgt} PROPERTY SOVERSION 1)
    set_property(TARGET ${tgt} PROPERTY
      OUTPUT_NAME ${tgt}-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR})
  endif()

  export(TARGETS ${tgt}
    APPEND FILE "${CMAKE_BINARY_DIR}/SimpleITKTargets.cmake"
    )

  install(TARGETS ${tgt}
    EXPORT SimpleITKTargets
    RUNTIME DESTINATION ${SimpleITK_INSTALL_RUNTIME_DIR} COMPONENT Runtime
    LIBRARY DESTINATION ${SimpleITK_INSTALL_LIBRARY_DIR} COMPONENT Runtime
    ARCHIVE DESTINATION ${SimpleITK_INSTALL_ARCHIVE_DIR} COMPONENT Development
    )
endfunction()

include(sitkStripOption)

#------------------------------------------------------------------------------
# These are some system specific compiler options needed to build SimpleITK

include(CheckCXXCompilerFlag)

if( NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE )
  set( CMAKE_POSITION_INDEPENDENT_CODE 1 )
endif()


if( NOT DEFINED CMAKE_C_VISIBILITY_PRESET )
  set(CMAKE_C_VISIBILITY_PRESET hidden)
endif()

if( NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET )
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()

if( NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN )
  set( CMAKE_VISIBILITY_INLINES_HIDDEN 1 )
endif()


#-----------------------------------------------------------
# Place all checks and try compile variable for sitkConfigure.h here

include(CheckIncludeFileCXX)


# check for stdint
# This generates a configuration error if the compiler is not supported
check_include_file_cxx( stdint.h SITK_HAS_STDINT_H )
if(NOT SITK_HAS_STDINT_H)
  message(FATAL_ERROR "Unable to find require \"stdint.h\" header file.")
endif()

#------------------------------------------------------------------------------
# assemble a list of important documentation from Simple ITK and ITK

set ( SimpleITK_DOC_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
  "${CMAKE_CURRENT_SOURCE_DIR}/NOTICE"
  "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md"
  )

# add important files from ITK

# if using from build tree then ITK_USE_FILE will be
# ITK_SOURCE_DIR/CMake/UseITK.cmake. The needed docs should be in the
# root of the source tree
get_filename_component( _itk_root "${ITK_USE_FILE}" PATH )
get_filename_component( _itk_root "${_itk_root}" PATH )

set(_itk_doc_search_paths "${_itk_root}")

get_filename_component( _itk_root "${_itk_root}" PATH )
get_filename_component( _itk_root "${_itk_root}" PATH )
list( APPEND _itk_doc_search_paths
   "${_itk_root}/share/doc/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}"
   "${_itk_root}/share/doc/ITK"
)


#
# Only append file if it exists
#
function(append_if_exists list_var file)
   if( EXISTS ${file} )
     list( APPEND ${list_var} ${file} )
     set( ${list_var} ${${list_var}} PARENT_SCOPE )
   endif()
endfunction()

foreach( _p IN LISTS _itk_doc_search_paths)
  if( EXISTS "${_p}/NOTICE" )
    append_if_exists(ITK_DOC_FILES "${_p}/NOTICE")
    append_if_exists(ITK_DOC_FILES "${_p}/README.txt")
    append_if_exists(ITK_DOC_FILES "${_p}/README.md")
    break()
  endif()
endforeach()

if( NOT ITK_DOC_FILES )
  message( WARNING "Unable to file ITK's NOTICE File!\n This file will not be included in SimpleITK packaging!" )
endif()


foreach(_f IN LISTS ITK_DOC_FILES)
  get_filename_component( _name "${_f}" NAME )
  set( _o "${CMAKE_CURRENT_BINARY_DIR}/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}-${_name}" )
  configure_file( "${_f}"  "${_o}" )
  list( APPEND SimpleITK_DOC_FILES "${_o}" )
endforeach()

#------------------------------------------------------------------------------
# Set up wrapping.
#
# Use CMake file which present options for wrapped languages, and finds languages as needed
#
include(sitkLanguageOptions)

#------------------------------------------------------------------------------
# Set up Documentation
include(${SimpleITK_SOURCE_DIR}/Utilities/Doxygen/Doxygen.cmake)

#------------------------------------------------------------------------------
# Ensure that development strips have been setup
include(sitkCheckSourceTree)

#-----------------------------------------------------------------------------
if(NOT EXISTS "${SimpleITK_SOURCE_DIR}/.ExternalData/README.rst")
  # This file is always present in version-controlled source trees
  # so we must have been extracted from a source tarball with no
  # data objects needed for testing.  Turn off tests by default
  # since enabling them requires network access or manual data
  # store configuration.
  option(BUILD_TESTING "Build the testing tree." OFF)
endif()

#------------------------------------------------------------------------------
# set things up for testing, this configuration needs to occour before
# we enter the sub-directories
include(CTest)


#------------------------------------------------------------------------------
# Go to subdirectories
add_subdirectory ( Utilities )
add_subdirectory ( Code )
add_subdirectory ( Wrapping )

#------------------------------------------------------------------------------
# ITK uses KWStyle for checking the coding style
include(${SimpleITK_SOURCE_DIR}/Utilities/KWStyle/KWStyle.cmake)

#------------------------------------------------------------------------------
# set things up for testing, if enabled

if ( BUILD_TESTING )

  include( sitkAddTest )

  enable_testing()
  add_subdirectory ( Testing )

  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  configure_file(CMake/CTestCustom.cmake.in CTestCustom.cmake)
endif()

# optional examples directory with testing
option(BUILD_EXAMPLES "Build the Examples directory." ON)

if(BUILD_EXAMPLES)
  add_subdirectory ( Examples )
endif()


#------------------------------------------------------------------------------
# Configure SimpleITKConfig.cmake for the build tree.
set(SimpleITKConfig_TREE "build")
set(SimpleITKConfig_CODE "")
set(SimpleITKConfig_INCLUDE_DIRS ${SimpleITK_INCLUDE_DIRS})

configure_file(SimpleITKConfig.cmake.in
               SimpleITKConfig.cmake @ONLY IMMEDIATE)

#------------------------------------------------------------------------------
# Configure SimpleITKConfig.cmake for the install tree.
set(SimpleITKConfig_TREE "install")

set(SimpleITKConfig_CODE "set(SimpleITK_INSTALL_PREFIX \"\${_SimpleITKConfig_DIR}\")")
# Construct the proper number of get_filename_component(... PATH)
# calls to compute the installation prefix.
string(REGEX REPLACE "/" ";" _count "${SimpleITK_INSTALL_PACKAGE_DIR}")
foreach(p ${_count})
  set(SimpleITKConfig_CODE "${SimpleITKConfig_CODE}
get_filename_component(SimpleITK_INSTALL_PREFIX \"\${SimpleITK_INSTALL_PREFIX}\" PATH)")
endforeach(p)
set(SimpleITKConfig_CODE "${SimpleITKConfig_CODE}\n")

set(SimpleITKConfig_INCLUDE_DIRS
  "\${SimpleITK_INSTALL_PREFIX}/${SimpleITK_INSTALL_INCLUDE_DIR}")

configure_file(SimpleITKConfig.cmake.in
               CMakeFiles/SimpleITKConfig.cmake @ONLY IMMEDIATE)

#------------------------------------------------------------------------------
# Help other projects use SimpleITK
configure_file(UseSimpleITK.cmake.in
               UseSimpleITK.cmake COPYONLY IMMEDIATE)

configure_file(SimpleITKConfigVersion.cmake.in
               SimpleITKConfigVersion.cmake @ONLY IMMEDIATE)


#------------------------------------------------------------------------------
# INSTALLATION

install(FILES ${SimpleITK_BINARY_DIR}/CMakeFiles/SimpleITKConfig.cmake
              ${SimpleITK_BINARY_DIR}/SimpleITKConfigVersion.cmake
              ${SimpleITK_BINARY_DIR}/UseSimpleITK.cmake
  DESTINATION ${SimpleITK_INSTALL_PACKAGE_DIR}
  COMPONENT Development)

install(EXPORT SimpleITKTargets
  DESTINATION ${SimpleITK_INSTALL_PACKAGE_DIR}
  COMPONENT Development)

file( GLOB __files
  ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include/[^.]*.h
  ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include/[^.]*.hxx
  ${CMAKE_SOURCE_DIR}/Code/Common/include/[^.]*.h
  ${CMAKE_SOURCE_DIR}/Code/Common/include/[^.]*.hxx
  ${CMAKE_SOURCE_DIR}/Code/IO/include/[^.]*.h
  ${CMAKE_SOURCE_DIR}/Code/IO/include/[^.]*.hxx
  ${CMAKE_SOURCE_DIR}/Code/Registration/include/[^.]*.h
  ${CMAKE_SOURCE_DIR}/Code/Registration/include/[^.]*.hxx
  )

install(FILES ${__files}
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development)

install(
  DIRECTORY
    ${CMAKE_SOURCE_DIR}/Code/Common/include/Ancillary
  DESTINATION
    ${SimpleITK_INSTALL_INCLUDE_DIR}/
  COMPONENT Development
  FILES_MATCHING PATTERN "*.h"
)

install(FILES ${SimpleITK_DOC_FILES} DESTINATION "${SimpleITK_INSTALL_DOC_DIR}" COMPONENT Runtime)


#------------------------------------------------------------------------------
# CPack

set(CPACK_SOURCE_IGNORE_FILES  "${ITK_MODULES_DISABLED_CPACK};/\\\\.git")
set(CPACK_PACKAGE_VERSION_MAJOR "${SimpleITK_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SimpleITK_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${SimpleITK_VERSION_PATCH}")


include( CPack )

if(BUILD_TESTING)
  if(COMMAND ExternalData_Add_Target )
    ExternalData_Add_Target( SimpleITKData )
  endif()
endif()
