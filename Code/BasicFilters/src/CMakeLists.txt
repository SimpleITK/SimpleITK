# Include the hand-written and auto-generated code
include_directories (
 ${CMAKE_CURRENT_SOURCE_DIR}
 )


set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )

# these files are the instantiated ITK filter, but they do not do IO,
# so we don't need to register the IO factoried here.
set ( ITK_NO_IO_FACTORY_REGISTER_MANAGER 1 )
include ( ${ITK_USE_FILE} )

# common source which all basic filter libraries need to be linked against
set ( SimpleITKBasicFilters0Source
  sitkImageFilter.cxx
  sitkMeasurementMap.cxx
)

add_library ( SimpleITKBasicFilters0 ${SimpleITKBasicFilters0Source} )
target_link_libraries ( SimpleITKBasicFilters0 SimpleITKCommon ${ITK_LIBRARIES} )
set_target_properties( SimpleITKBasicFilters0  PROPERTIES SKIP_BUILD_RPATH TRUE )
sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globally cached list
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters0 )
set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )


set ( SimpleITKBasicFiltersSource
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter.cxx
  sitkHashImageFilter.cxx
  sitkLabelStatisticsImageFilter.cxx
  sitkLabelStatisticsImageFilter-2.cxx
  sitkLabelStatisticsImageFilter-3.cxx
  sitkLabelStatisticsImageFilter.cxx
  sitkStatisticsImageFilter.cxx
)
# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersGeneratedSource )

# add additional files which may depend on Filters0
list ( APPEND SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} )
list ( APPEND SimpleITKBasicFiltersSource sitkAdditionalProcedures.cxx )

list ( LENGTH SimpleITKBasicFiltersSource _length )
math( EXPR _end_range "${_length} - 1 " )

# The other filters an automatically split into files. They all
# use the following for export their interface. There must not be and
# inter-filter include.
if(BUILD_SHARED_LIBS)
  add_definitions(-DSimpleITKBasicFilters_EXPORTS)
endif()

# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 25 )
set ( _library_i 0 )
foreach ( _start RANGE 0 ${_end_range} ${_stride} )

  math( EXPR _library_i "${_library_i} + 1 " )

  # compute the end of the range ensuring that the inclusive range
  # [_start, _end] is all valid indexes
  math( EXPR _end "${_start} + ${_stride} - 1" )
  if ( ${_end} VERSION_GREATER ${_end_range} OR
      ${_end} VERSION_EQUAL ${_end_range} )
    math( EXPR _end "${_end_range}" )
    set(_last 1)
  endif()

  # extract out the range into SRC
  set ( SRC "" )
  foreach( _j RANGE ${_start} ${_end} )
    list ( GET SimpleITKBasicFiltersSource ${_j} _v )
    list ( APPEND SRC ${_v} )
  endforeach()

  add_library ( SimpleITKBasicFilters${_library_i} ${SRC} )
  target_link_libraries ( SimpleITKBasicFilters${_library_i} SimpleITKCommon SimpleITKBasicFilters0 ${ITK_LIBRARIES} )
  if(_last)
    # the last library include additional cxx files which may depend on
    # other filter libraries
    target_link_libraries ( SimpleITKBasicFilters${_library_i} ${SimpleITK_LIBRARIES} )
  endif()
  set_target_properties( SimpleITKBasicFilters${_library_i}  PROPERTIES SKIP_BUILD_RPATH TRUE )
  add_dependencies ( SimpleITKBasicFilters${_library_i} BasicFiltersSourceCode )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

  sitk_install_exported_target( SimpleITKBasicFilters${_library_i} )

endforeach ()


install( FILES ${CMAKE_CURRENT_BINARY_DIR}/../include/SimpleITKBasicFiltersGeneratedHeaders.h
  DESTINATION ${SimpleITK_INSTALL_INCLUDE_DIR}
  COMPONENT Development )
