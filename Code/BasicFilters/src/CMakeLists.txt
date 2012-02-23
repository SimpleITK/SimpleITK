# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/../include
 ${CMAKE_CURRENT_BINARY_DIR}/../include
 )


set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

# Glob non-generated BasicFilters and add to cache
file ( GLOB SimpleITKBasicFiltersSource *.cxx )
list ( APPEND SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} )

# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersSource )
list ( LENGTH SimpleITKBasicFiltersSource _length )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factoried here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER )
include ( ${ITK_USE_FILE} )

# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 50 )
set ( _library_i 0 )
foreach ( _start RANGE 0 ${_length} ${_stride} )

  # compute the end of the range ensuring that the inclusive range
  # [_start, _end] is all valid indecies
  math( EXPR _end "${_start} + ${_stride} - 1" )
  if ( ${_end} VERSION_GREATER ${_length} OR
      ${_end} VERSION_EQUAL ${_length} )
    math( EXPR _end "${_length} - 1" )
  endif()

  # extract out the range into SRC
  set ( SRC "" )
  foreach( _j RANGE ${_start} ${_end} )
    list ( GET SimpleITKBasicFiltersSource ${_j} _v )
    list ( APPEND SRC ${_v} )
  endforeach()

  add_library ( SimpleITKBasicFilters${_library_i} ${SRC} )
  target_link_libraries ( SimpleITKBasicFilters${_library_i} SimpleITKCommon ${ITK_LIBRARIES} )
  add_dependencies ( SimpleITKBasicFilters${_library_i} BasicFiltersSourceCode )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

  math( EXPR _library_i "${_library_i} + 1 " )

endforeach ()


