include("${CMAKE_CURRENT_SOURCE_DIR}/CMake/sitkCMakeInit.cmake")
cmake_minimum_required(
  VERSION ${SITK_CMAKE_MINIMUM_REQUIRED_VERSION}...${SITK_CMAKE_POLICY_VERSION}
)

# Explicitly add INCREMENTAL linking option to command lines.
# http://www.cmake.org/pipermail/cmake/2010-February/035174.html
set(MSVC_INCREMENTAL_DEFAULT ON)

project(SimpleITK)

foreach(
  p
  CMP0156 # De-duplicate libraries on link lines based on linker capabilities.
  CMP0175 # add_custom_command() rejects invalid arguments.
)
  if(POLICY ${p})
    cmake_policy(SET ${p} NEW)
  endif()
endforeach()

# Include extra CMake files
list(PREPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")

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

option(
  SimpleITK_BUILD_DISTRIBUTE
  "Remove '-g#####' from version. ( for official distribution only )"
  OFF
)
mark_as_advanced(SimpleITK_BUILD_DISTRIBUTE)
if(NOT SimpleITK_BUILD_DISTRIBUTE)
  set(SimpleITK_VERSION "${SimpleITK_VERSION}-g${SimpleITK_VERSION_HASH}")
endif()

message(STATUS "Building SimpleITK version \"${SimpleITK_VERSION}\"")

#-----------------------------------------------------------
# Check and set required flags for compilation
# This must be done before any other try compiles based tests are
# done.
include(sitkCheckRequiredFlags)
include(sitkCompilerWarningsSettings)

include(sitkGitProtocol)
include(sitkITKFetchContent)

include(sitkSITKLegacyNaming)
include(sitkForbidDownloadsOption)

# Include GNUInstallDirs for standard installation directories
include(GNUInstallDirs)

find_package(ITK REQUIRED)

#we require certain packages be turned on in ITK
include(sitkCheckForITKModuleDependencies)

option(SimpleITK_USE_ELASTIX "Use the Elastix image registration library" OFF)
if(SimpleITK_USE_ELASTIX)
  include(sitkElastixFetchContent)
endif()
itk_generate_factory_registration(ImageIO TransformIO FFTImageFilterInit)

list(APPEND SimpleITK_PRIVATE_COMPILE_OPTIONS ${CXX_ADDITIONAL_WARNING_FLAGS})

#----------------------------------------------------------
# Place all options to go into sitkConfigure.h here
option(
  BUILD_SHARED_LIBS
  "Build SimpleITK ITK with shared libraries. This does not effect wrapped languages."
  OFF
)
set(SITK_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})

set(SimpleITK_EXPLICIT_INSTATIATION_DEFAULT OFF)
if(MSCV)
  set(SimpleITK_EXPLICIT_INSTATIATION_DEFAULT ON)
endif()
option(
  SimpleITK_EXPLICIT_INSTANTIATION
  "Enable an ITK static library of explicitly instantiated templates."
  ${SimpleITK_EXPLICIT_INSTATIATION_DEFAULT}
)
sitk_legacy_naming(SimpleITK_EXPLICIT_INSTANTIATION)

if(MSVC AND SITK_BUILD_SHARED_LIBS)
  set(SITK_SimpleITKExplit_STATIC 1)
endif()

option(
  SimpleITK_INT64_PIXELIDS
  "Instantiate 64-bit integer pixels, including unsigned, vector and label maps (required for 64-bit compilation and deprecated)."
  ON
)
sitk_legacy_naming(SimpleITK_INT64_PIXELIDS)
if(NOT SimpleITK_INT64_PIXELIDS AND CMAKE_SIZEOF_VOID_P GREATER_EQUAL 8)
  message(
    FATAL_ERROR
    "SimpleITK_INT64_PIXELIDS is required to be enabled for 64-bit compilation."
  )
endif()

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

set(
  SimpleITK_INCLUDE_DIRS
  ${CMAKE_SOURCE_DIR}/Code/Common/include
  ${CMAKE_SOURCE_DIR}/Code/Registration/include
  ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include
  ${CMAKE_SOURCE_DIR}/Code/IO/include
  ${CMAKE_BINARY_DIR}/Code/BasicFilters/include
  ${CMAKE_BINARY_DIR}/Code/Common/include
)

set(
  SimpleITK_LIBRARIES
  SimpleITKCommon
  SimpleITKIO
  SimpleITKRegistration
  CACHE INTERNAL
  ""
)

if(SimpleITK_USE_ELASTIX)
  list(
    APPEND
    SimpleITK_INCLUDE_DIRS
    ${CMAKE_SOURCE_DIR}/Code/ElastixTransformixWrappers/include
  )
  cache_list_append( SimpleITK_LIBRARIES SimpleElastix)
endif()

if(SimpleITK_EXPLICIT_INSTANTIATION)
  list(APPEND SimpleITK_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Code/Explicit/include)
  # This library is linked privately to SimpleITK libraries and is not
  # part of the public link interface
  #list ( APPEND SimpleITK_LIBRARIES  SimpleITKExplicit )
endif()

#------------------------------------------------------------------------------
# Variables for use in install rules:
# Using GNUInstallDirs standard variables with project-specific subdirectories

# Set project-specific installation directories using GNUInstallDirs defaults
set(
  SimpleITK_INSTALL_INCLUDEDIR
  "${CMAKE_INSTALL_INCLUDEDIR}/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}"
  CACHE STRING
  "Include directory for SimpleITK headers"
)

set(
  SimpleITK_INSTALL_DOCDIR
  "${CMAKE_INSTALL_DOCDIR}-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}"
  CACHE STRING
  "Documentation directory for SimpleITK"
)

set(
  SimpleITK_INSTALL_PACKAGEDIR
  "${CMAKE_INSTALL_LIBDIR}/cmake/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}"
  CACHE STRING
  "CMake package files directory for SimpleITK"
)

mark_as_advanced(
  SimpleITK_INSTALL_INCLUDEDIR
  SimpleITK_INSTALL_DOCDIR
  SimpleITK_INSTALL_PACKAGEDIR
)

function(sitk_install_exported_target tgt)
  get_target_property(type ${tgt} TYPE)
  if(type IN_LIST "STATIC_LIBRARY;MODULE_LIBRARY;SHARED_LIBRARY")
    set_property(
      TARGET
        ${tgt}
      PROPERTY
        VERSION
          1
    )
    set_property(
      TARGET
        ${tgt}
      PROPERTY
        SOVERSION
          1
    )
    set_property(
      TARGET
        ${tgt}
      PROPERTY
        OUTPUT_NAME
          ${tgt}-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}
    )
  endif()

  # Exports are used for both build and install tree
  install(
    TARGETS
      ${tgt}
    EXPORT SimpleITKTargets
    RUNTIME
      DESTINATION ${CMAKE_INSTALL_BINDIR}
      COMPONENT Runtime
    LIBRARY
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT Runtime
    ARCHIVE
      DESTINATION ${CMAKE_INSTALL_LIBDIR}
      COMPONENT Development
    FILE_SET HEADERS
      DESTINATION ${SimpleITK_INSTALL_INCLUDEDIR}
      COMPONENT Development
  )
endfunction()

include(sitkStripOption)

#------------------------------------------------------------------------------
# These are some system specific compiler options needed to build SimpleITK

include(CheckCXXCompilerFlag)

if(NOT DEFINED CMAKE_POSITION_INDEPENDENT_CODE)
  set(CMAKE_POSITION_INDEPENDENT_CODE 1)
endif()

if(NOT DEFINED CMAKE_C_VISIBILITY_PRESET)
  set(CMAKE_C_VISIBILITY_PRESET hidden)
endif()

if(NOT DEFINED CMAKE_CXX_VISIBILITY_PRESET)
  set(CMAKE_CXX_VISIBILITY_PRESET hidden)
endif()

if(NOT DEFINED CMAKE_VISIBILITY_INLINES_HIDDEN)
  set(CMAKE_VISIBILITY_INLINES_HIDDEN 1)
endif()

#-----------------------------------------------------------
# Place all checks and try compile variable for sitkConfigure.h here

include(CheckIncludeFileCXX)

# check for stdint
# This generates a configuration error if the compiler is not supported
check_include_file_cxx(
  stdint.h
  SITK_HAS_STDINT_H
)
if(NOT SITK_HAS_STDINT_H)
  message(FATAL_ERROR "Unable to find require \"stdint.h\" header file.")
endif()

#------------------------------------------------------------------------------
# assemble a list of important documentation from Simple ITK and ITK

set(
  SimpleITK_DOC_FILES
  "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE"
  "${CMAKE_CURRENT_SOURCE_DIR}/NOTICE"
  "${CMAKE_CURRENT_SOURCE_DIR}/Readme.md"
)

# add important files from ITK

# if using from build tree then ITK_USE_FILE will be
# ITK_SOURCE_DIR/CMake/UseITK.cmake. The needed docs should be in the
# root of the source tree
get_filename_component(_itk_root "${ITK_USE_FILE}" PATH)
get_filename_component(_itk_root "${_itk_root}" PATH)

set(_itk_doc_search_paths "${_itk_root}")

get_filename_component(_itk_root "${_itk_root}" PATH)
get_filename_component(_itk_root "${_itk_root}" PATH)
list(
  APPEND
  _itk_doc_search_paths
  "${_itk_root}/share/doc/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}"
  "${_itk_root}/share/doc/ITK"
)

#
# Only append file if it exists
#
function(append_if_exists list_var file)
  if(EXISTS ${file})
    list(APPEND ${list_var} ${file})
    set(${list_var} ${${list_var}} PARENT_SCOPE)
  endif()
endfunction()

foreach(_p IN LISTS _itk_doc_search_paths)
  if(EXISTS "${_p}/NOTICE")
    append_if_exists(ITK_DOC_FILES "${_p}/NOTICE")
    append_if_exists(ITK_DOC_FILES "${_p}/README.txt")
    append_if_exists(ITK_DOC_FILES "${_p}/README.md")
    break()
  endif()
endforeach()

if(NOT ITK_DOC_FILES)
  message(
    WARNING
    "Unable to file ITK's NOTICE File!\n This file will not be included in SimpleITK packaging!"
  )
endif()

foreach(_f IN LISTS ITK_DOC_FILES)
  get_filename_component(_name "${_f}" NAME)
  set(
    _o
    "${CMAKE_CURRENT_BINARY_DIR}/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}-${_name}"
  )
  configure_file("${_f}" "${_o}")
  list(APPEND SimpleITK_DOC_FILES "${_o}")
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
add_subdirectory(Code)
add_subdirectory(Wrapping)

#------------------------------------------------------------------------------
# ITK uses KWStyle for checking the coding style
include(${SimpleITK_SOURCE_DIR}/Utilities/KWStyle/KWStyle.cmake)

#------------------------------------------------------------------------------
# set things up for testing, if enabled

if(BUILD_TESTING)
  include(sitkAddTest)

  enable_testing()
  add_subdirectory(Testing)

  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  configure_file(CMake/CTestCustom.cmake.in CTestCustom.cmake)
endif()

# optional examples directory with testing
option(BUILD_EXAMPLES "Build the Examples directory." ON)

if(BUILD_EXAMPLES)
  add_subdirectory(Examples)
endif()

#------------------------------------------------------------------------------
# Configure SimpleITKConfig.cmake for the build tree.
set(SimpleITKConfig_TREE "build")
set(SimpleITKConfig_CODE "")
set(SimpleITKConfig_INCLUDE_DIRS ${SimpleITK_INCLUDE_DIRS})

configure_file(SimpleITKConfig.cmake.in SimpleITKConfig.cmake @ONLY IMMEDIATE)

#------------------------------------------------------------------------------
# Configure SimpleITKConfig.cmake for the install tree.
set(SimpleITKConfig_TREE "install")

set(
  SimpleITKConfig_CODE
  "set(SimpleITK_INSTALL_PREFIX \"\${_SimpleITKConfig_DIR}\")"
)
# Construct the proper number of get_filename_component(... PATH)
# calls to compute the installation prefix.
string(REGEX REPLACE "/" ";" _count "${SimpleITK_INSTALL_PACKAGEDIR}")
foreach(p IN LISTS _count)
  set(
    SimpleITKConfig_CODE
    "${SimpleITKConfig_CODE}
get_filename_component(SimpleITK_INSTALL_PREFIX \"\${SimpleITK_INSTALL_PREFIX}\" PATH)"
  )
endforeach(p)
set(SimpleITKConfig_CODE "${SimpleITKConfig_CODE}\n")

set(
  SimpleITKConfig_INCLUDE_DIRS
  "\${SimpleITK_INSTALL_PREFIX}/${SimpleITK_INSTALL_INCLUDEDIR}"
)

configure_file(
  SimpleITKConfig.cmake.in
  CMakeFiles/SimpleITKConfig.cmake
  @ONLY
  IMMEDIATE
)

#------------------------------------------------------------------------------
# Help other projects use SimpleITK
configure_file(UseSimpleITK.cmake.in UseSimpleITK.cmake COPYONLY IMMEDIATE)

configure_file(
  SimpleITKConfigVersion.cmake.in
  SimpleITKConfigVersion.cmake
  @ONLY
  IMMEDIATE
)

#------------------------------------------------------------------------------
# INSTALLATION

install(
  FILES
    ${SimpleITK_BINARY_DIR}/CMakeFiles/SimpleITKConfig.cmake
    ${SimpleITK_BINARY_DIR}/SimpleITKConfigVersion.cmake
    ${SimpleITK_BINARY_DIR}/UseSimpleITK.cmake
  DESTINATION ${SimpleITK_INSTALL_PACKAGEDIR}
  COMPONENT Development
)

install(
  EXPORT SimpleITKTargets
  DESTINATION ${SimpleITK_INSTALL_PACKAGEDIR}
  COMPONENT Development
)

# Ancillary headers are installed via SimpleITKCommon FILE_SET, no separate install needed

install(
  FILES
    ${SimpleITK_DOC_FILES}
  DESTINATION "${SimpleITK_INSTALL_DOCDIR}"
  COMPONENT Runtime
)

export(
  EXPORT SimpleITKTargets
  FILE "${CMAKE_BINARY_DIR}/SimpleITKTargets.cmake"
)

#------------------------------------------------------------------------------
# CPack

set(CPACK_SOURCE_IGNORE_FILES "${ITK_MODULES_DISABLED_CPACK};/\\\\.git")
set(CPACK_PACKAGE_VERSION_MAJOR "${SimpleITK_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${SimpleITK_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${SimpleITK_VERSION_PATCH}")

include(CPack)

if(BUILD_TESTING)
  if(COMMAND ExternalData_Add_Target)
    ExternalData_Add_Target(SimpleITKData)
  endif()
endif()
