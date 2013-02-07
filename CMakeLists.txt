cmake_minimum_required ( VERSION 2.8.1 FATAL_ERROR )

# Explicitly add INCREMENTAL linking option to command lines.
# http://www.cmake.org/pipermail/cmake/2010-February/035174.html
SET(MSVC_INCREMENTAL_DEFAULT ON)

project ( SimpleITK )

cmake_policy( VERSION 2.8.1 )

# Include extra CMake files
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/CMake")


find_package(ITK REQUIRED ) # the modules needed can be listed here as required components
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

if( NOT ITK_USE_REVIEW )
# TODO need to check ITK configuration to verify that it has the needed modules
#  message(FATAL_ERROR "Please reconfigure ITK by turning ITK_USE_REVIEW ON")
endif()

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
      ${CMAKE_SOURCE_DIR}/Code/Registration
      ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include
      ${CMAKE_SOURCE_DIR}/Code/IO/include
      ${CMAKE_BINARY_DIR}/Code/BasicFilters/include
      ${CMAKE_BINARY_DIR}/Code/Common/include
      )

set ( SimpleITK_LIBRARIES SimpleITKCommon SimpleITKIO CACHE INTERNAL "" )

# Be sure to clear these each time
set ( GENERATED_TEST_LIST "" CACHE INTERNAL "" )
set ( GENERATED_FILTER_LIST "" CACHE INTERNAL "" )
set ( GENERATED_TEST_SOURCE_LIST "" CACHE INTERNAL "" )

#----------------------------------------------------------
# Place all options to go into sitkConfigure.h here

# Setting this option will shorten compile times by reducing the
# amount of pixel types and generated code.
# NB: this option should _NOT_ be used for releases!
option ( SITK_EXPRESS_INSTANTIATEDPIXELS "Instantiate very few pixel types ( for use for development only )" OFF )
mark_as_advanced ( SITK_EXPRESS_INSTANTIATEDPIXELS )


#-----------------------------------------------------------------------------
# SimpleITK build configuration options.
option(BUILD_SHARED_LIBS "Build SimpleITK ITK with shared libraries. This does not effect wrapped languages." OFF)
set(SITK_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})


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

if( NOT SimpleITK_BUILD_DISTRIBUTE )
  set(SimpleITK_VERSION "${SimpleITK_VERSION}-g${SimpleITK_VERSION_HASH}")
endif()

message(STATUS "Building SimpleITK version \"${SimpleITK_VERSION}\"")

set(JAR_FILE "simpleitk-${SimpleITK_VERSION}.jar")
set(JAVADOC_FILE "simpleitk-javadoc-${SimpleITK_VERSION}.jar")
set(JAVA_SOURCE_FILE "simpleitk-source-${SimpleITK_VERSION}.jar")


# Create cached list of all template components
file( GLOB template_components
      ${SimpleITK_SOURCE_DIR}/TemplateComponents/*.h.in
      ${SimpleITK_SOURCE_DIR}/TemplateComponents/*.cxx.in
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
  set(SimpleITK_INSTALL_PACKAGE_DIR "lib/cmake/SimpleITK-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR}")
endif()

function(sitk_install_exported_target tgt)
  # Remove the build tree's SimpleITKTargets file if this is the first call:
  get_property(first_time GLOBAL PROPERTY SimpleITK_FIRST_EXPORTED_TARGET)
  if(NOT first_time)
    file(REMOVE ${CMAKE_BINARY_DIR}/SimpleITKTargets.cmake)
    set_property(GLOBAL PROPERTY SimpleITK_FIRST_EXPORTED_TARGET 1)
  endif()

  set_property(TARGET ${tgt} PROPERTY VERSION 1)
  set_property(TARGET ${tgt} PROPERTY SOVERSION 1)
  set_property(TARGET ${tgt} PROPERTY
    OUTPUT_NAME ${tgt}-${SimpleITK_VERSION_MAJOR}.${SimpleITK_VERSION_MINOR})

  export(TARGETS ${tgt}
    APPEND FILE "${CMAKE_BINARY_DIR}/SimpleITKTargets.cmake"
    )

  install(TARGETS ${tgt}
    EXPORT SimpleITKTargets
    RUNTIME DESTINATION ${SimpleITK_INSTALL_RUNTIME_DIR}
    LIBRARY DESTINATION ${SimpleITK_INSTALL_LIBRARY_DIR}
    ARCHIVE DESTINATION ${SimpleITK_INSTALL_ARCHIVE_DIR}
    )
endfunction()


#------------------------------------------------------------------------------
# These are some system specific compiler options needed to build SimpleITK

if(MSVC)
  # /bigobj is required for windows builds because of the size of
  # some object files (CastImage for instance)
  # Also supress the pesky warning about std::vector not being marked
  # for export in the dll
  set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /bigobj /wd4251" )
  set ( CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /bigobj" )

  # Avoid some warnings
  add_definitions ( -D_SCL_SECURE_NO_WARNINGS )


  # force debug linking not to be incremental
  foreach( _varName
      CMAKE_EXE_LINKER_FLAGS_DEBUG
      CMAKE_EXE_LINKER_FLAGS_RELWITHDEBINFO )
    STRING(REGEX REPLACE "INCREMENTAL(:[a-zA-Z]+)?" "INCREMENTAL:NO" ${_varName} ${${_varName}})
  endforeach()

endif()


include(CheckCXXCompilerFlag)

# The fPIC flags is used to create position independent code. It is
# required on some systems to produce shared libraries. On Apple
# systems the flag has no effect as it is the default. On other
# platforms, this flag may enable libraries to be better shared
# between processes. Therefore, if the compiler supports it, we will
# use it.
check_cxx_compiler_flag( "-fPIC" CXX_HAS_fPIC )
if( CXX_HAS_fPIC )
  if(NOT "${CMAKE_CXX_FLAGS}" MATCHES "-fPIC")
    set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC" )
  endif()
endif( )



#-----------------------------------------------------------
# Place all checks and try compile variable for sitkConfigure.h here

# check for C++0x static_assert
try_compile(SITK_SUPPORTS_STATIC_ASSERT
  ${SimpleITK_BINARY_DIR}/CMakeTmp
  ${SimpleITK_SOURCE_DIR}/CMake/static_assert.cxx )


include(CheckIncludeFileCXX)

# check for the required tr1/functional header
check_include_file_cxx( tr1/functional SITK_HAS_STLTR1_TR1_FUNCTIONAL )
check_include_file_cxx( functional SITK_HAS_STLTR1_FUNCTIONAL )

# check for the required tr1/type_traits header
check_include_file_cxx( tr1/type_traits SITK_HAS_STLTR1_TR1_TYPE_TRAITS )
check_include_file_cxx( type_traits SITK_HAS_STLTR1_TYPE_TRAITS )

if ( NOT SITK_HAS_STLTR1_TR1_FUNCTIONAL AND NOT SITK_HAS_STLTR1_FUNCTIONAL )
  message( FATAL_ERROR
    "SimpleITK requires usage of parts C++ Technical Report 1 (TR1).\n"
    "It may be available as an optional download for your compiler. Please see the FAQ for details.\n"
    "http://www.itk.org/Wiki/ITK_Release_4/SimpleITK/FAQ#Do_I_need_to_download_an_option_package_for_TR1_support.3F")
endif ( )

# check for the optional tr1/unordered_map header
check_include_file_cxx( tr1/unordered_map SITK_HAS_STLTR1_TR1_UNORDERED_MAP )
check_include_file_cxx( unordered_map SITK_HAS_STLTR1_UNORDERED_MAP )
if ( ${SITK_HAS_STLTR1_UNORDERED_MAP} )
  set( SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS "-DSITK_HAS_STLTR1_UNORDERED_MAP")
elseif ( ${SITK_HAS_STLTR1_TR1_UNORDERED_MAP} )
  set( SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS "-DSITK_HAS_STLTR1_TR1_UNORDERED_MAP" )
endif()
try_compile(SITK_UNORDERED_MAP_FUNCTIONAL
  ${SimpleITK_BINARY_DIR}/CMakeTmp
  ${SimpleITK_SOURCE_DIR}/CMake/tr1_unordered_map.cxx
  COMPILE_DEFINITIONS "${SITK_UNORDERED_MAP_FUNCTIONAL_DEFINITIONS}"
  OUTPUT_VARIABLE out )

# check for stdint
# This generates a configuration error if the compiler is not supported
check_include_file_cxx( stdint.h SITK_HAS_STDINT_H )

if(NOT STDINT_HAVE_STDINT_H)
  if( WIN32 )
    if(MSVC)
      list(APPEND SimpleITK_INCLUDE_DIRS
        "${SimpleITK_SOURCE_DIR}/Utilities/C99")
      add_subdirectory("${SimpleITK_SOURCE_DIR}/Utilities/C99")
    endif()
  endif()
endif()

include_directories( ${SimpleITK_INCLUDE_DIRS} )


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
set( _itk_source_path "${_itk_root}" )

get_filename_component( _itk_root "${_itk_root}" PATH )
get_filename_component( _itk_root "${_itk_root}" PATH )
set( _itk_doc_path "${_itk_root}/share/doc/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}" )

if( EXISTS "${_itk_source_path}/NOTICE" )
  set( ITK_DOC_FILES
    # "${_itk_source_path}/LICENSE" SimpleITK has same license file
    "${_itk_source_path}/NOTICE"
    "${_itk_source_path}/README.txt"
    )
elseif( EXISTS "${_itk_doc_path}/NOTICE" )
  set( ITK_DOC_FILES
    # "${_itk_doc_path}/LICENSE" SimpleITK has same license file
    "${_itk_doc_path}/NOTICE"
    "${_itk_doc_path}/README.txt"
    )
else()
  message( "doc_path: ${_itk_doc_path}" )
  message( WARNING "Unable to file ITK's NOTICE File!\n This file will not be included in SimpleITK packaging!" )
endif()


foreach(_f IN LISTS ITK_DOC_FILES)
  get_filename_component( _name "${_f}" NAME )
  set( _o "${CMAKE_CURRENT_BINARY_DIR}/ITK-${ITK_VERSION_MAJOR}.${ITK_VERSION_MINOR}-${_name}" )
  configure_file( "${_f}"  "${_o}" )
  list( APPEND SimpleITK_DOC_FILES "${_o}" )
endforeach()


#------------------------------------------------------------------------------
# Set up Documentation
include(${SimpleITK_SOURCE_DIR}/Utilities/Doxygen/Doxygen.cmake)

#------------------------------------------------------------------------------
# Set up wrapping.
#
# Use CMake file which present options for wrapped languages, and finds languages as needed
#
include(SITKLanguageOptions)

#------------------------------------------------------------------------------
# Ensure that development strips have been setup
include(sitkCheckSourceTree)

#------------------------------------------------------------------------------
# set things up for testing, this configuration needs to occour before
# we enter the sub-directories
include(CTest)

#------------------------------------------------------------------------------
# Go to subdirectories
add_subdirectory ( Utilities )
add_subdirectory ( Code )
add_subdirectory ( Wrapping )
add_subdirectory ( Examples )

#------------------------------------------------------------------------------
# ITK uses KWStyle for checking the coding style
include(${SimpleITK_SOURCE_DIR}/Utilities/KWStyle/KWStyle.cmake)

#------------------------------------------------------------------------------
# set things up for testing, if enabled

if ( BUILD_TESTING )
  enable_testing()
  add_subdirectory ( Testing )
  option ( RUN_LONG_TESTS "Run long tests.  Some tests have been identified as long running, should these be run?" OFF )
  mark_as_advanced(RUN_LONG_TESTS)
  set(BUILDNAME "${BUILDNAME}" CACHE STRING "Name of build on the dashboard")
  configure_file(CMake/CTestCustom.cmake.in CTestCustom.cmake)
endif()

#------------------------------------------------------------------------------
# Options for documentation
option ( BUILD_DOCUMENTS "Build the Documentation subdirectory" OFF )

if ( BUILD_DOCUMENTS )
  add_subdirectory ( Documentation )
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
  ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include/*.h
  ${CMAKE_SOURCE_DIR}/Code/BasicFilters/include/*.hxx
  ${CMAKE_SOURCE_DIR}/Code/Common/include/*.h
  ${CMAKE_SOURCE_DIR}/Code/Common/include/*.hxx
  ${CMAKE_SOURCE_DIR}/Code/IO/include/*.h
  ${CMAKE_SOURCE_DIR}/Code/IO/include/*.hxx
  ${CMAKE_SOURCE_DIR}/Code/Registration/include/*.h
  ${CMAKE_SOURCE_DIR}/Code/Registration/include/*.hxx
  )

set(__files ${__files}
  ${SimpleITKBasicFiltersGeneratedHeader}
  )

install(FILES ${__files}
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development)

file( GLOB __files
  ${CMAKE_SOURCE_DIR}/Code/Common/include/Ancillary/*.h
  )

install(FILES ${__files}
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}/Ancillary
  COMPONENT Development)

install(FILES ${SimpleITK_DOC_FILES} DESTINATION "${SimpleITK_INSTALL_DOC_DIR}" COMPONENT Runtime)


#------------------------------------------------------------------------------
# CPack

set(CPACK_SOURCE_IGNORE_FILES  "${ITK_MODULES_DISABLED_CPACK};/\\\\.git")
set(CPACK_PACKAGE_VERSION_MAJOR "${SimpleITK_Major}")
set(CPACK_PACKAGE_VERSION_MINOR "${SimpleITK_Minor}")
set(CPACK_PACKAGE_VERSION_PATCH "${SimpleITK_Patch}")


include( CPack )
