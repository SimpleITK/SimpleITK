set_source_files_properties ( ${SimpleITKBasicFiltersGeneratedSource} PROPERTIES GENERATED 1 )


# add_filter_library
# This function is used to apply standard building options for the
# libraries in the basic filters directory given a list of SimpleITK
# source files, and a list of ITK modules.
#
# This method is used to encapsulate the directory properties set when
# using an ITK module
#
function(add_filter_library library_name src_list_var itk_module_list_var)

  add_library ( ${library_name} ${${src_list_var}}  )

  sitk_target_use_itk( ${library_name} PRIVATE ${${itk_module_list_var}}
    ITKLabelMap ITKImageIntensity)

  target_link_libraries ( ${library_name}
    PUBLIC
      SimpleITKCommon
      SimpleITKBasicFilters0 )

  if (SimpleITK_EXPLICIT_INSTANTIATION)
    target_link_libraries ( ${library_name} PRIVATE SimpleITKExplicit )
  endif()

  target_include_directories( ${library_name}
    PUBLIC
      $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
      $<BUILD_INTERFACE:${CMAKE_BINARY_DIR}/Code/BasicFilters/include>
      $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
    PRIVATE
      ${CMAKE_CURRENT_SOURCE_DIR} )
  if(BUILD_SHARED_LIBS)
    # These other filters are split into files. They all use the
    # following for export their interface. There must not be and
    # inter-filter include.
    target_compile_definitions( ${library_name}
      PRIVATE
        SimpleITKBasicFilters_EXPORTS )
  endif()
  target_compile_options( ${library_name}
    PUBLIC
      ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
    PRIVATE
      ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )

  add_dependencies ( ${library_name} BasicFiltersSourceCode )


  sitk_install_exported_target( ${library_name} )

  # append this new library to the globaly cached list
  list ( APPEND SimpleITK_LIBRARIES ${library_name} )
  set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

endfunction()


find_package(ITK COMPONENTS ITKCommon REQUIRED)


# common source which all basic filter libraries need to be linked against
set ( SimpleITKBasicFilters0Source
  sitkImageFilter.cxx
)

add_library ( SimpleITKBasicFilters0 ${SimpleITKBasicFilters0Source} )
sitk_target_use_itk( SimpleITKBasicFilters0 PRIVATE ITKCommon)
target_link_libraries ( SimpleITKBasicFilters0
  PUBLIC
    SimpleITKCommon)
if (SimpleITK_EXPLICIT_INSTANTIATION)
  target_link_libraries ( SimpleITKBasicFilters0 PRIVATE SimpleITKExplicit )
endif()
target_include_directories( SimpleITKBasicFilters0
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/Code/BasicFilters/include>
    $<INSTALL_INTERFACE:${SimpleITK_INSTALL_INCLUDE_DIR}>
  PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR} )
target_compile_options( SimpleITKBasicFilters0
  PUBLIC
    ${SimpleITK_PUBLIC_COMPILE_OPTIONS}
  PRIVATE
    ${SimpleITK_PRIVATE_COMPILE_OPTIONS} )
sitk_install_exported_target( SimpleITKBasicFilters0 )

# append this new library to the globally cached list
list ( APPEND SimpleITK_LIBRARIES SimpleITKBasicFilters0 )
set ( SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES} CACHE INTERNAL "" )

# manually written
list(APPEND SimpleITKBasicFiltersGeneratedSource_ITKCommon
  sitkCastImageFilter-2.cxx
  sitkCastImageFilter-2l.cxx
  sitkCastImageFilter-2v.cxx
  sitkCastImageFilter-3.cxx
  sitkCastImageFilter-3l.cxx
  sitkCastImageFilter-3v.cxx
  sitkCastImageFilter.cxx
  sitkHashImageFilter.cxx )
set(SimpleITKBasicFiltersGeneratedSource_ITKCommon ${SimpleITKBasicFiltersGeneratedSource_ITKCommon} CACHE INTERNAL "")

list(APPEND SimpleITKBasicFiltersGeneratedSource_ITKTransform
  sitkBSplineTransformInitializerFilter.cxx )
set(SimpleITKBasicFiltersGeneratedSource_ITKTransform ${SimpleITKBasicFiltersGeneratedSource_ITKTransform} CACHE INTERNAL "")

list(APPEND SimpleITKBasicFiltersGeneratedSource_ITKRegistrationCommon
  sitkCenteredTransformInitializerFilter.cxx
  sitkCenteredVersorTransformInitializerFilter.cxx
  sitkLandmarkBasedTransformInitializerFilter.cxx )
set(SimpleITKBasicFiltersGeneratedSource_ITKRegistrationCommon ${SimpleITKBasicFiltersGeneratedSource_ITKRegistrationCommon} CACHE INTERNAL "")


#
# Module based libraries
#
get_cmake_property( _varNames VARIABLES )
foreach (_varName ${_varNames})
  if(_varName MATCHES "^SimpleITKBasicFiltersGeneratedSource_")
    string(REGEX MATCH  "ITK[A-Za-z0-9]+$"  itk_module ${_varName})
    list(APPEND module_vars ${itk_module})
  endif()

endforeach()

foreach( itk_module ${module_vars} )

  # cmake >= 3.3
  # if( ${itk_module} IN_LIST ITK_MODULES_ENABLED)
  list (FIND ITK_MODULES_ENABLED ${itk_module} _index)
  list (LENGTH SimpleITKBasicFiltersGeneratedSource_${itk_module} _len)
  if (${_index} GREATER -1 AND ${_len} GREATER 0)
    add_filter_library( SimpleITK_${itk_module}
                        SimpleITKBasicFiltersGeneratedSource_${itk_module}
                        itk_module )

  endif()

  list( REMOVE_ITEM SimpleITKBasicFiltersGeneratedSource ${SimpleITKBasicFiltersGeneratedSource_${itk_module}})

endforeach()

#
#
#

# sort the list to en-sure the same list across platforms
list ( SORT SimpleITKBasicFiltersGeneratedSource )

# add additional files which may depend on Filters0-N
list ( APPEND SimpleITKBasicFiltersSource ${SimpleITKBasicFiltersGeneratedSource} sitkAdditionalProcedures.cxx )

list ( LENGTH SimpleITKBasicFiltersSource _length )
math( EXPR _end_range "${_length} - 1 " )


# Break all these source files into a bunch of libraries base on every
# n files in the list.
set ( _stride 25 )
set ( _library_i 1 )
foreach ( _start RANGE 0 ${_end_range} ${_stride} )

  math( EXPR _library_i "${_library_i} " )

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

  add_filter_library(SimpleITKBasicFilters${_library_i} SRC ITK_MODULES_ENABLED)

  if(_last)

    set(_last_SimpleITK_LIBRARIES ${SimpleITK_LIBRARIES})
    list(REMOVE_ITEM _last_SimpleITK_LIBRARIES SimpleITKBasicFilters${_library_i})
    # the last library include additional cxx files which may depend on
    # other filter libraries
    target_link_libraries ( SimpleITKBasicFilters${_library_i}
      PRIVATE ${_last_SimpleITK_LIBRARIES} )
  endif()


endforeach ()
