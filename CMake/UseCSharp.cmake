#
# A CMake Module for finding and using C# (.NET and Mono).
#
# The following global variables are assumed to exist: CSHARP_SOURCE_DIRECTORY - path to C# sources
# CSHARP_BINARY_DIRECTORY - path to place resultant C# binary files
#
# The following variables are set: CSHARP_TYPE - the type of the C# compiler (eg. ".NET" or "Mono") CSHARP_COMPILER -
# the path to the C# compiler executable (eg. "C:/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe") CSHARP_VERSION -
# the version number of the C# compiler (eg. "v4.0.30319")
#
# The following macros are defined: CSHARP_ADD_EXECUTABLE( name references [files] [output_dir] ) - Define C# executable
# with the given name CSHARP_ADD_LIBRARY( name references [files] [output_dir] ) - Define C# library with the given name
#
# Examples: CSHARP_ADD_EXECUTABLE( MyExecutable "" "Program.cs" ) CSHARP_ADD_EXECUTABLE( MyExecutable "ref1.dll
# ref2.dll" "Program.cs File1.cs" ) CSHARP_ADD_EXECUTABLE( MyExecutable "ref1.dll;ref2.dll" "Program.cs;File1.cs" )
#
# This file is based on the work of GDCM: http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/UseCSharp.cmake Copyright (c)
# 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

# TODO: ADD SUPPORT FOR LINK LIBRARIES

# Check something was found
if(NOT CSHARP_COMPILER)
  message(WARNING "A C# compiler executable was not found on your system")
endif(NOT CSHARP_COMPILER)

# Include type-based USE_FILE
if(CSHARP_TYPE MATCHES ".NET")
  include(${DotNetFrameworkSdk_USE_FILE})
elseif(CSHARP_TYPE MATCHES "Mono")
  include(${Mono_USE_FILE})
endif(CSHARP_TYPE MATCHES ".NET")

macro(CSHARP_ADD_LIBRARY name)
  csharp_add_project("library" ${name} ${ARGN})
endmacro(CSHARP_ADD_LIBRARY)

macro(CSHARP_ADD_EXECUTABLE name)
  csharp_add_project("exe" ${name} ${ARGN})
endmacro(CSHARP_ADD_EXECUTABLE)

# Private macro
macro(CSHARP_ADD_PROJECT type name)
  set(refs "/reference:System.dll")
  set(sources)
  set(sources_dep)

  if(${type} MATCHES "library")
    set(output "dll")
  elseif(${type} MATCHES "exe")
    set(output "exe")
  endif(${type} MATCHES "library")

  # Step through each argument
  foreach(it ${ARGN})
    if(${it} MATCHES "(.*)(dll)")
      # Argument is a dll, add reference
      list(APPEND refs /reference:${it})
    else()
      # Argument is a source file
      if(EXISTS ${it})
        list(APPEND sources ${it})
        list(APPEND sources_dep ${it})
      elseif(EXISTS ${CSHARP_SOURCE_DIRECTORY}/${it})
        list(APPEND sources ${CSHARP_SOURCE_DIRECTORY}/${it})
        list(APPEND sources_dep ${CSHARP_SOURCE_DIRECTORY}/${it})
      elseif(${it} MATCHES "[*]")
        # For dependencies, we need to expand wildcards
        file(GLOB it_glob ${it})
        list(APPEND sources ${it})
        list(APPEND sources_dep ${it_glob})
      elseif(IS_ABSOLUTE ${it})
        list(APPEND sources ${it})
        list(APPEND sources_dep ${it})
      endif()
    endif()
  endforeach()

  # Check we have at least one source
  list(LENGTH sources_dep sources_length)
  if(${sources_length} LESS 1)
    message(SEND_ERROR "No C# sources were specified for ${type} ${name}")
  endif()
  list(SORT sources_dep)

  # Perform platform specific actions
  if(WIN32)
    string(
      REPLACE "/"
              "\\"
              sources
              ${sources})
  else(UNIX)
    string(
      REPLACE "\\"
              "/"
              sources
              ${sources})
  endif(WIN32)

  # Add custom target and command MESSAGE( STATUS "Adding C# ${type} ${name}: '${CSHARP_COMPILER} /t:${type}
  # /out:${name}.${output} /platform:${CSHARP_PLATFORM} ${CSHARP_SDK} ${refs} ${sources}'" )
  add_custom_command(
    COMMENT
      "Compiling C# ${type} ${name}: '${CSHARP_COMPILER} /t:${type} /out:${name}.${output} /platform:${CSHARP_PLATFORM} ${CSHARP_SDK} ${refs} ${sources}'"
    OUTPUT ${CSHARP_BINARY_DIRECTORY}/${name}.${output}
    COMMAND ${CSHARP_COMPILER} ARGS /t:${type} /out:${name}.${output} /platform:${CSHARP_PLATFORM} ${CSHARP_SDK} ${refs}
            ${sources}
    WORKING_DIRECTORY ${CSHARP_BINARY_DIRECTORY}
    DEPENDS ${sources_dep})
  add_custom_target(
    ${name} ALL
    DEPENDS ${CSHARP_BINARY_DIRECTORY}/${name}.${output}
    SOURCES ${sources_dep})
endmacro(CSHARP_ADD_PROJECT)
