# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}/../include
 ${CMAKE_CURRENT_BINARY_DIR}/../include
 ${CMAKE_CURRENT_SOURCE_DIR}
 )


set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factoried here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include ( ${ITK_USE_FILE} )


set ( SimpleITKBasicFiltersSource
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter.cxx
  sitkHashImageFilter.cxx
  sitkImageFilter.cxx
  sitkJoinSerriesImageFilter.cxx
  sitkComposeImageFilter.cxx
  sitkLabelStatisticsImageFilter.cxx
  sitkMeasurementMap.cxx
  sitkStatisticsImageFilter.cxx
)

add_library ( SimpleITKBasicFilters0 ${SimpleITKBasicFiltersSource} )
target_link_libraries ( SimpleITKBasicFilters0 SimpleITKCommon ${ITK_LIBRARIES} )
sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globaly cached list
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters0 )
set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersGeneratedSource )
set ( SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} )
list ( LENGTH SimpleITKBasicFiltersSource _length )

# The other filters an automatically split into files. They all
# use the following for export their interface. There must not be and
# inter-filter include.
if(BUILD_SHARED_LIBS)
  add_definitions(-DSimpleITKBasicFilters_EXPORTS)
endif()

# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 50 )
set ( _library_i 1 )
foreach ( _start RANGE 0 ${_length} ${_stride} )

  # the above foreach range in inclusive, which is not quite what is wanted
  if( _start VERSION_EQUAL ${_length} )
    break()
  endif()

  # compute the end of the range ensuring that the inclusive range
  # [_start, _end] is all valid indicies
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
  target_link_libraries ( SimpleITKBasicFilters${_library_i} SimpleITKCommon SimpleITKBasicFilters0 ${ITK_LIBRARIES} )
  add_dependencies ( SimpleITKBasicFilters${_library_i} BasicFiltersSourceCode )

  sitk_install_exported_target( SimpleITKBasicFilters${_library_i} )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

  math( EXPR _library_i "${_library_i} + 1 " )

endforeach ()


install( FILES ${CMAKE_CURRENT_BINARY_DIR}/../include/SimpleITKBasicFiltersGeneratedHeaders.h
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development )