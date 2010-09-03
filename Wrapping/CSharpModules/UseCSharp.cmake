#
# A CMake Module for finding and using C# (.NET and Mono).
#
# The following variables are set:
#   CSHARP_TYPE - the type of the C# compiler (eg. ".NET" or "Mono")
#   CSHARP_COMPILER - the path to the C# compiler executable (eg. "C:/Windows/Microsoft.NET/Framework/v4.0.30319/csc.exe")
#   CSHARP_VERSION - the version number of the C# compiler (eg. "v4.0.30319")
#
# The following macros are defined:
#   CSHARP_ADD_EXECUTABLE( name references [files] [output_dir] ) - Define C# executable with the given name
#   CSHARP_ADD_LIBRARY( name references [files] [output_dir] ) - Define C# library with the given name
#
# Examples:
#   CSHARP_ADD_EXECUTABLE( MyExecutable "" "Program.cs" )
#   CSHARP_ADD_EXECUTABLE( MyExecutable "ref1.dll ref2.dll" "Program.cs File1.cs" )
#   CSHARP_ADD_EXECUTABLE( MyExecutable "ref1.dll;ref2.dll" "Program.cs;File1.cs" )
#
# This file is based on the work of GDCM:
#   http://gdcm.svn.sf.net/viewvc/gdcm/trunk/CMake/UseCSharp.cmake
# Copyright (c) 2006-2010 Mathieu Malaterre <mathieu.malaterre@gmail.com>
#

# TODO: ADD SUPPORT FOR LINK LIBRARIES

# Check something was found
if( NOT CSHARP_COMPILER )
  message( WARNING "A C# compiler executable was not found on your system" )
endif( NOT CSHARP_COMPILER )

# Include type-based USE_FILE
if( CSHARP_TYPE MATCHES ".NET" )
  include( ${DotNetFrameworkSdk_USE_FILE} )
endif ( CSHARP_TYPE MATCHES ".NET" )

macro( CSHARP_ADD_LIBRARY name )
  CSHARP_ADD_PROJECT( "library" ${name} ${ARGN} )
endmacro( CSHARP_ADD_LIBRARY )

macro( CSHARP_ADD_EXECUTABLE name )
  CSHARP_ADD_PROJECT( "exe" ${name} ${ARGN} )
endmacro( CSHARP_ADD_EXECUTABLE )

# Private macro
macro( CSHARP_ADD_PROJECT type name )
  set( refs "System.dll" )
  set( sources )
  set( sources_dep )
  if( ${type} MATCHES "library" )
    set( output "dll" )
  elseif( ${type} MATCHES "exe" )
    set( output "exe" )
  endif( ${type} MATCHES "library" )
  
  foreach( it ${ARGN} )
    if( ${it} MATCHES "(.*)(dll)" )
       set( refs "${refs};${it}" )
    else( ${it} MATCHES "(.*)(dll)" )
      if( EXISTS ${it} )
        set( sources "${it} ${sources}" )
        set( sources_dep ${it} ${sources_dep} )
      else( EXISTS ${it} )
        if( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it} )
          set( sources "${CMAKE_CURRENT_SOURCE_DIR}/${it} ${sources}" )
          set( sources_dep ${CMAKE_CURRENT_SOURCE_DIR}/${it} ${sources_dep} )
        else( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it} )
          set( sources "${it} ${sources}" )
        endif( EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${it} )
      endif( EXISTS ${it} )
    endif ( ${it} MATCHES "(.*)(dll)" )
  endforeach( it )
  
  string( REPLACE "/" "\\" sources ${sources} )
  separate_arguments( sources )

  add_custom_command(
    OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/${name}.${output}
    COMMAND ${CSHARP_COMPILER}
    ARGS "/t:${type}" "/out:${name}.${output}" "/reference:${refs}" ${sources}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS "${sources_dep}"
    COMMENT "Compiling C# ${type} ${name}"
  )
  add_custom_target( ${name} ALL
    DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${name}.${output}
  )
endmacro( CSHARP_ADD_PROJECT )
